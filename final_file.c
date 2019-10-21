#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

struct node
{
	char name[20];
	int price;
	int quantity;
	int cost;
	struct node *next;
	struct node *prev;
};

struct node *start=NULL;
struct node *end=NULL;
void data_writer();
void data_reader();
void append();
void printList();
int counter();
void sort();
void swap_data(struct node *ptr1,struct node *ptr2);
void sort_name();
void print_node(struct node*);
void sort_cost();
struct node* search_name();
void delete_node(struct node *ptr);

void main()
{
	int choice;
	struct node *temp_ptr;
	data_reader();
	printList();// to print elements from inventory
	do
	 {
	 	printf("\n1:add new element \n");
	
		printf("2:print the list\n");
		printf("3:sort the list\n");
		printf("4:search by element's name\n");
		printf("5:delete by element's name\n");
		printf("6:save and exit\n");
		printf("eneter the choice------");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
			append();
			break;
			case 2:
			printList();
			break;
			case 3:
			sort();
			break;
			case 4:
			temp_ptr = search_name();
			print_node(temp_ptr);
			break;
			case 5:
			temp_ptr = search_name();
			delete_node(temp_ptr);
			break;
			case 6:
			printList();// to print all elemets at the end of programe
			printf("programe ended\n");
			break;
			default:
			printf("invalid operation\n");
		}
	 } while (choice!=6);
	data_writer();
	getch();  //  needed to be removed in case of ubuntu system
}

void data_writer()//to write all data to inventary
{	
	int n = counter();
	FILE *fp;
	fp = fopen("inv.txt", "w");
	if(fp==NULL)
		printf("File failed to open\n");
	else
	{
		fprintf(fp, "%d\n", n);
		struct node*ptr=start;
		while (ptr!= NULL)
		{ 
			fprintf(fp, "%s %d %d %d\n",ptr->name,ptr->price,ptr->quantity,ptr->cost); 
			ptr=ptr->next; 
		} 
		printf("Written to file\n");
	}
	fclose(fp);
}

void data_reader()// to read data from inveratry
{
 	int n;
 	FILE *fp;
 	fp=fopen("inv.txt","r");
 	if (fp==NULL)
 	{
 		printf("file failed to open\n");
 	}
 	else
 	{
 		fscanf(fp,"%d",&n);
		for (int i = 0; i <n; ++i)
		{
			struct node *new_node;
			new_node=(struct node*)malloc(sizeof(struct node));
			fscanf(fp, "%s %d %d %d",&new_node->name,&new_node->price
					,&new_node->quantity,&new_node->cost);
 			new_node->next=NULL;
 			if (start == NULL)
			{ 
				new_node->prev = NULL; 
				start = new_node;
				end=new_node; 
			} 
			else
			{
				end->next = new_node; 
				new_node->prev =end; 
				end=new_node;
			}
		}
		printf("\t\t\t%d elemets are added\n", n);
	}
 	fclose(fp);	
}

void append() 
{ 
	struct node* new_node = (struct node*)malloc(sizeof(struct node)); 
	printf("Enter name of item : ");
	scanf("%s", new_node->name);
	printf("Enter price : ");
	scanf("%d", &(new_node->price));
	printf("Enter quantity : ");
	scanf("%d", &(new_node->quantity));
	new_node->cost = new_node->price * new_node->quantity;
	printf("elemets :\t\t\t%s %d %d %d\n", new_node->name, new_node->price, new_node->quantity, new_node->cost);
	new_node->next = NULL; 
	if (start == NULL) 
	{ 
		new_node->prev = NULL; 
		start = new_node; 
		end=new_node;
	} 
	else
	{
		end->next = new_node; 
		new_node->prev =end; 
		end=new_node;
	}	
}

void printList() // to print entire list
{ 
	struct node*ptr; 
	ptr=start;
	while (ptr!= NULL) 
	{ 
		printf("\t\t\t\t%s %d %d %d\n",ptr->name,ptr->price,ptr->quantity,ptr->cost);
		ptr= ptr->next;
	}
}

int counter()// needed in data writer function
{
	struct node*ptr=start;
	int count=0;
	while(ptr!=NULL)
	{
		count++;
		ptr=ptr->next;
	}
	return count;
}

void sort()
{
	int choice;
	printf("1.Sort by cost\n");
	printf("2.Sort by name\n");
	scanf("%d", &choice);
	switch(choice)
	{
		case 1:
		sort_cost();
		break;
		case 2:
		sort_name();
		break;
		default:
		printf("Check input\n");
	}
}

void swap_data(struct node *ptr1,struct node *ptr2)
{

	// struct node *temp=(struct node *)malloc(sizeof(struct node *));
	int temp;
	char temp_name[20];

	temp=ptr1->cost;
	ptr1->cost=ptr2->cost;
	ptr2->cost=temp;

	temp=ptr1->price;
	ptr1->price=ptr2->price;
	ptr2->price=temp;

	temp=ptr1->quantity;
	ptr1->quantity=ptr2->quantity;
	ptr2->quantity=temp;

	strcpy(temp_name, ptr1->name);
	strcpy(ptr1->name, ptr2->name);
	strcpy(ptr2->name, temp_name);

	// free(temp);
}

void sort_cost()
{
	struct node *ptr;
	struct node *lptr=NULL;
	int swapped,temp;

	while(start==NULL)
		return;
	do
	{
		ptr=start;
		swapped=0;
		while(ptr->next!=lptr)
		{
			if(ptr->cost>ptr->next->cost)
			{
				swap_data(ptr,ptr->next);
				swapped=1;
			}
			ptr=ptr->next;
		}
		lptr=ptr;
	}while(swapped!=0);
}

void sort_name()
{
	struct node *key,*ptr,*temp_end;
	temp_end = end;
	key=start->next;
	while(temp_end!=NULL)
	{
		ptr=start;
		key=start->next;
		while(key!=temp_end->next)
		{
			if(strcmp(ptr->name, key->name)>0)
			{
				swap_data(ptr, key);
			}
			ptr = ptr->next;
			key = key->next;
		}
		temp_end = temp_end->prev;
	}
}

void print_node(struct node *ptr)// to print specific node
{
	if (ptr==NULL)
	{
		printf("node dosen't exist\n");
	}
	else
	{
		printf("\t\t\t\t%s %d %d %d\n",ptr->name,ptr->price,ptr->quantity,ptr->cost);
	}
}

struct node* search_name()// seraching node by name
{
	char key[20];
	printf("enter the name of item : ");
	scanf("%s",&key);
	struct node *ptr=start;
	while(ptr!=NULL)
	{
		if(0==strcmp(key,ptr->name))
		break;
		ptr=ptr->next;
	}
	return ptr;
}

void delete_node(struct node *ptr)// to delete specific node
{
	print_node(ptr);
	ptr->prev->next=ptr->next;
	ptr->next->prev=ptr->prev;
	free(ptr);
}
