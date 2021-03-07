#include <stdio.h>
#include <stdlib.h>

#define MAX_CHAR_SIZE 5


// Typedefs
typedef enum {false, true} bool;


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

	// Initialize the buffer array
	buffer = (char*)calloc(MAX_CHAR_SIZE, sizeof(char));
	buffer[MAX_CHAR_SIZE - 1] = '\0';

	// Main while loop to get characters from STDIN
	// Will then add the char to the char array and increase the count of each character
	// TODO: Add characters and count to arrays
	char ch;
	while((ch = getchar()) != EOF)
	{
		// If this byte is the first byte, then need to determine how many total bytes
		if(isFirstByte)
		{
			numBytes = numBytes(ch);

			// Check for error
			if(numBytes == 0)
				return -1;

			// Print for testing
			printf("%d bytes: ", numBytes);

			buffer[0] = ch;

			isFirstByte = false;
		}
		
		if(ch == ' ' || count == numBytes)
		{	
			// Print for testing
			printf("%s\n", buffer);	
			
			for(int i = 0; i < count; i++)
			{
				buffer[i] = 0; 
			}	

			count = 0;

			isFirstByte = true;
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
 * A function that returns the total number of bytes of a unicode character
 * based on the control bits 
 * Could also implement as a for loop that counts the number of ones
 */
int numBytes(char checkByte)
{
	// First, check the high order bit
	// 0x80 = 0b10000000
	char highOrderBit = CheckByte & 0x80;
	if(highOrderBit == 0)
	{
		// If high-order bit is 0, then the character is an ASCII character
		return 1;
	}


	// Use an & bitwise operator in order to keep the first 4 bits intact while having the last 4 be 0
	// 0xF0 = 0b11110000
	char firstFour = checkByte & 0xF0;

	// Use the switch statement to match the high order bits
	switch(firstFour)
	{
		// 0b11000000 - Two byte long unicode character
		case 0xC0:
			return 2;
		
		// 0b11100000 - Three byte long unicode character
		case 0xE0:
			return 3;

		// 0b11110000 - Four byte long unicode character
		case 0xF0:
			return 4;

		// If the byte does not match, can return 0 to signify an error
		default:
			return 0;
			break;
	}
}
