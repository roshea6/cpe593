/*
	 Author: Ryan O'Shea

	 Description: Reads in arrays of number from a specified file and uses
	 quicksort to sort them from least to greatest

	 cite: http://www.cplusplus.com/reference/algorithm/swap/ for swap Function
	 Discussed weird edge cases with roomate Frank Lenge.


	 "I pledge my honor that I have abided by the Stevens Honor System"
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <time.h>

using namespace std;

// Uses the quicksort algorithm to sort the passed in array and then displays the sorted
// array
void quickSort(int * arr, int left, int right)
{
	int i = left;
	int j = right;
	int pivot = arr[(left + (rand() % right))]; //Choose a random nuber in the array as the pivot point

	// Move i and j towards the pivot point while swapping values along the way
	while(i <= j)
	{
		// Increment i until it hits a number on the left side greater than the pivot
		while(arr[i] < pivot)
		{
			i++;
		}
		// Decrement j until it hits number on the right side less than the pivot
		while(arr[j] > pivot)
		{
			j--;
		}

		if(i <= j)
		{
			// Swap the values to their proper sides
			swap(arr[i], arr[j]);

			// Increment i and decrement j incase a number equal to the pivot was
			// swapped so we don't get caught in an infinite loop
			i++;
			j--;
		}
	}

	// Call two new quicksorts on the new unsorted portions of the array
	if(left < j)
		quickSort(arr, left, j);
	if(i < right)
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
	//Generate random seed based off current time
	srand(time(NULL));
	string file_name = "hw2a.dat";
	int unsorted_arr;

	loadAndSort(file_name);

	return 0;
}
