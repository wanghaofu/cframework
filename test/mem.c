#include <stdlib.h>
#include <stdio.h>


int main()
{
//	int s=100;
//	int *ptr = &s;
	int s[10];
	int i;
	char v[10]="hello";
	for(i=0;i<=9;i++)
	{
		*(s+i)=i+1;
		printf("s address is %x,s[%d] is %d\n",s+i,i,s[i]);
	}
	int	*xptr=(int *)malloc(sizeof(int)*10);
	int j;
	for(j=0;j<10;j++)
{
	*(xptr+j)=j*2;
	printf("xptr address is %x,xptr[%d] is %d\n",xptr+j,j,*(xptr+j));
}
free(xptr);
xptr=0;
}
