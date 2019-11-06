/*
	 Author: Ryan O'Shea

	 Description: Takes in the list from a file and then splits it into two seperate
	 linked lists where one is numbers and one is odd numbers

	 cite:

	 "I pledge my honor that I have abided by the Stevens Honor System"
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class LinkedList{
private:
	class Node { //Node object to make the linked list out of
	public:
		int val;
		Node* next; // Points to the next Node object in the list or nullptr

		// Constructor
		Node(int v, Node* n) : val(v), next(n) {}
	};

	// Pointer to first node in the list
	Node* head;

public:
	// Constructor
	LinkedList()
	{
		head = nullptr;
	}

	// Add Node to start of linked list.
	// Head -> New Node -> whatever head was pointing to
	void addStart(int v)
	{
		head = new Node(v, head);
	}

	// Add Node to the end of the linked list
	// Head -> middle stuff -> New Node -> nullptr
	void addEnd(int v)
	{
		Node* temp = new Node(v, nullptr); // Node being placed at the end
		Node* n;

		// Check if there are no nodes in the list
		if(head == nullptr)
		{
			head = temp;
			return;
		}

		// Loop until the end of the list is found
		// Once n->next == nullptr the last node in the list has been found
		for(n = head; n->next != nullptr; n = n->next)
		{
			// Do nothing
		}

		// n now points to the last node in the list so switch the node that points
		// to from nullptr to the node we want to add to the end
		n->next = temp;
	}

	// Inserts a node at a specified index i
	// Head -> middle stuff -> node at desired index -> new node -> whatever node at desired index at desired index was pointing to
	void insert(int i, int v)
	{
		Node* n = head;

		// Check if it's inserting in the first index
		if(i == 0)
		{
			addStart(v);
			return;
		}

		// Move the pointer until we've reached the desired node
		while(i > 0)
		{
			n = n->next;
			i--;
		}

		// We're at the desired node so insert the new one between the two
		n->next = new Node(v, n->next);
	}

	// Remove the node at the beginning of the list and return its value
	// head -> old node -> what old node was pointing to
	// becomes
	// head -> what old node was pointing to
	int removeStart()
	{
		Node* n = head; // Point to whatever head is pointing at to save the node temporarily
		head = head->next; // Remove the node from the list
		return n->val; // Return the value from the removed node
	}

	// Remove the node at the end of the list
	// head -> middle stuff -> last node -> nullptr
	// becomes
	// head -> middle stuff -> nullptr
	int removeEnd()
	{
		Node* n = head;
		Node* m = n->next;

		// There's only one node in the list
		if(m == nullptr)
		{
			int v = head->val; // Get the value
			head = nullptr; // Remove the node
			return v;
		}

		// Loop until the end of the list is found by m.
		// Once m->next == nullptr, n will point to the 2nd to last node
		for(; m->next != nullptr;)
		{
			n = m; // Move n to m
			m = m->next; // Move up m to the next node
		}

		// n now points to the 2nd to last node and m points to the last node
		n->next = nullptr; // Remove the last node
		return m->val;
	}

	// Remove the node at the specified index
	// Head -> middle stuff -> node at desired index -> whatever node at desired index at desired index is pointing to
	// becomes
	// Head -> middle stuff -> whatever node at desired index at desired index was pointing to
	// TODO: Doesn't work for first element in list or last element
	int remove(int i)
	{
		Node* n = head;
		Node* m = n->next;

		// If we want to remove the first node
		if(i == 0)
		{
			return removeStart();
		}

		// There's only one node in the list
		if(m == nullptr)
		{
			int v = head->val; // Get the value
			head = nullptr; // Remove the node
			return v;
		}

		// Move the pointer until we've reached the desired node
		while(i > 1)
		{
			n = m;
			m = m->next;
			i--;
		}

		// n now points to the node before the node to remove and m points to
		// the node to remove
		n->next = m->next; // Remove the desired node
		return m->val;
	}

	// Return the value stored in the node at the specified index
	// TODO: After the first element all the indexes become off by one
	int getVal(int i)
	{
		Node* n = head;

		// Move the pointer until we've reached the desired node
		while(i > 0)
		{
			n = n->next;
			i--;
		}

		// We're at the desired node so return the value
		return n->val;
	}

	// Returns the length of the Linkedlist
	int getLength()
	{
		Node* n;
		int count = 0;

		// Check if there are no nodes in the list
		if(head == nullptr)
		{
			return 0;
		}

		// Loop until the end of the list is found
		// Once n->next == nullptr the last node in the list has been found
		for(n = head; n->next != nullptr; n = n->next)
		{
			count++;
		}
		return count + 1;
	}

	// Display all the numbers in the LinkedList
	void display()
	{
		Node* n = head;

		for(; n != nullptr; n = n->next)
		{
			cout << n->val << " ";
		}
	}

};

// Loop through a linked list, remove all the even numbers and return them in a 2nd
// linked list
LinkedList splitOddsAndEvens(LinkedList* listA)
{
	LinkedList listB;

	int val = 0;
	int len = listA->getLength();

	for(int i = 0; i < len;)
	{
		val = listA->getVal(i);

		// If the value is even remove it from A and add it to B
		if(val%2 == 0)
		{
			listB.addEnd(val);
			listA->remove(i);
			len--;	//Update length value
		}

		// Only increment when an odd number is found so we don't miss two evens
		 // in a row
		else
		{
			i++;
		}

	}

	return listB;
}

// Read the contents out of a file and returns them as a LinkedList
LinkedList loadFile()
{
	fstream file;
	file.open("hw5.dat");

	int x;

	LinkedList list;

	// Load the contents of the file into the linkedList
	while(file >> x)
	{
		list.addEnd(x);
	}

	file.close();

	return list;
}

int main(int argc, char **argv)
{
	LinkedList listA = loadFile();

	listA.display();
	cout << "\n";

	LinkedList listB = splitOddsAndEvens(&listA);

	// LinkedList listB;
	//
	// int val = listA.getVal(0);
	//
	// listB.addEnd(val);
	//
	// // listA.insert(2, 999);
	// // listA.insert(5, 1000);
	//
	// listA.remove(listA.getLength() - 1);

	listA.display();
	cout << "\n";
	listB.display();
	cout << "\n";

}
