#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
typedef struct{
  char name[500];
  char cut[20];
  int row;
  int count;
  // inital position
  int pos;
}Rec;
 
int cmp(const void *a, const void *b){
  Rec x = *((Rec *)a);
  Rec y = *((Rec *)b);
  int tmp = strcmp(x.name,y.name);
  if ( tmp == 0 )
    return x.row - y.row;
  return tmp;
}
 
int cmp2(const void *a, const void *b){
  Rec x = *((Rec *)a);
  Rec y = *((Rec *)b);
  int tmp = y.count - x.count;
  if ( tmp == 0 )
    return x.pos - y.pos;
  return tmp;
}
 
int get_split(char *data){
  int i,len;
  for ( i = strlen(data) - 1; i >= 0; i -- ){
    if (data[i] == '\\')
      return i;
  }
  return 0;
}
 
int main(){
  char path[1000];
  int row;
  int len;
  int n,i = 0,j  = 0;
  char *name;
  Rec data[1000];
  Rec res[1000];
  while( scanf("%s%d",path,&row) != EOF ){
    name = path + get_split(path) + 1;
    strcpy(data[i].name,name);
    len = strlen(name);
    if ( len > 16 ){
      name = name + (len - 16);
    }
    strcpy(data[i].cut,name);
    data[i].row = row;
    data[i].count = 1;
    data[i].pos = i;
    i ++;
  }
  n = i;
  qsort(data,n,sizeof(Rec),cmp);
  i = j = 0;
  res[j++] = data[i++];
  while( i < n ){
    if ( strcmp(data[i].name,res[j-1].name) == 0 && data[i].row == res[j-1].row ){
      res[j-1].count ++;
    }
    else{
      res[j++] = data[i];
    }
    i ++;
  }
  qsort(res,j,sizeof(Rec),cmp2);
  j = j > 8 ? 8 : j;
  for ( i = 0; i < j; i ++ ){
    printf("%s %d %d\n",res[i].cut,res[i].row,res[i].count);
  }
  return 0;
}
