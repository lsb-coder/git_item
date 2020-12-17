/*涉及：
 *1、linux下编写c语言，文件头的添加
 *2、缓存的使用
 *3、YUYV转RGB、BMP图片的文件头重定义及设置
 *4、摄像头驱动API——V4L2
 *：打开（open） -> 查询、设置、采集（ioctl()） -> 关闭（close）
 *（1）结构体及命令等定义在/usr/include/linux/videodev2.h
 *（2）打开：有阻塞和非阻塞两种方式,open			O_RDWR或O_NONBLOCK
 *（3）查询、设置、采集：利用ioctl()
 *a.查询设备支持的图像/视频格式				VIDIOC_ENUM_FMT
 *b.查询设备的能力					VIDIOC_QUERYCAP
 *c.查询图像捕获/视频采集格式				VIDIOC_S_FMT
 *d.申请内核空间的缓冲区					VIDIOC_REQBUFS
 *e.查询内核空缓冲区信息并映射到用户空间，mmap		VIDIOC_QUERYBUF
 *f.投放一个空的缓冲区到输入队列				VIDIOC_QBUF
 *g.启动采集						VIDIOC_STREAMON
 *h.采集完成后，从缓冲输出队列获取一个有数据的缓冲区	VIDIOC_DQBUF
 *i.读取数据并保存成图片文件
 *（4）关闭：
 *a.关闭流						VIDIOC_STREAMOFF
 *关闭内存映射，munmap
 *释放申请的内存，free
 *关闭设备,close
 */


/******头文件******/
/*常用头文件*/
#include <fcntl.h>	//unix标准中通用的头文件,包含open等函数及大量宏
#include <sys/types.h>	//基本系统数据类型，以访问_LP64、_ILP32等定义
//#include <sys/stat.h>	//轻松获取文件属性的头文件
#include <stdlib.h>	//standard library标准库头文件，包含malloc等函数及一些宏
#include <stdio.h>	//standard input & output标准输入输出文件
#include <unistd.h>	//对POSIX操作系统（含linux等）API的访问功能的头文件
#include <errno.h>	//C标准函式库里的标头档，定义了通过错误码来回报错误资讯的宏
//#include <sys/time.h>	//Linux系统的日期头文件，若代码与平台无关，则include time.h
#include <string.h>	//C语言标准库中一个常用的头文件，在使用到字符数组时需要使用
//#include <stdint.h>	//c99中引进的一个标准C库的文件,定义了几种扩展的整数类型和宏

/*此例必要头文件*/
#include <linux/videodev2.h>	//V4L2驱动必须包含的头文件
#include <sys/ioctl.h>	//包含ioctl()函数（很多与I/O操作相关的事情都要依靠它来完成）
#include <sys/mman.h>	//内存管理声明头文件


/******宏定义******/
#define  TRUE	1
#define  FALSE    0

#define  FILE_VIDEO     "/dev/video0"		//摄像头设备路径
#define  PHOTO_BMP          "./photo/photo30.bmp"	//BMP格式图片存储路径

#define  PHOTO_WIDTH    640 			//图片分辨率宽×高
#define  PHOTO_HEIGHT   480
#define  BUFEER_COUNT   4			//缓存帧数
#define  IMAGE_COUNT	300			//30张

/******结构体定义******/
/*定义结构体buffer，存储mmap后的地址信息*/
struct buffer
{
	void *start;  /*mmap函数定义时返回的地址是个void *，故start也是
个void *。实际地址在运行的时候会自动分配*/
	unsigned int length;
    } *buffers;

/*定义BMP头结构体*/
typedef unsigned short  WORD;		//定义BMP文件头的数据类型
typedef unsigned int  DWORD;		
typedef struct tagBITMAPFILEHEADER	//文件头  
{  
	WORD   bfType;      		//BMP文件头，必须为BM (值为0x4d42 = 19778)
	DWORD  bfSize;      		//文件大小，字节为单位 
	DWORD  bfReserved; 			//预保留字  
	DWORD  bfOffBits;   		//位图数据的起始位置  
}BITMAPFILEHEADER;			//14字节  
typedef struct tagBITMAPINFOHEADER 	//信息头  
{  
	DWORD  biSize;  			//图像数据块字节数  
	DWORD  biWidth;   			//图像宽度，像素为单位  
	DWORD  biHeight;  			//高度，同上  
	WORD   biPlanes;			//目标设备级别，此处必须为1为1  
	WORD   biBitCount; 			//像素位数，8-灰度图；24-真彩色  
	DWORD  biCompression;		//压缩方式  
	DWORD  biSizeImage;  		//图像区数据大小  
	DWORD  biXPelsPerMeter;  		//水平分辨率  
	DWORD  biYPelsPerMeter;		//竖直分辨率
	DWORD  biClrUsed;   		//位图实际用到的颜色数  
	DWORD  biClrImportant;		//位图显示过程中重要的颜色数；0--都重要  
}BITMAPINFOHEADER;			//40字节

/*V4L2相关结构体定义，都可以在/usr/include/linux/videodev2.h找到*/
struct v4l2_capability   cap;	//描述设备能力
struct v4l2_fmtdesc fmtdesc;	//描述设备支持的像素格式
struct v4l2_format fmt;		//设置流数据格式
struct v4l2_streamparm setfps;  	//设置帧数
struct v4l2_requestbuffers req;	//申请缓存
struct v4l2_buffer buf;		//描述视频缓冲区信息


/******其他重要定义******/
int fd;	//定义摄像头的句柄
enum v4l2_buf_type type; //定义枚举变量type，枚举类型v4l2_buf_type定义在videodev2.h
unsigned char frame_buffer[PHOTO_WIDTH*PHOTO_HEIGHT*3];/*定义一个frame_buffer，用来缓存RGB颜色数据*/
static BITMAPFILEHEADER   bf;	//定义bmp文件头
static BITMAPINFOHEADER   bi;	//定义bmp信息头
unsigned int n_buffers;


/*******摄像头配置与图像采集相关函数******/
/*初始化V4L2*/
int init_v4l2(void)
{
	/*打开摄像头设备，O_RDWR：阻塞式，O_NONBLOCK：非阻塞式——即使摄像头尚未捕获到信息，驱动依旧会把缓存里的东西返回给应用程序*/
	if ((fd = open(FILE_VIDEO, O_RDWR)) == -1) 
	{
		printf("Error opening V4L interface\n");
		return FALSE;
	}

	//查询设备属性，命令：VIDIOC_QUERYCAP，包括后面的表示皆可在videodev2.h找到
	if (ioctl(fd, VIDIOC_QUERYCAP, &cap) == -1) 
	{
		printf("Error opening device %s: unable to query device.\n",FILE_VIDEO);
		return FALSE;
	}
	else
	{
		printf("driver:\t\t%s\n",cap.driver);
		printf("card:\t\t%s\n",cap.card);
		printf("bus_info:\t%s\n",cap.bus_info);
		printf("version:\t%d\n",cap.version);
		printf("capabilities:\t%x\n",cap.capabilities);

         	/*检查是否是为视频采集设备，宏V4L2_CAP_VIDEO_CAPTURE，在包括后面的表
示皆可在videodev2.h找到*/
         	if ((cap.capabilities & V4L2_CAP_VIDEO_CAPTURE) == V4L2_CAP_VIDEO_CAPTURE) 
         	{
            		printf("Device %s: supports capture.\n",FILE_VIDEO);
        	}

		//检查是否支持流IO操作
		if ((cap.capabilities & V4L2_CAP_STREAMING) == V4L2_CAP_STREAMING) 
		{
			printf("Device %s: supports streaming.\n",FILE_VIDEO);
		}
	} 

	//列举摄像头所支持像素格式
	fmtdesc.index=0;
	fmtdesc.type=V4L2_BUF_TYPE_VIDEO_CAPTURE;	
	printf("Support format:\n");
	while(ioctl(fd,VIDIOC_ENUM_FMT,&fmtdesc)!=-1)
	{
		printf("\t%d.%s\n",fmtdesc.index+1,fmtdesc.description);
		fmtdesc.index++;
	}

	//设置像素格式
	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
	fmt.fmt.pix.height = PHOTO_HEIGHT;
	fmt.fmt.pix.width = PHOTO_WIDTH;
	fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;

	if(ioctl(fd, VIDIOC_S_FMT, &fmt) == -1)	//设置
	{
		printf("Unable to set format\n");
		return FALSE;
	}     
	if(ioctl(fd, VIDIOC_G_FMT, &fmt) == -1)	//将摄像头设置读取回来
	{
		printf("Unable to get format\n");
		return FALSE;
	} 
	{
		printf("fmt.type:\t\t%d\n",fmt.type);
		printf("pix.pixelformat:\t%c%c%c%c\n",fmt.fmt.pix.pixelformat & 0xFF, (fmt.fmt.pix.pixelformat >> 8) & 0xFF,(fmt.fmt.pix.pixelformat >> 16) & 0xFF, (fmt.fmt.pix.pixelformat >> 24) & 0xFF);  //将每个字节内容取出来转换出目标数据
		printf("pix.height:\t\t%d\n",fmt.fmt.pix.height);
		printf("pix.width:\t\t%d\n",fmt.fmt.pix.width);
		printf("pix.field:\t\t%d\n",fmt.fmt.pix.field);
	}
	//设置每秒传输帧数“denominator/numerator”
	setfps.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	setfps.parm.capture.timeperframe.numerator = 1;
	setfps.parm.capture.timeperframe.denominator = 30;

	if(ioctl(fd, VIDIOC_S_PARM, &setfps) == -1)	//设置
	{
		printf("Unable to set frame rate\n");
		return FALSE;
	}
	if(ioctl(fd, VIDIOC_G_PARM, &setfps) == -1)	//读取设置
	{
		printf("Unable to get frame rate\n");
		return FALSE;       
	}

	printf("init %s \t[OK]\n",FILE_VIDEO);

	return TRUE;
}


/*图像捕获*/
int v4l2_mmap(void)
{
	//unsigned int n_buffers;

	//申请缓存区
	req.count = BUFEER_COUNT;  //缓存数量为4
	req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	req.memory = V4L2_MEMORY_MMAP;
	if(ioctl(fd,VIDIOC_REQBUFS,&req) == -1)
	{
		printf("request for buffers error\n");
	}

	//获取每个缓存的信息，并mmap到用户空间
	/*malloc动态内存分配，申请一块连续的指定大小的内存块区域以void*类型返回分配的内存区域地址*/
	buffers = malloc(req.count*sizeof (*buffers));/*若c++,须在malloc前添加(struct buffer *)强制转换，c中不需要*/
	if (!buffers) 
	{
		printf ("Out of memory\n");
		return FALSE;
	}
	//进入内存映射
	for (n_buffers = 0; n_buffers < req.count; n_buffers++) 
	{
		buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory = V4L2_MEMORY_MMAP;
		buf.index = n_buffers;
		//查询缓存
		if (ioctl (fd, VIDIOC_QUERYBUF, &buf) == -1)
		{
			printf("query buffer error\n");
			return FALSE;
		}

		buffers[n_buffers].length = buf.length;
		//映射
		buffers[n_buffers].start = mmap(NULL,buf.length,PROT_READ |PROT_WRITE, MAP_SHARED, fd, buf.m.offset);
		if (buffers[n_buffers].start == MAP_FAILED)
		{
		printf("buffer map error\n");
		return FALSE;
		}
	}
}

int v4l2_get_frame()
{   
	//入队
	for (n_buffers = 0; n_buffers < req.count; n_buffers++)
	{
		buf.index = n_buffers;
		ioctl(fd, VIDIOC_QBUF, &buf);
	} 

	//采集
	type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	ioctl (fd, VIDIOC_STREAMON, &type);

	//取出缓存区中已经采样的缓存
	ioctl(fd, VIDIOC_DQBUF, &buf);

	printf("capture yuyv OK\n");
	return TRUE;
}


/******YUYV转RGB888******/
/*摄像头采集的数据格式为YUYV，为了方便后续设计，需要转变为RGB888，并将转换完成的数据存储到frame_buffer*/
int yuyv_2_rgb888(void)
{
	int i,j;
	unsigned char y1,y2,u,v;
	int r1,g1,b1,r2,g2,b2;
	int height,width;
	height = PHOTO_HEIGHT;
	width = PHOTO_WIDTH/2;

	//定义时buffers[index].start是个void *，没办法进行+1这样的操作，需强制转换
	char *pointer;
	pointer = buffers[0].start;

	for(i = 0;i < height;i++)
	{
		for(j = 0;j < width;j++)
		{
			y1 = *( pointer + (i*width+j)*4);
			u  = *( pointer + (i*width+j)*4 + 1);
			y2 = *( pointer + (i*width+j)*4 + 2);
			v  = *( pointer + (i*width+j)*4 + 3);

			r1 = y1 + 1.042*(v-128);
			g1 = y1 - 0.34414*(u-128) - 0.71414*(v-128);
			b1 = y1 + 1.772*(u-128);

			r2 = y2 + 1.042*(v-128);
			g2 = y2 - 0.34414*(u-128) - 0.71414*(v-128);
			b2 = y2 + 1.772*(u-128);

			if(r1>255)
			r1 = 255;
			else if(r1<0)
			r1 = 0;

			if(b1>255)
			b1 = 255;
			else if(b1<0)
			b1 = 0;    

			if(g1>255)
			g1 = 255;
			else if(g1<0)
			g1 = 0;    

			if(r2>255)
			r2 = 255;
			else if(r2<0)
			r2 = 0;

			if(b2>255)
			b2 = 255;
			else if(b2<0)
			b2 = 0;    

			if(g2>255)
			g2 = 255;
			else if(g2<0)
			g2 = 0;        

			/*后续RGB的数据要存储到BMP中，而BMP文件中颜色数据是“倒序”，即从下到上，从左到右，故向frame_buffer写数据时是从最后一行最左测开始写，每写满一行行数减一*/
			*(frame_buffer + ((height-1-i)*width+j)*6    ) = (unsigned char)b1;
			*(frame_buffer + ((height-1-i)*width+j)*6 + 1) = (unsigned char)g1;
			*(frame_buffer + ((height-1-i)*width+j)*6 + 2) = (unsigned char)r1;
			*(frame_buffer + ((height-1-i)*width+j)*6 + 3) = (unsigned char)b2;
			*(frame_buffer + ((height-1-i)*width+j)*6 + 4) = (unsigned char)g2;
			*(frame_buffer + ((height-1-i)*width+j)*6 + 5) = (unsigned char)r2;
		}
	}
	printf("change to RGB OK \n");
	return TRUE;
}


/******停止采集和关闭设备******/
int v4l2_release(void)
{
	unsigned int n_buffers;

	//关闭流
	type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	ioctl(fd, VIDIOC_STREAMOFF, &type);     

	//关闭内存映射
	for(n_buffers = 0;n_buffers < req.count;n_buffers++)
	{
		munmap(buffers[n_buffers].start,buffers[n_buffers].length);
	}

	//释放自己申请的内存
	free(buffers);

	//关闭设备	
	if(fd != -1) 
	{
		close(fd);
		return TRUE;
	}
	else 
	return FALSE;
}


/******设定BMP头******/
int set_bmp_header(void)
{
	//Set BITMAPINFOHEADER
	bi.biSize = 40;
	bi.biWidth = PHOTO_WIDTH;
	bi.biHeight = PHOTO_HEIGHT;
	bi.biPlanes = 1;
	bi.biBitCount = 24;
	bi.biCompression = 0;
	bi.biSizeImage = PHOTO_WIDTH*PHOTO_HEIGHT*3;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	//Set BITMAPFILEHEADER
	bf.bfType = 0x4d42;
	bf.bfSize = 54 + bi.biSizeImage;     
	bf.bfReserved = 0;
	bf.bfOffBits = 54;

	return TRUE;
}


int fwrite_bmp(FILE *fp)
{
	fwrite(&bf.bfType, 2, 1, fp);
	fwrite(&bf.bfSize, 4, 1, fp);
	fwrite(&bf.bfReserved, 4, 1, fp);
	fwrite(&bf.bfOffBits, 4, 1, fp);

	fwrite(&bi.biSize, 4, 1, fp);
	fwrite(&bi.biWidth, 4, 1, fp);
	fwrite(&bi.biHeight, 4, 1, fp);
	fwrite(&bi.biPlanes, 2, 1, fp);
	fwrite(&bi.biBitCount, 2, 1, fp);
	fwrite(&bi.biCompression, 4, 1, fp);
	fwrite(&bi.biSizeImage, 4, 1, fp);
	fwrite(&bi.biXPelsPerMeter, 4, 1, fp);
	fwrite(&bi.biYPelsPerMeter, 4, 1, fp);
	fwrite(&bi.biClrUsed, 4, 1, fp);
	fwrite(&bi.biClrImportant, 4, 1, fp);   

	return TRUE;
}


/******主函数******/
int main(void)
{
	FILE *fp1;

	fp1 = fopen(PHOTO_BMP, "wb");
	if(!fp1)
	{
		printf("open "PHOTO_BMP" error\n");
		return  FALSE;
	}

	if(init_v4l2() == FALSE) 
	{
		return FALSE;
	}

	set_bmp_header();
	v4l2_mmap();

	//v4l2_frame();

	//yuyv_2_rgb888();

	//fwrite_bmp(fp1);

	//fwrite(frame_buffer, bi.biSizeImage, 1, fp1);
	//printf("save "PHOTO_BMP" OK\n");

	char file_name[100];
	char index_str[10];
	int image_count;
	

	for (image_count = 0;image_count < IMAGE_COUNT;image_count++)
	{
		/*FILE *fp1;

		//新建一个二进制文件BMP
		sprintf(index_str,"%d",image_count);
		strcpy(file_name,PHOTO_BMP);
		strcat(file_name,index_str);
		strcat(file_name,".bmp");
		fp1 = fopen(file_name, "wb");
		if(!fp1)
		{
			printf("open %s error\n",file_name);
			return  FALSE;
		}*/
		v4l2_get_frame();
    
		yuyv_2_rgb888();
		fwrite_bmp(fp1);
 
		fwrite(frame_buffer, bi.biSizeImage, 1, fp1);
		//fwrite(buffers[0].start, PHOTO_WIDTH*PHOTO_HEIGHT*2, 1, fp1);
		printf("save "PHOTO_BMP" OK\n");
    
		//fclose(fp1);
	}
	fclose(fp1);
	v4l2_release();

	return(TRUE);
}
