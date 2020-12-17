#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct ErrordLog {
	int line;
	int num;
	int pos; //增加初始位置，排序等量记录
	char f_name[20];
} EL;

int main()
{
	EL errordlogs[1000];
	int n =0;
	char path[100];
	char f_name[20],*p;
	int line;

	while (scanf("%s %d",path,&line) != EOF) {
		strcpy(f_name,(p=strrchr(path,'\\')) ? p+1 : path);
		int exist =0;
		for (int i = 0;i < n;i++) {
			if ( !strcmp(f_name,errordlogs[i].f_name) && line == (errordlogs[i].line)) {
				errordlogs[i].num = (errordlogs[i].num) + 1;
				exist = 1;
				break;
			}
		}
		if (exist == 0) {
			if (n == 0) {
				strcpy(errordlogs[0].f_name, f_name);
				errordlogs[0].line = line;
				errordlogs[0].num = 1;
				errordlogs[0].pos = 0;
				n = 1;
			}
			else {
				n++;
				strcpy(errordlogs[n-1].f_name, f_name);
				errordlogs[n-1].line = line;
				errordlogs[n-1].num = 1;
				errordlogs[n-1].pos = n-1;
			}
		}

	}

	for (int i = 0;i < n;i++) {
		for (int j = i + 1;j < n;j++) {
			if (errordlogs[i].num < errordlogs[j].num || errordlogs[i].pos > errordlogs[j].pos) {
				char fn_temp[20];
				strcpy(fn_temp,errordlogs[i].f_name);
				int l_temp = errordlogs[i].line;
				int n_temp = errordlogs[i].num;
				int p_temp = errordlogs[i].pos;//注意位置也要一起交换

				strcpy(errordlogs[i].f_name,errordlogs[j].f_name);
				errordlogs[i].line = errordlogs[j].line;
				errordlogs[i].num = errordlogs[j].num;
				errordlogs[i].pos = errordlogs[j].pos;

				strcpy(errordlogs[j].f_name,fn_temp);
				errordlogs[j].line = l_temp;
				errordlogs[j].num = n_temp;
				errordlogs[j].pos = p_temp;

			}
		}
	}

	for (int i = 0;i < n && i < 8;i++) {
		char fn_final[20],*p = errordlogs[i].f_name;
		strcpy(fn_final,(strlen(errordlogs[i].f_name) > 16) ? p+strlen(errordlogs[i].f_name)-16 : p);
		printf("%s %d %d %d\n",fn_final,errordlogs[i].line,errordlogs[i].num,errordlogs[i].pos);
	}

	return 0;
}

/*
int main()
{
	EL *errordlogs = (EL *)calloc(2,sizeof(EL));
	printf("%s",errordlogs[0].f_name);
	errordlogs[0].line =1;
	errordlogs[0].num =1;
	strcpy(errordlogs[0].f_name, "123");
	errordlogs[1].line =1;
	errordlogs[1].num =1;
	strcpy(errordlogs[1].f_name, "23");
	int a=sizeof(errordlogs);
	errordlogs=(EL *)realloc(errordlogs, sizeof(EL)*3);
	errordlogs[2].line =1;
	errordlogs[2].num =1;
	strcpy(errordlogs[2].f_name, "231");
	int b=sizeof(errordlogs);
	printf("%d %s %d %s %s",a,errordlogs[0].f_name,b,errordlogs[1].f_name,errordlogs[2].f_name);
	free(errordlogs);
	return 0;
}
*/



















