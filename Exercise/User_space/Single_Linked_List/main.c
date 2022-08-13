#include<stdio.h>
#include<stdlib.h>

#define ADD_AT_HEAD 1
#define ADD_AT_TAIL 0

struct my_list
{
	int val;
	struct my_list *next;
};

struct my_list *head, *tail;

void add_node_to_list(int value, int pos)
{
	struct my_list *ptr = (struct my_list*)malloc(sizeof(struct my_list));
	
	if(ptr == NULL)
	{
		printf("Unable to allocate the memory for create new node\n");
	}
	
	ptr->val = value;
	ptr->next = NULL;
	
	if(head == NULL)
	{
		head = tail = ptr;
	}
	else if(pos == ADD_AT_HEAD)
	{
		ptr->next = head;
		head = ptr;
	}
	else
	{
		tail->next = ptr;
		tail = ptr;
	}
}

void del_node_from_list(int val_to_del)
{
	struct my_list *prev_list_ptr = head, *ptr = head;

	
	while(ptr != NULL)
	{
		if(ptr->val == val_to_del)
		{
			if(ptr == head)
			{
				head = ptr->next;
			}
			else if(ptr == tail)
			{
				prev_list_ptr->next = ptr->next;
				tail = prev_list_ptr;
			}
			else
			{
				prev_list_ptr->next = ptr->next;
			}
			free(ptr);
			printf("Removed the node with value %d\n", val_to_del);
			return;
		}

		prev_list_ptr = ptr;
		ptr = ptr->next;
	}
}
void print_list(void)
{
	if(head == NULL)
	{
		printf("List is empty\n");
		return;
	}
	
	struct my_list *ptr = head;
	
	printf("Following are list values\n");
	while(ptr != NULL)
	{
		printf("%d ", ptr->val);
		ptr = ptr->next;
	}
	printf("\n");
}

int main(void)
{
	printf("I am from main\n");
	print_list();
	add_node_to_list(2, ADD_AT_HEAD);
	print_list();
	
	add_node_to_list(1, ADD_AT_HEAD);
	print_list();
	
	add_node_to_list(3, ADD_AT_TAIL);
	print_list();
	
	del_node_from_list(1);
	print_list();
	
	add_node_to_list(1, ADD_AT_HEAD);
	print_list();
	
}