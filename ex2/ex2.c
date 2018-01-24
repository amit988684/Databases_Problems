#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

typedef struct
{
	int rollno, age;
	char name[50], branch[20];


}student_rec;

void enterInFile();
void displayFileContents();
void sortFile();
void mergeSort();
void linearSearch();
void FakeData();
void FakeDataForMegeSort();

int main()
{
	int choice ;
	char ch;
	clock_t t;
	double time_taken;
	int num;
	while(1)
	{	system("clear");
		printf("1. Create FIle\n2. Display FIle\n3. merge two files \n4. clear screen ? \n5. linear search on a particular file ?\n6.sort particular file\n7.Do you want to Create Fake Data of 10000 records ? ?\n");
		
		//system("clear");
	

		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				system("clear");
				enterInFile();
				break;
			case 2:
				system("clear");
				displayFileContents();
				break;

			case 3:
				system("clear");
				t = clock();
    			mergeSort();
    			t = clock() - t;
    			time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
    			printf("mergeSort() took %f seconds to execute \n\n", time_taken);
				break;
			case 4:
				system("clear");
				break;
			case 5:
			    system("clear");
    			t = clock();
    			linearSearch();
    			t = clock() - t;
    			time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
    			printf("linearSearch() took %f seconds to execute \n\n", time_taken);
    			break;
			case 6:
				system("clear");
				sortFile();
				break;
			case 7:
				system("clear");
				FakeData();
				break;
			default:
				printf("%s\n", "enter correct option !!!!! ");
			
		}
		scanf("%c",&ch);
		printf("%s","want to continue  y or n ?? ");
		scanf("%c",&ch);
		if(ch!='y')
			break;
	}
	
	// merge(num,num1)
	return 0;
}

void enterInFile()
{	//variables
	FILE *fp;
	char filename[75];
	int n;
	int i;
	student_rec student;


	//expressions
	printf("enter any name for File = ");
	scanf("%s",filename);

	fp = fopen(filename,"wb");
	
	printf("\n%s","enter number of records you want to save = ");
	scanf("%d",&n);
	


	// if(fp==NULL)
	// {
	// 	printf("%s\n", "file not opened !! ");
	// 	return;
	// }

	for (i = 0; i < n; ++i)
	{
		printf("rollno = ? ");			scanf("%d",&student.rollno);

		printf("name = ? ");			scanf("%s",student.name);

		printf("age = ? ");				scanf("%d",&student.age);

		printf("branch = ? ");			scanf("%s",student.branch);

		fwrite(&student,sizeof(student_rec),1,fp);
	}

fclose(fp);
}


void displayFileContents()
{
	FILE *fp;
	char filename[100];
	student_rec student;
	printf("%s","enter the name of the file you want to diplay : " );
	scanf("%s",filename);

	fp = fopen(filename,"rb");


	while(fread(&student,sizeof(student_rec),1,fp)!=0)
	{	
		printf("rollno = %d\n",student.rollno );
		printf("name = %s\n",student.name );
		printf("age = %d\n",student.age );
		printf("branch = %s\n________________________________\n\n",student.branch );
	}
	fclose(fp);
}


void sortFile()
{

	student_rec student,stu[50];
	FILE *fptr;
	int i,j,n=0;
	
	char filename[100];
	printf("%s","enter the name of the file to sort : " );
	scanf("%s",filename);
	
	fptr = fopen(filename, "rb");

	while(fread(&student,sizeof(student_rec),1,fptr)!=0)
	{	stu[n]=student;
		/*printf("rollno = %d\n",stu[n].rollno );
		printf("name = %s\n",stu[n].name );
		printf("age = %d\n",stu[n].age );*/
		n++;
	}

	fclose(fptr);
	printf("%d\n",n);


	for(i = 0; i < n; i++)						//outer loop	run from "0" to the "lenght" 0f array;
	{
		for(j=0; j < n; j++)					//inner loop	run from "0" to the "lenght" 0f array;
		{	if(j == n-1)						//reached the end of iteration
				break;
			if(stu[j].rollno > stu[j+1].rollno)					//if 2nd element smaller than the 1st ..  "SWAP" 
			{
				student_rec temp = stu[j];
				stu[j] = stu[j+1];
				stu[j+1] = temp;
			}


		}
	}

/*
	for(i = 0; i < n; i++)						//outer loop	run from "0" to the "lenght" 0f array;
	{
		printf("rollno = %d\n",stu[i].rollno );
		printf("name = %s\n",stu[i].name );
		printf("age = %d\n",stu[i].age );
	
	}
*/

	fptr = fopen(filename, "wb");
	
	for (i = 0; i < n; ++i)
	{
		fwrite(&stu[i],sizeof(student_rec),1,fptr);
	}

	fclose(fptr);


}


void mergeSort()
{
	int t1,t2;
	char filename1[100],filename2[100],filename[100];
	FILE *fp1,*fp2,*fp3;
	student_rec student1,student2;

	printf("%s","enter the first file name (sorted data) : ");
	scanf("%s",filename1);

	printf("%s","enter the second file name (sorted data) : ");
	scanf("%s",filename2);

	printf("%s","enter the file name to save the merged data into ?  " );
	scanf("%s",filename);

	fp1 = fopen(filename1,"rb");
	fp2 = fopen(filename2,"rb");
	fp3 = fopen(filename,"wb");

	if(fp1==NULL)
		return;
	if(fp2==NULL)
		return;
	if(fp3==NULL)
		return;

	t1 = fread(&student1,sizeof(student_rec),1,fp1);
	t2 = fread(&student2,sizeof(student_rec),1,fp2);

	while(1)
	{

		if(t1==0 && t2==0)
			break;	
		if(t1==0 && t2!=0)
		{	//printf("%s\n","i am here 1");
			fwrite(&student2,sizeof(student_rec),1,fp3);
			while(fread(&student2,sizeof(student_rec),1,fp2)!=0)
			{
				fwrite(&student2,sizeof(student_rec),1,fp3);
			}
			break;
		}
		if(t1!=0 && t2==0)
		{	//printf("%s\n","i am here 2");
			fwrite(&student1,sizeof(student_rec),1,fp3);
			while(fread(&student1,sizeof(student_rec),1,fp1)!=0)
			{
				fwrite(&student1,sizeof(student_rec),1,fp3);
			}
			break;
		}	

		if (t1!=0 && t2!=0)
		{	//printf("%s\n","i am here 3");
			if(student1.rollno<student2.rollno)
			{
				fwrite(&student1,sizeof(student_rec),1,fp3);
				fseek(fp2,-sizeof(student_rec),SEEK_CUR);
			}
			else
			{
				fwrite(&student2,sizeof(student_rec),1,fp3);
				fseek(fp1,-sizeof(student_rec),SEEK_CUR);
			}
		}	

		t1 = fread(&student1,sizeof(student_rec),1,fp1);
		t2 = fread(&student2,sizeof(student_rec),1,fp2);

	}

fclose(fp1);
fclose(fp2);
fclose(fp3);
}


void linearSearch()
{
	FILE *fp;
	char filename[100];
	student_rec student;
	int flag=0;
	int roll;

	printf("%s","enter the name of the file to linear search on ? ");
	scanf("%s",filename);
	printf("\n%s","enter the roll number to search ? ");
	scanf("%d",&roll);

	fp = fopen(filename,"rb");
	while(fread(&student,sizeof(student_rec),1,fp)!=0)
	{
		if(student.rollno == roll)
		{
			printf("rollno : %d\nname : %s\nbranch : %s\nage : %d\n________________________________\n",student.rollno,student.name,student.branch,student.age);
			flag=1;
			break;
		}

	}
	if(flag==0)
			printf("%s","not found !! __________error__________\n" );
}


void FakeData()
{
	//variables
	FILE *fp;
	char filename[75];
	int n;
	int i;
	//char names_some="abcdefghijklmnopqrstuvwxyz";
	//srand((unsigned) time(&t));
	student_rec student;


	//expressions
	printf("enter any name for File to put FAKE data into  = ");
	scanf("%s",filename);

	fp = fopen(filename,"wb");
	/*
	printf("\n%s","enter number of records you want to save = ");
	scanf("%d",&n);
	*/


	// if(fp==NULL)
	// {
	// 	printf("%s\n", "file not opened !! ");
	// 	return;
	// }

	for (i = 0; i < 10000; ++i)
	{
		student.rollno = i;

		student.name[0] = (char)(97+(rand()%26));

		student.age = (rand() % 30);

		student.branch[0] = (char)(97+(rand()%26));

		fwrite(&student,sizeof(student_rec),1,fp);
	}

fclose(fp);
}

