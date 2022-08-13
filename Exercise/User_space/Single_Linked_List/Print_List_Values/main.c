#include<stdio.h>

struct node
{
	int data;
	struct node *Next;
};

void print_list_val(struct node *node_ptr);

int main(void)
{
	struct node *head = NULL;

	print_list_val(head);	
}

void print_list_val(struct node *node_ptr)
{
	if(node_ptr == NULL)
	{
		printf("List is Empty\n");
		return;
	}
	
	printf("List values are: ");
	while(node_ptr != NULL)
	{
		printf("%d ", node_ptr->data);
		node_ptr = node_ptr->Next;
	}
	printf("\n");
}
