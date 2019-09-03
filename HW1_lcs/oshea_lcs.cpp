/*
	 Author: Ryan O'Shea

	 Description: Takes in the two specified files via the terminal and finds the
	 number of bytes in common as well as the longest common subsequence (LCS)

	 cite: http://www.fredosaurus.com/notes-cpp/io/readtextfile.html and
	 http://www.cplusplus.com/doc/tutorial/files/ for help with reading from files

	 Discussed with Frank Lenge Jr. about what exactly LCS is

	 "I pledge my honor that I have abided by the Stevens Honor System"
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
		file_contents.append("0"); // Add a garbage character in the beginning of each file
		while(getline(file, data))
		{
			file_contents.append(data);
		}
	}

	file.close();

	return file_contents;
}

// Function that return the longest common subsequence of two strings. Also prints
// out the total number of bytes in common between the two
string getLCS(string file1, string file2)
{
	string lcs = "";
	int file1_len = file1.length();
	int  file2_len = file2.length();

	// Create a 2D array based on the lengths of the files
	int saved_len_arr [file1_len+1][file2_len+1];

	// Populate the first row with 0's
	for(int i = 0; i <= file1_len; i++)
	{
		saved_len_arr[i][0] = 0;
	}

	// Populate the first column with 0's
	for(int j = 0; j <= file2_len; j++)
	{
		saved_len_arr[0][j] = 0;
	}

	// Loop through the files to determine bytes in common and build the LCS table
	for(int i = 1; i <= file1_len; i++)
	{
		for(int j = 1; j <= file2_len; j++)
		{
			// Compare the current characters in the files
			if(file1[i-1] == file2[j-1])
			{
				saved_len_arr[i][j] = saved_len_arr[i-1][j-1] + 1;
			}

			else
			{
				saved_len_arr[i][j] = max(saved_len_arr[i][j-1], saved_len_arr[i-1][j]);
			}
		}
	}

	cout << "Bytes in common: " << saved_len_arr[file1_len][file2_len] - 1 << "\n";

	// Use the LCS table to find the actual LCS
	int n = file1_len;
	int m = file2_len;

	// Start in the bottom right corner of the LCS box and loop until the beginning
	// of the shorter file
	while(n > 1 && m > 1)
	{
		// If current characters in the two files are the same then the char is part
		// of the LCS
		if(file1[n - 1] == file2[m - 1])
		{
			// Insert the matching character at the beginning of the string
			lcs.insert(0, 1, file1[n - 1]);

			// Decrement n and m to move up to the next potential character
			n--;
			m--;
		}

		// If the characters are different then find the larger value to correctly
		// follow the path to the next char in the sequence
		else if(saved_len_arr[n-1][m] > saved_len_arr[n][m-1])
		{
			n--;
		}

		else
		{
			m--;
		}
	}

	return lcs;
}

// The main function will take in the two names of the files that will be compared
int main(int argc, char **argv)
{
	cout << "Loading data from files " << argv[1] << " and " << argv[2] << "\n";

	// Get the contents of the two specified files
	string file1 = loadFile(argv[1]);
	string file2 = loadFile(argv[2]);

	if(file1.length() == 1 || file2.length() == 1)
	{
		cout << "One of the files has nothing in it and there is no need to perform LCS. \n";
	}

	else
	{
		// Get the LCS of the two files and display it and its length
		string lcs = getLCS(file1, file2);
		cout << "The LCS of the two files is: " << lcs << "\n";
		cout << "The length of the LCS is: " << lcs.length() << "\n";
	}


	return 0;
}
