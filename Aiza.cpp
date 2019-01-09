#include <iostream>
#include <windows.h>
#include <math.h>

using namespace std;

static int *consoleSize;                     // Initialize global consoleSize variable

int* getConsoleSize()
{
	static int array[2];                     // Initialize array with two elements, for width and height
	CONSOLE_SCREEN_BUFFER_INFO myConsole;    // Initialize variable for info capture

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &myConsole); // Retrieve width and height of current console
	array[0] = myConsole.srWindow.Right - myConsole.srWindow.Left + 1;       // Console Width
	array[1] = myConsole.srWindow.Bottom - myConsole.srWindow.Top + 1;       // Console Height
	return array;
}

/*******************************************/
/* Data Backend                            */
/*******************************************/

struct Item
{
	char *name;    // Name of menu item
	int type;      // 0: Pastry, 1: Drinks
	int cost;      // Cost of item
};

Item* newItem(char *name, int cost)     // Initializer of Item struct
{
	Item *myItem = new Item;            // Allocate new Item on memory
	myItem->name = name;                // Set struct member's data accordingly
	myItem->cost = cost;                // Likewise
	return myItem;
}

void write(char *a, char *b)
{
	for (int i = 0; *(b + i) != '\0'; i++)
	{
		*(a + i) = *(b + i);
	}
}

void append(char *a, char*b)
{
	int i = 0;
	int offset = 0;
	while (*(a + offset) != '\0')
	{
		offset++;
	}
	write(a + offset, b);
}

/*******************************************/
/* Graphical Backend                       */
/*******************************************/

int getStringLength(char *str)
{
	char *tmp = str;
	int i = 0;
	while (*tmp != '\0')
	{
		i++;
		tmp++;
	}
	return i;
}

char *pad(int amount, char padder)
{
	static char *temp = new char[amount + 1];
	for (int i = 0; i < amount; i++)
	{
		*(temp + i) = padder;
	}
	*(temp + amount) = '\0';
	return temp;
}

void centerPrint(char *str)
{
	int stringLength = getStringLength(str);
	int padAmount = (consoleSize[0] - stringLength) / 2;
	char *tmp = pad(padAmount, ' ');
	cout << tmp;
	cout << str;
}

void centerOneByOnePrint(char *str)
{
	int stringLength = getStringLength(str);
	int padAmount = (consoleSize[0] - stringLength) / 2;
	char *tmp = pad(padAmount, ' ');
	cout << tmp;
	for (int i = 0; i < stringLength; i++)
	{
		cout << str[i];
		Sleep(20);
	}
}

/*******************************************/
/* Graphical Frontend                      */
/*******************************************/

void loading_animation()
{
	double magic = (double) 100 / (double) consoleSize[0];
	double loadNumber = 0;
	int verticalPad = (consoleSize[1] - 3) / 2;
	for (int i = 0; i < 120; i++)
	{
		cout << pad(verticalPad, '\n');
		centerPrint((char *) &"Loading....");
		cout << floor(loadNumber) << '%' << '\n' << '\n';
		cout << pad(i, '|');
		loadNumber += magic;
		Sleep(1000/100); // Divide 1 second to 100 animation frames. Loader animation finishes more than 1 second since Windows cmd output is slower than expected.
		if (i != 119)
		{
			system("cls");
		}
		else
		{
			Sleep(1000);
			system("cls");
		}
	}
}

void intro_animation()
{
	
	// Store individual letters in a two-dimensional array for the animation later in the code and arrange them in an array. Three-dimensional?
	// Maintain length per letter for automatic padding of space in between individual letters (and word spacing)
	
	char letters[][5][6] = {	{ "**** " ,
								  "*   *" ,
								  "**** " ,
								  "*   *" ,
								  "**** " } ,
								  
								{ "**** " ,
								  "*   *" ,
								  "**** " ,
								  "*  * " ,
								  "*   *" } ,
								  
								{ "*****" ,
								  "*    " ,
								  "**** " ,
								  "*    " ,
								  "*****" } ,
								  
								{ " *** " ,
								  "*   *" ,
								  "*****" ,
								  "*   *" ,
								  "*   *" } ,
								  
								{ "**** " ,
								  "*   *" ,
								  "*   *" ,
								  "*   *" ,
								  "**** " } ,
								  
								{ "  ", "  ", "  ", "  ", "  "} ,
								
								{ " *** " ,
								  "*   *" ,
								  "*   *" ,
								  "*   *" ,
								  " *** " } ,
								  
								{ "*****" ,
								  "*    " ,
								  "**** " ,
								  "*    " ,
								  "*    " } ,
								  
								{ "  ", "  ", "  ", "  ", "  "} ,
								
								{ "*    " ,
								  "*    " ,
								  "*    " ,
								  "*    " ,
								  "*****" } ,
								  
								{ "*****" ,
								  "  *  " ,
								  "  *  " ,
								  "  *  " ,
								  "*****" } ,
								  
								{ "*****" ,
								  "*    " ,
								  "***  " ,
								  "*    " ,
								  "*    " } ,
								  
								{ "*****" ,
								  "*    " ,
								  "*****" ,
								  "*    " ,
								  "*****" }	};
	
	// Start of animation coding

	int length = 0;                                   // Measure the total length of the letters
	for (int i = 0; i < 13; i++)                      // The letters (including word space) are 13 in total
	{
		length += getStringLength(letters[i][0]);
		if (i != 12)
		{
			length++;                                 // Add spaces to the calculation of length except last letter
		}
	}
	
	int padAmount = (consoleSize[0] - length) / 2;    // Calculate required padding to center "Bread of Life"
	int verticalPad = (consoleSize[1] - 23) / 2;      // Calculate required vertical padding to center "Bread of Life"
	
	char **buffer = new char*[5]; // Create and initialize buffer array for storing previously displayed letters
	//char *hyperbuffer = new char[consoleSize[0]*consoleSize[1]];
	for (int i = 0; i < 5; i++)
	{
		buffer[i] = new char[padAmount + consoleSize[0]];
		for (int j = 0; j < padAmount + consoleSize[0]; j++)
		{
			buffer[i][j] = {0};
		}
		strcat(buffer[i], pad(padAmount, ' '));      // Add the padding to center "Bread of Life"
	}
	
	for (int i = 0; i < 13; i++)
	{
		if (i != 13)
		{
			system("cls");
		}
		for (int j = 0; j < 5; j++)
		{ 
			system("cls");
			cout << pad(verticalPad, '\n');

			strcat(buffer[j], letters[i][j]);
			strcat(buffer[j], " ");
			for (int k = 0; k < 5; k++)
			{
				cout << buffer[k];
				cout << "\n";
			}
		}
	}
}

void post_intro_animation()
{
	Sleep(750);
	cout << pad(3, '\n');
	centerOneByOnePrint((char *) &"Welcome to the Bread Of Life!");
	
	Sleep(500);
	cout << pad(5, '\n');
	centerOneByOnePrint((char *) &"Where pastries are affordable and 'veggie-veggie' healthy!");
	
	Sleep(500);
	cout << pad(5, '\n');
	centerOneByOnePrint((char *) &"combined with our homemade affordable drinks!");
	
	Sleep(2000);
	cout << pad(4, '\n');
	centerOneByOnePrint((char *) &"Do you wish to order?");
	
	Sleep(2000);
	cout << pad(4, '\n');
	centerOneByOnePrint((char *) &"Order?(Y/N): ");
}

void printMenu()
{
	system("cls");
}
/*******************************************/
/* Main                                    */
/*******************************************/

int main()
{	
	consoleSize = getConsoleSize();    // Retrieve current console's height and width.
	loading_animation();               // Start Loading Animation
	intro_animation();                 // Start Bread of Life Animation
	post_intro_animation();            // Start Welcome Message Animation
	
	char choice;
	cin >> choice;
	
	if (choice == 'y' || choice == 'Y')
	{
		printMenu();
	}
}
