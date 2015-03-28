/*
 *  Name: Vanessa Hurtado
 *  ID: vahurtad
 *  Assignment: pa2
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"


#define MAX_LEN 160

int main(int argc, char* argv[])
{
	int lineCount = 0;
	int ch = 0;
	char line[MAX_LEN];

	/* Check the correct number of command line arguments for running the program */
	if (argc != 3)
	{
		printf("Proper Usage inputFile outputFile\n ");
		exit(1);
	}

	/* open file given by user for reading and writing */
	FILE *in = fopen(argv[1], "r");
	FILE *out = fopen(argv[2], "w");

	/* Check if files are able to be open */
	if (in == NULL)
	{
		printf("Unable to open %s \n", argv[1]);
		exit(1);
	}
	if (out == NULL)
	{
		printf("Unable to open %s \n", argv[2]);
		exit(1);
	}
	

	/* Read each line of the file and count the lines for length usage */
	while (fgets(line, MAX_LEN, in) != NULL)
	{
		lineCount++;
	}
	fclose(in);

	FILE *in1 = fopen(argv[1], "r");

	/* Store the char values in the file into an array */
	char **arr = calloc(MAX_LEN, sizeof(char**) * lineCount);

	for (int i = 0; i < lineCount; i++)
	{
		fgets(line, MAX_LEN, in);
		arr[i] = _strdup(line);
	}
	fclose(in1);


	/* Make a new list to sort the values in lexicographical order */
	List list = newList();

	/* Append first element to the list */
	if (isEmpty(list) == 1)
		append(list, 0);

	/* Add elements to the list while sorting them in lex order */
	for (int i = 1; i < lineCount; i++)
	{
		char* t = arr[i];
		int j = i - 1;
		moveTo(list, j);

		while (j > -1 && strcmp(t, arr[getElement(list)]) < 0)
		{
			j--;
			movePrev(list);
		}
		if (getIndex(list) == -1)
			prepend(list, i);
		else
			insertAfter(list, i);
	}

	/* Print sorted elements into the output file */
	for (moveTo(list, 0); getIndex(list) >= 0; moveNext(list))
		fprintf(out, "%s\n", arr[getElement(list)]);

	/* Close file and free the list */
	fclose(out);
	freeList(&list);
	return 0;
}
