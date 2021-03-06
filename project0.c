#include <stdio.h>
#include <stdlib.h>

#define MAX_CHAR_SIZE 5

// Typedefs
typedef enum {false, true} bool;

// Structs
struct DoubleArray
{
	char *key[];
	int *values[];
};

// Prototype Functions
void printOutput(struct HashMap *map);
int numBytes(char checkByte);

// Main Function
int main(int argc, char *argv[])
{
	// Variables
	char *buffer;
	int count = 1;
	bool isFirstByte = true;
	int numBytes;
	struct DoubleArray *array;	

	// Initialize the buffer array
	buffer = (char*)calloc(MAX_CHAR_SIZE, sizeof(char));
	buffer[MAX_CHAR_SIZE - 1] = '\0';


	// Main while loop to get characters from STDIN
	// Will then add the char to the map and increase the count of each character
	char ch;
	while((ch = getchar()) != EOF)
	{
		// 
		if(isFirstByte)
		{
			numBytes = numBytes(ch);

			// Check for error
			if(numBytes == 0)
				return -1;

			buffer[0] = ch;

			isFirstByte = FALSE;
		}
		
		if(ch == ' ' || count == numBytes)
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

	printOutput(map);

	return 0;
}



// Function Declarations

/*
 *
 */
void printOutput()
{
	

}

/*
 *
 */
int numBytes(char checkByte)
{
	// Use an & bitwise operator in order to keep the first 4 bits intact while having the last 4 be 0
	char firstFour = checkByte & 11110000;

	// Use the switch statement to match the high order bits
	switch(firstFour)
	{
		
		default:
			return 0;
			break;
	}
}
