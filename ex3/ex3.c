#include <stdio.h>

// A large portion of the code below is from https://www.geeksforgeeks.org/escape-sequence-in-c/
// The rest is from Learn C The Hard Way or myself.

void crash() {
	char *test = NULL;
	int i = 0;

	for(i = 0; i < 1000000; i++)
	{
		printf("%c", test[i]);
	}
}

int main(int argc, char *argv[])
{
	int age = 100;
	int height = 72;

	// crash();
	printf("I am %s years old.\n", argv[1]);
	printf("I am %d years\b old.\n", age);
	printf("I am %d inches\t tall.\n", height);
	printf("My mobile number "
           "is 7\a8\a7\a3\a9\a2\a3\a4\a0\a8\a.\n");
	printf("Hallo friends.\v");
	printf("Hallo\v family.\n");
	printf("Hallo again.\n");
	printf("Goodbye The Hard Way \rLearn C\n");
    printf("Hello\\GFG\n");
	printf("He said, \"Here's an escape sequence.\"\n");
	printf("And we stood there in \'awe\'.\n");
	printf("Can you believe your eyes\?\n");
    char* s = "A\072\065";
    printf("%s\n", s);
	s = "B\x4a";
    printf("%s\n\n", s);

	printf("Her age is %d\n", 32);
	printf("Her age is \t%5d\n", 32);
	printf("Her age is \t%-5d\n", 32);
	printf("Her age is %o\n", 49);
	printf("His age is %o\n", 200);
	printf("His age is %u\n", 0xffff);
	printf("His age is %u\n", 2);
	printf("His age is %u\n", -2);
	printf("Her age is %x\n", 67);
	printf("His age is %X\n", 67);
	printf("Her age is %x\n", 127);
	printf("His age is %X\n", 127);
	printf("My age is %e\n", 42.3456789);
	printf("Your age is %.2e\n", 37.9123456);
	printf("Her age is %f\n", 53.2345678);
	printf("Her age is %.3f\n", 53.2345678);
	printf("Your grade is %c\n", 65);
	printf("You have %s the class\n", "passed");

	return 0;
}
