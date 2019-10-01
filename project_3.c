#include<stdio.h>
#include<stdlib.h>
#include<conio.h>// needed to be removed in case of ubunto system
#include<string.h>

struct node
{
	char name[20];
	int price;
	int quantity;
	int cost;
	//char expiry[20];
	//int min_limit;
	//char feedback[50];
	//char category[20];
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
struct node * search_name();
void print_node(struct node *);
void delete_node(struct node*);

void main()
{
	int choice;
	data_reader();
	printList();// to print elements from invertary
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
			printf("not available yet\n");
			//sort();
			break;
			case 4:
			print_node(search_name());
			break;
			case 5:
			delete_node(search_name());
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
	getch();  //  needed to be removed in case of ubunto system
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

void append() // to add new element
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

/*void sort()
{
	struct node*ptr1=start->next,*ptr2,*temp;
	if(start==NULL)
		printf("empty list\n");
	else
	{
		while(ptr1!=NULL)
		{
			ptr1->next->prev=ptr1->prev;
			ptr1->prev->next=ptr1->next;
			while(ptr1->cost > ptr2->cost)
			{
				ptr2=ptr2->prev;
			}
			ptr1->prev=ptr2->prev;
			ptr1->next=ptr2;
			ptr2->prev->next=ptr1;
			ptr2->prev=ptr1;
			ptr1=ptr1->next;
		}
	}
}*/

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

struct node * search_name()// seraching node by name
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
