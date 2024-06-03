#include <stdio.h>

// Go with arrays anytime you can for simpler code that is usually just as fast, and then only use pointers as a performance optimization if you absolutely have to. At the beginning of C history, the compilers weren't optimized for arrays as they were pointers, but now they are most of the time.

// C Pointers Manual: https://www.gnu.org/software/c-intro-and-ref/manual/html_node/Pointers.html#Pointers

int main(int argc, char *argv[])
{
    // create two arrays we care about
	// this also works
	//int ages[] = { 23, 43, 12, 89, 2 }
	//int *cur_age = ages;
    int ages[5];
	// int * is like an array of integers
	int *cur_age = ages;
	// Incrementing a variable means adding 1 to it, as in p = p + 1. Since p is a pointer, adding 1 to it advances it by the width of the datum it points to—in this case, sizeof (int). Source: https://www.gnu.org/software/c-intro-and-ref/manual/html_node/Pointer-Increment_002fDecrement.html
// 	*cur_age = 23;
//	cur_age++;
// 	*cur_age = 43;
//	cur_age++;
// 	*cur_age = 12;
//	cur_age++;
// 	*cur_age = 89;
//	cur_age++;
// 	*cur_age = 2;
//	cur_age++;
//	// this line is needed to point cur_age back to &ages[0]
//	cur_age = ages;
	// dereference the address of ages[0], ie *&ages[0] or *ages, which is the value there and assign 23 to that element
 	cur_age[0] = 23;
 	cur_age[1] = 43;
 	cur_age[2] = 12;
 	cur_age[3] = 89;
 	cur_age[4] = 2;
	// pointer to int[]. ‘double (*ptrda)[5];’ means, “if you dereference ptrda, then subscript it by an integer less than 5, you get a double.” The parentheses express the point that you would dereference it first, then subscript it. Source: https://www.gnu.org/software/c-intro-and-ref/manual/html_node/Pointer-Declarations.html
	//int (*cur_age)[] = &ages;
	// char ** is like an array of char * aka an array of character arrays aka an array of strings
	char *names[] = {"Alan", "Frank", "Mary", "John", "Lisa"};
    char **cur_name = names;
	
    // safely get the size of ages. [Me speaking: The following source says nothing about different sizes on different platforms for any other type of integer other than long aka long int. So I think he means if ages was declared as a long aka long int since this data type can be a different size depending on the system. Typically 8 bytes, 64 bits, on 64 bit computers vs. 4 bytes, 32 bits, on 32 bit computers. Source: https://www.gnu.org/software/c-intro-and-ref/manual/html_node/Basic-Integers.html]
    int count = sizeof(ages) / sizeof(int);
    int i = 0;

    // first way using indexing
    for (i = 0; i < count; i++) {
//	for(i = count - 1; i >= 0; i--)
        //printf("%s has %d years alive.\n", names[i], ages[i]);

		// all three print statements below print the same thing. See notes in ex15PointersAsArrays and/or this link: https://www.gnu.org/software/c-intro-and-ref/manual/html_node/Pointers-and-Arrays.html
        printf("%s has %d years alive.\n", cur_name[i], cur_age[i]);
        //printf("%s has %d years alive.\n", *(cur_name + i), cur_age[i]);
        //printf("%s has %d years alive.\n", *(&cur_name[0] + i), cur_age[i]);
        //printf("%s has %d years alive.\n", *&cur_name[i], cur_age[i]);
    }

    printf("---\n");

	i = 0;
	while(i < count)
	{
        printf("%s has %d years alive.\n", cur_name[i], cur_age[i]);
		i++;
	}

	printf("---\n");

    // setup the pointers to the start of the arrays
    //int *cur_age = (int *)names;
	//int *cur_age = ages;
	int *cur_age_array[] = {&cur_age[0], &cur_age[1], &cur_age[2], &cur_age[3], &cur_age[4]};
	// this also works (must initialize a pointer to some memory address otherwise it's a wild pointer; in this case an array of five 0's). Wild Pointers are pointers that have not been initialized with something yet. These types of C-pointers can cause problems in our programs and can eventually cause them to crash. If values is updated using wild pointers, they could cause data abort or data corruption. Source: https://www.geeksforgeeks.org/c-pointers/
//	int *cur_age_array[5] = {0};
//	cur_age_array[0] = &cur_age[0];
//	cur_age_array[1] = &cur_age[1];
//	cur_age_array[2] = &cur_age[2];
//	cur_age_array[3] = &cur_age[3];
//	cur_age_array[4] = &cur_age[4];
	// int ** is like an array of int *, ie integer pointers, and int * is like an array of integers
	int **cur_age_ptrs = cur_age_array;
    //char **cur_name = names;
	char **cur_name_array[] = {&cur_name[0], &cur_name[1], &cur_name[2], &cur_name[3], &cur_name[4]};
	// char *** is like an array of char ** which is like an array of char * aka an array of character arrays aka an array of strings
	char ***cur_name_ptrs = cur_name_array;

    // second way using pointers
    for (i = 0; i < count; i++) {
        printf("%s is %d years old.\n",
                //*(cur_name + i), *(cur_age + i));
                **(cur_name_ptrs + i), **(cur_age_ptrs + i));
    }

    printf("---\n");

	i = 0;
	while(i < count)
	{
        printf("%s is %d years old.\n",
                **(cur_name_ptrs + i), **(cur_age_ptrs + i));
		i++;
	}

	printf("---\n");

    // third way, pointers are similar to arrays
    for (i = 0; i < count; i++) {
        //printf("%s is %d years old again.\n", cur_name[i], cur_age[i]);
        printf("%s is %d years old again.\n", *cur_name_ptrs[i], *cur_age_ptrs[i]);
    }

    printf("---\n");

	i = 0;
	while(i < count)
	{
        printf("%s is %d years old again.\n", *cur_name_ptrs[i], *cur_age_ptrs[i]);
		i++;
	}

	printf("---\n");

	// Initialize our for-loop by setting cur_name and cur_age to the beginning of the names and ages arrays. 
	// The test portion of the for-loop then compares the distance of the pointer cur_age from the start of ages. The short answer for why this works is: Pointer subtraction works by subtracting p1’s numeric value from p3’s, and dividing by target object size. Read on for more explanation. The difference between two pointers has type int, or long if necessary (see Integer Types [I put this link above where count is assigned]). The clean way to declare it is to use the typedef name ptrdiff_t defined in the file stddef.h. C defines pointer subtraction to be consistent with pointer-integer addition, so that (p3 - p1) + p1 equals p3, as in ordinary algebra. Pointer subtraction works by subtracting p1’s numeric value from p3’s, and dividing by target object size [me speaking; target object size must be 4 bytes (see math below for reasoning) which is the size of int and is the data type of cur_age and ages]. The two pointer arguments should point into the same array. Source: https://www.gnu.org/software/c-intro-and-ref/manual/html_node/Pointer-Arithmetic.html
	// The output of (void *) cur_age - (void *) ages: 0x7ffefda7e6d0 - 0x7ffefda7e6d0 = 0 (in decimal)
	// The output of (void *) cur_age - (void *) ages: 0x7ffefda7e6d4 - 0x7ffefda7e6d0 = 4 (in decimal)
	// The output of (void *) cur_age - (void *) ages: 0x7ffefda7e6d8 - 0x7ffefda7e6d8 = 8 (in decimal)
	// And so on...
	// 0 / 4 = 0. 4 / 4 = 1. 8 / 4 = 2 (where 4 is the size in bytes of type int). And so on...The division results match (cur_age - ages) with each iteration of for loop.
    // fourth way with pointers in a stupid complex way
//    for (cur_name = names, cur_age = ages;
//            (cur_age - ages) < count; cur_name++, cur_age++) {
//        printf("%s lived %d years so far.\n", *cur_name, *cur_age);
//    }
    for (cur_name_ptrs = cur_name_array, cur_age_ptrs = cur_age_array;
            (cur_age_ptrs - cur_age_array) < count; cur_name_ptrs++, cur_age_ptrs++) {
        printf("%s lived %d years so far.\n", **cur_name_ptrs, **cur_age_ptrs);
    }

	printf("---\n");

	i = 0;
	cur_name_ptrs = cur_name_array;
	cur_age_ptrs = cur_age_array;
	while((cur_age_ptrs - cur_age_array) < count)
	{
        printf("%s lived %d years so far.\n", **cur_name_ptrs, **cur_age_ptrs);
		cur_name_ptrs++;
		cur_age_ptrs++;
	}

    return 0;
}
