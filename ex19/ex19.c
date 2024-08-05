//#define NDEBUG

#include "dbg.h"
#include <stdlib.h>
#include <stdio.h>

// a way to cause elusive bugs is to not put braces around your if and else statements. Writing without braces can make you or others think that because another line of code is indented like the above if or else statement it is included in that block. The macros in dbg.h will prevent you from doing excluding braces most of the time. You'll just run into weird formatting errors sometimes if you don't include braces.

// More about using the C predefined identifiers __func__ or __FUNCTION__ (which is another name for __func__, provided for backward compatibility with old versions of GCC). These variables are implicitly declared as a static const char array variable, are NOT a preprocessor macro, and may not be used to initialize char arrays or be concatenated with string literals: https://gcc.gnu.org/onlinedocs/gcc/Function-Names.html and https://gcc.gnu.org/onlinedocs/cpp/Standard-Predefined-Macros.html

void test_debug()
{
	// notice you don't use the \n
	debug("%s: I have Brown Hair.", __func__);

	// passing in arguments like printf
	debug("%s: I am %d years old.", __func__, 37);
}

void test_log_err()
{
	log_err("%s: I believe everything is broken.", __func__ );
	log_err("%s: There are %d problems in %s.", __func__, 0, "space");
}

void test_log_warn()
{
	log_warn("%s: You can safely ignore this.", __func__);
	log_warn("%s: Maybe consider looking at: %s.", __func__, "/etc/passwd");
}

void test_log_info()
{
	log_info("%s: Well I did something mundane.", __func__);
	log_info("%s: It happened %f times today.", __func__, 1.3f);
}

int test_check(char *file_name)
{
	FILE *input = NULL;
	char *block = NULL;

	block = malloc(100);
	check_mem(block, __func__);		// should work
	
	input = fopen(file_name, "r");
	check(input, "%s: Failed to open %s.", __func__, file_name);

	free(block);
	fclose(input);
	return 0;

error:
	if (block) free(block);
	if (input) fclose(input);
	return -1;
}

int test_sentinel(int code)
{
	char *temp = malloc(100);
	check_mem(temp, __func__);

	switch(code)
	{
		case 1:
			log_info("%s: It worked.", __func__);
			break;
		default:
			sentinel("%s: I shouldn't run.", __func__);
	}

	free(temp);
	return 0;

error:
	if(temp)
		free(temp);
	return -1;
}

int test_check_mem()
{
	char *test = NULL;
	check_mem(test, __func__);

	free(test);
	return 1;

error:
	return -1;
}

int test_check_debug()
{
	int i = 0;
	check_debug(i != 0, "%s: Oops, I was 0.", __func__);

	return 0;

error:
	return -1;
}

int main(int argc, char *argv[])
{
	check(argc == 2, "%s: Need an argument.", __func__);

	test_debug();
	test_log_err();
	test_log_warn();
	test_log_info();

	check(test_check("ex19.c") == 0, "%s: failed with ex19.c", __func__);
	//check(test_check("ex20.c") == 0, "%s: failed with ex20.c", __func__);
	check(test_check(argv[1]) == -1, "%s: failed with argv", __func__);
	check(test_sentinel(1) == 0, "%s: test_sentinel failed.", __func__);
	check(test_sentinel(100) == -1, "%s: test_sentinel failed.", __func__);
	check(test_check_mem() == -1, "%s: test_check_mem failed.", __func__);
	check(test_check_debug() == -1, "%s: test_check_debug failed.", __func__);

	return 0;

error:
	return 1;
}
