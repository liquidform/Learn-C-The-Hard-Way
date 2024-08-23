// Header file that sets up some external variables (when not using struct State) and some functions

#ifndef _ex22_h
#define _ex22_h

// deleting the global variables, THE_SIZE and THE_AGE, and putting them in a struct with appropriate setters and getters allows you to use threads better because global variables can't be shared between threads. That's the biggest reason you do this. Almost always, if you have some global variable, you should pack it into a struct before main and then pass the struct around. If you absolutely have to have one big global, at least make it a struct so that way you can have one cohesive place where it lives. Avoid using too many globals, especially if across multiple files. If you have to use them, then use accessor functions like I've done with get_age. This doesn't apply to constants, since those are read-only. I'm talking about variables like THE_SIZE. If you want people to modify or set this variable, then make accessor functions.

// replaces `extern int THE_SIZE;`
struct State
{
	int the_size;
	int the_age;
};

// parameter is an example of pass by reference bc a pointer is a reference to a place. If it's a pointer, it's a reference, and if you pass it to something else you pass by reference. Everything else is just pass by value.
int get_size(struct State *state);
void set_size(struct State *state, int size);

// replaces:
// `int get_age();
// void set_age(int age);`
int get_age(struct State *state);
void set_age(struct State *state, int age);

// makes THE_SIZE in ex22.c available to other .c files. extern: This keyword is a way to tell the compiler "the variable exists, but it's in another 'external' location." Typically this means that one .c file is going to use a variable that's been defined in another .c file. In this case, we're saying ex22.c has a variable THE_SIZE that will be accessed from ex22_main.c.
//extern int THE_SIZE;

// gets and sets an internal static variable in ex22.c
//int get_age();
//void set_age(int age);

// updates a static variable that's inside update_ratio. This parameter is an example of pass by value because you're passing the actual value
double update_ratio(double ratio);

void print_size();

#endif
