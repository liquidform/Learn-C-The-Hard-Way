#include <stdio.h>

int main (int argc, char *argv[])
{
//	char full_name[] = 
//	{
//		'Z', 'e', 'd',
//		' ', 'A', '.', ' ',
//		//'S', 'h', 'a', 'w', '\0'
//		'S', 'h', 'a', 'w'
//	};

	int areas[] = { 10, 12, 13, 14, 20 };
	areas[0] = 100;
	areas[1] = 'B';
	areas[5] = 200;
	areas[6] = 'A';
	areas[8] = 'C';

	char name[] = "Zed";
	name[2] = 'n';
	// Doesn't trigger 11841 for areas[0] w/ printf. The problem with `name[5] = '.';` must have something to do with going past the initial size of the array when not setting it up manually like with full_name.
	name[3] = '.';
//	name[3] = ' ';
	name[4] = 65;
	// Also triggers a weird number for areas[0] w/ printf but this time 46.
//	name[4] = '.';
	// `name[5] = '.';` is what is triggering 11841 for areas[0] w/ printf. Strangely, `full_name[5] = '.';` doesn't trigger it. Why is this? Maybe it has to do with manually setting up the characters in full_name but with name we don't set it up manually? Notice that areas is set up manually as well.
//	name[5] = '.';
//	name[6] = '\0';

	char full_name[] = 
	{
		'Z', 'e', 'd',
		' ', 'A', '.', ' ',
		'S', 'h', 'a', 'w', '\0'
		//'S', 'h', 'a', 'w'
	};
	full_name[2] = 'n';
	full_name[3] = ' ';
	full_name[4] = 65;
	full_name[5] = '.';

	areas[2] = name[1];

	// WARNING: On some systems you may have to change the 
	// %ld in this code to a %u since it will use unsigned ints
	printf("The size of an int: %ld\n", sizeof(int));
	printf("The size of areas (int[]): %ld\n", sizeof(areas));
	printf("The number of ints in areas: %ld\n",
			sizeof(areas) / sizeof(int));
	printf("The first area is %d, the 2nd %d.\n", areas[0], areas[1]);
	printf("The third area is %d, the 4th %d.\n", areas[2], areas[3]);
	printf("The 6th area is %d, the 7th %d.\n", areas[5], areas[6]);
	// areas[7] wasn't assigned on purpose
	printf("The 8th area is %d, 9th area is %d.\n", areas[7], areas[8]);

	printf("The size of a char: %ld\n", sizeof(char));
	printf("The size of name (char[]): %ld\n", sizeof(name));
	printf("The number of chars: %ld\n", sizeof(name) / sizeof(char));

	printf("The size of full_name (char[]): %ld\n", sizeof(full_name));
	printf("The number of chars: %ld\n",
			sizeof(full_name) / sizeof(char));

//	full_name[12] = 'X';
	
	printf("name=\"%s\" and full_name=\"%s\"\n", name, full_name);
//	printf("name=\"%c\" and full_name=\"%c\"\n", name[4], full_name[10]);

	return 0;
}
