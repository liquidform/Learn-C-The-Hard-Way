// From https://www.baeldung.com/java-array-deque
//Notes on ArrayDeque (from link above):
//It’s not thread-safe
//Null elements are not accepted
//Works significantly faster than the synchronized Stack class
//It is a faster queue than LinkedList due to the better locality of reference
//Most operations have amortized constant time complexity
//An Iterator returned by an ArrayDeque is fail-fast
//ArrayDeque automatically doubles the size of an array when the head and tail pointer meets each other while adding an element

import java.util.*;

public class StackArrayDeque
{
	public static void main(String[] args) throws NoSuchElementException
	{
		Deque<String> stack = new ArrayDeque<>();

		stack.push("first");
		stack.push("second");

		System.out.println(stack.getFirst());

		stack.pop();

		System.out.println(stack.getFirst());
	}
}
