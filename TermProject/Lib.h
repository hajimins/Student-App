#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#pragma warning (disable : 4996)

typedef enum size {
	COURSE_NAME = 40,
	COURSE_SUBJECT = 50,
	INST_NAME = 10,
	INST_SURNAME = 20,
	MAX_COURSES = 100,
	ROOM_NUMBER = 5,
	N = 10
};

typedef struct instructor
{
	char name[INST_NAME];
	char surname[INST_SURNAME];
} Instructor;

typedef struct course
{
	char crn[N];
	char name[COURSE_NAME];
	char subject[COURSE_SUBJECT];
	char room[ROOM_NUMBER];
	char credithours[N];
	Instructor inst;
	int idc;
}Course;

void insert(int);
void search(int);
void update(int);
void print(int);
void delete(void);
void sort(int);
void filter(int);

int courseID(int, int);
int courseName(char name[COURSE_NAME], int nCourses);
int courseSubject(char subject[COURSE_SUBJECT], int nCourses);
int courseIName(char iName[INST_NAME], int nCourses);
int courseISurname(char iSurname[INST_SURNAME], int nCourses);
int courseCRN(char crn[N], int nCourses);
int courseRoom(char room[N], int nCourses);
int courseCreditHours(char ch[N], int nCourses);

int comparename(const void* a, const void* b);
int comparesub(const void* a, const void* b);
int compareinstN(const void* a, const void* b);
int compareinstS(const void* a, const void* b);
int compareCRN(const void* a, const void* b);
int compareID(const void* a, const void* b);
