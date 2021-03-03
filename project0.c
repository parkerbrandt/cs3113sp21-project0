#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 5

// Structs
struct HashMap
{
	char key;
	int value;
};

// Prototype Functions
void printOutput(int* array);


// Main Function
int main(int argc, char *argv[])
{
	// Variables
	char buffer[MAX_SIZE];
	int count = 0;
	char ch;
	struct HashMap *map;	

	while((ch = getchar()) != EOF)
	{
		buffer[count] = ch;

		if(ch == ' ')
		{
			
			count = 0;
		}
		else
		{
			//
			
			count++;
		}

		printf("Char: ");
		putchar(ch);
		printf("\n");
	}

	return 0;
}
