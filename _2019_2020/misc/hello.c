#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>

int main()
{
	/*int a,*p;
	a = 10;
	p = &a;
	printf("%d\n",a);
	//printf("%d\n",p);
	printf("%d\n",*p);*/
	char a[10] = "0123456789";
	printf("%ld\n",sizeof(a[10]));
	printf("%ld\n",sizeof(a));
	printf("%ld\n",sizeof("0123456789"));
	int b[10] = {1,2,3,4,5,6,7,8,9,0};
	printf("%ld\n",sizeof(b[10]));
	printf("%ld\n",sizeof(b));
	return 0;
}
