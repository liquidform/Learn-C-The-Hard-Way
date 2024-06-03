#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

// For finding memory leaks debug w/ these flags:
/* valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
         ./executable exampleParam1
*/

// The flags are, in short:
//    --leak-check=full: "each individual leak will be shown in detail"
//    --show-leak-kinds=all: Show all of "definite, indirect, possible, reachable" leak kinds in the "full" report.
//    --track-origins=yes: Favor useful output over speed. This tracks the origins of uninitialized values, which could be very useful for memory errors. Consider turning off if Valgrind is unacceptably slow.
//    --verbose: Can tell you about unusual behavior of your program. Repeat for more verbosity.
//    --log-file: Write to a file. Useful when output exceeds terminal space.

// As long as you have -g debugging flag when compiling your program with gcc the output of valgrind should tell you WHERE the memory leak(s) occurred

// For more info and to see where this info came from see the first answer by the community at: https://stackoverflow.com/questions/5134891/how-do-i-use-valgrind-to-find-memory-leaks

struct Person {
	char *name;
	int age;
	int height;
	int weight;
};

struct Person *Person_create(char *name, int age, int height, int weight)
{
	struct Person *who = malloc(sizeof(struct Person));
	assert(who != NULL);

	// I use the strdup function to duplicate the string for the name, just to make sure that this structure actually owns it. The strdup actually is like malloc, and it also copies the original string into the memory it creates. Me speaking: make a copy in case name is changed elsewhere which could unintentionally change name in the Person struct.
	who->name = strdup(name);
	who->age = age;
	who->height = height;
	who->weight = weight;

	return who;
}

void Person_destroy(struct Person *who)
{
	assert(who != NULL);

	// I use the function free to return the memory I got with malloc and strdup
	// memory I got w/ strdup (next line deletes the pointer but not the string that name points to)
	free(who->name);
	// memory I got w/ malloc
	free(who);
}

void Person_print(struct Person *who)
{
	printf("Name: %s\n", who->name);
	printf("\tAge: %d\n", who->age);
	printf("\tHeight: %d\n", who->height);
	printf("\tWeight: %d\n", who->weight);
}

int main(int argc, char *argv[])
{
	// make two people structures
	struct Person *joe = Person_create("Joe Alex", 32, 64, 140);
	struct Person *frank = Person_create("Frank Blank", 20, 72, 180);

	// print them out and where they are in memory
	printf("Joe is at memory location %p:\n", joe);
	Person_print(joe);

	printf("Frank is at memory location %p:\n", frank);
	Person_print(frank);

	// make everyone age 20 years and print them again
	joe->age += 20;
	joe->height -= 2;
	joe->weight += 40;
	Person_print(joe);

	frank->age += 20;
	frank->weight += 20;
	//free(frank);
	Person_print(frank);
	//Person_print(NULL);

	// destroy them both so we clean up
	Person_destroy(joe);
	//Person_destroy(NULL);
	Person_destroy(frank);

	return 0;
}
