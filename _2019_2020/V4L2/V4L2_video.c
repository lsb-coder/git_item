/******头文件******/
#include <fcntl.h>
//#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <linux/videodev2.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <errno.h>
//#include <sys/time.h>
//#include <string.h>
//#include <stdint.h>

/******宏定义与结构体定义******/
#define  TRUE    1
#define  FALSE    0

#define FILE_VIDEO     "/dev/video0"          //摄像头设备
#define BMP          "./image_bmp.bmp"     //BMP格式图片存储
#define YUV            "./image_yuv.yuv"   //YUV格式图片存储

#define  IMAGEWIDTH    1280                    //图像大小
#define  IMAGEHEIGHT   720

//V4L2相关结构体定义，都可以在/usr/include/linux/videodev2.h找到
static   int      fd;
static   struct   v4l2_capability   cap;
struct v4l2_fmtdesc fmtdesc;
struct v4l2_format fmt,fmtack;
struct v4l2_streamparm setfps;  
struct v4l2_requestbuffers req;
struct v4l2_buffer buf;
enum v4l2_buf_type type;
unsigned char frame_buffer[IMAGEWIDTH*IMAGEHEIGHT*3];


/*******摄像头配置与图像采集******/
//初始化V4L2
int init_v4l2(void)
{
    int i;
    int ret = 0;
    
    //判断V4L接口是否打开
    if ((fd = open(FILE_VIDEO, O_RDWR)) == -1) 
    {
        printf("Error opening V4L interface\n");
        return (FALSE);
    }

    //判断摄像头是否打开
    if (ioctl(fd, VIDIOC_QUERYCAP, &cap) == -1) 
    {
        printf("Error opening device %s: unable to query device.\n",FILE_VIDEO);
        return (FALSE);
    }
    else
    {
         printf("driver:\t\t%s\n",cap.driver);
         printf("card:\t\t%s\n",cap.card);
         printf("bus_info:\t%s\n",cap.bus_info);
         printf("version:\t%d\n",cap.version);
         printf("capabilities:\t%x\n",cap.capabilities);
         
         //检查是否是为视频采集设备
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
    fmt.fmt.pix.height = IMAGEHEIGHT;
    fmt.fmt.pix.width = IMAGEWIDTH;
    fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;
    
    if(ioctl(fd, VIDIOC_S_FMT, &fmt) == -1)
    {
        printf("Unable to set format\n");
        return FALSE;
    }     
    if(ioctl(fd, VIDIOC_G_FMT, &fmt) == -1)
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
    setfps.parm.capture.timeperframe.numerator = 10;
    setfps.parm.capture.timeperframe.denominator = 10;
    
    printf("init %s \t[OK]\n",FILE_VIDEO);
        
    return TRUE;
}

//定义结构体，存储mmap后的地址信息
struct buffer
    {
        void * start;  /*mmap函数定义时返回的地址是个void *，因而这里面的start也是
个 void *。实际地址在运行的时候会自动分配*/
        unsigned int length;
    } * buffers;

//图像采集
int v4l2_grab(void)
{
    unsigned int n_buffers;
    
    //申请缓存区
    req.count=4;  //缓存数量为4
    req.type=V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory=V4L2_MEMORY_MMAP;
    if(ioctl(fd,VIDIOC_REQBUFS,&req)==-1)
    {
        printf("request for buffers error\n");
    }

    //获取每个缓存的信息，并mmap到用户空间
    
    /*malloc动态内存分配，申请一块连续的指定大小的内存块区域以void*类型返回分配的内
存区域地址*/
    buffers = (struct buffer *)malloc(req.count*sizeof (*buffers));//(struct buffer *)强制转换，c中不需要，此处是为了方便可能移植到c++
    if (!buffers) 
    {
        printf ("Out of memory\n");
        return(FALSE);
    }
    
    for (n_buffers = 0; n_buffers < req.count; n_buffers++) 
    {
        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;
        buf.index = n_buffers;
        //查询缓存
        if (ioctl (fd, VIDIOC_QUERYBUF, &buf) == -1)
        {
            printf("query buffer error\n");
            return(FALSE);
        }

        buffers[n_buffers].length = buf.length;
        //mmap
        buffers[n_buffers].start = mmap(NULL,buf.length,PROT_READ |PROT_WRITE, MAP_SHARED, fd, buf.m.offset);
        if (buffers[n_buffers].start == MAP_FAILED)
        {
            printf("buffer map error\n");
            return(FALSE);
        }
    }
        
    //排列
    for (n_buffers = 0; n_buffers < req.count; n_buffers++)
    {
        buf.index = n_buffers;
        ioctl(fd, VIDIOC_QBUF, &buf);
    } 
    
    //采集视频
    type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    ioctl (fd, VIDIOC_STREAMON, &type);
    
    //取出缓存中已经采样的缓存
    ioctl(fd, VIDIOC_DQBUF, &buf);

    printf("grab yuyv OK\n");
    return(TRUE);
}


/******YUYV转RGB888******/
/*摄像头采集的数据格式为YUYV，为了方便后续设计，需要转变为RGB888，并将转换完成的数据存储到frame_buffer*/
int yuyv_2_rgb888(void)
{
    int i,j;
    unsigned char y1,y2,u,v;
    int r1,g1,b1,r2,g2,b2;
    int height,width;

    //定义的时候buffers[index].start是个void *，没办法进行+1这样的操作，需强制转换
    char * pointer;
    pointer = buffers[0].start;
    
    height = IMAGEHEIGHT;
    width = IMAGEWIDTH/2;

    for(i=0;i<height;i++)
    {
        for(j=0;j<width;j++)
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
            
            /*后续RGB的数据要存储到BMP中，而BMP文件中颜色数据是“倒序”，即从下到
上，从左到右，故向frame_buffer写数据时是从最后一行最左测开始写，每写满一行行数减一*/
            *(frame_buffer + ((height-1-i)*width+j)*6    ) = (unsigned char)b1;
            *(frame_buffer + ((height-1-i)*width+j)*6 + 1) = (unsigned char)g1;
            *(frame_buffer + ((height-1-i)*width+j)*6 + 2) = (unsigned char)r1;
            *(frame_buffer + ((height-1-i)*width+j)*6 + 3) = (unsigned char)b2;
            *(frame_buffer + ((height-1-i)*width+j)*6 + 4) = (unsigned char)g2;
            *(frame_buffer + ((height-1-i)*width+j)*6 + 5) = (unsigned char)r2;
        }
    }
    printf("change to RGB OK \n");
}


/******停止采集和关闭设备******/
int close_v4l2(void)
{
    ioctl(fd, VIDIOC_STREAMOFF, &type);     
    if(fd != -1) 
     {
         close(fd);
         return (TRUE);
     }
     else 
     return (FALSE);
}

#pragma pack(2)                     //修改结构体字节对齐规则
//定义BMP头结构体
typedef struct tagBITMAPFILEHEADER //文件头  
{  
    unsigned short bfType;      //标识该文件为bmp文件,判断文件是否为bmp文件，即用该值与"0x4d42"比较是否相等即可，0x4d42 = 19778  
    unsigned long  bfSize;      //文件大小  
    unsigned long bfReserved; //预保留位 
    //unsigned short bfReserved1; //预保留位 
    //unsigned short bfReserved2; //预保留位  
    unsigned long  bfOffBits;   //图像数据区的起始位置  
}BITMAPFILEHEADER;//14字节  
typedef struct tagBITMAPINFOHEADER //信息头  
{  
    unsigned long  biSize;  //图像数据块大小  
    long     biWidth;   //宽度  
    long     biHeight;  //高度  
    unsigned short biPlanes;//为1  
    unsigned short biBitCount; //像素位数，8-灰度图；24-真彩色  
    unsigned long biCompression;//压缩方式  
    unsigned long biSizeImage;  //图像区数据大小  
    long     biXPelsPerMeter;  //水平分辨率，像素每米  
    long     biYPelsPerMeter;  
    unsigned long biClrUsed;   //位图实际用到的颜色数  
    unsigned short biClrImportant;//位图显示过程，重要的颜色数；0--所有都重要  
}BITMAPINFOHEADER;//40字节 
#pragma pack()                     


/******主函数******/
int main(void)
{

    FILE *fp1,*fp2;

    BITMAPFILEHEADER   bf;
    BITMAPINFOHEADER   bi;
   
    //新建一个二进制文件BMP
    fp1 = fopen(BMP, "wb");
    if(!fp1)
    {
        printf("open "BMP"error\n");
        return(FALSE);
    }
    
    //新建一个二进制文件YUV
    fp2 = fopen(YUV, "wb");
    if(!fp2)
    {
        printf("open "YUV"error\n");
        return(FALSE);
    }

    if(init_v4l2() == FALSE) 
    {
         return(FALSE);
    }
    
    //Set BITMAPINFOHEADER
    bi.biSize = 40;
    bi.biWidth = IMAGEWIDTH;
    bi.biHeight = IMAGEHEIGHT;
    bi.biPlanes = 1;
    bi.biBitCount = 24;
    bi.biCompression = 0;
    bi.biSizeImage = IMAGEWIDTH*IMAGEHEIGHT*3;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;
 

    //Set BITMAPFILEHEADER
    bf.bfType = 0x4d42;
    bf.bfSize = 54 + bi.biSizeImage;     
    bf.bfReserved = 0;
    bf.bfOffBits = 54;
    
    v4l2_grab();
    fwrite(buffers[0].start, 640*480*2, 1, fp2);
    printf("save "YUV"OK\n");
    
    yuyv_2_rgb888();
    //fwrite(&bf, 14, 1, fp1);
    //fwrite(&bi, 40, 1, fp1); 
    fwrite(&bf.bfType, 2, 1, fp1);
    fwrite(&bf.bfSize, 4, 1, fp1);
    fwrite(&bf.bfReserved, 4, 1, fp1);
    fwrite(&bf.bfOffBits, 4, 1, fp1);

    fwrite(&bi.biSize, 4, 1, fp1);
    fwrite(&bi.biWidth, 4, 1, fp1);
    fwrite(&bi.biHeight, 4, 1, fp1);
    fwrite(&bi.biPlanes, 2, 1, fp1);
    fwrite(&bi.biBitCount, 2, 1, fp1);
    fwrite(&bi.biCompression, 4, 1, fp1);
    fwrite(&bi.biSizeImage, 4, 1, fp1);
    fwrite(&bi.biXPelsPerMeter, 4, 1, fp1);
    fwrite(&bi.biYPelsPerMeter, 4, 1, fp1);
    fwrite(&bi.biClrUsed, 4, 1, fp1);
    fwrite(&bi.biClrImportant, 4, 1, fp1);   
    fwrite(frame_buffer, bi.biSizeImage, 1, fp1);
    printf("save "BMP"OK\n");
    
    
    fclose(fp1);
    fclose(fp2);
    close_v4l2();
    
    return(TRUE);
}
