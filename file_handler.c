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
	// char limit[20];
	char feedback[20];
	char category[20];
};

void data_writer(struct inv a);
void data_reader();
void add_element();

void main()
{
	// struct inv obj;
	// obj.price = 20;
	// obj.quantity = 50;
	// printf("%d %d\n", obj.price, obj.quantity);
	add_element();
	// data_writer();
	// data_reader();
	getch();
}

void data_writer(struct inv a)
{
	FILE *fp;
	fp = fopen("test.txt", "w");
	if(fp==NULL)
		printf("File failed to open\n");
	else
	{
		printf("File is now open.\n");
		fprintf(fp, "%s %d %d %d\n", a.name, a.price, a.quantity, a.cost);
		printf("Written to file\n");
	}
	fclose(fp);
}
void data_reader()
{
	FILE *fp;
	int a;
	fp = fopen("test.txt", "r");
		if(fp==NULL)
			printf("File failed to open\n");
		else
		{
			printf("File is now open.\n");
			fscanf(fp, "%d", &a);
			printf("Read from file\n");
			printf("%d\n", a);
		}
	fclose(fp);
}
void add_element()
{
	// char name[20];
	// int price;
	// int quantity;
	// int cost;
	// char expiry[20];
	// // char limit[20];
	// char feedback[20];
	// char category[20];
	struct inv ap;

	printf("Enter name of item\n");
	gets(ap.name);
	printf("Enter price\n");
	scanf("%d", &ap.price);
	printf("Enter quantity\n");
	scanf("%d", &ap.quantity);

	ap.cost = ap.price * ap.quantity;

	printf("%s %d %d %d\n", ap.name, ap.price, ap.quantity, ap.cost);

	data_writer(ap);
}
