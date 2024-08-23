#include "dbg.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// zed's favorite feature of C is pointers to functions. It's really handy but you don't encounter it often because most C programmers don't use them for some reason.

// Debugging a core file with gdb to see the state of the program when it crashed: Sometimes core dumps aren't enabled on OSs. In my case, it already was so I didn't need to enable them for a shell session with `ulimit -c unlimited`. The systemd-coredump handler writes coredump files to /var/lib/systemd/coredump/. Old files are cleaned up periodically by systemd-tmpfiles(8). But the core files were compressed and `gdb <binary file> <core file>` wasn't running because the file format wasn't recognized. So I used `coredumpctl debug` or `coredumpctl gdb` to view the last generated dump. The debugger coredumpctl uses by default is gdb. From there I ran the usual gdb commands. Most importantly, I used `thread apply all bt full` and `bt full`. To check for stored core dumps you can also use `coredumpctl` or `coredumpctl list`. From there you can select the dump you want by PID using `coredumpctl debug <PID>`. There may be better ways to analyze a core dump file though. Maybe Binutils, Mozilla rr, or kdump.

void die(const char *message)
{
	if(errno)
		perror(message);
	else
		printf("ERROR: %s\n", message);

	exit(1);
}

// a typedef creates a fake type, in this case for a function pointer
typedef int (*compare_cb) (int a, int b);
typedef int *(*sorting_algorithm) (int *array, int size, compare_cb cmp);

int *bubble_sort(int *numbers, int count, compare_cb cmp)
{
	int *target = malloc(count * sizeof(int));
	if(!target)
		die("Memory error.");

	memcpy(target, numbers, count * sizeof(int));

	int temp;
	for(int i = 0; i < count; i++)
	{
		for(int j = 0; j < count - 1; j++)
		{
			if(cmp(target[j], target[j + 1]) > 0)
			{
				temp = target[j + 1];
				target[j + 1] = target[j];
				target[j] = temp;
			}
		}
	}

	return target;
}

int *selection_sort(int *numbers, int count, compare_cb cmp)
{
	int *target = malloc(count * sizeof(int));
	if(!target)
		die("Memory error.");

	memcpy(target, numbers, count * sizeof(int));

	int minIndex, minValue;
	for(int i = 0; i < count - 1; i++)
	{
		minIndex = i;
		minValue = target[i];
		for(int j = i + 1; j < count; j++)
		{ //if(numbers[j] < minValue)
			if(cmp(minValue, target[j]) > 0)
			{
				minValue = target[j];
				minIndex = j;
			}
		}
		target[minIndex] = target[i];
		target[i] = minValue;
	}

	return target;
}

int sorted_order(int a, int b)
{
	return a - b;
}

int reverse_order(int a, int b)
{
	return b - a;
}

int strange_order(int a, int b)
{
	if(a == 0 || b == 0)
		return 0;
	else
		return a % b;
}

void test_sorting(int *numbers, int count, sorting_algorithm sort, compare_cb cmp)
{
	int *sorted = sort(numbers, count, cmp);
	if(!sorted)
		die("Failed to sort as requested.");

	for(int i = 0; i < count; i++)
		printf("%d ", sorted[i]);
	
	printf("\n");

	free(sorted);
}

// in the video around 9:15, he speaks about how this is one of the major ways to hack or exploit C code. A lot of OSs don't have protection against overwriting executable code (binary) in RAM. You find a pointer pointing to somewhere random and you find a way to move it to a function or you write new code that you want. So either you overwrite the function with your own code that you want that's malicious or you find a spot in RAM where you can write the code and then you find a way to point a function pointer at that code in RAM.
void destroy(compare_cb cmp)
{
	unsigned char *data = (unsigned char *) cmp;

	for(int i = 0; i < 1; i++)
		data[i] = i;

	printf("\n");
}

// in the video around 6:30 he says this converts the binary code (the executable) that the CPU processes in RAM into character data. Because you can point any pointer at pretty much anywhere that your system or user owns or whatever it allows you can treat code like it's data. So this function prints the first bytes of the function, ie, the raw assembler byte code of the function itself. This won't break your program unless the CPU and OS you're on has a problem with you doing this.
void dump(compare_cb cmp)
{
	unsigned char *data = (unsigned char *) cmp;

	for(int i = 0; i < 25; i++)
		printf("%02x:", data[i]);

	printf("\n");
}

int main(int argc, char *argv[])
{
	if(argc < 2) die("USAGE: ex20 4 3 1 5 6");

	int count = argc - 1;

	int *numbers = malloc(count * sizeof(int));
	if(!numbers) die("Memory error.");

	char **inputs = argv + 1;
	for(int i = 0; i < count; i++)
		numbers[i] = atoi(inputs[i]);

	printf("Bubble sort:\n");
	test_sorting(numbers, count, bubble_sort, sorted_order);
	test_sorting(numbers, count, bubble_sort, reverse_order);
	test_sorting(numbers, count, bubble_sort, strange_order);

	printf("Selection sort:\n");
	test_sorting(numbers, count, selection_sort, sorted_order);
	test_sorting(numbers, count, selection_sort, reverse_order);
	test_sorting(numbers, count, selection_sort, strange_order);

	free(numbers);

	// strings you find are the easiest to change. So using a hex editor, "hack" is changed to "done". Follow these steps in order to find "done" in xxd and change it to something else if you like:
	// `nvim ex20`
	// `:%!xxd` (use the xxd(1) tool to convert a file to more readable format, and (this is the important bit), parse the edited "readable format" and write it back as binary data.)
	// `:set binary` or `:se binary` (MUST have binary option set before writing because if your environment is using a multibyte encoding (e.g. UTF-8, as most people use), Vim tries to encode the text as such, usually leading to file corruption.)
	// `/hack` (you will see it in the human readable right column)
	// hack in hex is 6861 636b (you will see it in the hex columns in the middle of the binary file.)
	// change this hex to a new hex of the same length using a text to hexadecimal converter online. Changes to the human readable column are ignored on write
	// `%!xxd -r > ex20` (saves the file to ex18 using the -r | -revert operation to convert hexdump into binary)
	// `l` to load the file again (should say converted)
	// `:w` (MUST have binary option set before writing because if your environment is using a multibyte encoding (e.g. UTF-8, as most people use), Vim tries to encode the text as such, usually leading to file corruption.)
	char * test = "hack";	
	printf("Hacked string via hex editor:\n%s\n", test);
	
	printf("SORTED:");
	dump(sorted_order);

	printf("REVERS:");
	dump(reverse_order);

	printf("STRANG:");
	dump(strange_order);

	printf("Purposely seg. faulting:\n");
	// according to valgrind alias, these seg fault bc "Bad permissions for mapped region at address 0x40147A". According to gdbSupervisor alias this address is the cmp parameter passed to destroy of type sorted_order.
	destroy(sorted_order);
	destroy(reverse_order);
	destroy(strange_order);

	printf("SORTED:");
	dump(sorted_order);

	printf("REVERSE SORTED:");
	dump(reverse_order);

	printf("STRANGE SORTED:");
	dump(strange_order);

	return 0;
}
