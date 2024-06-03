#include <stdio.h>

int main(int argc, char *argv[])
{
	int i = 0;

//	// go through each string in argv. argv[0] contains the first arg passed which is the program name so we skip this if i begins at 1
//	for(i = 0; i < argc; i++)
//	{
//		printf("arg %d: %s\n", i, argv[i]);
//	}

	// making our own array of strings: by combining the char *str = "blah" syntax with the char str[] = {'b','l','a','h'} syntax to construct a two-dimensional array. The syntax char *states[] = {...} on line 14 is this two-dimensional combination, each string being one element, and each character in the string being another. Since each String is an element and row in this 2D array, and each varies in length, this would be a ragged 2D array, at least in Java.
	char *states[] = {"California", "Oregon", "Washington", "Texas"};
	//char *states[] = {"California", "Oregon", "Washington", "Texas", NULL};

	int num_states = 5;
	// w/ NULL and without in states array gives the same output and ends with a seg fault
	//int num_states = 6;
	
	states[0] = argv[0];
	argv[1] = states[1];

	for(i= 0; i < num_states; i++)
	{
		printf("state %d: %s\n", i, states[i]);
	}

	// go through each string in argv. argv[0] contains the first arg passed which is the program name so we skip this if i begins at 1
	for(i = 0; i < argc; i++)
	{
		printf("arg %d: %s\n", i, argv[i]);
	}

	return 0;
}
