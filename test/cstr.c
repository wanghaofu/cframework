#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
const 	char  *sptr;
	sptr="hello";
	printf("sptr %c\n",sptr[2]);
	int i=0;
	for(i=0;i<5;i++)
	{
		printf("sptr %c\n",*(sptr+i));
	}
}
