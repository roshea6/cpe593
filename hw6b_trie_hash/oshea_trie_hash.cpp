/*
	 Author: Ryan O'Shea

	 Description: Implementation of trie and linear chaining hashmap

	 cite: Just the stuff from the course github

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
	void load(const char dictionary[]) {

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
			char arr[temp.length()];

			for(int i = 0; i < sizeof(arr); i++)
			{
				arr[i] = temp[i];
			}
			
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

int main(int argc, char** atgv)
{
	Trie tri;

	// Add the words in the file to the trie
	tri.load("testAdd.txt");

	cout << "Words in common between testAdd and testContains: \n";

	// Test which words from the file are in the trie
	containsFileContents(&tri, "testContains.txt");

	cout << "\n";


	cout << "Words and prefixes in common between testAdd and testContains: \n";

	containsPrefixes(&tri, "testTriePrefix.txt");

	cout << "\n";


	removeFromTrie(&tri, "testRemove.txt");

	cout << "Trie after remove of words from testRemove \n";

	tri.print();

}