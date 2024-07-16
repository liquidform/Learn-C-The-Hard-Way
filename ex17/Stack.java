// From: https://algorithmtutor.com/Data-Structures/Basic/Stacks/ and https://www.programiz.com/dsa/stack

public class Stack
{
	private int[] stackArray;
	private int capacity;
	private int top;

	public Stack(int size)
	{
		stackArray = new int[size];
		capacity = size;
		top = -1;
	}

	public void push(int item)
	{
		if(top >= capacity - 1)
		{
			System.out.println("Error: Can not push item. Stack overflow!");
			System.exit(1); // or `return;`
		}

		stackArray[++top] = item;
	}

	public int pop()
	{
		if(top <= -1)
		{
			System.out.println("Error: Can not pop item. Stack underflow!");
			System.exit(1); // or `return -999999;`
		}

		return stackArray[top--];
	}

	public int peek()
	{
		if(top <= -1)
		{
			System.out.println("Error: Can not read item. Stack underflow!");
			System.exit(1); // or `return -999999;`
		}

		return stackArray[top];
	}

	public void printStack()
	{
		for(int i = 0; i <= top; i++)
			System.out.println(stackArray[i]);
	}

	public static void main(String[] args)
	{
		Stack stack = new Stack(10);
		stack.push(22);
		stack.push(44);
		stack.push(37);
		System.out.println(stack.peek());
		System.out.println(stack.pop());
		System.out.println(stack.peek());
		stack.printStack();
	}
}
