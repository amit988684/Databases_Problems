#include<stdio.h>


//structure
typedef struct 
{
	int rollno,age;
	char name[50], branch[20];
}student_rec;

//prototypes
void createFile();


//driver
void main()
{
	createFile();
	// return 0;
}


void createFile()
{	//variables
	int num_record,i;
	
	char file_name[100];
	FILE *fp;

	//program
	printf("%s\n","enter the name of the file" );
	scanf("%s",file_name);
	printf("%s\n","enter the number of records" );
	scanf("%d",&num_record);
	student_rec student[num_record];
	fp = fopen(file_name,"wb");

	while(i<num_record)
	{
		scanf("%d",&student[i].rollno);
		scanf("%s",student[i].name);
		scanf("%s",student[i].branch);
		scanf("%d",&student[i].age);
		student[num_record-1].eof='$';
		fwrite(&student,sizeof(student_rec),1,fp);
		i++;
	}
	fclose(fp);
}

void sortFile()
{	char file_name[100];
	student_rec student[100];
	int i,num;
	printf("%s\n","enter the name of the file to sort" );
	scanf("%s",file_name);
	FILE *fp;

	fp = fopen(file_name, "rb");
	fread(&student,sizeof(student_rec),1,fp);
	while(fread(&student,sizeof(student_rec),1,fp)>0)
	{
		printf("%d%d%s%s\n",student.rollno,student.age,student.name,student.branch);
		num++;
	}
printf("%d\n",num );
	fclose(fp);

	// SortOwn(student,num);

	// fp = fopen(file_name, "wb");

	// for (i = 0; i < n; ++i)
	// {
	// 	fwrite(&student,sizeof(student_rec),1,fp);
	// }

	// fclose(fp);
}


// void sub_sortFile()
// {
// 	int i,j;
// 	for(i = 0; i < num_record; i++)						//outer loop	run from "0" to the "lenght" 0f array;
// 	{
// 		for(j=0; j < num_record; j++)					//inner loop	run from "0" to the "lenght" 0f array;
// 		{	if(j == num_record-1)						//reached the end of iteration
// 				break;
// 			if(student[j].rollno > student[j+1].rollno)					//if 2nd element smaller than the 1st ..  "SWAP" 
// 			{
// 				student_rec temp = student[j];
// 				student[j] = student[j+1];
// 				student[j+1] = temp;
// 			}


// 		}
// 	}
// }