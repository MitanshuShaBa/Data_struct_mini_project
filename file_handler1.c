#include <stdio.h>
#include<stdlib.h>
#include<conio.h>

struct inv
{
	char name[20];
	int price;
	int quantity;
	int cost;
	char expiry[20];
	int limit;
	char feedback[20];
	char category[20];

	struct inv *next;
	struct inv *prev;
};

int n=0;
struct inv *data;

void data_writer(struct inv* node);
// void data_reader();
void append(struct inv** head_ref);
void printList(struct inv* node);
int counter(struct inv* node);

void main()
{

	struct inv* head = NULL; 
	append(&head);	
	append(&head);
	printList(head);
	n = counter(head);
	data_writer(head);
	getch();
}

void data_writer(struct inv *node)
{
	//writing inventory
	FILE *fp;
	fp = fopen("inv.txt", "w");
	if(fp==NULL)
		printf("File failed to open\n");
	else
	{
		printf("File is now open.\n");
		// for (int i = 0; i < n; ++i)
		// {
		// 	fprintf(fp, "%s %d %d %d\n", (a+i)->name, (a+i)->price, (a+i)->quantity, (a+i)->cost);
		// }
		while (node != NULL)
		{ 
			fprintf(fp, "%s %d %d %d\n", node->name, node->price, node->quantity, node->cost); 
			node = node->next; 
		} 
		printf("Written to file\n");
	}
	fclose(fp);

	//writing count of list
	fp = fopen("num.txt", "w");
	if(fp==NULL)
		printf("File failed to open\n");
	else
	{
		fprintf(fp, "%d", n);
	}
	fclose(fp);
}
// void data_reader()
// {
// 	FILE *fp;
// 	struct inv a[2];
// 	fp = fopen("inv.txt", "r");
// 		if(fp==NULL)
// 			printf("File failed to open\n");
// 		else
// 		{
// 			printf("File is now open.\n");
// 			for (int i = 0; i < 2; ++i)
// 			{
// 				fscanf(fp, "%s %d %d %d", a[i].name, &a[i].price, &a[i].quantity, &a[i].cost);
// 			}
// 			printf("Read from file\n");
// 			for (int i = 0; i < 2; ++i)
// 			{
// 				printf("%s %d %d %d\n", a[i].name, a[i].price, a[i].quantity, a[i].cost);
// 			}
// 		}
// 	fclose(fp);
// }
void append(struct inv** head_ref) 
{ 
	/* 1. allocate node */
	struct inv* new_node = (struct inv*)malloc(sizeof(struct inv)); 

	struct inv* last = *head_ref; /* used in step 5*/

	/* 2. put in the data */
	// new_node->data = new_data; 
	printf("Enter name of item\n");
	scanf("%s", new_node->name);
	printf("Enter price\n");
	scanf("%d", &(new_node->price));
	printf("Enter quantity\n");
	scanf("%d", &(new_node->quantity));

	new_node->cost = new_node->price * new_node->quantity;
	
	printf("Added:\n");

	printf("%s %d %d %d\n\n", new_node->name, new_node->price, new_node->quantity, new_node->cost);

	/* 3. This new node is going to be the last node, so 
		make next of it as NULL*/
	new_node->next = NULL; 

	/* 4. If the Linked List is empty, then make the new 
		node as head */
	if (*head_ref == NULL) { 
		new_node->prev = NULL; 
		*head_ref = new_node; 
		return; 
	} 

	/* 5. Else traverse till the last node */
	while (last->next != NULL) 
		last = last->next; 

	/* 6. Change the next of last node */
	last->next = new_node; 

	/* 7. Make last node as previous of new node */
	new_node->prev = last; 

	return; 
} 
void printList(struct inv* node) 
{ 
	struct inv* last; 
	printf("Traversal in forward direction \n"); 
	while (node != NULL) { 
		printf("%s %d %d %d\n", node->name, node->price, node->quantity, node->cost); 
		last = node; 
		node = node->next; 
	} 

	printf("\nTraversal in reverse direction \n"); 
	while (last != NULL) { 
		printf("%s %d %d %d\n", last->name, last->price, last->quantity, last->cost); 
		last = last->prev; 
	} 
} 
int counter(struct inv* node)
{
	int count=0;
	while(node!=NULL)
	{
		count++;
		node = node->next;
	}
	return count;
}
