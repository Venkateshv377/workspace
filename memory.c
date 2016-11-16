#include <stdio.h>
#include <stdlib.h>
#include "mem.h"
#pragma pack(1)

struct mem_alloc {
	int size;
	int *address;
	char flag;
	struct mem_alloc *link;
};

struct mem_alloc *head = NULL;
struct mem_alloc *tail = NULL;
int *new_mem;
int temp_size;
int struct_size = sizeof(struct mem_alloc);

void init(int size)
{
	temp_size = size;

	new_mem = (int *)malloc(sizeof(size));
	head = (struct mem_alloc *)(new_mem);
	head->size = size;
	head->address = (int *)((char*)new_mem + struct_size); 
	head->flag = 0;
	head->link = NULL;

	if (head->link == NULL)
	{
		tail = head;
	}
}

int *my_malloc(int size)
{
	struct mem_alloc *new;
	if (size > temp_size) {
		printf("Stack overflow\n");
		return NULL;
	}
	if (head == tail)
	{
		new = (struct mem_alloc *)(head);
		new->size = size;
		new->address = (int *)((char *)new + struct_size);
		new->flag = 1;
		tail = (struct mem_alloc *)((char *)new + new->size + \
				struct_size);
		new->link = tail;
		tail->size = temp_size - struct_size + size;
		tail->address = (int *)((char*)tail + struct_size);
		temp_size -= size + struct_size;
	}
	else 
	{
		struct mem_alloc *temp = head;

		if (size <= temp_size)
		{
			while(temp->link != NULL)
			{
				if (temp->flag == 0)
				{
					int value_size = temp->size;
					int *temp_link = (int*)temp->link;
					if (size + struct_size < value_size)
					{
						new = (struct mem_alloc*)temp;
						new->size = size;
						new->flag = 1;
						new->address = (int*)((char*)new + struct_size);
						temp = (struct mem_alloc*)((int*)new+size+ \
								struct_size);
						new->link = temp;
						temp->size = value_size - new->size - \
							     struct_size;
						temp->flag = 0;
						temp->link = (struct mem_alloc *)temp_link;
						temp->address = (int*)((char*)temp + struct_size);
						temp_size -= size + struct_size;
					}
					else
					{
						temp->flag = 1;
					}
					return new->address;
				}
				temp = temp->link;
			}
			if (size == tail->size)
			{
				tail->flag = 1;
				temp_size -= size;
				return tail->address;
			}
			else if (size <= tail->size)
			{
				new = (struct mem_alloc *)tail;
				tail = (struct mem_alloc*)((int *)new + size + \
						struct_size);
				new->size = size;
				new->address = (int *)((char *)new + struct_size);
				new->flag = 1;
				new->link = tail;
				tail->size = temp_size - struct_size - size;
				tail->address = (int *)((char *)tail + struct_size);
				temp_size -= size + struct_size;
			}
		}
		else
		{
			return NULL;
		}
	}
	return new->address;
}

void my_free(int *address)
{
	struct mem_alloc *temp = head;

	while((temp->link != NULL))
	{
		if (((temp->address == address) && (temp->link->flag == 0)) || \
				((temp->flag == 0) && (temp->link->address == address)))
		{
			temp->size += temp->link->size + struct_size;
			temp->link = temp->link->link;
			temp_size += temp->size;
			temp->flag = 0;
			return;
		}
		if (temp->address == address)
		{
			temp->flag = 0;
			return;
		}
		temp = temp->link;
	}
}

void my_func()
{
	struct mem_alloc *temp = head;

	while(temp->link)
	{
		printf("temp: %p\n", temp);
		printf("temp->size: %d\n", temp->size);
		printf("temp->flag: %d\n", temp->flag);
		printf("temp->address: %p\n", temp->address);
		printf("temp->link: %p\n", temp->link);
		temp = temp->link;
	}
	printf("temp: %p\n", temp);
	printf("temp->size: %d\n", temp->size);
	printf("temp->flag: %d\n", temp->flag);
	printf("temp->address: %p\n", temp->address);
	printf("temp->link: %p\n", temp->link);
}
