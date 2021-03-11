# CS3113 Project 0
<h4>By Parker Brandt (ID: 113521131)

<h3>To Compile</h3>
To run this program, in the command-line type:</br>
make all</br>
to compile the program, and then type:</br>
./project0 <"filename" </br>
in order to run the program with "filename" replaced with whatever file is to be used for input

<h3>Known Bugs & Assumptions</h3>
The main assumption I had to make is on the size of the arrays I am using.</br>


<h3>Logic</h3>
The main logic for the program is:</br>
Get a character</br>
If that character is the first byte of a unicode character, check to see how many bytes the entire character is</br>
Add that character to the array, and increment the number of occurrences of that character in another array</br>


<h3>Functions</h3>

<b>void printOutput(char** charArray, int* countArray, int arrayCount)</b></br>
This function outputs the contents of charArray and countArray in the form of "charArray[index]->countArray[index]".</br></br>


<b>int numBytes(char checkByte)</b></br>
This function returns the integer number of bytes in a given Unicode character. This function is called whenever the main function determines that 
the first byte has been consumed from the input. UTF-8 encoding is assumed to be used to determine the number of bytes by counting the number of 1s in the high order bits of checkByte.</br></br>

<b>void addCharToArray(char* unicodeChar, char** charArray, int* countArray, int* arrayCount)</b></br>
This function will add the Unicode character, unicode char to the string array, charArray. The function will also check if the character already exists, and if so, it will just increment the count in the integer array, countArray.</br></br>

<b>void bubbleSort(char** charArray, int* countArray, int arrayCount)</b></br>
This function sorts the corresponding character and integer arrays using a non-recursive bubble sort algorithm in descending order. The character array and integer array are changed at the same time so all numbers that correspond should be kept together.
