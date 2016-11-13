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
	struct mem_op *temp_node = oper1;
	struct mem_op *node = (struct mem_op *)malloc(sizeof(struct mem_op));

	if (node == NULL)
		printf("Erron in allocating data structure for storing process details\n");

	node->size = size;
	if (head->flag == 1)
	{
		node->address = temp_address;
		head->flag = 0;
		printf("head->flag: %d\n", head->flag);
	}
	else
	{
		while (i < head->count)
		{
			//	printf("temp_node: %d\n", temp_node->size);
			if (temp_node->flag == 1)
			{
				printf("flag: %d\n", temp_node->flag);
				value += temp_node->size;
			}
			printf("Value: %d\n", value);
			if (temp_node->link != NULL)
			{
				temp_node = temp_node->link;
				//				printf("%d\n", temp_node->flag);
			}
			i++;
		}
		if (value + size <= head->size)
		{
			node->address = oper2->address + oper2->size;
			//		printf("Value: %d\n", value + size);
			//		printf("size: %d\n", size);
			//		printf("Address: %p\n", node->address);		
		}
		else
		{
			//		printf("Value: %d\n", value + size);
			printf("Segmentation fault\n");		
		}
	}
	node->link = NULL;
	node->flag = 1;

	if (oper1 == NULL)
		oper1 = oper2 = node;
	else
	{
		oper2->link = node;
		oper2 = node;
	}
	head->count++;
	return oper2->address;
}

void my_free(int *free)
{
	struct mem_op *temp_free = oper1;

	while((temp_free)->address != free)
	{
		temp_free = (temp_free)->link;
	}
	(temp_free)->flag = 0;
}

void my_func()
{
	struct mem_op **temp = &oper1;
	int i;
	for(i = 0; i < 5; i++)
	{
		printf("flag: %d\n", (*temp)->flag);
		printf("flag: %x\n", (*temp)->address);
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
	int *ptr5 = my_malloc(974);
	printf("ptr5:%p\n", ptr5);
	printf("head->count: %d\n", head->count);

	my_free(ptr4);
	my_free(ptr2);
	//	ptr4 = my_malloc(20);
	printf("ptr4:%p\n", ptr4);

	my_func();
}
