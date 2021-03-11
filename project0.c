#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1

#define MAX_CHAR_SIZE 7


// Global variables
unsigned long arraySize = 3000000;


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

	// Initialize the buffer array
	buffer = (char*)calloc(MAX_CHAR_SIZE, sizeof(char));

	// Initialize the two arrays used for counting
	// Can use realloc() to increase needed memory if necessary
	charArray = (char**)malloc(arraySize * MAX_CHAR_SIZE * sizeof(*charArray));
	for(int i = 0; i < arraySize; i++)
		charArray[i] = (char*)calloc(MAX_CHAR_SIZE, sizeof(char));

	countArray = (int*)malloc(arraySize * sizeof(*countArray));	

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
			{
				printf("Error\n");
				return -1;
			}

			// Print for testing
			// printf("%d bytes: ", numbytes);
				
			// Check for 1 byte ASCII characters here
			// Cannot do below because when increment happens it screws it up
			if(numbytes == 1)
			{
				// Add character to the array
				buffer[0] = ch;
				buffer[1] = endOfString;
				
				// Print for testing
				// printf("%s\n", buffer);

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
				printf("Count: %d\n", arrayCount);	

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


	// Need to find the number of ones before a 0
	// Previously used a switch statement, but that didn't account for extra ones that may be causing issues
	
	// New method is to use the bitwise & with different numbers to determine one by one the number of bytes
	// There is probably a more clever solution to this using the << operator
	
	// 0xE0 = 0b11100000
	unsigned char testByte = checkByte & 0xE0;
	if(testByte == 0xC0)
		return 2;

	// 0xF0 = 0b11110000
	testByte = checkByte & 0xF0;
	if(testByte == 0xE0)
		return 3;

	// 0xF8 = 0b11111000
	testByte = checkByte & 0xF8;
	if(testByte == 0xF0)
		return 4;

	// 0xFC = 0b11111100
	testByte = checkByte & 0xFC;
	if(testByte == 0xF8)
		return 5;

	// 0xFE = 0b11111110
	testByte = checkByte & 0xFE;
	if(testByte == 0xFC)
		return 6;

	// If it fails, just return 0
	return 0;
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
 * A non-recursive bubble sort from geeksforgeeks.org to sort the arrays in descending order
 * Tried to use a recursive bubble sort, but encountered stack overflow
 */
void bubbleSort(char** charArray, int* countArray, int arrayCount)
{
	// Variables
	char *temp;
	int numTemp;

	int i, j;
	for(i = 0; i < arrayCount - 1; i++)
	{
		for(j = 0; j < arrayCount - i - 1; j++)
		{
			if(countArray[j] < countArray[j+1])
			{
				// Swap the elements in the character array
				// and in the count array
				temp = charArray[j];
				charArray[j] = charArray[j+1];
				charArray[j+1] = temp;

				numTemp = countArray[j];
				countArray[j] = countArray[j+1];
				countArray[j+1] = numTemp;
			}
		}
	}	
}
