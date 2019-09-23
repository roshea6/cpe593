/*
	 Author: Ryan O'Shea

	 Description: Reads in a arrays of number from a specified file and uses
	 quicksort to sort them from least to greatest

	 cite:

	 "I pledge my honor that I have abided by the Stevens Honor System"
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

// Uses the quicksort algorithm to sort the passed in array and then displays the sorted
// array
void quickSort(int * arr, int left, int right)
{
	// Check if array length is 1 or 0
	if((right - left) < 2)
	{
		return;
	}

	// Pick a pivot (Change this to random pivot point)
	int pivot = (arr[left] + arr[right])/2;

	int i = left;
	int j = right;

	while(i < j)
	{
		while(arr[i] < pivot)
		{
			i++;
		}

		while(arr[j] >= pivot)
		{
			j--;
		}

		if(i < j)
		{
			swap(arr[i], arr[j]);
		}
	}
	//i and j are now equal
	quickSort(arr, left, i-1);
	quickSort(arr, i, right);
}

// Function that returns the contents of the specified filename as an integer array
void loadAndSort(string filename)
{
	int num;

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
		// Get the number of tests to perform
		int num_tests;
		int num_elems;

		file >> num_tests;

		// Loop through and test all the different cases
		for(int i = 0; i < num_tests; i++)
		{
			// Get number of elements in the array
			file >> num_elems;

			// Get unsorted array
			int unsorted_arr[num_elems];
			for(int j = 0; j < num_elems; j++)
			{
				file >> unsorted_arr[j];
			}

			// Sort array
			quickSort(unsorted_arr, 0, num_elems - 1);

			//Display sorted array
			for(int k = 0; k < num_elems; k++)
			{
				cout << unsorted_arr[k] << " ";
			}
			cout << "\n";
		}

	}

	file.close();

}

int main(int argc, char **argv)
{
	 string file_name = argv[1];
	 int unsorted_arr;

	 loadAndSort(file_name);

	 return 0;
}
