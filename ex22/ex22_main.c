#include "ex22.h"
#include "dbg.h"
#include <stdlib.h>

// refer to rulesToAvoidStackBugs.txt

// stands for constant and is an alternative to using `define` to create a constant variable
const char *MY_NAME = "Zed A. Shaw";

void die(const char *message)
{
	if(errno) perror(message);
	else printf("ERROR: %s\n", message);

	exit(1);
}

// simple function that demonstrates scope issues
void scope_demo(int count)
{
	log_info("count is: %d", count);

	if(count > 10)
	{
		int count = 100; // CAUSES ACCIDENTAL, ELUSIVE BUGS! IT SHADOWS THE FUNCTION PARAMETER WITH THE SAME NAME
		
		log_info("count in this scope is: %d", count);
	}

	log_info("count is at exit: %d", count);	

	count = 3000;

	log_info("count after assign: %d", count);

	// recursive stack overflow
	//scope_demo(25);
}

int main(int argc, char *argv[])
{
	struct State *state = malloc(sizeof(struct State));
	if(!state) die("Memory error.");

	set_age(state, 37);

	// test out the THE_AGE accessors
	//log_info("My name: %s, age: %d", MY_NAME, THE_AGE);
	log_info("My name: %s, age: %d", MY_NAME, get_age(state));

	//set_age(100);
	set_age(state, 100);

	if(get_age(state) >= 100) debug("Doubt you're %d years old.", get_age(state));

	//log_info("My age is now: %d", THE_AGE);
	log_info("My age is now: %d", get_age(state));

	// test out THE_SIZE extern
	//log_info("THE_SIZE is: %d", THE_SIZE);
	set_size(state, 1000);
	log_info("THE_SIZE is: %d", get_size(state));
	print_size(state);

	//THE_SIZE = 9;
	set_size(state, 9);

	//log_info("THE_SIZE is now: %d", THE_SIZE);
	log_info("THE_SIZE is now: %d", get_size(state));
	print_size(state);

	// test the ratio function's static variable called ratio
	log_info("Ratio at first: %f", update_ratio(2.0));
	log_info("Ratio again: %f", update_ratio(10.0));
	log_info("Ratio once more: %f", update_ratio(300.0));

	// test the scope demo
	int count = 4;
	scope_demo(count);
	scope_demo(count * 20);

	log_info("count after calling scope_demo: %d", count);


//	printf("\nPointer practice with const char *:\n\n");
//	// A POINTER IS THE ADDRESS OF SOME DATA IN MEMORY, IT CAN BE CALLED AN ADDRESS OR A REFERENCE (POINTER TO A VARIABLE (AKA "A REFERENCE TO A VARIABLE")) as well.
//	printf("Address of 'Zed A. Shaw': %p\n", MY_NAME);
//	printf("Value at the address assigned to MY_NAME: %s\n", MY_NAME);
//	// the next 2 are printing the address of the pointer itself (so the address of a pointer pointing to a pointer) rather than the address of the data (pointer definition)
//	printf("Address of MY_NAME pointer: %p\n", &MY_NAME);
//	// seg. faults because dereferencing the pointer to const char returns a character since char * is char[] and char * points to the first character in the char[]. So we need to use the %c format specifier.
//	//printf("%s\n", *MY_NAME);
//	// According to Beej's Guide to C: The dereference operator, *, tells the computer to use the variable the pointer points to instead of using the pointer itself.
//	printf("First character of 'Zed A. Shaw': %c\n", *MY_NAME);
//	// reassigns to "Bobby" because you are changing the pointer (ie, the address of the data being pointed at; this creates a new value in memory at a different location and assigns the address to the pointer) which is not const (the thing it is pointing to is const; this is why when you print any pointer variables pointing to a const char variable containing "Zed A. Shaw" or "Bobby" the address is the same for those different pointers (the address of the data being pointed at) because they are pointing to the same value). A string literal is actually a char[], which can be implicitly converted to a pointer to its first element.
//	MY_NAME = "Bobby";
//	printf("MY_NAME pointer to const variable in ex22_main.c was 'Zed A. Shaw', now it is: %s\n", MY_NAME);
//	printf("Address of 'Bobby': %p\n", MY_NAME);
//	printf("Value at the address assigned to MY_NAME: %s\n", MY_NAME);
//	printf("Address of MY_NAME pointer: %p\n", &MY_NAME);
//	printf("First character of 'Bobby': %c\n\n", *MY_NAME);
//
//
//	const char *NEW_NAME = "Zed A. Shaw";
//	printf("Address of 'Zed A. Shaw': %p\n", NEW_NAME);
//	printf("Value at the address assigned to NEW_NAME: %s\n", NEW_NAME);
//	// the next 2 are printing the address of the pointer itself (so the address of a pointer pointing to a pointer) rather than the address of the data (pointer definition)
//	printf("Address of NEW_NAME pointer: %p\n", &NEW_NAME);
//	// seg. faults because dereferencing the pointer to const char returns a character since char * is char[] and char * points to the first character in the char[]. So we need to use the %c format specifier.
//	//printf("%s\n", *MY_NAME);
//	// According to Beej's Guide to C: The dereference operator, *, tells the computer to use the variable the pointer points to instead of using the pointer itself.
//	printf("First character of 'Zed A. Shaw': %c\n", *NEW_NAME);
//	// reassigns to "Bobby" because you are changing the pointer (ie, the address of the data being pointed at; this creates a new value in memory at a different location and assigns the address to the pointer) which is not const (the thing it is pointing to is const; this is why when you print any pointer variables pointing to a const char variable containing "Zed A. Shaw" or "Bobby" the address is the same for those different pointers (the address of the data being pointed at) because they are pointing to the same value). A string literal is actually a char[], which can be implicitly converted to a pointer to its first element.
//	NEW_NAME = "Bobby";
//	printf("NEW_NAME pointer to char variable in main was 'Zed A. Shaw', now it is: %s\n", NEW_NAME);
//	printf("Address of 'Bobby': %p\n", NEW_NAME);
//	printf("Value at the address assigned to NEW_NAME: %s\n", NEW_NAME);
//	printf("Address of NEW_NAME pointer: %p\n", &NEW_NAME);
//	printf("First character of 'Bobby': %c\n\n", *NEW_NAME);
//
//
//	const char **DUB_PTR = &MY_NAME;
//	printf("Address of 'Bobby': %p\n", *DUB_PTR);
//	printf("Value at the address assigned to DUB_PTR: %s\n", *DUB_PTR);
//	// bad access to see what it looks like in the debugger
//	printf("Bad access of memory: %s\n", DUB_PTR);
//	printf("DUB_PTR pointer is pointing at the address of the MY_NAME pointer: %p\n", DUB_PTR);
//	printf("Address of DUB_PTR pointer: %p\n", &DUB_PTR);
//	printf("First character of 'Bobby': %c\n", **DUB_PTR);

	free(state);

	return 0;
}
