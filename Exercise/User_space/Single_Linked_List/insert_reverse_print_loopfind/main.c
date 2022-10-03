#include<stdio.h>
#include<stdlib.h>

struct Node
{
    int data;
    struct Node* next;
};

void add_to_head(struct Node **, int);
void print_node_val(struct Node *);
void add_to_tail(struct Node **, int);
void add_to_assend(struct Node **, int);
void find_loop(struct Node *);
void reverse_nod_method1(struct Node **);
void reverse_nod_method2(struct Node **);
void assend_only_value(struct Node *);
int main(void)
{
    struct Node *head = NULL;
    
    printf("Hellow world\n");
    
    add_to_head(&head, 3);
    add_to_head(&head, 4);
    add_to_head(&head, 1);
    print_node_val(head);
    
    add_to_tail(&head, 6);
    add_to_tail(&head, 7);
    print_node_val(head);
    
    add_to_assend(&head, 5);
    print_node_val(head);
    
    assend_only_value(head);
    print_node_val(head);
    
  //  head->next->next = head;
  //  find_loop(head);
    
    reverse_nod_method1(&head);
    print_node_val(head);
    
    reverse_nod_method2(&head);
    print_node_val(head);
    
    
    
    return 0;
    
}

void add_to_head(struct Node **my_head, int val)
{
    struct Node *new = (struct Node *)malloc(sizeof(struct Node));
    new->data = val;
    new->next = *my_head;
    
    *my_head = new;
}

void add_to_tail(struct Node **my_head, int val)
{
    struct Node *new = (struct Node *) malloc(sizeof(struct Node));
    struct Node *current_node = *my_head;
    
    new->data = val;
    new->next = NULL;
    
    if(current_node == NULL)
    {
        *my_head = new;
        return;
    }
    
    while(current_node->next != NULL)
    {
        current_node = current_node->next;
    }
    current_node->next = new;
}

void add_to_assend(struct Node **my_head, int val)
{
    struct Node *new = (struct Node *) malloc(sizeof(struct Node));
    struct Node *current_node = *my_head;
    
    new->data = val;
    new->next= NULL;
    
    if(current_node == NULL)
    {
        *my_head = new;
        return;
    }
    else if(current_node->data > new->data)
    {
        new->next = current_node;
        *my_head = new;
        return;
    }
    
    if((current_node->next != NULL) && (current_node->next->data <= new->data))
    {
        current_node = current_node->next;
    }
    new->next = current_node->next;
    current_node->next = new;
}


void assend_only_value(struct Node *my_head)
{
    struct Node *temp1 = NULL, *temp2 = NULL;
    
    if(my_head == NULL)
    {
        return;
    }
    
    for(temp1 = my_head; temp1 != NULL; temp1 = temp1->next)
    {
        for(temp2 = temp1->next; temp2 != NULL; temp2 = temp2->next)
        {
            if(temp1->data > temp2->data)
            {
                temp1->data = temp1->data + temp2->data;
                temp2->data = temp1->data - temp2->data;
                temp1->data = temp1->data - temp2->data;
            }
        }
    }
}

void find_loop(struct Node *my_head)
{
    struct Node * slow = my_head, *fast = my_head;
    
    while((slow != NULL) && (fast != NULL) && (fast->next != NULL))
    {
        slow = slow->next;
        fast = fast->next->next;
        
        if(slow == fast)
        {
            printf("Loop found\n");
            return;
        }
    }
    printf("Loop not found\n");
    
}

void reverse_nod_method1(struct Node **my_head)
{
    
    struct Node *prev_nod = NULL, *next_nod = NULL, * current_nod = *my_head;
    
    if(current_nod == NULL)
    {
        printf("List is empty\n");
        return;
    }
    
    while(current_nod->next != NULL)
    {
        next_nod = current_nod->next;
        current_nod->next = prev_nod;
        prev_nod = current_nod;
        current_nod = next_nod;
    }
    current_nod->next = prev_nod;
    
     *my_head = current_nod;
    
}

void reverse_nod_method2(struct Node **my_head)
{
    
    struct Node *prev_nod = NULL, *next_nod = NULL, * current_nod = *my_head;
    
    while(current_nod != NULL)
    {
        next_nod = current_nod->next;
        current_nod->next = prev_nod;
        prev_nod = current_nod;
        current_nod = next_nod;
    }
    
    *my_head = prev_nod;
    
}

void print_node_val(struct Node *my_head)
{
    struct Node * current_node = my_head;
    
    if(current_node == NULL)
    {
        printf("List is empty\n");
        return;
    }
    
    printf("List values: ");
    while(current_node != NULL)
    {
        printf("%d ", current_node->data);
        current_node = current_node->next;
    }
    printf("\n");
}
