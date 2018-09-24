#include <iostream>
#include <string.h>
using namespace std;

void write(char *a, char *b)
{
	int i = 0;
	while (*(b + i) != '\0')
	{
		*(a + i) = *(b + i);
		i++;
	}
}

int main()
{
	char array1[100] = {0};
	char array2[100] = {0};
	char insert[] = " ";
	int length = 1;
	write(array1, "abcde");
//	write(array2, "");
	cout << array1 << "\n";
	write(array2, array1 + 2);
	cout << array2 << "\n";
	write((array1 + 2), insert);
	cout << array1 << "*1" << "\n";
	write((array1 + 3), array2);
	cout << array1;
}
