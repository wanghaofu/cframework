#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

int main()
{
	//c
	int n=123;
	int *p =(int*) malloc(sizeof(int)*n);

	//struct
	struct test{
		int num;
		char name[2];
	};

	//	struct test *pTest=(struct test*)malloc(sizeof(struct test));

	//	struct test *pArray = pTest;
	int *pArray = p;
	*pArray = 123;
	*(pArray +1 ) =456;
cout<<"pArray: " << *pArray<<endl;
	cout<<"pArray+1: "  <<*(pArray+1)<< endl;
	free(p);
	p= 0;






}	


