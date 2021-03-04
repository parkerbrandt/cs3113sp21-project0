#include <stdio.h>
#include <stdlib.h>

#define MAX_CHAR_SIZE 5

// Structs
struct HashMap
{
	char *key[MAX_CHAR_SIZE];
	int value;
};

// Prototype Functions
void printOutput(int* array);


// Main Function
int main(int argc, char *argv[])
{
	// Variables
	char *buffer;
	int count = 0;
	char ch;
	struct HashMap *map;	

	// Initialize the buffer array
	buffer = (char*)malloc(sizeof(char) * MAX_CHAR_SIZE);
	buffer[4] = '\0';


	// Main while loop to get characters from STDIN
	// Will then add the char to the map and increase the count of each character
	while((ch = getchar()) != EOF)
	{
		// TODO: Add a better way to detect an end of character
		// Can use the first 3 bits to determine what the number of bytes are
		if(ch == ' ' || count == 4)
		{
			printf("%s\n", buffer);	
			
			for(int i = 0; i < count; i++)
			{
				buffer[i] = 0; 
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
