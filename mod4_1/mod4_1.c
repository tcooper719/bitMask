#include <stdio.h>
#include <stdlib.h>

//function prototypes
unsigned int packCharacters(char toShift[], unsigned int numMask);
void printBin (unsigned int numWord);
void printCharBin(char toPrint[]);

int main(void)
{
	int c, i;
	unsigned int number = 0;
	char word[4], temp[5];

	//prompt for getting the four chars from the user via keyboard. I used a temporary char array of 5 so 
	//I could store the terminating character at the end of the string. Then to ensure I had my correct array
	//with only 4 chars, I copied the temp array to the proper word array that I am going to mask
	printf_s("%s", "Please input 4 characters to be packed int the unsigned int (i.e. \"wasd\"): ");
	fgets(temp, 5, stdin);
	for (i = 0; i < 4; i++)
		word[i] = temp[i];

	//This prints the chars binary representation
	puts("\nThis is the characters from the array before being passed to the unsigned int:\n");
	printCharBin(word);

	//this prints the unsigned ints binary representation so that the user can see it is all zeros
	puts("\nThis is the unsigned int before masking\n     ");
	printBin(number);

	//we assign the binary representation of the chars that were entered previously
	number = packCharacters(word, number);

	//this prints the unsigned int after the chars have been masked into binary
	puts("\nThis is the unsigned int after masking\n");
	printBin(number);
}

//the required function
unsigned int packCharacters(char toShift[], unsigned int numMask)
{
	int i, r = 0;
	//needed a counter in both directions to correctly push the characters to the end but to
	//start at the beginning of the char array. Without the counter r counting up, the chars
	//enter the unsigned int backwards.
	for (i = 3; i >= 0; i--)
	{
		numMask |= toShift[r] << i * 8;
		r++;
	}

	return numMask;
}

//the function from the book that prints the bit representation of the unsigned int.
void printBin(unsigned int numWord)
{
	unsigned int c;
	unsigned int displayMask = 1 << 31;
	printf_s("%15u = ", numWord);
	
	for (c = 1; c <= 32; c++)
	{
		putchar(numWord & displayMask ? '1' : '0');
		numWord <<= 1;

		if (c % 8 == 0)
		{
			putchar(' ');
		}
	}
	putchar('\n');
}

//this function is just to print the binary representation of the letters so that the user
//can see that the bits are being correctly assigned into the unsigned int.
void printCharBin(char toPrint[])
{
	int i, temp, num, b;
	unsigned int numB;

	for (i = 0; i < 4; i++)
	{
		num = toPrint[i];
		b = 1;
		numB = 0;
		while (num != 0)
		{
			temp = num % 2;
			num = num / 2;
			numB = numB + (temp * b);
			b = b * 10;
		}
		printf_s("The char %c's binary representation is 0%d\n", toPrint[i], numB);
	}
}