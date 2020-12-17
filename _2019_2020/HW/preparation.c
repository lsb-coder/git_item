#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

/*
int main()
{
   char str[30];
   char *ptr;
   long ret;
   scanf("%s",str);
   ret = strtol(str, &ptr, 16);
   printf("数字（无符号长整数）是 %ld\n", ret);
   //printf("字符串部分是 |%s|", ptr);

   return(0);
}*/

/*
int main ()
{
   char str[50],*s;

   strcpy(str,"This is string.h library function");
   puts(str);
   strcpy(str," is string.h library function");
   puts(str);

   s = str+4;
   puts(s);

   memset(str,'$',7);
   puts(str);
   
   return(0);
}
*/
/*
int main ()
{
   int len;
   const char str1[] = "ABC1DEF4960910";
   const char str2[] = "013";

   len = strcspn(str1, str2);

   printf("第一个匹配的字符是在 %d\n", len + 1);
   
   return(0);
}
*/
/*
#include <string.h>
#include <stdio.h>
 
int main () {
   char str[80] = "This is - www.runoob.com - website";
   const char s[3] = "-";
   char *token;
   
   //获取第一个子字符串 
   token = strtok(str, s);
   
   //继续获取其他的子字符串 
   while( token != NULL ) {
      printf( "%s\n%s\n", token,str );
      token = strtok(NULL, s);
	if ( token != NULL )
		strcat(str,token);
   }
   
   return(0);
}*/

/*
int main ()
{
   int len;
   const char str1[] = "ABCDEFG019874";
   const char str2[] = "ABC";

   len = strspn(str1, str2);

   printf("初始段匹配长度 %d\n", len );
   
   return(0);
}
*/
/*
int main()
{
	void number_off(int *p, int n);
	int num[100],*p=num,n,i;
	printf("总共有多少个人参加：");
	scanf("%d", &n);
	for(i=1;p<num+n;p++){  // 用顺序数来保存位数 ,最后那一位还有数，那么就是它留下来了 
		*p=i++;
	}
	number_off(num, n);
	for(p=num;p<num+n;p++){  
		if(*p){
			printf("最后留下来的是原来的第%d位",*p);
			break;
		}
	}
	return 0;
} 

void number_off(int *p, int n)
{
	int *first=p, count=0, i=0, k=0, rest=n;
	while(rest!=1){  // 当还剩下一位时 
		if(*(first+i)!=0){  // 说明这个数还没退出圈
			k++;  //报数 
			if(k==3){
				count++;  // 退出人数 
				*(first+i) = 0;  // 退出 
				k=0;
			}
		} 
		i++;
		if(i==n){  // 这就形成一个圈了呀！ 
			i=0; 
		}
		rest = n-count; 
	}
} 
*/
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
typedef struct LNode{
    int          data;
    struct LNode *next;
}LNode,*LinkList;
 
LinkList CreateList(int n);
void print(LinkList h);
int main()
{
    LinkList Head=NULL;
    int n;
    
    scanf("%d",&n);
    Head=CreateList(n);
    
    printf("刚刚建立的各个链表元素的值为：\n");
    print(Head);
    
    printf("\n\n");
    system("pause");
    return 0;
}
LinkList CreateList(int n)
{
    LinkList L,p,q;
    int i;
    L=(LNode*)malloc(sizeof(LNode));
    if(!L)return 0;
    L->next=NULL;
    q=L;
    for(i=1;i<=n;i++)
    {
        p=(LinkList)malloc(sizeof(LNode));
        printf("请输入第%d个元素的值:",i);
        scanf("%d",&(p->data));
        p->next=NULL;
        q->next=p;
        q=p;
    }
    return L->next;
}
void print(LinkList h)
{
    LinkList p=h->next;
    while(p!=NULL){
        printf("%d ",p->data);
        p=p->next;
    }
}








































































































































































































































































































































































































































































































/*C 标准库（简略）
1 <assert.h>🤔️
void assert(int expression);
实际上是一个宏，允许诊断信息被写入到标准错误文件中。换句话说，它可用于在 C 程序中添加诊断。

2 <ctype.h>🤔️
int isalnum(int c)
该函数检查所传的字符是否是字母和数字。
int isalpha(int c)
该函数检查所传的字符是否是字母。
int iscntrl(int c)
该函数检查所传的字符是否是控制字符。
int isdigit(int c)
该函数检查所传的字符是否是十进制数字。
int isgraph(int c)
该函数检查所传的字符是否有图形表示法。
int islower(int c)
该函数检查所传的字符是否是小写字母。
int isprint(int c)
该函数检查所传的字符是否是可打印的。
int ispunct(int c)
该函数检查所传的字符是否是标点符号字符。
int isspace(int c)
该函数检查所传的字符是否是空白字符。
int isupper(int c)
该函数检查所传的字符是否是大写字母。
int isxdigit(int c)
该函数检查所传的字符是否是十六进制数字。
int tolower(int c)
该函数把大写字母转换为小写字母。
int toupper(int c)
该函数把小写字母转换为大写字母。

3 <errno.h>
errno为整型提示，strerrno(errno)为字符提示
extern int errno
这是通过系统调用设置的宏，在错误事件中的某些库函数表明了什么发生了错误。
EDOM Domain Error
这个宏表示一个域错误，它在输入参数超出数学函数定义的域时发生，errno 被设置为 EDOM。
ERANGE Range Error
这个宏表示一个范围错误，它在输入参数超出数学函数定义的范围时发生，errno 被设置为 ERANGE。

4 <float.h>
包含了一组与浮点值相关的依赖于平台的常量。

5  <limits.h>
决定了各种变量类型的各种属性。

6 <locale.h>
定义了特定地域的设置，比如日期格式和货币符号。
char *setlocale(int category, const char *locale)
设置或读取地域化信息。
struct lconv *localeconv(void)
设置或读取地域化信息。

7 <math.h>🤔️
double acos(double x)
返回以弧度表示的 x 的反余弦。
double asin(double x)
返回以弧度表示的 x 的反正弦。
double atan(double x)
返回以弧度表示的 x 的反正切。
double atan2(double y, double x)
返回以弧度表示的 y/x 的反正切。y 和 x 的值的符号决定了正确的象限。
double cos(double x)
返回弧度角 x 的余弦。
double cosh(double x)
返回 x 的双曲余弦。
double sin(double x)
返回弧度角 x 的正弦。
double sinh(double x)
返回 x 的双曲正弦。
double tanh(double x)
返回 x 的双曲正切。
double exp(double x)
返回 e 的 x 次幂的值。
double frexp(double x, int *exponent)
把浮点数 x 分解成尾数和指数。返回值是尾数，并将指数存入 exponent 中。所得的值是 x = mantissa * 2 ^ exponent。
double ldexp(double x, int exponent)
返回 x 乘以 2 的 exponent 次幂。
double log(double x)
返回 x 的自然对数（基数为 e 的对数）。
double log10(double x)
返回 x 的常用对数（基数为 10 的对数）。
double modf(double x, double *integer)
返回值为小数部分（小数点后的部分），并设置 integer 为整数部分。
double pow(double x, double y)
返回 x 的 y 次幂。
double sqrt(double x)
返回 x 的平方根。
double ceil(double x)
返回大于或等于 x 的最小的整数值。
double fabs(double x)
返回 x 的绝对值。
double floor(double x)
返回小于或等于 x 的最大的整数值。
double fmod(double x, double y)
返回 x 除以 y 的余数。

8 <setjmp.h>
定义了宏 setjmp()、函数 longjmp() 和变量类型 jmp_buf，该变量类型会绕过正常的函数调用和返回规则。

9 <signal.h>
void (*signal(int sig, void (*func)(int)))(int)
该函数设置一个函数来处理信号，即信号处理程序。
int raise(int sig)
该函数会促使生成信号 sig。sig 参数与 SIG 宏兼容。

a <stdarg.h>
定义了一个变量类型 va_list 和三个宏，这三个宏可用于在参数个数未知（即参数个数可变）时获取函数中的参数。可变参数的函数通在参数列表的末尾是使用省略号(,...)定义的。

b <stddef.h>
定义了各种变量类型和宏。这些定义中的大部分也出现在其它头文件中。

c <stdio.h>🤔️
库宏
NULL
这个宏是一个空指针常量的值。
_IOFBF、_IOLBF 和 _IONBF
这些宏扩展了带有特定值的整型常量表达式，并适用于 setvbuf 函数的第三个参数。
BUFSIZ
这个宏是一个整数，该整数代表了 setbuf 函数使用的缓冲区大小。
EOF
这个宏是一个表示已经到达文件结束的负整数。
FOPEN_MAX
这个宏是一个整数，该整数代表了系统可以同时打开的文件数量。
FILENAME_MAX
这个宏是一个整数，该整数代表了字符数组可以存储的文件名的最大长度。如果实现没有任何限制，则该值应为推荐的最大值。
L_tmpnam
这个宏是一个整数，该整数代表了字符数组可以存储的由 tmpnam 函数创建的临时文件名的最大长度。
SEEK_CUR、SEEK_END 和 SEEK_SET
这些宏是在 fseek 函数中使用，用于在一个文件中定位不同的位置。
TMP_MAX
这个宏是 tmpnam 函数可生成的独特文件名的最大数量。
stderr、stdin 和 stdout
这些宏是指向 FILE 类型的指针，分别对应于标准错误、标准输入和标准输出流。
库函数
int fclose(FILE *stream)
关闭流 stream。刷新所有的缓冲区。
void clearerr(FILE *stream)
清除给定流 stream 的文件结束和错误标识符。
int feof(FILE *stream)
测试给定流 stream 的文件结束标识符。
int ferror(FILE *stream)
测试给定流 stream 的错误标识符。
int fflush(FILE *stream)
刷新流 stream 的输出缓冲区。
int fgetpos(FILE *stream, fpos_t *pos)
获取流 stream 的当前文件位置，并把它写入到 pos。
FILE *fopen(const char *filename, const char *mode)
使用给定的模式 mode 打开 filename 所指向的文件。
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
从给定流 stream 读取数据到 ptr 所指向的数组中。
FILE *freopen(const char *filename, const char *mode, FILE *stream)
把一个新的文件名 filename 与给定的打开的流 stream 关联，同时关闭流中的旧文件。
int fseek(FILE *stream, long int offset, int whence)
设置流 stream 的文件位置为给定的偏移 offset，参数 offset 意味着从给定的 whence 位置查找的字节数。
int fsetpos(FILE *stream, const fpos_t *pos)
设置给定流 stream 的文件位置为给定的位置。参数 pos 是由函数 fgetpos 给定的位置。
long int ftell(FILE *stream)
返回给定流 stream 的当前文件位置。
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
把 ptr 所指向的数组中的数据写入到给定流 stream 中。
int remove(const char *filename)
删除给定的文件名 filename，以便它不再被访问。
int rename(const char *old_filename, const char *new_filename)
把 old_filename 所指向的文件名改为 new_filename。
void rewind(FILE *stream)
设置文件位置为给定流 stream 的文件的开头。
void setbuf(FILE *stream, char *buffer)
定义流 stream 应如何缓冲。
int setvbuf(FILE *stream, char *buffer, int mode, size_t size)
另一个定义流 stream 应如何缓冲的函数。
FILE *tmpfile(void)
以二进制更新模式(wb+)创建临时文件。
char *tmpnam(char *str)
生成并返回一个有效的临时文件名，该文件名之前是不存在的。
int fprintf(FILE *stream, const char *format, ...)
发送格式化输出到流 stream 中。
int printf(const char *format, ...)
发送格式化输出到标准输出 stdout。
int sprintf(char *str, const char *format, ...)🤔️
发送格式化输出到字符串。sprintf(str, "Pi 的值 = %f", M_PI);—>Pi 的值 = 3.141593
int vfprintf(FILE *stream, const char *format, va_list arg)
使用参数列表发送格式化输出到流 stream 中。
int vprintf(const char *format, va_list arg)
使用参数列表发送格式化输出到标准输出 stdout。
int vsprintf(char *str, const char *format, va_list arg)
使用参数列表发送格式化输出到字符串。
int fscanf(FILE *stream, const char *format, ...)
从流 stream 读取格式化输入。
int scanf(const char *format, ...)
从标准输入 stdin 读取格式化输入。
int sscanf(const char *str, const char *format, ...)🤔️
从字符串读取格式化输入。
int fgetc(FILE *stream)🤔️
从指定的流 stream 获取下一个字符（一个无符号字符），并把位置标识符往前移动。
char *fgets(char *str, int n, FILE *stream)🤔️
从指定的流 stream 读取一行，并把它存储在 str 所指向的字符串内。当读取 (n-1) 个字符时，或者读取到换行符时，或者到达文件末尾时，它会停止，具体视情况而定。
int fputc(int char, FILE *stream)🤔️
把参数 char 指定的字符（一个无符号字符）写入到指定的流 stream 中，并把位置标识符往前移动。
int fputs(const char *str, FILE *stream)🤔️
把字符串写入到指定的流 stream 中，但不包括空字符。
int getc(FILE *stream)🤔️
从指定的流 stream 获取下一个字符（一个无符号字符），并把位置标识符往前移动。
int getchar(void)🤔️
从标准输入 stdin 获取一个字符（一个无符号字符）。
char *gets(char *str)🤔️
从标准输入 stdin 读取一行，并把它存储在 str 所指向的字符串中。当读取到换行符时，或者到达文件末尾时，它会停止，具体视情况而定。
int putc(int char, FILE *stream)🤔️
把参数 char 指定的字符（一个无符号字符）写入到指定的流 stream 中，并把位置标识符往前移动。
int putchar(int char)🤔️
把参数 char 指定的字符（一个无符号字符）写入到标准输出 stdout 中。
int puts(const char *str)🤔️
把一个字符串写入到标准输出 stdout，直到空字符，但不包括空字符。换行符会被追加到输出中。
int ungetc(int char, FILE *stream)
把字符 char（一个无符号字符）推入到指定的流 stream 中，以便它是下一个被读取到的字符。
void perror(const char *str)
把一个描述性错误消息输出到标准错误 stderr。首先输出字符串 str，后跟一个冒号，然后是一个空格。
int snprintf(char *str, size_t size, const char *format, ...)🤔️
格式字符串到 str 中。

d <stdlib.h>🤔️
double atof(const char *str)
把参数 str 所指向的字符串转换为一个浮点数（类型为 double 型）。
int atoi(const char *str)
把参数 str 所指向的字符串转换为一个整数（类型为 int 型）。
long int atol(const char *str)
把参数 str 所指向的字符串转换为一个长整数（类型为 long int 型）。
double strtod(const char *str, char **endptr)
把参数 str 所指向的字符串转换为一个浮点数（类型为 double 型）。
long int strtol(const char *str, char **endptr, int base)🤔️
把参数 str 所指向的字符串转换为一个长整数（类型为 long int 型）。
unsigned long int strtoul(const char *str, char **endptr, int base)
把参数 str 所指向的字符串转换为一个无符号长整数（类型为 unsigned long int 型）。
void *calloc(size_t nitems, size_t size)🤔️
分配所需的内存空间，并返回一个指向它的指针。
void free(void *ptr)🤔️
释放之前调用 calloc、malloc 或 realloc 所分配的内存空间。
void *malloc(size_t size)🤔️
分配所需的内存空间，并返回一个指向它的指针。
void *realloc(void *ptr, size_t size)🤔️
尝试重新调整之前调用 malloc 或 calloc 所分配的 ptr 所指向的内存块的大小。
void abort(void)
使一个异常程序终止。
int atexit(void (*func)(void))
当程序正常终止时，调用指定的函数 func。
void exit(int status)
使程序正常终止。
char *getenv(const char *name)
搜索 name 所指向的环境字符串，并返回相关的值给字符串。
int system(const char *string)
由 string 指定的命令传给要被命令处理器执行的主机环境。
void *bsearch(const void *key, const void *base, size_t nitems, size_t size, int (*compar)(const void *, const void *))🤔️
执行二分查找。
void qsort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void*))🤔️
数组排序。
int abs(int x)
返回 x 的绝对值。
div_t div(int numer, int denom)🤔️返回商和余
分子除以分母。
long int labs(long int x)
返回 x 的绝对值。
ldiv_t ldiv(long int numer, long int denom)
分子除以分母。
int rand(void)🤔️
返回一个范围在 0 到 RAND_MAX 之间的伪随机数。
void srand(unsigned int seed)🤔️
该函数播种由函数 rand 使用的随机数发生器。
int mblen(const char *str, size_t n)
返回参数 str 所指向的多字节字符的长度。
size_t mbstowcs(schar_t *pwcs, const char *str, size_t n)
把参数 str 所指向的多字节字符的字符串转换为参数 pwcs 所指向的数组。
int mbtowc(whcar_t *pwc, const char *str, size_t n)
检查参数 str 所指向的多字节字符。
size_t wcstombs(char *str, const wchar_t *pwcs, size_t n)
把数组 pwcs 中存储的编码转换为多字节字符，并把它们存储在字符串 str 中。
int wctomb(char *str, wchar_t wchar)
检查对应于参数 wchar 所给出的多字节字符的编码。

e <string.h>🤔️
void *memchr(const void *str, int c, size_t n)
在参数 str 所指向的字符串的前 n 个字节中搜索第一次出现字符 c（一个无符号字符）的位置。
int memcmp(const void *str1, const void *str2, size_t n)
把 str1 和 str2 的前 n 个字节进行比较。
void *memcpy(void *dest, const void *src, size_t n)
从 src 复制 n 个字符到 dest。
void *memmove(void *dest, const void *src, size_t n)
另一个用于从 src 复制 n 个字符到 dest 的函数。
void *memset(void *str, int c, size_t n)
复制字符 c（一个无符号字符）到参数 str 所指向的字符串的前 n 个字符。
char *strcat(char *dest, const char *src)
把 src 所指向的字符串追加到 dest 所指向的字符串的结尾。
char *strncat(char *dest, const char *src, size_t n)
把 src 所指向的字符串追加到 dest 所指向的字符串的结尾，直到 n 字符长度为止。
char *strchr(const char *str, int c)
在参数 str 所指向的字符串中搜索第一次出现字符 c（一个无符号字符）的位置。
int strcmp(const char *str1, const char *str2)
把 str1 所指向的字符串和 str2 所指向的字符串进行比较。
int strncmp(const char *str1, const char *str2, size_t n)
把 str1 和 str2 进行比较，最多比较前 n 个字节。
int strcoll(const char *str1, const char *str2)
把 str1 和 str2 进行比较，结果取决于 LC_COLLATE 的位置设置。
char *strcpy(char *dest, const char *src)
把 src 所指向的字符串复制到 dest。
char *strncpy(char *dest, const char *src, size_t n)
把 src 所指向的字符串复制到 dest，最多复制 n 个字符。
size_t strcspn(const char *str1, const char *str2)
检索字符串 str1 开头连续有几个字符都不含字符串 str2 中的字符。
char *strerror(int errnum)
从内部数组中搜索错误号 errnum，并返回一个指向错误消息字符串的指针。
size_t strlen(const char *str)
计算字符串 str 的长度，直到空结束字符，但不包括空结束字符。
char *strpbrk(const char *str1, const char *str2)
检索字符串 str1 中第一个匹配字符串 str2 中字符的字符，不包含空结束字符。也就是说，依次检验字符串 str1 中的字符，当被检验字符在字符串 str2 中也包含时，则停止检验，并返回该字符位置。
char *strrchr(const char *str, int c)
在参数 str 所指向的字符串中搜索最后一次出现字符 c（一个无符号字符）的位置。
size_t strspn(const char *str1, const char *str2)
检索字符串 str1 中第一个不在字符串 str2 中出现的字符下标。
char *strstr(const char *haystack, const char *needle)
在字符串 haystack 中查找第一次出现字符串 needle（不包含空结束字符）的位置。
char *strtok(char *str, const char *delim)🤔️
分解字符串 str 为一组字符串，delim 为分隔符。
size_t strxfrm(char *dest, const char *src, size_t n)
根据程序当前的区域选项中的 LC_COLLATE 来转换字符串 src 的前 n 个字符，并把它们放置在字符串 dest 中。

f <time.h>
char *asctime(const struct tm *timeptr)
返回一个指向字符串的指针，它代表了结构 timeptr 的日期和时间。
clock_t clock(void)
返回程序执行起（一般为程序的开头），处理器时钟所使用的时间。
char *ctime(const time_t *timer)
返回一个表示当地时间的字符串，当地时间是基于参数 timer。
double difftime(time_t time1, time_t time2)
返回 time1 和 time2 之间相差的秒数 (time1-time2)。
struct tm *gmtime(const time_t *timer)
timer 的值被分解为 tm 结构，并用协调世界时（UTC）也被称为格林尼治标准时间（GMT）表示。
struct tm *localtime(const time_t *timer)
timer 的值被分解为 tm 结构，并用本地时区表示。
time_t mktime(struct tm *timeptr)
把 timeptr 所指向的结构转换为一个依据本地时区的 time_t 值。
size_t strftime(char *str, size_t maxsize, const char *format, const struct tm *timeptr)
根据 format 中定义的格式化规则，格式化结构 timeptr 表示的时间，并把它存储在 str 中。
time_t time(time_t *timer)
计算当前日历时间，并把它编码成 time_t 格式。
*/
