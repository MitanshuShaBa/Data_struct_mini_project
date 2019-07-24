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
};

void data_writer(struct inv a[]);
void data_reader();
void add_element();

void main()
{
	// add_element();
	// data_writer();
	data_reader();
	getch();
}

void data_writer(struct inv a[])
{
	FILE *fp;
	fp = fopen("test.txt", "w");
	if(fp==NULL)
		printf("File failed to open\n");
	else
	{
		printf("File is now open.\n");
		for (int i = 0; i < 2; ++i)
		{
			fprintf(fp, "%s %d %d %d\n", a[i].name, a[i].price, a[i].quantity, a[i].cost);
		}
		printf("Written to file\n");
	}
	fclose(fp);
}
void data_reader()
{
	FILE *fp;
	struct inv a[2];
	fp = fopen("test.txt", "r");
		if(fp==NULL)
			printf("File failed to open\n");
		else
		{
			printf("File is now open.\n");
			for (int i = 0; i < 2; ++i)
			{
				fscanf(fp, "%s %d %d %d", a[i].name, &a[i].price, &a[i].quantity, &a[i].cost);
			}
			printf("Read from file\n");
			for (int i = 0; i < 2; ++i)
			{
				printf("%s %d %d %d\n", a[i].name, a[i].price, a[i].quantity, a[i].cost);
			}
		}
	fclose(fp);
}
void add_element()
{
	struct inv ap[2];

	for (int i = 0; i < 2; ++i)
	{
		printf("Enter name of item\n");
		scanf("%s", ap[i].name);
		printf("Enter price\n");
		scanf("%d", &ap[i].price);
		printf("Enter quantity\n");
		scanf("%d", &ap[i].quantity);

		ap[i].cost = ap[i].price * ap[i].quantity;
	}

	for (int i = 0; i < 2; ++i)
	{
		printf("%s %d %d %d\n", ap[i].name, ap[i].price, ap[i].quantity, ap[i].cost);
	}

	data_writer(ap);
}
