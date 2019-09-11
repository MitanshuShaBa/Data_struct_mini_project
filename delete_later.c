//store num & inv in single file inv
#include<stdio.h>
#include<stdlib.h>

struct node
{
	char name[20];
	int price;
	int quantity;
	int cost;
	//char expiry[20];
	//int limit;
	//char feedback[20];
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

int file_flag = 0;

void main()
{
	data_reader();
	int choice,flag=0;
	do
	 {
	 	printf("1:add new element \n");
		printf("2:print the list\n");
		printf("3:sort the list\n");
		printf("4:scan present inventory\n");
		printf("5:exit & save\n");
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
			sort();
			break;
			case 4:
			if(flag==0)
			{
				data_reader();
				if (file_flag==1)
				{
					printf("File not found\n");
				}
				flag=1;
			}
			else
				printf("already scaned\n");
			break;
			case 5:
			printf("programe ended\n");
			break;
			default:
			printf("invalid operation\n");
		}
	 } while (choice!=5);
	data_writer();
}

void data_writer()
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
void data_reader()
{
 	int n;
 	FILE *fp;
 	fp=fopen("inv.txt","r");
 	if (fp==NULL)
 	{
 		file_flag = 1;
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

void printList() 
{ 
	struct node*ptr; 
	printf("Traversal in forward direction \n"); 
	ptr=start;
	while (ptr!= NULL) 
	{ 
		printf("\t\t\t\t%s %d %d %d\n",ptr->name,ptr->price,ptr->quantity,ptr->cost);
		ptr= ptr->next; 
	} 
/*	ptr=end;
	printf("\nTraversal in reverse direction \n");
	while (ptr != NULL) { 
		printf("%s %d %d %d\n",ptr->name, last->price, ptr->quantity, ptr->cost); 
		ptr = ptr->prev; 
	} */
} 

int counter()
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
void sort_name()
{
	struct node *key,*ptr,*temp;
	key=start->next;
	while(key!=NULL)
	{
		ptr=key->prev;
		key->prev->next=key->next;
		key->next->prev=key->prev;
		while((ptr!=NULL)&&(ptr->cost < key->cost))
		{
			ptr=ptr->prev;
		}
		temp=key->next;
		ptr->next->prev=key;
		key->next=ptr->next;
		ptr->next=key;
		key->prev=ptr;
		key=temp;
	}
}
