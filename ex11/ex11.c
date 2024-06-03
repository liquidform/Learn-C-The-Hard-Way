#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[])
{
	//int numbers[4] = { 0 };
	int number[4];
	// int * is like an array of integers
	int *numbers = number;
	// this line doesn't change the output
	*numbers = 0;
//	char name[4] = { 'a' };
	//char name[4] = { 97 };
	int a = 97;
	char *name = (char *) &a;
	printf("%d\n", *name + 2);
	printf("%c\n", *name + 2);
	int crazyHack = 65;
	memcpy(name, &crazyHack, 4);
	printf("%d\n", *((int *) name) + 2);
	printf("%c\n", *((char *) name) + 2);
	// does the same thing as above
//	printf("%d\n", *name + 2);
//	printf("%c\n", *name + 2);
	printf("%ld\n", sizeof(name));
	printf("%ld\n", sizeof(crazyHack));
//	name[1] = 0;
//	name[2] = 0;
//	name[3] = 0;
	name++;
	*name = 0;
	name++;
	*name = 0;
	name++;
	*name = 0;
	name = (char *) &a;

	// first, print them out raw
	printf("numbers: %d %d %d %d\n",
			//numbers[0], numbers[1], numbers[2], numbers[3]);
			*numbers, *numbers, *numbers, *numbers);

	printf("name each: %c %c %c %c\n",
			//name[0], name[1], name[2], name[3]);
			*name, *(name + 1), *(name + 2), *(name + 3));

	printf("name: %s\n", name);

	// setup the numbers
	// Incrementing a variable means adding 1 to it, as in p = p + 1. Since p is a pointer, adding 1 to it advances it by the width of the datum it points to—in this case, sizeof (int). Source: https://www.gnu.org/software/c-intro-and-ref/manual/html_node/Pointer-Increment_002fDecrement.html
	*numbers = 1;
	numbers++;
	*numbers = 2;
	numbers++;
	*numbers = 3;
	numbers++;
	*numbers = 4;
	// this line is needed to point numbers back to &number[0]
	numbers = number;

	// setup the name
//	name[0] = 'Z';
//	name[1] = 'e';
//	name[2] = 'd';
//	name[3] = '\0';
	*name = 'Z';
	name++;
	*name = 'e';
	name++;
	*name = 'd';
	name++;
	*name = '\0';
	name = (char *) &a;

	// then print them out initialized
	printf("numbers: %d %d %d %d\n",
			//numbers[0], numbers[1], numbers[2], numbers[3]);
			*numbers, *(numbers + 1), *(numbers + 2), *(numbers + 3));

	printf("name each: %c %c %c %c\n",
			//name[0], name[1], name[2], name[3]);
			*name, *(name + 1), *(name + 2), *(name + 3));

	// print the name like a string
	printf("name: %s\n", name);

	// another way to use name
	char *another = "Zed";

	printf("another: %s\n", another);

	printf("another each: %c %c %c %c\n",
			//another[0], another[1], another[2], another[3]);
			*another, *(another + 1), *(another + 2), *(another + 3));

	return 0;
}
