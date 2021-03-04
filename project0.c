#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 4

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

		if(ch == ' ' || ch == '\n' || count == 4)
		{
			printf("%s\n", buffer);	
			
			for(int i = 0; i < count; i++)
			{
				buffer[i] = ' '; 
			}	

			count = 0;
		}
		else
		{
			// Add character to char array
			buffer[count] = ch;
			
			count++;
		}
	}

	return 0;
}
