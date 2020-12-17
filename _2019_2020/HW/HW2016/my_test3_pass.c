#include <stdio.h>
#include <string.h>

int main()
{
	char cards[50];
	char card1[20];
	char card2[20];
	char *p;
	int str2int1,str2int2;

	while(scanf("%[^\n]",cards) && getchar() != EOF/*fgets(cards,25,stdin)*/) {
		p = strchr(cards,'-');
		strncpy(card2,p+1,strlen(p)); //先截取后牌
		strcpy(p,"\0"); //去除后牌
		strcpy(card1,cards); //截取前牌
		printf("%s\n%s\n",card1,card2);
		int len1 = strlen(card1);
		int len2 = strlen(card2);
		printf("%d %d\n",len1,len2);

		//牌面排序
		switch (card1[0]) {
			case '2' : str2int1 = 15;break;
			case '1' : if (card1[1] != '0') {str2int1 = 14;break;} //注意是'0'
				    else {str2int1 = 10;break;}
			case 'K' : str2int1 = 13;break;
			case 'Q' : str2int1 = 12;break;
			case 'J' : str2int1 = 11;break;
			default  : str2int1 = card1[0] - '0';break;
		}
		switch (card2[0]) {
			case '2' : str2int2 = 15;break;
			case '1' : if (card2[1] != '0') {str2int2 = 14;break;}
				    else {str2int2 = 10;break;}
			case 'K' : str2int2 = 13;break;
			case 'Q' : str2int2 = 12;break;
			case 'J' : str2int2 = 11;break;
			default  : str2int2 = card2[0] - '0';break;
		}
		printf("%d %d\n",str2int1,str2int2);		

		//牌的总长度不同
		//王炸
		if (!strcmp(card1,"joker JOKER") || !strcmp(card2,"joker JOKER"))
			printf("joker JOKER\n");
		//普通炸
		else if ( len1 == 7 && len2 != 7) {
			if (len2 == 11) //特殊炸四个10
				printf("%s\n",(str2int1 > str2int2) ? card1 : card2);
			else printf("%s\n",card1);
		}
		else if ( len2 == 7 && len1 != 7) {
			if (len1 == 11) 
				printf("%s\n",(str2int1 > str2int2) ? card1 : card2);
			else printf("%s\n",card2);
		}
		//特殊炸四个10
		else if ( len1 == 11 ) printf("%s\n",card1);
		else if ( len2 == 11 ) printf("%s\n",card2);
		//存在10的情况
		else if (str2int1 == 10 || str2int2 == 10){
			if ((len1 == 8 && len2 == 5) || (len1 == 5 && len2 == 8))
				printf("%s\n",(str2int1 > str2int2) ? card1 : card2);
			else if ((len1 == 5 && len2 == 3) || (len1 == 3 && len2 == 5))
				printf("%s\n",(str2int1 > str2int2) ? card1 : card2);
			else if ((len1 == 2 && len2 == 1) || (len1 == 1 && len2 == 2))
				printf("%s\n",(str2int1 > str2int2) ? card1 : card2);
			//顺子最小数为10
			else if ((len1 == 10 && len2 == 9) || (len1 == 9 && len2 == 10))
				printf("%s\n",(str2int1 > str2int2) ? card1 : card2);
			else printf("ERROR\n");
		}
		//不存在比较
		else if (len1 != len2) printf("ERROR\n");

		//牌的总长度相同
		//大王
		else if (card1 == "JOKER" || card2 == "JOKER") printf("JOKER\n");
		//小王
		else if (card1 == "joker" || card2 == "joker") printf("joker\n");
		//2
		else printf("%s\n",(str2int1 > str2int2) ? card1 : card2);
	}

	return 0;
}

/*
#include <stdio.h>
#include <string.h>
 
 
/* 功  能：将str字符串中的oldstr字符串替换为newstr字符串
 * 参  数：str：操作目标 oldstr：被替换者 newstr：替换者
 * 返回值：返回替换之后的字符串
 * 版  本： V0.2
 
char *strrpc(char *str,char *oldstr,char *newstr){
    char bstr[strlen(str)];//转换缓冲区
    memset(bstr,0,sizeof(bstr));
 
    for(int i = 0;i < strlen(str);i++){
        if(!strncmp(str+i,oldstr,strlen(oldstr))){//查找目标字符串
            strcat(bstr,newstr);
            i += strlen(oldstr) - 1;
        }else{
        	strncat(bstr,str + i,1);//保存一字节进缓冲区
	    }
    }
 
    strcpy(str,bstr);
    return str;
}
 
int main(void)
{
	char str[] = "Hello,中国!\n"; 
	strrpc(str,"中国","世界");
	printf("%s",str);
	strrpc(str,"Hello","你好");
	printf("%s",str);
	strrpc(str,"你好,世界","Hello,world");
	printf("%s",str);
	return 0;
}
*/
