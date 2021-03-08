#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

#define MAX_CHAR_SIZE 5
#define ARRAY_SIZE 1000


// Prototype Functions
void printOutput(char** charArray, int* countArray, int arrayCount);
int numBytes(char checkByte);
void addCharToArray(char* unicodeChar, char** charArray, int* countArray, int* arrayCount);


// Main Function
int main(int argc, char *argv[])
{
	// Variables
	char *buffer;
	int count = 1;
	int isFirstByte = TRUE;
	int numbytes;
	char endOfString = '\0';

	char **charArray;
	int *countArray;
	int arrayCount = 0;

	// Initialize the buffer array
	buffer = (char*)calloc(MAX_CHAR_SIZE, sizeof(char));

	// Initialize the two arrays used for counting
	// Can use realloc() to increase needed memory if necessary
	charArray = (char**)calloc(ARRAY_SIZE, sizeof(char) * 4);
	for(int i = 0; i < ARRAY_SIZE; i++)
		charArray[i] = (char*)calloc(MAX_CHAR_SIZE, sizeof(char));

	countArray = (int*)calloc(ARRAY_SIZE, sizeof(int));	

	// Main while loop to get characters from STDIN
	// Will then add the char to the char array and increase the count of each character
	char ch;
	while((ch = getchar()) != EOF)
	{
		// If this byte is the first byte, then need to determine how many total bytes
		if(isFirstByte == TRUE)
		{
			numbytes = numBytes(ch);

			// Check for error
			if(numbytes == 0)
				return -1;

			// Print for testing
			// printf("%d bytes: ", numbytes);
				
			// Check for 1 byte ASCII characters here
			// Cannot do below because when increment happens it screws it up
			if(numbytes == 1)
			{
				// Print for testing
				// printf("%c\n", ch);
				
				// Add character to the array
				buffer[0] = ch;
				buffer[1] = endOfString;
				
				addCharToArray(buffer, charArray, countArray, &arrayCount);

				// Reset the array and variables
				buffer[0] = 0;
				buffer[1] = 0;
			}
			else
			{
				buffer[0] = ch;
				isFirstByte = FALSE;
			}
		}
		else
		{
			// Add a byte to the character array
			buffer[count] = ch;

			count++;
			

			// Check if the count has reached the total number of bytes for that character
			if(count == numbytes)
			{	
				// Add the end of string symbol to the end to help with outputting
				buffer[count] = endOfString;

				// Print for testing
				// printf("%s\n", buffer);

				// Add the character to an array and increment the number of times it occurs
				addCharToArray(buffer, charArray, countArray, &arrayCount);
				

				// Reset the buffer array
				for(int i = 0; i < count; i++)
					buffer[i] = 0;

				// Reset the counter and isFirstByte variables
				// so the program can move onto the next character
				count = 1;
				isFirstByte = TRUE;
			}
		}		
	}

	// Deallocate memory used with buffer array
	free(buffer);

	// printOutput();

	return 0;
}



// Function Declarations

/*
 * TODO: Print the output given a character array and an integer array
 */
void printOutput(char** charArray, int* countArray, int arrayCount)
{

}

/*
 * A function that returns the total number of bytes of a unicode character
 * based on the control bits 
 */
int numBytes(char checkByte)
{
	// First, check the high order bit
	// 0x80 = 0b10000000
	char highOrderBit = checkByte & 0x80;
	if(highOrderBit == 0)
	{
		// If high-order bit is 0, then the character is an ASCII character
		return 1;
	}


	// Use an & bitwise operator in order to keep the first 4 bits intact while having the last 4 be 0
	// 0xF0 = 0b11110000
	unsigned char firstFour = checkByte & 0xF0;

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
	}
}


/*
 * 
 */
void addCharToArray(char* unicodeChar, char** charArray, int* countArray, int* arrayCount)
{
	// Loop through character array to check if character already exists or not
	int doesCharExist = FALSE;
	int foundIndex = 0;

	// If the arraycount is 0, then need to just add the character
	if((*arrayCount) == 0)
	{
		strcpy(charArray[0], unicodeChar);
		countArray[0]++;
		(*arrayCount)++;

		return;
	}

	// Loop through array to see if the character can be found
	for(int i = 0; i < (*arrayCount); i++)
	{
		// Use strcmp to compare the two strings
		if(strcmp(unicodeChar, charArray[i]) == 0)
		{
			doesCharExist = TRUE;
			foundIndex = i;
		}
	}

	// If the character was found, then increment the appropriate spot in the integer array, otherwise add it at the end
	if(doesCharExist == TRUE)
	{
		countArray[foundIndex]++;
	}
	else
	{
		(*arrayCount)++;

		strcpy(charArray[(*arrayCount)], unicodeChar);
	}
}
