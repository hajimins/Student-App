#include "Lib.h"
#include "readline.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
	FILE* fp;
	int nCourses;
	fp = fopen("courses.dat", "rb+");
	fseek(fp, 0, SEEK_END);
	nCourses = ftell(fp) / sizeof(Course);//finds the number of structs here
	fseek(fp, 0, SEEK_SET);
	fclose(fp);//closes the file

	char chp[N] = "print";
	char chi[N] = "insert";
	if (argc >= 2)// command line arguments
	{
		if (!strcmp(argv[1], chp))
			print(nCourses);
		if (!strcmp(argv[1], chi))
			insert(nCourses);
	}

	printf("%d Records Stored...\n\n", nCourses);

	Course* arr = (Course*)malloc((nCourses) * sizeof(Course));//allocating memory

	char code;
	for (;;) {
		printf("Enter operation code: i: insert | s: search | u: update | p: print |  c: sort | d: delete: | f: filter | q: quit \n");
		scanf(" %c", &code);
		while (getchar() != '\n')   /* skips to end of line */
			;
		switch (code) {
		case 'i': insert(nCourses);//inserts 
			break;
		case 's': search(nCourses);//searches for the course
			break;
		case 'u': update(nCourses);//updates the course
			break;
		case 'd':delete();//deletes the course and shows
			print(nCourses);
			break;
		case 'p': print(nCourses);//displays the course
			break;
		case 'c': sort(nCourses);
			break;
		case 'f': filter(nCourses);
			break;
		case 'q': return 0;
		default:  printf("Illegal code\n");
		}
		printf("\n");
	}
	free(arr);
	arr = NULL;
}
