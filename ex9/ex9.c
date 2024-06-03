#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int i = 0;
    while (i < 25) {
		// Ignores loop iterations where i is odd
		if(i % 2 > 0)
		{
			i++;
			continue;
		} else if(i > 23) // All even numbers are printed except for 24
		{
			break;
		} else // As a result of the first if test, only even numbers are printed
		{
        	printf("%d\n", i);
		}
        i++;
    }

	i = 1;
	while(i <= argc)
	{
		if(!strcmp(argv[i], "Happy"))
		{
			printf("You are %s. No help needed!\n", argv[i]);
			// Exits out of compound statement, ie, the while loop
			break;
		} else if(!strcmp(argv[i], "Sad"))
		{
			printf("You are %s\n", argv[i]);
		} else
		{
			printf("You are neither happy nor sad. There's the possibility that you're angry and I'm running away.\n");
			// Continue to the top of the loop. Won't increment i so this causes potentially an infinite loop depending on the order and content of argv
			continue;
		}
		i++;
	}

    return 0;
}
