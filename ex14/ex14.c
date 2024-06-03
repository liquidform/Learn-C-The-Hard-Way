#include <stdio.h>
#include <ctype.h>
#include <string.h>

// forward declarations
int can_print_it(char ch);
void print_letters(char arg[]);
//void print_letters(char arg[], int len);

void print_arguments(int argc, char *argv[])
//void print_arguments(int argc, char **argv)
{
	int i = 0;

	for(i = 0; i < argc; i++) {
		print_letters(argv[i]);
		//print_letters(*(argv + i));
		// for demonstration purposes; strlen is insecure
		//print_letters(argv[i], strlen(argv[i]));
	}
}

void print_letters(char arg[])
//void print_letters(char *arg)
//void print_letters(char arg[], int len)
{
	int i = 0;

	for(i = 0; arg[i] != '\0'; i++) {
	//for(i = 0; *(arg + i) != '\0'; i++) {
	//for(i = 0; i < len; i++) {
		char ch = arg[i];
		//char ch = *(arg + i);

		if(can_print_it(ch)) {
			printf("'%c' == %d ", ch, ch);
		}
	}

	printf("\n");
}

int can_print_it(char ch)
{
	return isalpha(ch) || isblank(ch);
	//return isdigit(ch) || isupper(ch);
}

int main(int argc, char *argv[])
//int main(int argc, char **argv)
{
	//print_arguments(argc+1, argv);
	print_arguments(argc, argv);
	return 0;
}
