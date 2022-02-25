#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "lib.h"
#include "readline.h"

#pragma warning (disable : 4996)
int n = 0;

void insert(int nCourses)//inserting the courses to the file
{
	FILE* fp;
	Course c;
	int id;

	char str[MAX_COURSES];
	char cmp;
	int num;
	fp = fopen("courses.dat", "rb+");
	fseek(fp, 0, SEEK_END);//comes to the end of the file
	printf("Enter records: \n");
	c.idc = nCourses + 1 + n;//automatically adds id for the course
	n++;
	printf("Course name: ");//adding course name
	read_line(str, COURSE_NAME + 1);
	while (!(str[0] >= 'A' && str[0] <= 'Z'))
	{
		printf("Wrong input. Start with a UpperCase Letter!\n");
		printf("Course name: ");//adding course name
		read_line(str, COURSE_NAME + 1);
	}
	strcpy(c.name, str);
	printf("Subject name: ");//adding subject
	read_line(str, COURSE_SUBJECT + 1);
	while (!(str[0] >= 'A' && str[0] <= 'Z'))
	{
		printf("Wrong input. Start with a UpperCase Letter!\n");
		printf("Subject name: ");//adding subject
		read_line(str, COURSE_SUBJECT + 1);
	}
	strcpy(c.subject, str);
	printf("Room: ");//adding room
	read_line(str, ROOM_NUMBER + 1);
	while (!(str[0] >= 'A' && str[0] <= 'Z'))
	{
		printf("Wrong input. Start with an UpperCase Letter!\n");
		printf("Room: ");//adding room
		read_line(str, ROOM_NUMBER + 1);
	}
	strcpy(c.room, str);
	printf("Course CRN: ");//adding crn
	read_line(str, N);
	while (!(num = atoi(str)))
	{
		printf("Wrong input. Enter a correct number!\n");
		printf("Course CRN: ");//adding crn
		read_line(str, N);
	}
	strcpy(c.crn, str);
	printf("Credit Hours: ");//adding credit hours
	read_line(str, N);
	while (!(num = atoi(str)))
	{
		printf("Wrong input. Enter a correct number!\n");
		printf("Credit Hours: ");//adding credit hours
		read_line(str, N);
	}
	strcpy(c.credithours, str);
	printf("Instructor name: ");
	read_line(str, INST_NAME + 1);//reads 
	while (!(str[0] >= 'A' && str[0] <= 'Z'))
	{
		printf("Wrong input. Start with an UpperCase Letter!\n");
		printf("Instructor name: ");
		read_line(str, INST_NAME + 1);
	}
	strcpy(c.inst.name, str);
	printf("Instructor surname: ");
	read_line(str, INST_SURNAME + 1);
	while (!(str[0] >= 'A' && str[0] <= 'Z'))
	{
		printf("Wrong input. Start with a UpperCase Letter!\n");
		printf("Instructor surname: ");
		read_line(str, INST_SURNAME + 1);
	}
	strcpy(c.inst.surname, str);

	fwrite(&c, sizeof(Course), 1, fp);//writes struct to the file
	nCourses++;
	fclose(fp);//closes the file
	print(nCourses);//prints the file
}
void print(int nCourses)//prints records inside file 
{
	FILE* fp;
	fp = fopen("courses.dat", "rb");//opens file for reading
	Course* a = (Course*)malloc(5 * sizeof(Course));//allocating memory

	printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
	printf("|  ID  |        Course Name       |       Course Subject       | Instructor Name | Instructor Surname | Room |   CRN  | Credit Hours |\n");
	printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
	while (1)
	{
		fread(a, sizeof(Course), 1, fp);//reads from file
		if (feof(fp) != 0)
			break;
		printf("|%6d|%26s|%28s|%17s|%20s|%6s|%8s|%14s|\n",
			a->idc, a->name, a->subject, a->inst.name, a->inst.surname, a->room, a->crn, a->credithours);
	printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");

	}
	fclose(fp);//closes file
}
void search(int nCourses)//search for courses based on id
{
	FILE* fp;
	fp = fopen("courses.dat", "rb");

	Course a;
	int code;
	int id, n;
	char name[COURSE_NAME], subject[COURSE_SUBJECT], iName[INST_NAME], iSurname[INST_SURNAME], crn[N], ch[N], room[N];
	printf("1: ID | 2: Name | 3: Subject | 4: Instructor name | 5: Instructor Surname | 6: CRN | 7: Credit Hours | 8: Room\n");
	printf("Choose one to search: ");
	scanf("%d", &code);

	while (code < 1 && code > 8)// checks whether the input is correct 
	{
		printf("Enter a correct code!\n");
		scanf("%d", &code);
	}
	if (code == 1)
	{
		printf("Enter the Course ID: ");//finds based on id
		scanf("%d", &id);
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		printf("|  ID  |        Course Name       |       Course Subject       | Instructor Name | Instructor Surname | Room |   CRN  | Credit Hours |\n");
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		while (!feof(fp))
		{
			fread(&a, sizeof(Course), 1, fp);
			if ((id == a.idc))
			{
				printf("|%6d|%26s|%28s|%17s|%20s|%6s|%8s|%14s|\n",
					a.idc, a.name, a.subject, a.inst.name, a.inst.surname, a.room, a.crn, a.credithours);
				printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
			}
		}
		n = courseID(id, nCourses);
		if (n < 0)	printf("Course not found");//checks whether the ID exist

	}
	if (code == 2)
	{
		printf("Enter the Course Name: ");//checks based on name
		read_line(name, COURSE_NAME);
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		printf("|  ID  |        Course Name       |       Course Subject       | Instructor Name | Instructor Surname | Room |   CRN  | Credit Hours |\n");
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		while (!feof(fp))
		{
			fread(&a, sizeof(Course), 1, fp);
			if (!strcmp(name, a.name))//checks whether input is equal to the strufct name
			{
				printf("|%6d|%26s|%28s|%17s|%20s|%6s|%8s|%14s|\n",
					a.idc, a.name, a.subject, a.inst.name, a.inst.surname, a.room, a.crn, a.credithours);
				printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
			}
		}
		n = courseName(name, nCourses);
		if (n < 0)	printf("Course not found");
	}
	if (code == 3)
	{
		printf("Enter the Course Subject: ");
		read_line(subject, COURSE_SUBJECT);
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		printf("|  ID  |        Course Name       |       Course Subject       | Instructor Name | Instructor Surname | Room |   CRN  | Credit Hours |\n");
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		while (!feof(fp))
		{
			fread(&a, sizeof(Course), 1, fp);
			if (!strcmp(subject, a.subject))//checks based on subject
			{
				printf("|%6d|%26s|%28s|%17s|%20s|%6s|%8s|%14s|\n",
					a.idc, a.name, a.subject, a.inst.name, a.inst.surname, a.room, a.crn, a.credithours);
				printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
			}
		}
		n = courseSubject(subject, nCourses);
		if (n < 0)	printf("Course not found");
	}
	if (code == 4)
	{
		printf("Enter the Instructor Name: ");
		read_line(iName, INST_NAME);
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		printf("|  ID  |        Course Name       |       Course Subject       | Instructor Name | Instructor Surname | Room |   CRN  | Credit Hours |\n");
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		while (!feof(fp))
		{
			fread(&a, sizeof(Course), 1, fp);//checks based on instructor name
			if (!strcmp(iName, a.inst.name))
			{
				printf("|%6d|%26s|%28s|%17s|%20s|%6s|%8s|%14s|\n",
					a.idc, a.name, a.subject, a.inst.name, a.inst.surname, a.room, a.crn, a.credithours);
				printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
			}
		}
		n = courseIName(iName, nCourses);
		if (n < 0)	printf("Course not found");
	}
	if (code == 5)
	{
		printf("Enter Instructor Surname: ");
		read_line(iSurname, INST_SURNAME);
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		printf("|  ID  |        Course Name       |       Course Subject       | Instructor Name | Instructor Surname | Room |   CRN  | Credit Hours |\n");
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		while (!feof(fp))
		{
			fread(&a, sizeof(Course), 1, fp);
			if (!strcmp(iSurname, a.inst.surname))//checks based on instructor surname
			{
				printf("|%6d|%26s|%28s|%17s|%20s|%6s|%8s|%14s|\n",
					a.idc, a.name, a.subject, a.inst.name, a.inst.surname, a.room, a.crn, a.credithours);
				printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
			}
		}
		n = courseISurname(iSurname, nCourses);
		if (n < 0)	printf("Course not found");
	}
	if (code == 6)
	{
		printf("Enter Course CRN: ");
		read_line(crn, N);
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		printf("|  ID  |        Course Name       |       Course Subject       | Instructor Name | Instructor Surname | Room |   CRN  | Credit Hours |\n");
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		while (!feof(fp))
		{
			fread(&a, sizeof(Course), 1, fp);
			if (!strcmp(crn, a.crn))
			{
				printf("|%6d|%26s|%28s|%17s|%20s|%6s|%8s|%14s|\n",
					a.idc, a.name, a.subject, a.inst.name, a.inst.surname, a.room, a.crn, a.credithours);
				printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
			}
		}
		n = courseCRN(crn, nCourses);
		if (n < 0)	printf("Course not found");
	}
	if (code == 7)
	{
		printf("Enter Course Credit Hours: ");
		read_line(ch, N);
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		printf("|  ID  |        Course Name       |       Course Subject       | Instructor Name | Instructor Surname | Room |   CRN  | Credit Hours |\n");
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		while (!feof(fp))
		{
			fread(&a, sizeof(Course), 1, fp);
			if (!strcmp(ch, a.credithours))
			{
				printf("|%6d|%26s|%28s|%17s|%20s|%6s|%8s|%14s|\n",
					a.idc, a.name, a.subject, a.inst.name, a.inst.surname, a.room, a.crn, a.credithours);
				printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
			}
		}
		n = courseCreditHours(ch, nCourses);
		if (n < 0)	printf("Course not found");
	}
	if (code == 8)
	{
		printf("Enter Course Room: ");
		read_line(room, ROOM_NUMBER);
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		printf("|  ID  |        Course Name       |       Course Subject       | Instructor Name | Instructor Surname | Room |   CRN  | Credit Hours |\n");
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		while (!feof(fp))
		{
			fread(&a, sizeof(Course), 1, fp);
			if (!strcmp(room, a.room))
			{
				printf("|%6d|%26s|%28s|%17s|%20s|%6s|%8s|%14s|\n",
					a.idc, a.name, a.subject, a.inst.name, a.inst.surname, a.room, a.crn, a.credithours);
				printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
			}
		}
		n = courseRoom(room, nCourses);
		if (n < 0)	printf("Course not found");
	}
}
void update(int nCourses)
{
	int id, n, choose;
	Course c;
	FILE* fp = fopen("courses.dat", "rb+");
	printf("Enter ID of the course you want to update: ");
	scanf("%d", &id);
	n = courseID(id, nCourses);
	if (n >= 0)
	{
		printf("| 1: Name | 2: Subject | 3: Instructor Name | 4: Instructor Surname | 5: CRN | 6: Room | 7: Credit Hours |\n");
		scanf("%d", &choose);
		while ((choose < 1 && choose > 7))//checks the validity of input
		{
			printf("Enter number between 1 and 7 ");
			scanf("%d", &choose);
		}
		char str[MAX_COURSES];

		if (choose == 1)//changes the name
		{
			printf("Enter new Name: ");
			read_line(str, COURSE_NAME);
			fseek(fp, (sizeof(Course) * n) + N, 1, SEEK_SET);// looks for the course name inside the file
			fwrite(&str, COURSE_NAME, 1, fp);
		}
		if (choose == 2)//changes the surname
		{
			printf("Enter new Subject: ");
			read_line(str, COURSE_SUBJECT);
			fseek(fp, (sizeof(Course) * n) + COURSE_NAME + N, 1, SEEK_SET);
			fwrite(&str, COURSE_SUBJECT, 1, fp);
		}
		if (choose == 3)// changes the instructor name
		{
			printf("Enter new Instructor Name: ");
			read_line(str, INST_NAME);
			fseek(fp, (sizeof(Course) * n) + COURSE_NAME + COURSE_SUBJECT + N + ROOM_NUMBER + N, 1, SEEK_SET);
			fwrite(&str, INST_NAME, 1, fp);//writes the name instructor name to the file
		}
		if (choose == 4)
		{
			printf("Enter new Instructor Surname: ");
			read_line(str, INST_SURNAME);
			fseek(fp, (sizeof(Course) * n) + COURSE_NAME + COURSE_SUBJECT + N + N + ROOM_NUMBER + INST_NAME, 1, SEEK_SET);
			fwrite(&str, INST_SURNAME, 1, fp);
		}
		if (choose == 5)
		{
			printf("Enter new CRN: ");
			read_line(str, N);
			fseek(fp, (sizeof(Course) * n), 1, SEEK_SET);
			fwrite(&str, N, 1, fp);
		}
		if (choose == 6)
		{
			printf("Enter new Room: ");
			read_line(str, ROOM_NUMBER);
			fseek(fp, (sizeof(Course) * n) + COURSE_NAME + COURSE_SUBJECT + N, 1, SEEK_SET);
			fwrite(&str, ROOM_NUMBER, 1, fp);
		}
		if (choose == 7)
		{
			printf("Enter new Credit Hours: ");
			read_line(str, N);
			fseek(fp, (sizeof(Course) * n) + COURSE_NAME + COURSE_SUBJECT + N + ROOM_NUMBER, 1, SEEK_SET);
			fwrite(&str, N, 1, fp);//changes the credit hours for the course
		}
	}
	else
		printf("Course not found...\n");
	fclose(fp);
	print(nCourses);
}
void delete(void)
{
	FILE* fp;
	FILE* fp_tmp;//creates 2 file 
	int nid = 0;
	Course c;
	int id;

	fp = fopen("courses.dat", "rb");
	fp_tmp = fopen("tmp.dat", "wb");
	printf("Enter ID of the course you want to delete: ");
	scanf("%d", &id);//finding the id of the record we want to delete

	while (fread(&c, sizeof(Course), 1, fp))
	{
		if (id == c.idc)// if the input is equal to the record's id
		{
			nid = 1;
		}
		else
		{
			fwrite(&c, sizeof(Course), 1, fp_tmp);
		}
	}
	if (!nid) {
		printf("No record found ID: %d\n\n", id);//if there is no such ID
	}

	fclose(fp);
	fclose(fp_tmp);//closes the file

	remove("courses.dat");
	rename("tmp.dat", "courses.dat");
	return 0;
}

int courseID(int n, int nCourses)//finds the course id
{
	FILE* fp;
	fp = fopen("courses.dat", "rb");
	Course* arr = malloc(sizeof(Course) * nCourses);

	for (int i = 0; i < nCourses; i++)
	{
		fread(arr, sizeof(Course), 1, fp);
		if (n == arr->idc)
			return i;
	}
	fclose(fp);
	free(arr);
	arr = NULL;
	return -1;
}
int courseName(char name[COURSE_NAME], int nCourses)//finds the course name
{
	FILE* fp = fopen("courses.dat", "rb");
	Course* arr = (Course*)malloc(sizeof(Course) * nCourses);

	for (int i = 0; i < nCourses; i++)
	{
		fread(arr, sizeof(Course), 1, fp);
		if (strcmp(arr->name, name))
			return i;
	}
	fclose(fp);
	free(arr);
	arr = NULL;
	return -1;
}
int courseSubject(char subject[COURSE_SUBJECT], int nCourses)//finds the course subject
{
	FILE* fp = fopen("courses.dat", "rb");
	Course* arr = (Course*)malloc(sizeof(Course) * nCourses);

	for (int i = 0; i < nCourses; i++)
	{
		fread(arr, sizeof(Course), 1, fp);
		if (!(strcmp(arr->subject, subject)))
			return i;
	}
	fclose(fp);
	free(arr);
	arr = NULL;
	return -1;
}
int courseIName(char iName[INST_NAME], int nCourses)
{
	FILE* fp = fopen("courses.dat", "rb");
	Course* arr = (Course*)malloc(sizeof(Course) * nCourses);

	for (int i = 0; i < nCourses; i++)
	{
		fread(arr, sizeof(Course), 1, fp);
		if (!strcmp(arr->inst.name, iName))
			return i;
	}
	fclose(fp);
	free(arr);
	arr = NULL;
	return -1;
}
int courseISurname(char iSurname[INST_SURNAME], int nCourses)
{
	FILE* fp = fopen("courses.dat", "rb");
	Course* arr = (Course*)malloc(sizeof(Course) * nCourses);

	for (int i = 0; i < nCourses; i++)
	{
		fread(arr, sizeof(Course), 1, fp);
		if (!strcmp(arr->inst.surname, iSurname))
			return i;
	}
	fclose(fp);
	free(arr);
	arr = NULL;
	return -1;
}
int courseCRN(char crn[N], int nCourses)
{
	FILE* fp = fopen("courses.dat", "rb");
	Course* arr = (Course*)malloc(sizeof(Course) * nCourses);

	for (int i = 0; i < nCourses; i++)
	{
		fread(arr, sizeof(Course), 1, fp);
		if (!strcmp(arr->crn, crn))
			return i;
	}
	fclose(fp);
	free(arr);
	arr = NULL;
	return -1;
}
int courseRoom(char room[N], int nCourses)
{
	FILE* fp = fopen("courses.dat", "rb");
	Course* arr = (Course*)malloc(sizeof(Course) * nCourses);

	for (int i = 0; i < nCourses; i++)
	{
		fread(arr, sizeof(Course), 1, fp);
		if (!strcmp(arr->room, room))
			return i;
	}
	fclose(fp);
	free(arr);
	arr = NULL;
	return -1;
}
int courseCreditHours(char ch[N], int nCourses)
{
	FILE* fp = fopen("courses.dat", "rb");
	Course* arr = (Course*)malloc(sizeof(Course) * nCourses);

	for (int i = 0; i < nCourses; i++)
	{
		fread(arr, sizeof(Course), 1, fp);
		if (!strcmp(arr->credithours, ch))
			return i;
	}
	fclose(fp);
	free(arr);
	arr = NULL;
	return -1;
}

int comparename(const void* a, const void* b)
{
	return strcmp(((Course*)a)->name, ((Course*)b)->name);
}
int comparesub(const void* a, const void* b)
{
	return strcmp(((Course*)a)->subject, ((Course*)b)->subject);
}
int compareinstN(const void* a, const void* b)
{
	return strcmp(((Course*)a)->inst.name, ((Course*)b)->inst.surname);
}
int compareinstS(const void* a, const void* b)
{
	return strcmp(((Course*)a)->inst.surname, ((Course*)b)->inst.surname);
}
int compareCRN(const void* a, const void* b)
{
	return strcmp(((Course*)a)->crn, ((Course*)b)->crn);
}
int compareID(const void* a, const void* b)
{

	return strcmp(((Course*)a)->idc, ((Course*)b)->idc);
}
int compareCH(const void* a, const void* b)
{
	return strcmp(((Course*)a)->credithours, ((Course*)b)->credithours);
}
int compareRooms(const void* a, const void* b)
{
	return strcmp(((Course*)a)->room, ((Course*)b)->room);
}

void sort(int nCourses)//sorting courses
{
	printf("|---------+------------+--------------------+-----------------------+--------+-----------------+--- -----|\n");
	printf("|   Based on which attribute you want to sort?                                                           |\n");
	printf("| 1: Name | 2: Subject | 3: Instructor name | 4: Instructor Surname | 5: CRN | 6: Credit Hours | 7: Room |\n");
	printf("|                                                                                                        |\n");
	printf("|---------+------------+--------------------+-----------------------+--------+-----------------+---------|\n");
	int id;
	scanf("%d", &id);
	FILE* fp;
	fp = fopen("courses.dat", "rb");
	Course arr[MAX_COURSES];

	for (int i = 0; i < nCourses; i++)
		fread(arr + i, sizeof(Course), 1, fp);//reading from file
	switch (id) {
	case 1: qsort(arr, nCourses, sizeof(Course), comparename);//sorting based on name
		break;
	case 2: qsort(arr, nCourses, sizeof(Course), comparesub);//sorting based on subject
		break;
	case 3: qsort(arr, nCourses, sizeof(Course), compareinstN);//sorting based on instructor name
		break;
	case 4: qsort(arr, nCourses, sizeof(Course), compareinstS);//sorting based on instructor surname
		break;
	case 5: qsort(arr, nCourses, sizeof(Course), compareCRN);//sorting based on crn
		break;
	case 6: qsort(arr, nCourses, sizeof(Course), compareCH);//sorting based on credit hours
		break;
	case 7: qsort(arr, nCourses, sizeof(Course), compareRooms);//sorting based on room
		break;
	}

	printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
	printf("|  ID  |        Course Name       |       Course Subject       | Instructor Name | Instructor Surname | Room |   CRN  | Credit Hours |\n");
	printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
	for (int i = 0; i < nCourses; i++)
	{
		printf("|%6d|%26s|%28s|%17s|%20s|%6s|%8s|%14s|\n",
			arr[i].idc, arr[i].name, arr[i].subject, arr[i].inst.name, arr[i].inst.surname, arr[i].room, arr[i].crn, arr[i].credithours);
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
	}
}


void filter(int nCourses)
{
	FILE* fp;
	fp = fopen("courses.dat", "rb");

	Course a;
	int code;
	int id, n;
	//char str[MAX_COURSES];
	char name[COURSE_NAME], subject[COURSE_SUBJECT], iName[INST_NAME], iSurname[INST_SURNAME], crn[N], ch[N], room[ROOM_NUMBER];
	printf("| ID | Name |  Subject  | Instructor name | Instructor Surname | Room | CRN | Credit Hours |\n");
	printf("|---------------------------------------------------------------------------------------------------------|\n");
	printf("| 1:  Filter based on Name and Subject:                                                                   |\n");
	printf("| 2:  Filter based on Name and Subject and Instructor Name:                                               |\n");
	printf("| 3:  Filter based on Name and Subject and Instructor Name and Surname:                                   |\n");
	printf("| 4:  Filter based on Name and Subject and Instructor Name and Surname and Room:                          |\n");
	printf("| 5:  Filter based on Name and Subject and Instructor Name and Surname and Room and CRN:                  |\n");
	printf("| 6:  Filter based on Name and Subject and Instructor Name and Surname and Room and CRN and Credit Hours: |\n");
	printf("|                                                                                                         |\n");
	printf("| 7:  Filter based on Name and Instructor Name:                                                           |\n");
	printf("| 8:  Filter based on Name and Instructor Name and Surname:                                               |\n");
	printf("| 9:  Filter based on Name and Instructor Name and Surname and Room:                                      |\n");
	printf("| 10: Filter based on Name and Instructor Name and Surname and Room and CRN:                              |\n");
	printf("| 11: Filter based on Name and Instructor Name and Surname and Room and CRN and Credit Hours:             |\n");
	printf("|                                                                                                         |\n");
	printf("| 12: Filter based on Name and Instructor Surname:                                                        |\n");
	printf("| 13: Filter based on Name and Instructor Surname and Room:                                               |\n");
	printf("| 14: Filter based on Name and Instructor Surname and Room and CRN:                                       |\n");
	printf("| 15: Filter based on Name and Instructor Surname and Room and CRN and Credit Hours:                      |\n");
	printf("|                                                                                                         |\n");
	printf("| 16: Filter based on Name and Room:                                                                      |\n");
	printf("| 17: Filter based on Name and Room and CRN:                                                              |\n");
	printf("| 18: Filter based on Name and Room and CRN and Credit Hours:                                             |\n");
	printf("|                                                                                                         |\n");
	printf("| 19: Filter based on Name and CRN:                                                                       |\n");
	printf("| 20: Filter based on Name and CRN and Credit Hours:                                                      |\n");
	printf("|                                                                                                         |\n");
	printf("| 21: Filter based on Name and Credit Hours:                                                              |\n");
	printf("|---------------------------------------------------------------------------------------------------------|\n");
	printf("| 22: Filter based on Subject and Instructor Name:                                                        |\n");
	printf("| 23: Filter based on Subject and Instructor Name and Surname:                                            |\n");
	printf("| 24: Filter based on Subject and Instructor Name and Surname and Room:                                   |\n");
	printf("| 25: Filter based on Subject and Instructor Name and Surname and Room and CRN:                           |\n");
	printf("| 26: Filter based on Subject and Instructor Name and Surname and Room and CRN and Credit Hours:          |\n");
	printf("|                                                                                                         |\n");
	printf("| 27: Filter based on Subject and Instructor Surname:                                                     |\n");
	printf("| 28: Filter based on Subject and Instructor Surname and Room:                                            |\n");
	printf("| 29: Filter based on Subject and Instructor Surname and Room and CRN:                                    |\n");
	printf("| 30: Filter based on Subject and Instructor Surname and Room and CRN and Credit Hours:                   |\n");
	printf("|                                                                                                         |\n");
	printf("| 31: Filter based on Subject and Room:                                                                   |\n");
	printf("| 32: Filter based on Subject and Room and CRN:                                                           |\n");
	printf("|---------------------------------------------------------------------------------------------------------|\n\n");



	printf("Choose one to filter: ");
	scanf("%d", &code);
	while (code < 1 || code > 32)// checks whether the input is correct 
	{
		printf("Enter a correct code!\n");
		scanf("%d", &code);
	}

	if (code == 1)
	{
		printf("Enter Name of the Course: ");
		read_line(name, COURSE_NAME);
		printf("Enter Subject of the Course: ");
		read_line(subject, COURSE_SUBJECT);
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		printf("|  ID  |        Course Name       |       Course Subject       | Instructor Name | Instructor Surname | Room |   CRN  | Credit Hours |\n");
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		while (!feof(fp))
		{
			fread(&a, sizeof(Course), 1, fp);
			if (!strcmp(name, a.name) && !strcmp(subject, a.subject))//checks whether input is equal to the struct name
			{
				printf("|%6d|%26s|%28s|%17s|%20s|%6s|%8s|%14s|\n",
					a.idc, a.name, a.subject, a.inst.name, a.inst.surname, a.room, a.crn, a.credithours);
				printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
			}
		}
	}
	if (code == 2)
	{
		printf("Enter Name of the Course: ");
		read_line(name, COURSE_NAME);
		printf("Enter Subject of the Course: ");
		read_line(subject, COURSE_SUBJECT);
		printf("Enter Instructor of the Course: ");
		read_line(iName, INST_NAME);
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		printf("|  ID  |        Course Name       |       Course Subject       | Instructor Name | Instructor Surname | Room |   CRN  | Credit Hours |\n");
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		while (!feof(fp))
		{
			fread(&a, sizeof(Course), 1, fp);
			if (!strcmp(name, a.name) && !strcmp(subject, a.subject) && !strcmp(iName, a.inst.name))//checks whether input is equal to the struct name
			{
				printf("|%6d|%26s|%28s|%17s|%20s|%6s|%8s|%14s|\n",
					a.idc, a.name, a.subject, a.inst.name, a.inst.surname, a.room, a.crn, a.credithours);
				printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
			}
		}
	}
	if (code == 3)
	{
		printf("Enter Name of the Course: ");
		read_line(name, COURSE_NAME);
		printf("Enter Subject of the Course: ");
		read_line(subject, COURSE_SUBJECT);
		printf("Enter Instructor of the Course: ");
		read_line(iName, INST_NAME);
		printf("Enter Surname of the Instructor: ");
		read_line(iSurname, INST_SURNAME);
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		printf("|  ID  |        Course Name       |       Course Subject       | Instructor Name | Instructor Surname | Room |   CRN  | Credit Hours |\n");
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		while (!feof(fp))
		{
			fread(&a, sizeof(Course), 1, fp);
			if (!strcmp(name, a.name) && !strcmp(subject, a.subject) && !strcmp(iName, a.inst.name) && !strcmp(iSurname, a.inst.surname))
			{
				printf("|%6d|%26s|%28s|%17s|%20s|%6s|%8s|%14s|\n",
					a.idc, a.name, a.subject, a.inst.name, a.inst.surname, a.room, a.crn, a.credithours);
				printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
			}
		}
	}
	if (code == 4)
	{
		printf("Enter Name of the Course: ");
		read_line(name, COURSE_NAME);
		printf("Enter Subject of the Course: ");
		read_line(subject, COURSE_SUBJECT);
		printf("Enter Instructor of the Course: ");
		read_line(iName, INST_NAME);
		printf("Enter Surname of the Instructor: ");
		read_line(iSurname, INST_SURNAME);
		printf("Enter Room: ");
		read_line(room, ROOM_NUMBER);
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		printf("|  ID  |        Course Name       |       Course Subject       | Instructor Name | Instructor Surname | Room |   CRN  | Credit Hours |\n");
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		while (!feof(fp))
		{
			fread(&a, sizeof(Course), 1, fp);
			if (!strcmp(name, a.name) && !strcmp(subject, a.subject) && !strcmp(iName, a.inst.name) && !strcmp(iSurname, a.inst.surname) && !strcmp(room, a.room))
			{
				printf("|%6d|%26s|%28s|%17s|%20s|%6s|%8s|%14s|\n",
					a.idc, a.name, a.subject, a.inst.name, a.inst.surname, a.room, a.crn, a.credithours);
				printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
			}
		}
	}
	if (code == 5)
	{
		printf("Enter Name of the Course: ");
		read_line(name, COURSE_NAME);
		printf("Enter Subject of the Course: ");
		read_line(subject, COURSE_SUBJECT);
		printf("Enter Instructor of the Course: ");
		read_line(iName, INST_NAME);
		printf("Enter Surname of the Instructor: ");
		read_line(iSurname, INST_SURNAME);
		printf("Enter Room: ");
		read_line(room, ROOM_NUMBER);
		printf("Enter CRN: ");
		read_line(crn, N);
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		printf("|  ID  |        Course Name       |       Course Subject       | Instructor Name | Instructor Surname | Room |   CRN  | Credit Hours |\n");
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		while (!feof(fp))
		{
			fread(&a, sizeof(Course), 1, fp);
			if (!strcmp(name, a.name) && !strcmp(subject, a.subject) && !strcmp(iName, a.inst.name) && !strcmp(iSurname, a.inst.surname) && !strcmp(room, a.room) && !strcmp(crn, a.crn))
			{
				printf("|%6d|%26s|%28s|%17s|%20s|%6s|%8s|%14s|\n",
					a.idc, a.name, a.subject, a.inst.name, a.inst.surname, a.room, a.crn, a.credithours);
				printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
			}
		}
	}
	if (code == 6)
	{
		printf("Enter Name of the Course: ");
		read_line(name, COURSE_NAME);
		printf("Enter Subject of the Course: ");
		read_line(subject, COURSE_SUBJECT);
		printf("Enter Instructor of the Course: ");
		read_line(iName, INST_NAME);
		printf("Enter Surname of the Instructor: ");
		read_line(iSurname, INST_SURNAME);
		printf("Enter Room: ");
		read_line(room, ROOM_NUMBER);
		printf("Enter CRN: ");
		read_line(crn, N);
		printf("Enter Credit Hours: ");
		read_line(ch, N);
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		printf("|  ID  |        Course Name       |       Course Subject       | Instructor Name | Instructor Surname | Room |   CRN  | Credit Hours |\n");
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		while (!feof(fp))
		{
			fread(&a, sizeof(Course), 1, fp);
			if (!strcmp(name, a.name) && !strcmp(subject, a.subject) && !strcmp(iName, a.inst.name) && !strcmp(iSurname, a.inst.surname) && !strcmp(room, a.room) && !strcmp(crn, a.crn) && !strcmp(ch, a.credithours))
			{
				printf("|%6d|%26s|%28s|%17s|%20s|%6s|%8s|%14s|\n",
					a.idc, a.name, a.subject, a.inst.name, a.inst.surname, a.room, a.crn, a.credithours);
				printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
			}
		}
	}
	if (code == 7)
	{
		printf("Enter Name of the Course: ");
		read_line(name, COURSE_NAME);
		printf("Enter Name of the Instructor: ");
		read_line(iName, INST_NAME);
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		printf("|  ID  |        Course Name       |       Course Subject       | Instructor Name | Instructor Surname | Room |   CRN  | Credit Hours |\n");
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");;
		while (!feof(fp))
		{
			fread(&a, sizeof(Course), 1, fp);
			if (!strcmp(name, a.name) && !strcmp(iName, a.inst.name))//checks whether input is equal to the struct name
			{
				printf("|%6d|%26s|%28s|%17s|%20s|%6s|%8s|%14s|\n",
					a.idc, a.name, a.subject, a.inst.name, a.inst.surname, a.room, a.crn, a.credithours);
				printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
			}
		}
	}
	if (code == 8)
	{
		printf("Enter Name of the Course: ");
		read_line(name, COURSE_NAME);
		printf("Enter Name of the Instructor: ");
		read_line(iName, INST_NAME);
		printf("Enter Surname of the Instructor: ");
		read_line(iSurname, INST_SURNAME);
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		printf("|  ID  |        Course Name       |       Course Subject       | Instructor Name | Instructor Surname | Room |   CRN  | Credit Hours |\n");
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		while (!feof(fp))
		{
			fread(&a, sizeof(Course), 1, fp);
			if (!strcmp(name, a.name) && !strcmp(iName, a.inst.name) && !strcmp(iSurname, a.inst.surname))//checks whether input is equal to the struct name
			{
				printf("|%6d|%26s|%28s|%17s|%20s|%6s|%8s|%14s|\n",
					a.idc, a.name, a.subject, a.inst.name, a.inst.surname, a.room, a.crn, a.credithours);
				printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
			}
		}
	}
	if (code == 9)
	{
		printf("Enter Name of the Course: ");
		read_line(name, COURSE_NAME);
		printf("Enter Name of the Instructor: ");
		read_line(iName, INST_NAME);
		printf("Enter Surname of the Instructor: ");
		read_line(iSurname, INST_SURNAME);
		printf("Enter Room: ");
		read_line(room, ROOM_NUMBER);
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		printf("|  ID  |        Course Name       |       Course Subject       | Instructor Name | Instructor Surname | Room |   CRN  | Credit Hours |\n");
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		while (!feof(fp))
		{
			fread(&a, sizeof(Course), 1, fp);
			if (!strcmp(name, a.name) && !strcmp(iName, a.inst.name) && !strcmp(iSurname, a.inst.surname) && !strcmp(room, a.room))
			{
				printf("|%6d|%26s|%28s|%17s|%20s|%6s|%8s|%14s|\n",
					a.idc, a.name, a.subject, a.inst.name, a.inst.surname, a.room, a.crn, a.credithours);
				printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
			}
		}
	}
	if (code == 10)
	{
		printf("Enter Name of the Course: ");
		read_line(name, COURSE_NAME);
		printf("Enter Name of the Instructor: ");
		read_line(iName, INST_NAME);
		printf("Enter Surname of the Instructor: ");
		read_line(iSurname, INST_SURNAME);
		printf("Enter Room: ");
		read_line(room, ROOM_NUMBER);
		printf("Enter CRN: ");
		read_line(crn, N);
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		printf("|  ID  |        Course Name       |       Course Subject       | Instructor Name | Instructor Surname | Room |   CRN  | Credit Hours |\n");
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		while (!feof(fp))
		{
			fread(&a, sizeof(Course), 1, fp);
			if (!strcmp(name, a.name) && !strcmp(iName, a.inst.name) && !strcmp(iSurname, a.inst.surname) && !strcmp(room, a.room) && !strcmp(crn, a.credithours))
			{
				printf("|%6d|%26s|%28s|%17s|%20s|%6s|%8s|%14s|\n",
					a.idc, a.name, a.subject, a.inst.name, a.inst.surname, a.room, a.crn, a.credithours);
				printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
			}
		}
	}
	if (code == 11)
	{
		printf("Enter Name of the Course: ");
		read_line(name, COURSE_NAME);
		printf("Enter Name of the Instructor: ");
		read_line(iName, INST_NAME);
		printf("Enter Surname of the Instructor: ");
		read_line(iSurname, INST_SURNAME);
		printf("Enter Room: ");
		read_line(room, ROOM_NUMBER);
		printf("Enter CRN: ");
		read_line(crn, N);
		printf("Enter Credit Hours: ");
		read_line(ch, N);
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		printf("|  ID  |        Course Name       |       Course Subject       | Instructor Name | Instructor Surname | Room |   CRN  | Credit Hours |\n");
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		while (!feof(fp))
		{
			fread(&a, sizeof(Course), 1, fp);
			if (!strcmp(name, a.name) && !strcmp(iName, a.inst.name) && !strcmp(iSurname, a.inst.surname) && !strcmp(room, a.room) && !strcmp(crn, a.crn) && !strcmp(ch, a.credithours))
			{
				printf("|%6d|%26s|%28s|%17s|%20s|%6s|%8s|%14s|\n",
					a.idc, a.name, a.subject, a.inst.name, a.inst.surname, a.room, a.crn, a.credithours);
				printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
			}
		}
	}
	if (code == 12)
	{
		printf("Enter Name of the Course: ");
		read_line(name, COURSE_NAME);
		printf("Enter Surname of the Instructor: ");
		read_line(iSurname, INST_SURNAME);
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		printf("|  ID  |        Course Name       |       Course Subject       | Instructor Name | Instructor Surname | Room |   CRN  | Credit Hours |\n");
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		while (!feof(fp))
		{
			fread(&a, sizeof(Course), 1, fp);
			if (!strcmp(name, a.name) && !strcmp(iSurname, a.inst.surname))
			{
				printf("|%6d|%26s|%28s|%17s|%20s|%6s|%8s|%14s|\n",
					a.idc, a.name, a.subject, a.inst.name, a.inst.surname, a.room, a.crn, a.credithours);
				printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
			}
		}
	}
	if (code == 13)
	{
		printf("Enter Name of the Course: ");
		read_line(name, COURSE_NAME);
		printf("Enter Surname of the Instructor: ");
		read_line(iSurname, INST_SURNAME);
		printf("Enter Room: ");
		read_line(room, ROOM_NUMBER);
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		printf("|  ID  |        Course Name       |       Course Subject       | Instructor Name | Instructor Surname | Room |   CRN  | Credit Hours |\n");
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		while (!feof(fp))
		{
			fread(&a, sizeof(Course), 1, fp);
			if (!strcmp(name, a.name) && !strcmp(iSurname, a.inst.surname) && !strcmp(room, a.room))
			{
				printf("|%6d|%26s|%28s|%17s|%20s|%6s|%8s|%14s|\n",
					a.idc, a.name, a.subject, a.inst.name, a.inst.surname, a.room, a.crn, a.credithours);
				printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
			}
		}
	}
	if (code == 14)
	{
		printf("Enter Name of the Course: ");
		read_line(name, COURSE_NAME);
		printf("Enter Surname of the Instructor: ");
		read_line(iSurname, INST_SURNAME);
		printf("Enter Room: ");
		read_line(room, ROOM_NUMBER);
		printf("Enter CRN: ");
		read_line(crn, N);
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		printf("|  ID  |        Course Name       |       Course Subject       | Instructor Name | Instructor Surname | Room |   CRN  | Credit Hours |\n");
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		while (!feof(fp))
		{
			fread(&a, sizeof(Course), 1, fp);
			if (!strcmp(name, a.name) && !strcmp(iSurname, a.inst.surname) && !strcmp(room, a.room) && !strcmp(crn, a.crn))
			{
				printf("|%6d|%26s|%28s|%17s|%20s|%6s|%8s|%14s|\n",
					a.idc, a.name, a.subject, a.inst.name, a.inst.surname, a.room, a.crn, a.credithours);
				printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
			}
		}
	}
	if (code == 15)
	{
		printf("Enter Name of the Course: ");
		read_line(name, COURSE_NAME);
		printf("Enter Surname of the Instructor: ");
		read_line(iSurname, INST_SURNAME);
		printf("Enter Room: ");
		read_line(room, ROOM_NUMBER);
		printf("Enter CRN: ");
		read_line(crn, N);
		printf("Enter Credit Hours: ");
		read_line(ch, N);
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		printf("|  ID  |        Course Name       |       Course Subject       | Instructor Name | Instructor Surname | Room |   CRN  | Credit Hours |\n");
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		while (!feof(fp))
		{
			fread(&a, sizeof(Course), 1, fp);
			if (!strcmp(name, a.name) && !strcmp(iSurname, a.inst.surname) && !strcmp(room, a.room) && !strcmp(crn, a.crn) && !strcmp(ch, a.credithours))
			{
				printf("|%6d|%26s|%28s|%17s|%20s|%6s|%8s|%14s|\n",
					a.idc, a.name, a.subject, a.inst.name, a.inst.surname, a.room, a.crn, a.credithours);
				printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
			}
		}
	}
	if (code == 16)
	{
		printf("Enter Name of the Course: ");
		read_line(name, COURSE_NAME);
		printf("Enter Room: ");
		read_line(room, ROOM_NUMBER);
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		printf("|  ID  |        Course Name       |       Course Subject       | Instructor Name | Instructor Surname | Room |   CRN  | Credit Hours |\n");
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		while (!feof(fp))
		{
			fread(&a, sizeof(Course), 1, fp);
			if (!strcmp(name, a.name) && !strcmp(room, a.room))//checks whether input is equal to the struct name
			{
				printf("|%6d|%26s|%28s|%17s|%20s|%6s|%8s|%14s|\n",
					a.idc, a.name, a.subject, a.inst.name, a.inst.surname, a.room, a.crn, a.credithours);
				printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
			}
		}
	}
	if (code == 17)
	{
		printf("Enter Name of the Course: ");
		read_line(name, COURSE_NAME);
		printf("Enter Room: ");
		read_line(room, ROOM_NUMBER);
		printf("Enter CRN: ");
		read_line(crn, N);
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		printf("|  ID  |        Course Name       |       Course Subject       | Instructor Name | Instructor Surname | Room |   CRN  | Credit Hours |\n");
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		while (!feof(fp))
		{
			fread(&a, sizeof(Course), 1, fp);
			if (!strcmp(name, a.name) && !strcmp(room, a.room) && !strcmp(crn, a.crn))
			{
				printf("|%6d|%26s|%28s|%17s|%20s|%6s|%8s|%14s|\n",
					a.idc, a.name, a.subject, a.inst.name, a.inst.surname, a.room, a.crn, a.credithours);
				printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
			}
		}
	}
	if (code == 18)
	{
		printf("Enter Name of the Course: ");
		read_line(name, COURSE_NAME);
		printf("Enter Room: ");
		read_line(room, ROOM_NUMBER);
		printf("Enter CRN: ");
		read_line(crn, N);
		printf("Enter Credit Hours: ");
		read_line(ch, N);
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		printf("|  ID  |        Course Name       |       Course Subject       | Instructor Name | Instructor Surname | Room |   CRN  | Credit Hours |\n");
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		while (!feof(fp))
		{
			fread(&a, sizeof(Course), 1, fp);
			if (!strcmp(name, a.name) && !strcmp(room, a.room) && !strcmp(crn, a.crn) && !strcmp(ch, a.credithours))
			{
				printf("|%6d|%26s|%28s|%17s|%20s|%6s|%8s|%14s|\n",
					a.idc, a.name, a.subject, a.inst.name, a.inst.surname, a.room, a.crn, a.credithours);
				printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
			}
		}
	}
	if (code == 19)
	{
		printf("Enter Name of the Course: ");
		read_line(name, COURSE_NAME);
		printf("Enter CRN: ");
		read_line(crn, N);
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		printf("|  ID  |        Course Name       |       Course Subject       | Instructor Name | Instructor Surname | Room |   CRN  | Credit Hours |\n");
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		while (!feof(fp))
		{
			fread(&a, sizeof(Course), 1, fp);
			if (!strcmp(name, a.name) && !strcmp(crn, a.crn))//checks whether input is equal to the struct name
			{
				printf("|%6d|%26s|%28s|%17s|%20s|%6s|%8s|%14s|\n",
					a.idc, a.name, a.subject, a.inst.name, a.inst.surname, a.room, a.crn, a.credithours);
				printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
			}
		}
	}
	if (code == 20)
	{
		printf("Enter Name of the Course: ");
		read_line(name, COURSE_NAME);
		printf("Enter CRN: ");
		read_line(crn, N);
		printf("Enter Credit Hours: ");
		read_line(ch, N);
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		printf("|  ID  |        Course Name       |       Course Subject       | Instructor Name | Instructor Surname | Room |   CRN  | Credit Hours |\n");
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		while (!feof(fp))
		{
			fread(&a, sizeof(Course), 1, fp);
			if (!strcmp(name, a.name) && !strcmp(crn, a.crn) && !strcmp(ch, a.credithours))
			{
				printf("|%6d|%26s|%28s|%17s|%20s|%6s|%8s|%14s|\n",
					a.idc, a.name, a.subject, a.inst.name, a.inst.surname, a.room, a.crn, a.credithours);
				printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
			}
		}
	}
	if (code == 21)
	{
		printf("Enter Name of the Course: ");
		read_line(name, COURSE_NAME);
		printf("Enter Credit Hours: ");
		read_line(ch, N);
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		printf("|  ID  |        Course Name       |       Course Subject       | Instructor Name | Instructor Surname | Room |   CRN  | Credit Hours |\n");
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		while (!feof(fp))
		{
			fread(&a, sizeof(Course), 1, fp);
			if (!strcmp(name, a.name) && !strcmp(ch, a.credithours))
			{

				printf("|%6d|%26s|%28s|%17s|%20s|%6s|%8s|%14s|\n",
					a.idc, a.name, a.subject, a.inst.name, a.inst.surname, a.room, a.crn, a.credithours);
				printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
			}
		}
	}
	if (code == 22)
	{
		printf("Enter Subject of the Course: ");
		read_line(subject, COURSE_SUBJECT);
		printf("Enter Instructor Name: ");
		read_line(iName, INST_NAME);
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		printf("|  ID  |        Course Name       |       Course Subject       | Instructor Name | Instructor Surname | Room |   CRN  | Credit Hours |\n");
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		while (!feof(fp))
		{
			fread(&a, sizeof(Course), 1, fp);
			if (!strcmp(subject, a.subject) && !strcmp(iName, a.inst.name))
			{

				printf("|%6d|%26s|%28s|%17s|%20s|%6s|%8s|%14s|\n",
					a.idc, a.name, a.subject, a.inst.name, a.inst.surname, a.room, a.crn, a.credithours);
				printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
			}
		}
	}
	if (code == 23)
	{
		printf("Enter Subject of the Course: ");
		read_line(subject, COURSE_SUBJECT);
		printf("Enter Instructor Surname: ");
		read_line(iSurname, INST_SURNAME);
		printf("Enter Instructor Name: ");
		read_line(iName, INST_NAME);
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		printf("|  ID  |        Course Name       |       Course Subject       | Instructor Name | Instructor Surname | Room |   CRN  | Credit Hours |\n");
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		while (!feof(fp))
		{
			fread(&a, sizeof(Course), 1, fp);
			if (!strcmp(subject, a.subject) && !strcmp(iSurname, a.inst.surname) && !strcmp(iName, a.inst.name))
			{

				printf("|%6d|%26s|%28s|%17s|%20s|%6s|%8s|%14s|\n",
					a.idc, a.name, a.subject, a.inst.name, a.inst.surname, a.room, a.crn, a.credithours);
				printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
			}
		}
	}
	if (code == 24)
	{
		printf("Enter Subject of the Course: ");
		read_line(subject, COURSE_SUBJECT);
		printf("Enter Instructor Surname: ");
		read_line(iSurname, INST_SURNAME);
		printf("Enter Instructor Name: ");
		read_line(iName, INST_NAME);
		printf("Enter Room: ");
		read_line(room, ROOM_NUMBER);
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		printf("|  ID  |        Course Name       |       Course Subject       | Instructor Name | Instructor Surname | Room |   CRN  | Credit Hours |\n");
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		while (!feof(fp))
		{
			fread(&a, sizeof(Course), 1, fp);
			if (!strcmp(subject, a.subject) && !strcmp(iSurname, a.inst.surname) && !strcmp(iName, a.inst.name) && !(strcmp(room, a.room)))
			{

				printf("|%6d|%26s|%28s|%17s|%20s|%6s|%8s|%14s|\n",
					a.idc, a.name, a.subject, a.inst.name, a.inst.surname, a.room, a.crn, a.credithours);
				printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
			}
		}
	}
	if (code == 25)
	{
		printf("Enter Subject of the Course: ");
		read_line(subject, COURSE_SUBJECT);
		printf("Enter Instructor Surname: ");
		read_line(iSurname, INST_SURNAME);
		printf("Enter Instructor Name: ");
		read_line(iName, INST_NAME);
		printf("Enter Room: ");
		read_line(room, ROOM_NUMBER);
		printf("Enter CRN: ");
		read_line(crn, N);
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		printf("|  ID  |        Course Name       |       Course Subject       | Instructor Name | Instructor Surname | Room |   CRN  | Credit Hours |\n");
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		while (!feof(fp))
		{
			fread(&a, sizeof(Course), 1, fp);
			if (!strcmp(subject, a.subject) && !strcmp(iSurname, a.inst.surname) && !strcmp(iName, a.inst.name) && !(strcmp(room, a.room)) && !strcmp(crn, a.crn))
			{

				printf("|%6d|%26s|%28s|%17s|%20s|%6s|%8s|%14s|\n",
					a.idc, a.name, a.subject, a.inst.name, a.inst.surname, a.room, a.crn, a.credithours);
				printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
			}
		}
	}
	if (code == 26)
	{
		printf("Enter Subject of the Course: ");
		read_line(subject, COURSE_SUBJECT);
		printf("Enter Instructor Surname: ");
		read_line(iSurname, INST_SURNAME);
		printf("Enter Instructor Name: ");
		read_line(iName, INST_NAME);
		printf("Enter Room: ");
		read_line(room, ROOM_NUMBER);
		printf("Enter CRN: ");
		read_line(crn, N);
		printf("Enter Credit Hours: ");
		read_line(ch, N);
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		printf("|  ID  |        Course Name       |       Course Subject       | Instructor Name | Instructor Surname | Room |   CRN  | Credit Hours |\n");
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		{
			fread(&a, sizeof(Course), 1, fp);
			if (!strcmp(subject, a.subject) && !strcmp(iSurname, a.inst.surname) && !strcmp(iName, a.inst.name) && !(strcmp(room, a.room)) && !strcmp(crn, a.crn) && !strcmp(ch, a.credithours))
			{
				printf("|%6d|%26s|%28s|%17s|%20s|%6s|%8s|%14s|\n",
					a.idc, a.name, a.subject, a.inst.name, a.inst.surname, a.room, a.crn, a.credithours);
				printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
			}
		}
	}
	if (code == 27)
	{
		printf("Enter Subject of the Course: ");
		read_line(subject, COURSE_SUBJECT);
		printf("Enter Surname of the Instructor: ");
		read_line(iSurname, INST_SURNAME);
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		printf("|  ID  |        Course Name       |       Course Subject       | Instructor Name | Instructor Surname | Room |   CRN  | Credit Hours |\n");
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		while (!feof(fp))
		{
			fread(&a, sizeof(Course), 1, fp);
			if (!strcmp(subject, a.subject) && !strcmp(iSurname, a.inst.surname))
			{
				printf("|%6d|%26s|%28s|%17s|%20s|%6s|%8s|%14s|\n",
					a.idc, a.name, a.subject, a.inst.name, a.inst.surname, a.room, a.crn, a.credithours);
				printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
			}
		}
	}
	if (code == 28)
	{
		printf("Enter Subject of the Course: ");
		read_line(subject, COURSE_SUBJECT);
		printf("Enter Surname of the Instructor: ");
		read_line(iSurname, INST_SURNAME);
		printf("Enter Room: ");
		read_line(room, ROOM_NUMBER);
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		printf("|  ID  |        Course Name       |       Course Subject       | Instructor Name | Instructor Surname | Room |   CRN  | Credit Hours |\n");
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		while (!feof(fp))
		{
			fread(&a, sizeof(Course), 1, fp);
			if (!strcmp(subject, a.subject) && !strcmp(iSurname, a.inst.surname) && !strcmp(room, a.room))
			{
				printf("|%6d|%26s|%28s|%17s|%20s|%6s|%8s|%14s|\n",
					a.idc, a.name, a.subject, a.inst.name, a.inst.surname, a.room, a.crn, a.credithours);
				printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
			}
		}
	}
	if (code == 29)
	{
		printf("Enter Subject of the Course: ");
		read_line(subject, COURSE_SUBJECT);
		printf("Enter Surname of the Instructor: ");
		read_line(iSurname, INST_SURNAME);
		printf("Enter Room: ");
		read_line(room, ROOM_NUMBER);
		printf("Enter CRN: ");
		read_line(crn, N);
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		printf("|  ID  |        Course Name       |       Course Subject       | Instructor Name | Instructor Surname | Room |   CRN  | Credit Hours |\n");
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		while (!feof(fp))
		{
			fread(&a, sizeof(Course), 1, fp);
			if (!strcmp(subject, a.subject) && !strcmp(iSurname, a.inst.surname) && !strcmp(room, a.room) && !strcmp(crn, a.crn))
			{
				printf("|%6d|%26s|%28s|%17s|%20s|%6s|%8s|%14s|\n",
					a.idc, a.name, a.subject, a.inst.name, a.inst.surname, a.room, a.crn, a.credithours);
				printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
			}
		}
	}
	if (code == 30)
	{
		printf("Enter Subject of the Course: ");
		read_line(subject, COURSE_SUBJECT);
		printf("Enter Surname of the Instructor: ");
		read_line(iSurname, INST_SURNAME);
		printf("Enter Room: ");
		read_line(room, ROOM_NUMBER);
		printf("Enter CRN: ");
		read_line(crn, N);
		printf("Enter Credit Hours: ");
		read_line(ch, N);
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		printf("|  ID  |        Course Name       |       Course Subject       | Instructor Name | Instructor Surname | Room |   CRN  | Credit Hours |\n");
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		while (!feof(fp))
		{
			fread(&a, sizeof(Course), 1, fp);
			if (!strcmp(subject, a.subject) && !strcmp(iSurname, a.inst.surname) && !strcmp(room, a.room) && !strcmp(crn, a.crn) && !strcmp(ch, a.credithours))
			{
				printf("|%6d|%26s|%28s|%17s|%20s|%6s|%8s|%14s|\n",
					a.idc, a.name, a.subject, a.inst.name, a.inst.surname, a.room, a.crn, a.credithours);
				printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
			}
		}
	}
	if (code == 31)
	{
		printf("Enter Room of the Course: ");
		read_line(room, ROOM_NUMBER);
		printf("Enter Subject of the Course: ");
		read_line(subject, COURSE_SUBJECT);
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		printf("|  ID  |        Course Name       |       Course Subject       | Instructor Name | Instructor Surname | Room |   CRN  | Credit Hours |\n");
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		while (!feof(fp))
		{
			fread(&a, sizeof(Course), 1, fp);
			if (!strcmp(room, a.room) && !strcmp(subject, a.subject))//checks whether input is equal to the struct name
			{
				printf("|%6d|%26s|%28s|%17s|%20s|%6s|%8s|%14s|\n",
					a.idc, a.name, a.subject, a.inst.name, a.inst.surname, a.room, a.crn, a.credithours);
				printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
			}
		}
	}
	if (code == 31)
	{
		printf("Enter Room of the Course: ");
		read_line(room, ROOM_NUMBER);
		printf("Enter Subject of the Course: ");
		read_line(subject, COURSE_SUBJECT);
		printf("Enter CRN: ");
		read_line(crn, N);
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		printf("|  ID  |        Course Name       |       Course Subject       | Instructor Name | Instructor Surname | Room |   CRN  | Credit Hours |\n");
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		while (!feof(fp))
		{
			fread(&a, sizeof(Course), 1, fp);
			if (!strcmp(room, a.room) && !strcmp(subject, a.subject) && !strcmp(crn, a.crn))
			{
				printf("|%6d|%26s|%28s|%17s|%20s|%6s|%8s|%14s|\n",
					a.idc, a.name, a.subject, a.inst.name, a.inst.surname, a.room, a.crn, a.credithours);
				printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
			}
		}
	}
	if (code == 32)
	{
		printf("Enter Room of the Course: ");
		read_line(room, ROOM_NUMBER);
		printf("Enter Subject of the Course: ");
		read_line(subject, COURSE_SUBJECT);
		printf("Enter CRN: ");
		read_line(crn, N);
		printf("Enter Credit Hours: ");
		read_line(ch, N);
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		printf("|  ID  |        Course Name       |       Course Subject       | Instructor Name | Instructor Surname | Room |   CRN  | Credit Hours |\n");
		printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
		while (!feof(fp))
		{
			fread(&a, sizeof(Course), 1, fp);
			if (!strcmp(room, a.room) && !strcmp(subject, a.subject) && !strcmp(crn, a.crn) && !strcmp(ch, a.credithours))
			{
				printf("|%6d|%26s|%28s|%17s|%20s|%6s|%8s|%14s|\n",
					a.idc, a.name, a.subject, a.inst.name, a.inst.surname, a.room, a.crn, a.credithours);
				printf("|------+--------------------------+----------------------------+-----------------+--------------------+------+--------+--------------|\n");
			}
		}
	}
}