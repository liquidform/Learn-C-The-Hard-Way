// From https://dev.to/josethz00/data-structures-in-c-stack-55c7
// For uint64_t: https://www.badprog.com/c-type-what-are-uint8-t-uint16-t-uint32-t-and-uint64-t
// When to set pointers to NULL to prevent dangling pointer vulnerabilites: https://stackoverflow.com/a/1025604

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#define STACK_LENGTH 513

// From comment at dev.to link: The reason for using uint64_t is because then you can put any type you like in the stack. It's also guaranteed to work on all platforms, specifically 32-bit platforms where sizeof(void*) is 4 — uint64_t guarantees 8.
typedef uint64_t TmpT;

typedef struct stack
{
	int max;
	int top;
	TmpT *item;
} Stack;

Stack *stack(int m)
{
	// `Stack *` aka `struct stack *`
	Stack *S = (Stack *) malloc(sizeof(struct stack));
	S->max = m;
	S->top = -1;
	if(sizeof(TmpT) <= sizeof(uint64_t))
		S->item = (TmpT *) malloc(m * sizeof(TmpT));
	return S;
}

int is_empty_S(Stack S)
{
	return (S.top == -1);
}

int is_full_S(Stack S)
{
	return (S.top == S.max - 1);
}

void push_S(TmpT x, Stack *S)
{
	if(is_full_S(*S))
	{
		puts("Stack full!");
		abort();
	}
	
	S->top++;
	S->item[S->top] = x;
}

TmpT pop_S(Stack *S)
{
	if(is_empty_S(*S))
	{
		puts("Stack empty!");
		abort();
	}

	TmpT x = S->item[S->top];
	S->top--;

	return x;
}

TmpT top_S(Stack S)
{
	if(is_empty_S(S))
	{
		puts("Stack empty!");
		abort();
	}

	return S.item[S.top];
}

void destroy_S(Stack *S)
{
	free(S->item);
	free(S);
	S = NULL;
}

int main(void)
{
//	char c[STACK_LENGTH];
//	Stack *s = stack(STACK_LENGTH);
//
//	puts("Type a chain of characters: ");
//	fgets(c, STACK_LENGTH, stdin);
//
//	for(int i = 0; c[i]; i++)
//		push_S(c[i], s);
//
//	puts("Reversed chain: ");
//
//	while(!is_empty_S(*s))
//		printf("%c", pop_S(s));
//
//	puts("\n");
//
//	destroy_S(s);
//
//	return 0;

	int n;
	Stack *s = stack(8);

	puts("Enter a decimal number: ");
	scanf("%d", &n);

	printf("The binary representation of %d is: ", n);

	do
	{
		push_S(n % 2, s);
		n /= 2;
	} while(n > 0);

	while(!is_empty_S(*s))
		printf("%ld", pop_S(s));

	puts("\n");

	destroy_S(s);

	return 0;
}
