// This isn't your main like normal, but instead a source file that will become the object file ex22.o, which will have some functions (and an external variable depending on what is commented out) in it declared from ex22.h. (in C/C++ [what is a declaration vs. definition can be subtle and depends on the type of the identifier; ex1.`extern int i` is a declaration because it means that i is an int somewhere and not to worry about it, whereas `int i` is a definition in file/function/global scope because it means i is an int and it's address and scope are determined here; ex2. C++ templates]: introduce an identifier and describe its type, be it a type, object or function; a declaration is what the compiler needs to accept references to that identifier; an identifier can be declared as often as you want but you cannot redeclare members in class scope [ex. in a struct])

#include <stdio.h>
#include "ex22.h"
#include "dbg.h"

int get_size(struct State *state)
{
	return state->the_size;
}

void set_size(struct State *state, int size)
{
	state->the_size = size;
}

// `int get_age(struct State *state) and void set_age(struct State *state, int age)` replaces:
// `int THE_SIZE = 1000;
// static int THE_AGE = 37;
// int get_age() and void set_age(int age);`
int get_age(struct State *state)
{
	return state->the_age;
}

// same comment as get_age above
void set_age(struct State *state, int age)
{
	state->the_age = age;
}

// variable you declared extern that you'll play with from ex22_main.c
//int THE_SIZE = 1000;

// static (file): This keyword is kind of the inverse of extern, and says that the variable is only used in this .c file and should not be available to other parts of the program. Keep in mind that static at the file level (as with THE_AGE here) is different than in other places. In Java, a static class member belongs to the class (in C it belongs to the file), not objects instantiated from the class.
//static int THE_AGE = 37;

// get_age and set_age: These are taking the static variable THE_AGE, but exposing it to other parts of the program through functions. You can't access THE_AGE directly, but these functions can.
//int get_age()
//{
//	return THE_AGE;
//}

// same comment as get_age
//void set_age(int age)
//{
//	THE_AGE = age;
//}

// This takes a new ratio value, and returns the old one. It uses a function level static variable ratio to keep track of what the ratio currently is.
double update_ratio(double new_ratio)
{
	// static (function): If you declare or define (in C/C++ [what is a declaration vs. definition can be subtle and depends on the type of the identifier; ex1.`extern int i` is a declaration because it means that i is an int somewhere and not to worry about it, whereas `int i` is a definition in file/function/global scope because it means i is an int and it's address and scope are determined here; ex2. C++ templates]: instantiates/implements the identifier that has been declared or the identifier implicitly being declared in the definition; a definition is what the linker needs to link references to identifiers; an identifier must be defined exactly once) a variable in a function static, then that variable acts like a static defined (or declared?) in the file, but it's only accessible from that function. It's a way of creating constant state for a function, but in reality it's rarely used in modern C programming because they are hard to use with threads.
	static double ratio = 1.0;

	double old_ratio = ratio;
	ratio = new_ratio;

	return old_ratio;
}

// prints out what ex22.c thinks THE_SIZE is currently
void print_size(struct State *state)
{
	log_info("I think size is: %d", get_size(state));
}
