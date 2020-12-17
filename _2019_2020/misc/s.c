/*#include <stdio.h>
#include <string.h>

int main() {
    char url[200];
    char urlf[100],urlb[100];
    char s[2] = "/";
    char *p;
    int lenf,lenb;
    while(scanf("%s", url) != EOF){
        p = strchr(url,',');
        strcpy(urlb,p+1);
        strcpy(p,"\0");
        strcpy(urlf,url);
        lenf = strlen(urlf);
        lenb = strlen(urlb);
        if(lenf == 0 && lenb == 0)
            printf("/");
        else if(urlf[lenf-1] == '/')
                if(urlb[0] == '/'){strcat(urlf,urlb+1);printf("%s\n",urlf);}
                else {strcat(urlf,urlb);printf("%s\n",urlf);}
        else if(urlb[0] == '/'){strcat(urlf,urlb);printf("%s\n",urlf);}
        else {strcat(urlf,s);strcat(urlf,urlb);printf("%s\n",urlf);}
    }
    return 0;
}*/
#include <stdio.h>
#include <string.h>

int firstrun (int *str,int len) {
    for (int i=0;i<len/2;i++){
        if (str[i] == len-i-1)
            return 0;
    }
}
int main() {
    int int_array[100];
    int len = 0;
    while(scanf("%u", (int_array+len)) && getchar() != '\n'){ 
	len++;
    }
    if(firstrun(int_array,len+1) == 0) printf("2\n");
    //else
    
    return 0;
}
