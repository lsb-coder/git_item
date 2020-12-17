#include <stdio.h>
#include <stdlib.h>

typedef struct lifo_node{
	int data;
	struct lifo_node *next;
}lifo_node, *lifo;

int char_to_int(char c)
{
	switch (c){
	case '(':return 1;
	case '[':return 2;
	case '{':return 3;
	case ')':return -1;
	case ']':return -2;
	case '}':return -3;
	default:return 0;
	}
}

int match(char *str_brackets)
{
	lifo base = (lifo)malloc(sizeof(lifo_node));
	if(str_brackets[0] == '(' || str_brackets[0] == '[' || str_brackets[0] == '{'){
		
	}


} 

int main()
{
	

	return 0;
}
