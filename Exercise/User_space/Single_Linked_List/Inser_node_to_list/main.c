#include<stdio.h>
#include<stdlib.h>

struct node
{
	int data;
	struct node *Next;
};

void print_list_val(struct node *node_ptr);
void Insert_to_list_tail(struct node **node_ptr, int val_to_add);
void Insert_to_list_head(struct node **node_ptr, int val_to_add);
void Insert_to_list_pos(struct node **node_ptr, int pos, int val_to_add);
void delete_nod_of_val(struct node **node_ptr, int val_to_del);
void sorting_of_val(struct node *node_ptr);

int main(void)
{
	struct node *head = NULL;
	Insert_to_list_head(&head, 4);
	Insert_to_list_head(&head, 5);
	Insert_to_list_head(&head, 6);
	

//	print_list_val(head);
	
	Insert_to_list_tail(&head, 8);
	Insert_to_list_tail(&head, 7);
	Insert_to_list_tail(&head, 6);
	
//	print_list_val(head);
		
	Insert_to_list_pos(&head, 0, 1);
	Insert_to_list_pos(&head, 4, 5);
//	print_list_val(head);
	
//	delete_nod_of_val(&head, 1);
	print_list_val(head);
	
	sorting_of_val(head);
	print_list_val(head);

}

void sorting_of_val(struct node *node_ptr)
{
	int list_size = 0, Cnt1 = 0, Cnt2 = 0, tmp_data;
	struct node *current = NULL;
	
	if(node_ptr == NULL)
	{
		printf("List is Empty\n");
	}
	current = node_ptr;
	
	while(current != NULL)
	{
		current = current->Next;
		list_size++;
	}
	printf("Size of list %d\n", list_size);

	for(Cnt1 = 0; Cnt1 < list_size; Cnt1++)
	{
		current = node_ptr;
		for(Cnt2 = 0; (Cnt2 < (list_size - Cnt1 - 1)); Cnt2++)
		{
			if((current->data) > (current->Next->data))
			{
				tmp_data = current->data;
				current->data = current->Next->data;
				current->Next->data = tmp_data;
				
			}
			current = current->Next;
		}
	}
}

void delete_nod_of_val(struct node **node_ptr, int val_to_del)
{
	struct node *current = NULL, *prev_nod = NULL;
	if(*node_ptr == NULL)
	{
		printf("Node is NULL\n");
	}
	
	current = *node_ptr;
	while(current != NULL)
	{
		if(current->data == val_to_del)
		{
			if(current == *node_ptr)
			{
				*node_ptr = current->Next;
			}
			else
			{
				prev_nod->Next = current->Next;
			}
			free(current);
			return;
		}
		prev_nod = current;
		current = current->Next;
	}
}
void Insert_to_list_pos(struct node **node_ptr, int pos, int val_to_add)
{
	int Cnt;
	struct node * link = (struct node *)malloc(sizeof(struct node));
	struct node * current = NULL, *Prv = NULL;
	
	link->data = val_to_add;
	link->Next = NULL;

	current = *node_ptr;

	if(*node_ptr == NULL)
	{
		if(pos == 0)
		{
			*node_ptr = link;
		}
		else
		{
			printf("Invalid Possition\n");
		}
		return;
	}
	else
	{
		if(pos == 0)
		{
			link->Next = *node_ptr;
			*node_ptr = link;
			return;
		}

		for(Cnt = 0; Cnt < pos; Cnt++)
		{		
			if(current != NULL)
			{
				Prv = current;
				current = current->Next;
			}
			else
			{
				printf("Invalid Possition\n");
				return;
			}
		}
		link->Next = Prv->Next;
		Prv->Next = link;
	}
}
void Insert_to_list_tail(struct node **node_ptr, int val_to_add)
{
	struct node * link = (struct node *)malloc(sizeof(struct node));
	struct node * current = NULL, *prv_nod = NULL;
	
	link->data = val_to_add;
	link->Next = NULL;
	
	if(*node_ptr == NULL)
	{
		*node_ptr = link;
	}
	else
	{
		current = *node_ptr;
		while(current != NULL)
		{
			prv_nod = current;
			current = current->Next;
		}
		prv_nod->Next = link;
	}
}

void Insert_to_list_head(struct node **node_ptr, int val_to_add)
{
	struct node * link = (struct node *)malloc(sizeof(struct node));
	struct node * current = NULL;
	
	link->data = val_to_add;
	link->Next = NULL;
	
	if(*node_ptr == NULL)
	{
		*node_ptr = link;
	}
	else
	{
		link->Next = *node_ptr;
		*node_ptr = link;
	}
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
