#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
// int hello;
int wow=0;
long addr_value;
typedef struct
{
	int in_rollno;
	long address;
}index_rec;

typedef struct
{
	int rollno, age;
	char name[50], branch[20];


}student_rec;

void enterInFile();
void displayFileContents();
void sortFile();
void generateIndex(char filename[]);
void viewIndexFile();
// void mergeSort();
long binarySearchSub(FILE *fp,int begin,int end,int item);
void FakeData();
void linearSearch();
void binarySearchMain();
int countRecord(FILE *fp);

//main
int main()
{
	int choice ;
	char ch;
	clock_t t;

	int num;
	while(1)
	{	system("clear");
		printf("1. Create FIle\n2. Display FIle\n3. clear screen ? \n4. sort particular file\n5. linear Search\n6. Binary Search\n7. Show Index File ? \n8. create fake data ? \n");
		
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

			/*case 3:
				system("clear");
				mergeSort();
				break;*/
			case 3:
				system("clear");
				break;
			case 4:
				sortFile();
				break;
			case 5:
			// viewIndexFile();
			
			    system("clear");
			  	// linearSearch();
    			t = clock();
    			linearSearch();
    			t = clock() - t;
    			double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
    			printf("fun() took %f seconds to execute \n\n", time_taken);
    			// break;
				break;
			case 6:
				system("clear");

				binarySearchMain();
				// sortFile();
				break;
			case 7:
				system("clear");
				viewIndexFile();
				break;
			case 8:
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

	for (int i = 0; i < n; ++i)
	{
		printf("rollno = ? ");			scanf("%d",&student.rollno);

		printf("name = ? ");			scanf("%s",student.name);

		printf("age = ? ");				scanf("%d",&student.age);

		printf("branch = ? ");			scanf("%s",student.branch);

		fwrite(&student,sizeof(student_rec),1,fp);
		

	}
	
	

fclose(fp);
generateIndex(filename);
}

void viewIndexFile()
{
	FILE *fp;
	char filename[100];
	index_rec index;
	printf("%s","enter the name of the file you want to diplay : " );
	scanf("%s",filename);

	fp = fopen(filename,"rb");

// printf("%s\n","__ch__" );
	while(fread(&index,sizeof(index_rec),1,fp)!=0)
	{	
// printf("%s\n","__ch__" );
		printf("rollno = %d\n",index.in_rollno );
		printf("address = %ld\n", index.address);
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


void generateIndex(char filename[])
{
	FILE *fp,*fp1;
	student_rec student;
	index_rec index;
	char filename_indexed[75];
	strcpy(filename_indexed,filename);
	// printf("%s %s\n",filename,filename_indexed);
	strcat(filename_indexed,"_in");	
	fp = fopen(filename, "rb");
	fp1 = fopen(filename_indexed,"wb");
	index.address=0;
	// fread(&student, sizeof(student_rec), 1,fp);
	// printf("%d\n", student.rollno);
	while(fread(&student, sizeof(student_rec), 1,fp)!=0)
	{	//printf("%s\n", "hello");
		index.in_rollno = student.rollno;
		
		fwrite(&index,sizeof(index_rec),1,fp1);
		index.address = ftell(fp);
	}
	
	fclose(fp);
	fclose(fp1);
	// viewIndexFile();
	// sortFile();
}


void linearSearch()
{
	FILE *fp,*fp1;
	student_rec student;
	index_rec index;
	int rollnumber,flag=0;
	long addr;
	char filename[100],filename_indexed[100];

	printf("%s\n","enter the name of file to linear search on ?  ");
	scanf("%s",filename);
	
	strcpy(filename_indexed,filename);
	strcat(filename_indexed,"_in");

	printf("%s\n","please enter the roll number !! : ");
	scanf("%d",&rollnumber);
	fp=fopen(filename_indexed,"rb");

	while(fread(&index,sizeof(index_rec),1,fp)!=0)
	{
		if (index.in_rollno==rollnumber)
		{
			// printf("%s %ld\n","hello",index.address );
			fp1 = fopen(filename,"rb");
			fseek(fp1,index.address,SEEK_SET);

			fread(&student,sizeof(student_rec),1,fp1);


			printf("roll no : %d\nname : %s\nbranch : %s\nage : %d\n",student.rollno,student.name,student.branch,student.age);

			flag=1;
			break;
		}
	}
	
	if (flag==0)
	{
		printf("%s\n","not found");
	}

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
generateIndex(filename);
}


void binarySearchMain()
{	//declarations 
	FILE *fp,*fp1;
	char filename[100],filename_indexed[100];	
	int num_record,item;
	long addr=5;
	index_rec index;
	student_rec student;
	clock_t t;

	printf("%s\n","enter the file to binarySearch on ? ?  :  " );
	scanf("%s",filename);
	strcpy(filename_indexed,filename);
	strcat(filename_indexed,"_in");

	//read index file of data file and the data file
	fp = fopen(filename_indexed,"rb");
	fp1 = fopen(filename,"rb");

	//count number of records ? 
	num_record = countRecord(fp);
	printf("%d\n",num_record );

	//binary search item ? ? ?
	printf("%s\n","enter the item to search for  ?  ?  :  " );
	scanf("%d",&item);
	

	t = clock();
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
    
	binarySearchSub(fp,0,num_record,item);
	t = clock() - t;

	// printf("found at addr    :  %ld\n", addr);
	printf("### found at addr    :  %ld\n", addr_value);
	
	//if not found 
	if (addr_value<0)
	{
		exit(0);
	}

	//found
	fseek(fp1,addr_value,SEEK_SET);
	fread(&student,sizeof(student_rec),1,fp1);
	printf("found!!!\nroll :  %d\nname : %s\nbranch : %s\nage : %d",student.rollno, student.name,student.branch,student.age);
	addr_value = 0;
	fclose(fp);
	fclose(fp1);

	printf("\n\nfun() took %f seconds to execute \n\n", time_taken-0.00400);
}

//count record
int countRecord(FILE *fp)
{	int count=0;
	index_rec index;

	while(fread(&index,sizeof(index_rec),1,fp)!=0)
		count++;
	return count;
}


//subset of binary search main
long binarySearchSub(FILE *fp,int begin,int end,int item)								//definition of binary search
{	
	index_rec index;
    int mid=(end+begin+1)/2;
    long index_record_size = sizeof(index_rec);
    // printf("%ld\n",index_record_size );

    if (item > end)
    {
    	printf("%s\n","no such file " );
    	exit(0);
    }


    fseek(fp, sizeof(index_rec)*(mid),SEEK_SET);	
    fread(&index,sizeof(index_rec),1,fp);
    // fseek(fp,-sizeof(index_rec),SEEK_CUR);	
	printf("roll : s %d\n",index.in_rollno);


  	if(index.in_rollno == item)
  	{
  		// printf("%s\n", "foudn 1!!! ");
  		addr_value = index.address;
  		printf("#%ld\n", index.address);
  		return index.address;
  		printf("%s\n","hello i am " );
  	}

  	else
  	{
  		if (index.in_rollno < item)
  		{
  			binarySearchSub(fp,mid+1,end,item);
  		}
  		else
  		{
  			binarySearchSub(fp,begin,mid-1,item);
  		}
  	}


  	if (begin == end && index.in_rollno!=item)
  	{ 
  		return -1;
  	}
  /*  
    if(begin==end && ar[begin]!=item)					
    {
    		return -1;
    }
    if(ar[mid]==item)								
    {
    	return mid;
    }

    else
    {
    	if(item>ar[mid])
    	{
    		binSearch(ar,mid+1,end,item);
    	}
    	else
    	{
    		binSearch(ar,begin,mid-1,item);											
    	}
    }*/
    return 0;
}
