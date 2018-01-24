#include <stdio.h>
#include<stdlib.h>

//student records
typedef struct
{
	int rollno, age;
	char name[50], branch[20];


}student_rec;

//prototypes
int EnterRecords();
void ReadRecords(int n);
void SortOwn(student_rec student[], int num_record);
void Display(int num);
//main
int main()
{	
	int choice ;
	char ch;


	int num;
while(1){
	printf("1. Create FIle\n2. SortFIle\n3. Display FIle\n4. exit\n");

	

scanf("%d",&choice);
	switch(choice)
	{
		case 1:
			num=EnterRecords();
			break;
		case 2:
			ReadRecords(num);
			break;
		case 3:
			Display(num);
			break;
		case 4:
			exit(0);
	}


	
}
	
	// merge(num,num1)
	return 0;
}

// utility functions 
//enter the student details
int EnterRecords()
{
	student_rec student[50];
	int n,i;
	FILE *fptr;
	fptr = fopen("student_record", "wb");

	printf("Enter the number of student records to enter");
	scanf("%d", &n);
	for (i = 0; i < n; ++i)
	{
		printf("\nrollno: "); scanf("%d",&student[i].rollno);
		printf("name: ");  scanf("%s",student[i].name);
		printf("branch: "); scanf("%s",student[i].branch);
		printf("age: "); scanf("%d",&student[i].age);
		fwrite(&student,sizeof(student_rec),1,fptr);
	}

	fclose(fptr);
	return n;
}

//reading from file
void ReadRecords(int n)
{
	student_rec student[50];
	int i;
	FILE *fptr;
	fptr = fopen("student_record", "rb");

	for (i = 0; i < n; ++i)
	{
		fread(&student,sizeof(student_rec),1,fptr);
	}

	fclose(fptr);

	SortOwn(student,n);
	fptr = fopen("student_record", "wb");

	for (i = 0; i < n; ++i)
	{	
		fwrite(&student,sizeof(student_rec),1,fptr);

	}

	fclose(fptr);

}


//sortrecords inside themselves based on roll number

void SortOwn(student_rec student[], int num_record)
{
	int i,j;
	for(i = 0; i < num_record; i++)						//outer loop	run from "0" to the "lenght" 0f array;
	{
		for(j=0; j < num_record; j++)					//inner loop	run from "0" to the "lenght" 0f array;
		{	if(j == num_record-1)						//reached the end of iteration
				break;
			if(student[j].rollno > student[j+1].rollno)					//if 2nd element smaller than the 1st ..  "SWAP" 
			{
				student_rec temp = student[j];
				student[j] = student[j+1];
				student[j+1] = temp;
			}


		}
	}

}

void Display(int n)
{
	student_rec student[50];
	int i;
	FILE *fptr;
	fptr = fopen("student_record", "rb");

	for (i = 0; i < n; ++i)
	{
		fread(&student,sizeof(student_rec),1,fptr);
		printf("\nrollno: %d\n",student[i].rollno);
		printf("name: %s\n",student[i].name);
		printf("branch: %s\n",student[i].branch);
		printf("age: %d\n\n",student[i].age);
	}

	fclose(fptr);
}
// void merge()
// {
// 	FILE *fptr1, *fptr2;
// 	fptr1 = fopen("student_record", "rb");
// 	fptr2 = fopen("student_record1", "rb");
// 	student_rec student[100];

// }

void FakeData()
{
	
}