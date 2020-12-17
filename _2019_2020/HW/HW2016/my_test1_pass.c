#include <stdio.h>

int main() {
	for (int r=0;r<10;r++) { //加个循环测试多个案例
	int N,M;
	scanf("%d %d",&N,&M);
	int grade[N];
	char a[M];
	int b[M][2]; //不能把x和b并做一个数组，类型不同，难处理，易出错
	for (int i = 0;i < N;i++) {
		scanf("%d",&grade[i]);
	}
	for (int j = 0;j < M;j++) {
		scanf(" %c %d %d",&a[j],&b[j][0],&b[j][1]);//注意避免回车符作为字符输入，在%c前面加空格
	}
	for (int k = 0;k < M;k++) {
		if (a[k] == 'Q') {
			int n = (b[k][0]<b[k][1])?b[k][0]:b[k][1];//区分大小
			int m = (b[k][0]>b[k][1])?b[k][0]:b[k][1];
			int max;
			max = grade[n-1];
			for (;n < m;n++) {
				if (max < grade[n])
					max = grade[n];
			}
			printf("%d\n",max);
		}
		else if ( a[k] == 'U') {
			int m = b[k][0];
			grade[m-1] = b[k][1];
		}
		else printf("the %dth command is error!\n",k+1);
		
	}
	}
	return 0;
}

/*
int main() {
	int N,M;
	//int Grade[N];
	//int i,k;
	//int j;
	//char x;
	scanf("%d %d",&N,&M);
	int Grade[N];
	for (int i=0;i<N;i++) {
		scanf("%d",&Grade[i]);	//若"%d "，则需多输入一个数，why1？
	}
	printf("%d %d\n",N,M);
	for (int i=0;i<N;i++) {	//若i换成j，则segmentation fault (core dumped)，why2?
		printf("%d ",Grade[i]);	
	}
	return 0;
}
the reason of why1:空格找不到对应，so？
the reason of why2:在N赋值前，先定义了Grade[N]，致使Grade的每一个元素与第一个for循环的i的地址对应，若用另外的不同的局部地址来进行索引，就会发生segmentation fault (core dumped)。why3？
总而言之，语法不熟悉。
*/

