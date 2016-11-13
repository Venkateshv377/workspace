#include <stdio.h>
#include <stdlib.h>
#pragma pack(1)
struct mem_alloc {
	int size;
	int address;
	int flag;
	int count;
};

struct mem_op {
	int size;
	int address;
	struct mem_op *link;
	int flag;
};

struct mem_alloc *head = NULL;
struct mem_op *oper1 = NULL;
struct mem_op *oper2 = NULL;
int *temp_address;

void init(int size)
{
	struct mem_alloc *node = (struct mem_alloc *)malloc(sizeof(struct mem_alloc));

	int *ptr = (int *)malloc(size);

	node->size = size;
	node->address = ptr;

	if (ptr == NULL)
		return NULL;
	if (head == NULL)
		head = node;

	temp_address = (int *)head->address;
	if (temp_address != NULL)
		head->flag = 1;
	head->count = 0;
}

int* my_malloc(int size)
{
	int value = 0, i = 0;
	struct mem_op **temp = &oper1;
	struct mem_op *temp_node = oper1;
	struct mem_op *node = (struct mem_op *)malloc(sizeof(struct mem_op));

	if (node == NULL)
		printf("Erron in allocating data structure\n");

	node->size = size;
	if (head->flag == 1)
	{
		node->address = temp_address;
		head->flag = 0;
		node->link = NULL;
		node->flag = 1;
	}
	else
	{
		while (i < head->count)
		{
			printf("temp_node->flag: %d\n", temp_node->flag);
			if (temp_node->flag == 1)
			{
				value += temp_node->size;
			}
			else
			{
				if (size <= temp_node->size)
				{
					node->address = temp_node->address;
					goto L1;
				}
			}
			if (temp_node->link != NULL)
			{
				temp_node = temp_node->link;
			}
			printf("size: %d\n", value);
			i++;
		}
		if (value + size <= head->size)
		{
			node->address = oper2->address + oper2->size;
		}
		else
		{
			printf("Segmentation fault\n");		
			return;
		}
L1:
		node->link = NULL;
		node->flag = 1;
	}

	if (oper1 == NULL)
	{
		oper1 = oper2 = node;
		printf("Operation1 if condition\n");
	}
	else
	{
		printf("Operation else condtion\n");
		oper2->link = node;
		oper2 = node;
	}
	head->count++;
	return oper2->address;
}

void my_free(int *free)
{
	struct mem_op *temp_free = oper1;

	while(temp_free->address != free)
	{
		temp_free = (temp_free)->link;
	}
	temp_free->flag = 0;
}

void my_func()
{
	struct mem_op **temp = &oper1;
	while((*temp)->link != NULL)
	{
		printf("Size: %d\n", (*temp)->size);
		printf("flag: %d\n", (*temp)->flag);
		printf("Address: %x\n", (*temp)->address);
		printf("Link: %p\n", (*temp)->link);
		(*temp) = (*temp)->link;
	}
}

int main()
{
	init(1024);
	int *ptr1 = my_malloc(5);
	printf("ptr1:%p\n", ptr1);
	int *ptr2 = my_malloc(10);
	printf("ptr2:%p\n", ptr2);
	int *ptr3 = my_malloc(15);
	printf("ptr3:%p\n", ptr3);
	int *ptr4 = my_malloc(20);
	printf("ptr4:%p\n", ptr4);
	int *ptr5 = my_malloc(25);
	printf("ptr5:%p\n", ptr5);
	int *ptr6 = my_malloc(30);
	printf("ptr6:%p\n", ptr6);
	printf("head->count: %d\n", head->count);
	my_free(ptr3);
	int *ptr7 = my_malloc(15);
	printf("ptr7:%p\n", ptr7);
	//	my_func();
}
