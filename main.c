#include <stdio.h>
#include "mem.h"

int main()
{
	init(1024);

	int *ptr1 = (int*)my_malloc(100);
	printf("ptr1: %p\n", ptr1);

	int *ptr2 = my_malloc(100);
	printf("ptr2: %p\n", ptr2);

	int *ptr3 = my_malloc(100);
	printf("ptr3: %p\n", ptr3);

	int *ptr4 = my_malloc(100);
	printf("ptr4: %p\n", ptr4);

	int *ptr5 = my_malloc(100);
	printf("ptr5: %p\n", ptr5);
	
	int *ptr6 = my_malloc(100);
	printf("ptr6: %p\n", ptr6);
	
	int *ptr7 = my_malloc(100);
	printf("ptr7: %p\n", ptr7);
	
	int *ptr8 = my_malloc(100);
	printf("ptr8: %p\n", ptr8);
	
	int *ptr9 = my_malloc(56);
	printf("ptr9: %p\n", ptr9);
	
	my_func();
	printf("\n");
	my_free(ptr6);
	my_free(ptr7);
	
	my_func();
	int *ptr10 = my_malloc(199);
	printf("ptr10: %p\n", ptr10);
	
	printf("\n");
	my_func();
	printf("\n");
	my_free(ptr10);
	my_func();
/*	int *ptr11 = my_malloc(150);
	printf("ptr11: %p\n", ptr11);
	printf("\n");
	my_func();		*/
}
