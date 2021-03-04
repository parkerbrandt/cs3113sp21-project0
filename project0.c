#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

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
	short isFirstByte = 1;
	struct HashMap *map;	

	// Initialize the buffer array
	buffer = (char*)calloc(MAX_CHAR_SIZE, sizeof(char));
	buffer[4] = '\0';


	// Main while loop to get characters from STDIN
	// Will then add the char to the map and increase the count of each character
	while((ch = getchar()) != EOF)
	{
		// Use this short variable to determine if the byte that is being read is the first bit or not
		// 1 will denote this is the first byte, 0 will denote it is not
		if(isFirstByte == 1)
		{
			// Now, read first 3 btis to determine how many bytes the Unicode character is
			char byteCheck = ch | 0b1110000;


			isFirstBit = 0;
		}
		
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
