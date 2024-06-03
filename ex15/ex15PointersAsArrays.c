#include <stdio.h>

// Very helpful Pointers and Arrays link and other ways to do fourth for loop in commented out block of code

// forward declarations
void indexing(char *charPtrArray[], int *intArray, int size);
void pointers(char **charPtrArray, int *intArray, int size); 
void pointersLikeArrays(char **charPtrArray, int *intArray, int size); 
void pointersStupidly(char **charPtrArray, char *charPtrArrayOrig[], int *intArray, int size); 
void pointerAddr(char **charPtrArray, int *intArray, int size);

void indexing(char *charPtrArray[], int *intArray, int size)
{
    // first way using indexing
	for (int i = 0; i < size; i++) {
        printf("%s has %d years alive.\n", charPtrArray[i], intArray[i]);
    }

    printf("---\n");
}

void pointers(char **charPtrArray, int *intArray, int size)
{
    // second way using pointers
    for (int i = 0; i < size; i++) {
        printf("%s is %d years old.\n",
                *(charPtrArray + i), intArray[i]);
    }

    printf("---\n");
}

void pointersLikeArrays(char **charPtrArray, int *intArray, int size)
{
    // third way, pointers are similar to arrays
    for (int i = 0; i < size; i++) {
        printf("%s is %d years old again.\n", charPtrArray[i], intArray[i]);
    }

	printf("---\n");
}

void pointersStupidly(char **charPtrArray, char *charPtrArrayOrig[], int *intArray, int size)
{
	char **charPtrArrayCopy = charPtrArray;
	char **charPtrArrayOrigCopy = charPtrArrayOrig;
	// if declaring inside for loop I get errors
	int i = 0;
    // fourth way with pointers in a stupid complex way
    for (i = 0, charPtrArrayCopy = charPtrArrayOrigCopy;
            (charPtrArrayCopy - charPtrArrayOrigCopy) < size; charPtrArrayCopy++, i++) {
        printf("%s lived %d years so far.\n", *charPtrArrayCopy, intArray[i]);
    }

//	char **namesCopy;
//	int agesArray[5] = {ages[0], ages[1], ages[2], ages[3], ages[4]};
//	for (namesCopy = names, i = 0; i < count; i++) {
//    	printf("%s lived %d years so far.\n", *(namesCopy + i), agesArray[i]);    
		// compiler says (namesCopy + i) is char ** but %s is char *. The name of the array, when used by itself as an expression (other than in sizeof), stands for a pointer to the array’s zeroth element. Thus, array + 3 converts array implicitly to &array[0], and the result is a pointer to element 3, equivalent to &array[3]. Very helpful source where this is explained as well as more: https://www.gnu.org/software/c-intro-and-ref/manual/html_node/Pointers-and-Arrays.html
//    	printf("%s lived %d years so far.\n", (namesCopy + i), agesArray[i]);    
//	 	printf("%s lived %d years so far.\n", namesCopy[i], agesArray[i]);    
//	}

	printf("---\n");
}

void pointerAddr(char **charPtrArray, int *intArray, int size)
{
    printf("Address of cur_name: %p\nAddress of cur_age: %p\n", (void *) charPtrArray, (void *) intArray);
    for (int i = 0; i < size; i++) {
        printf("Address of cur_name[%d]: %p\nAddress of cur_age[%d]: %p\n", i, (void *) (charPtrArray + i), i, (void *) &intArray[i]);
        //printf("Address of cur_name[%d]: %p\nAddress of cur_age[%d]: %p\n", i, (void *) (cur_name + i), i, (void *) (cur_age + i));
    }
}

int main(int argc, char *argv[])
{
    // create two arrays we care about
    int ages[] = { 23, 43, 12, 89, 2 };
//    char *names[] = {
//        "Alan", "Frank",
//        "Mary", "John", "Lisa"
//    };
	char name1[5] = {'A', 'l', 'a', 'n', '\0'};
	char name2[6] = {'F', 'r', 'a', 'n', 'k', '\0'};
	char name3[5] = {'M', 'a', 'r', 'y', '\0'};
	char name4[5] = {'J', 'o', 'h', 'n', '\0'};
	char name5[5] = {'L', 'i', 's', 'a', '\0'};
	char *names[] = {name1, name2, name3, name4, name5};

    // safely get the size of ages
    int count = sizeof(ages) / sizeof(int);
    int i = 0;

	indexing(names, ages, count);

    // setup the pointers to the start of the arrays
    //int *cur_age = (int *)names;
	//int *cur_age = ages;
	int cur_age[5] = {ages[0], ages[1], ages[2], ages[3], ages[4]};
    char **cur_name = names;

	pointers(cur_name, cur_age, count);

	pointersLikeArrays(cur_name, cur_age, count);

	pointersStupidly(cur_name, names, cur_age, count);

	pointerAddr(cur_name, cur_age, count);

	return 0;

}
