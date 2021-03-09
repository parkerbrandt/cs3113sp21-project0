#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

#define MAX_CHAR_SIZE 5


// Prototype Functions
void printOutput(char** charArray, int* countArray, int arrayCount);
int numBytes(char checkByte);
void addCharToArray(char* unicodeChar, char** charArray, int* countArray, int* arrayCount);
void bubbleSort(char** charArray, int* countArray, int arrayCount);

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
	long arraySize = 50000;

	// Initialize the buffer array
	buffer = (char*)calloc(MAX_CHAR_SIZE, sizeof(char));

	// Initialize the two arrays used for counting
	// Can use realloc() to increase needed memory if necessary
	charArray = (char**)calloc(arraySize, sizeof(char) * 4);
	for(int i = 0; i < arraySize; i++)
		charArray[i] = (char*)calloc(MAX_CHAR_SIZE, sizeof(char));

	countArray = (int*)calloc(arraySize, sizeof(int));	

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

	// Sort the array in descending order and then output it
	bubbleSort(charArray, countArray, arrayCount);
	printOutput(charArray, countArray, arrayCount);


	return 0;
}



// Function Declarations

/*
 * Print the output given a character array and an integer array
 * Print format: Character->Count
 */
void printOutput(char** charArray, int* countArray, int arrayCount)
{
	for(int i = 0; i < arrayCount; i++)
	{
		// Ran into minor error with outputting
		if(countArray[i] != 0)
			printf("%s->%d\n", charArray[i], countArray[i]);
	}
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
 * Adds a unicode character to the string array, and then will increment its count in the corresponding spot in the 
 * count array
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
		// 0 indicates they are equal
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
		countArray[(*arrayCount)]++;
	}
}

/*
 * A recursive bubble sort from geeksforgeeks.org to sort the arrays in descending order
 */
void bubbleSort(char** charArray, int* countArray, int arrayCount)
{
	if(arrayCount == 1)
		return;

	for(int i = 0; i < arrayCount - 1; i++)
	{
		if(countArray[i] < countArray[i + 1])
		{
			// Swap the two variables in both the char array and count array
			// Swap in the char array
			char *temp = charArray[i];
			charArray[i] = charArray[i+1];
			charArray[i+1] = temp;

			// Swap in the count array
			int numTemp = countArray[i];
			countArray[i] = countArray[i+1];
			countArray[i+1] = numTemp;
		}
	}

	// The largest element is complete, now to do the rest of the array
	bubbleSort(charArray, countArray, arrayCount - 1);
}
