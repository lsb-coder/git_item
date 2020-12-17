#include <stdio.h>
#include <string.h>

int main()
{
	char *s;
	char index[1000];
	int max[500];
	int num[][2];
	int p=0;
	int temp1,temp2,temp3;
	for(int i=0;i<strlen(s);i++){
		if (s[i]==s[i+1])
			for (int j=1;s[i-j] == s[i+j+1];j++) {
				max[p]= 2*(i-j+1);num[p][0]=i-j;num[p][1]=i+j+1;
			}
		else if (i !=0 && s[i-1] == s[i+1])
			for (int j=1;s[i-1-j] == s[i-1+j+1];j++) {
				max[p]= 2*(i-j+1);num[p][0]=i-j;num[p][1]=i-j+1;
			}
		p++;
	}
	for (int k=0;k<=p;k++){
		for(int r=0;r<p;r++){
			if(max[r] <max[r+1]){
				temp1 = max[r+1];
				max[r+1]=max[r];
				max[r]=temp;
				temp2 = mum[r+1][0];
				mum[r+1][0]=mum[r][0];
				mum[r][0]=temp2;
				temp3 = mum[r+1][1];
				mum[r+1][1]=mum[r][1];
				mum[r][1]=temp2;
			}
		}
	}
	if(max[0]> max[1])
		for(int n=mum[0][0];n<=mum[0][1];n++)
			printf("%c",s[n]);
	else {
		for (int n=1;n<=p;n++)
			if (max[n][1]-max[n][0] == max[0][1]-maxx[0][0])
				for(int k=max[n][0];i<=max[n][1];k++)
					printf("%c",s[k]);	
	}

}
