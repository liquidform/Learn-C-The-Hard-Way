#include <stdio.h>
#include <ctype.h>

int main (int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("ERROR: You need one argument.\n");
		// this is how you abort a program
		return 1;
	}

	char letter;
	for (int j = 1; j < argc; j++)
	{
		for (int i = 0; letter = tolower(argv[j][i]), argv[j][i] != '\0'; i++)
		{
			switch (letter)
			{
				case 'a':
					printf("%d: 'A'\n", i);
					break;

				case 'e':
					printf("%d: 'E'\n", i);
					break;

				case 'i':
					printf("%d: 'I'\n", i);
					break;

				case 'o':
					printf("%d: 'O'\n", i);
					break;

				case 'u':
					printf("%d: 'U'\n", i);
					break;

				case 'y':
					if (i > 2)
					{
						// it's only sometimes Y
						printf("%d: 'Y'\n", i);
					} else 
						printf("%d: %c is not a vowel unless it's the 4th character or greater\n", i, letter);
					break;

				default:
					printf("%d: %c is not a vowel\n", i, letter);
			}
		}
		// print a newline character after processing each argument UNLESS it's the last argument
		if (j < argc - 1)
		{
			printf("\n");
		}
	}

//	char letter;
//	for (int j = 1; j < argc; j++)
//	{
//		for (int i = 0; letter = tolower(argv[j][i]), argv[j][i] != '\0'; i++)
//		{
//			if (letter == 'a')
//			{
//				printf("%d: 'A'\n", i);
//			} else if (letter == 'e')
//			{
//				printf("%d: 'E'\n", i);
//			} else if (letter == 'i')
//			{
//				printf("%d: 'I'\n", i);
//			} else if (letter == 'o')
//			{
//				printf("%d: 'O'\n", i);
//			} else if (letter == 'u')
//			{
//				printf("%d: 'U'\n", i);
//			} else if (letter == 'y')
//			{
//				if (i > 2)
//				{
//					// it's only sometimes Y
//					printf("%d: 'Y'\n", i);
//				}
//			} else
//			{
//				printf("%d: %c is not a vowel\n", i, letter);
//			}
//		}
//		// print a newline character after processing each argument UNLESS it's the last argument
//		if (j < argc - 1)
//		{
//			printf("\n");
//		}
//	}

	return 0;
}
