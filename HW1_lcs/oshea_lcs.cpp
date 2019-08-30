/*
	 Author: Ryan O'Shea

	 Description: Takes in the two specified files via the terminal and finds the
	 number of bytes in common as well as the longest common subsequence (LCS)
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Function that returns the contents of the specified filename as a string
string loadFile(string filename)
{
	string file_contents = "";
	string data;

	// Declare file object and open specified file
	fstream file;
	file.open(filename);

	// Check if the file opening failed
	if(!file)
	{
		cout << "Error opening the file \n";
		exit(1); //Exit the program
	}

	// Loop through the file and put the contents into a string to be returned
	else
	{
		while(file >> data)
		{
			file_contents.append(data);
		}
	}

	file.close();

	return file_contents;
}

// The main function will take in the two names of the files that will be compared
int main(int argc, char **argv)
{
	cout << "Loading data from files " << argv[1] << "and " << argv[2] << "\n";

	// Get the contents of the two specified files
	string file1 = loadFile(argv[1]);
	string file2 = loadFile(argv[2]);


	cout << file1 << "\n";
	cout << file2 << "\n";
}
