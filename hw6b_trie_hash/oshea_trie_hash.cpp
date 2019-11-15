/*
	 Author: Ryan O'Shea

	 Description: Implementation of trie and linear chaining hashmap

	 cite: https://www.geeksforgeeks.org/convert-string-char-array-cpp/
	 cplusplus.com/reference/functional/hash/ 

	 "I pledge my honor that I have abided by the Stevens Honor System"
*/

#include <iostream>
#include <fstream>
#include <string>


using namespace std;

class Trie {
private:
	class Node {
	public:
		Node* next[26];
		bool isWord;
		Node() {
			// make sure all pointers point to nullptr
			isWord = false;
			for(int i = 0; i < 26; i++)
			{
				next[i] = nullptr;
			}
		}
	};
	Node root;
public:
	Trie() {}
	~Trie() {}

	// load the trie from a file name given
	void load(const char dictionary[]) 
	{
		fstream file;
		file.open(dictionary);

		if(!file)
		{
			cout << "File not found \n";
			return;
		}

		Node* p = &root;

		string temp;

		while(file >> temp)
		{
			// Convert string to char array
			char arr[temp.length() + 1];

			for(int i = 0; i < sizeof(arr); i++)
			{
				arr[i] = temp[i];
			}

			arr[temp.length()] = '\0'; // Append ending character 

			// cout << temp << "\n";
			
			add(arr);
		}

		file.close();
	}

	Trie(const Trie& orig) = delete;
	Trie& operator =(const Trie& orig) = delete;

	// Add a word to the trie
	void add(const char word[])
	{
		Node* p = &root;

		// Loop through word. Char arrays end in 0 so loop until you hit that
		for(int i = 0; word[i] != 0; i++)
		{
			int idx = word[i] - 'a'; // Get the proper index from 0-25

			// Check for non lowercase a-z
			if(idx < 0 || idx > 25)
			{
				return;
			}

			if(p->next[idx] == nullptr)
			{
				// cout << "Making new node for letter " << word[i] << "\n";
				p->next[idx] = new Node();
			}

			p = p->next[idx];
		}
		p->isWord = true;
	}

	// Remove a word from the trie. 
	void remove(const char word[])
	{
		Node* p = &root;

		// Loop through word until you hit the end
		for(int i = 0; word[i] != 0; i++)
		{
			int idx = word[i] - 'a'; // Get the proper index from 0-25

			// Check for non lowercase a-z
			if(idx < 0 || idx > 25)
			{
				return;
			}

			if(p->next[idx] == nullptr)
			{
				return;
			}

			p = p->next[idx];
		}
		p->isWord = false;
	}

	// Returns if the trie dictionary contains the word
	bool contains(const char word[])
	{
		Node* p = &root;

		// Loop through word until you hit the end
		for(int i = 0; word[i] != 0; i++)
		{
			int idx = word[i] - 'a'; // Get the proper index from 0-25

			// Check for non lowercase a-z
			if(idx < 0 || idx > 25)
			{
				return false;
			}

			if(p->next[idx] == nullptr)
			{
				return false;
			}

			p = p->next[idx];
		}
		return p->isWord;
	}	

	// Returns if the word contains the prefix at all 
  	bool containsPrefix(const char word[])
	{
		Node* p = &root;

		// Loop through word until you hit the end
		for(int i = 0; word[i] != 0; i++)
		{
			int idx = word[i] - 'a'; // Get the proper index from 0-25

			// Check for non lowercase a-z
			if(idx < 0 || idx > 25)
			{
				return false;
			}

			if(p->next[idx] == nullptr)
			{
				return false;
			}

			p = p->next[idx];
		}
		return true;
	}

	// Driver function to print the contents of the tree
	void print()
	{
		char buf[100];
		printTree(&root, 0, buf);
	}

	// Prints all words stored in the trie dictionary
	void printTree(Node * p, int level, char buf[]) const
	{
		// If a word is found print it out
		if(p->isWord)
		{
			buf[level] = '\0'; // Add string terminating character 
			cout << buf << "\n";
		}

		for(int i = 0; i < 26; i++)
		{
			if(p->next[i] != nullptr)
			{
				buf[level] = 'a' + i;
				printTree(p->next[i], level + 1, buf);
			}		
		}
	}
}; 

template<typename T>
	class Node { //Node object to make the linked list out of
	public:
		T val;
		Node* next; // Points to the next Node object in the list or nullptr

		// Constructor
		Node(T v, Node* n) : val(v), next(n) {}
	};

template<typename T>
class LinkedList
{
private:
	// class Node { //Node object to make the linked list out of
	// public:
	// 	T val;
	// 	Node* next; // Points to the next Node object in the list or nullptr

	// 	// Constructor
	// 	Node(T v, Node* n) : val(v), next(n) {}
	// };


public:
	// Pointer to first node in the list
	Node<T>* head;

	// Constructor
	LinkedList()
	{
		head = nullptr;
	}

	// Add Node to start of linked list.
	// Head -> New Node -> whatever head was pointing to
	void addStart(T v)
	{
		head = new Node<T>(v, head);
	}

	// Add Node to the end of the linked list
	// Head -> middle stuff -> New Node -> nullptr
	void addEnd(T v)
	{
		Node<T>* temp = new Node<T>(v, nullptr); // Node being placed at the end
		Node<T>* n;

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
	void insert(int i, T v)
	{
		Node<T>* n = head;

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
		n->next = new Node<T>(v, n->next);
	}

	// Remove the node at the beginning of the list and return its value
	// head -> old node -> what old node was pointing to
	// becomes
	// head -> what old node was pointing to
	T removeStart()
	{
		Node<T>* n = head; // Point to whatever head is pointing at to save the node temporarily
		head = head->next; // Remove the node from the list
		return n->val; // Return the value from the removed node
	}

	// Remove the node at the end of the list
	// head -> middle stuff -> last node -> nullptr
	// becomes
	// head -> middle stuff -> nullptr
	T removeEnd()
	{
		Node<T>* n = head;
		Node<T>* m = n->next;

		// There's only one node in the list
		if(m == nullptr)
		{
			T v = head->val; // Get the value
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
	T remove(int i)
	{
		Node<T>* n = head;
		Node<T>* m = n->next;

		// If we want to remove the first node
		if(i == 0)
		{
			return removeStart();
		}

		// There's only one node in the list
		if(m == nullptr)
		{
			T v = head->val; // Get the value
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
	T getVal(int i)
	{
		Node<T>* n = head;

		// Move the pointer until we've reached the desired node
		while(i > 0)
		{
			n = n->next;
			i--;
		}

		// We're at the desired node so return the value
		return n->val;
	}

	// Return the value stored in the node at the specified index
	void updateVal(int i, T newVal)
	{
		Node<T>* n = head;

		// Move the pointer until we've reached the desired node
		while(i > 0)
		{
			n = n->next;
			i--;
		}

		// We're at the desired node so return the value
		n->val = newVal;
	}

	// Returns the length of the Linkedlist
	int getLength()
	{
		Node<T>* n;
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
		Node<T>* n = head;

		for(; n != nullptr; n = n->next)
		{
			cout << n->val << " ";
		}
		cout << "\n";
	}

};

class HashMapLinearChaining {
private:
	uint32_t size;
	LinkedList<string>* table;

	
public:
	HashMapLinearChaining(uint32_t buckets) {
		table = new LinkedList<string>[buckets];
		size = buckets;
	}
	~HashMapLinearChaining() {}
	HashMapLinearChaining(const HashMapLinearChaining& orig) = delete;
	HashMapLinearChaining& operator =(const HashMapLinearChaining& orig) = delete;
	
	// Add a new word to to the hash map
	void add(const string& s) 
	{
		// Get the position by taking hashing the key
		hash<string> get_pos;
		int pos = get_pos(s) % size;
		
		cout << "pos = " << pos << "\n";

		LinkedList<string>* p = &table[pos];
		// p->addStart(s);

		Node<string>* n = p->head;

		int idx = 0;

		// Check if item already exists in the hash map
		while(n != nullptr)
		{
			// If it does then update its value
			if(p->getVal(idx) == s)
			{
				p->updateVal(idx, s);
				cout << "Updating value for " << s << "\n";
				return;
			}
			idx++;
			n = n->next;
		}

		// If the value didn't previously exist make add it as a new entry 
		p->addStart(s);
	}

	void remove(const string& s) 
	{

	}
	bool contains(const string& s) 
	{
		// Get the position by taking hashing the key
		hash<string> get_pos;
		int pos = get_pos(s) % size;
		
		cout << "pos = " << pos << "\n";

		LinkedList<string>* p = &table[pos];
		// p->addStart(s);

		Node<string>* n = p->head;

		int idx = 0;

		// Check if item already exists in the hash map
		while(n != nullptr)
		{
			// If it does then update its value
			if(p->getVal(idx) == s)
			{
				cout << "Found it at "<< idx << " \n";
				return true;
			}
			idx++;
			n = n->next;
		}

		// If we made it through the entire linkedlist without finding it then return false
		return false;
	}

	void computeHistogram() {
    // generate an array of 10 elements
		//hist[0] = number of empty bins
		// hist[1] = number of bins containing 1 element
		// hist[2] = number of bins containing 2 elements...

		// hist[9] = number of bins containing 9 OR GREATER
		//		print all non-zero bins:
	}
};

// Prints out all the words in a given file that the passed in trie contains
void containsFileContents(Trie* tri, string filename)
{
	fstream file;
	file.open(filename);

	if(!file)
	{
		cout << "File not found \n";
		return;
	}

	string temp;

	while(file >> temp)
	{
		// Convert string to char array
		char arr[temp.length()];

		for(int i = 0; i < sizeof(arr); i++)
		{
			arr[i] = temp[i];
		}
		
		if(tri->contains(arr))
		{
			cout << temp << "\n";
		}
	}

	file.close();
}

// Prints out all the prefixes and words in a given file that the passed in trie contains
void containsPrefixes(Trie* tri, string filename)
{
	fstream file;
	file.open(filename);

	if(!file)
	{
		cout << "File not found \n";
		return;
	}

	string temp;

	while(file >> temp)
	{
		// Convert string to char array
		char arr[temp.length()];

		for(int i = 0; i < sizeof(arr); i++)
		{
			arr[i] = temp[i];
		}
		
		if(tri->containsPrefix(arr))
		{
			cout << temp << "\n";
		}
	}

	file.close();
}

// Removes all the words from the trie that are in the passed in file
void removeFromTrie(Trie* tri, string filename)
{
	fstream file;
	file.open(filename);

	if(!file)
	{
		cout << "File not found \n";
		return;
	}

	string temp;

	while(file >> temp)
	{
		// Convert string to char array
		char arr[temp.length()];

		for(int i = 0; i < sizeof(arr); i++)
		{
			arr[i] = temp[i];
		}
		
		tri->remove(arr);
	}

	file.close();
}

int prideNonWords(Trie* dict, string filename)
{
	fstream file;
	file.open(filename);

	int count = 0;

	if(!file)
	{
		cout << "File not found \n";
		return -1;
	}

	string temp;

	while(file >> temp)
	{
		// Convert string to char array
		char arr[temp.length() + 1];

		for(int i = 0; i < sizeof(arr); i++)
		{
			arr[i] = temp[i];
		}

		// Add ending character
		arr[temp.length()] = '\0';
		
		if(dict->contains(arr))
		{
			continue;
		}
		else
		{
			count++;
		}
	}

	file.close();

	return count;
}

int main(int argc, char** atgv)
{
	// Trie portion 
	// Trie tri;

	// // Add the words in the file to the trie
	// tri.load("testAdd.txt");

	// cout << "Words in common between testAdd and testContains: \n";

	// // Test which words from the file are in the trie
	// containsFileContents(&tri, "testContains.txt");

	// cout << "\n";


	// cout << "Words and prefixes in common between testAdd and testContains: \n";

	// containsPrefixes(&tri, "testTriePrefix.txt");

	// cout << "\n";


	// removeFromTrie(&tri, "testRemove.txt");

	// cout << "Trie after removal of words from testRemove \n";

	// tri.print();

	// Pride and prejuidice Trie 

	// Trie prideTrie;

	// prideTrie.load("dict.txt");

	// cout << "Number of non-dictionary entries: " << prideNonWords(&prideTrie, "prideandprejudice.txt") << "\n";


	// Hashmap portion

	// hash<string> str_hash;
	// string str1 = "world";

	// cout << str1 << " = " << str_hash(str1) << "\n";

	HashMapLinearChaining hash_map(500000);

	string str1 = "Hello";

	hash_map.add(str1);

	string str2 = "World";

	hash_map.add(str2);

	string str3 = "Hello";
	hash_map.add(str3);

}