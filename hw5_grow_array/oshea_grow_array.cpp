/*
	 Author: Ryan O'Shea

	 Description: Implementation of 8x8 array of growarrays used for splitting
	 points into different boxes

	 cite:


	 "I pledge my honor that I have abided by the Stevens Honor System"
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

class Point {
public:
  double x,y;
};

// Grow arry class. Dynamic array that grows as more items are added to it.
// Should double in capacity when filled
template<typename T>
class GrowArray {
private:
	int capacity; // the amount of memory allocated
 	int used;     // the current size of the list
 	T* data;
 	void grow()
	{
		capacity *= 2;
	}
public:
	GrowArray() : capacity(1), used(0), data(new T[1]) {}
	GrowArray(int initialSize) {} // set initial capacity
	~GrowArray()
	{
		delete [] data;
	}
	GrowArray(const GrowArray& orig) = delete;
	GrowArray& operator =(const GrowArray& orig) = delete;

	// Add item to the end of the array
	void addEnd(T v)
	{
		// If we've filled the capacity of the array
		if(used == capacity)
		{
			T* old = data; // Save old data
			grow();
			data = new T[capacity];

			// Transfer data into new larger array
			for(int i = 0; i < used; i++)
			{
				data[i] = old[i];
			}

			// Add newest value to end
			data[used] = v;
			used++;

			delete [] old;
		}
		// Array still has room
		else
		{
			data[used] = v;
			used++;
		}
	}

	// Shift all other items over and add item to the start of the array
	void addStart(T v)
	{
		// If we've filled the capacity of the array
		if(used == capacity)
		{
			T* old = data; // Save old data
			grow();
			data = new T[capacity];

			// Transfer data into new larger array but shifted over one
			for(int i = 0; i < used; i ++)
			{
				data[i+1] = old[i];
			}

			// Add newest value to end
			data[0] = v;
			used++;

			delete [] old;
		}
		// Array still has room
		else
		{
			T* old = data;
			data = new T[capacity];
			// Transfer data into new larger array but shifted over one
			for(int i = 0; i < used; i ++)
			{
				data[i+1] = old[i];
			}
			data[0] = v;
			used++;

			delete [] old;
		}
	}

	// Insert an item at the specified index
	void insert(int i, T v)
	{
		// If we've filled the capacity of the array
		if(used == capacity)
		{
			T* old = data; // Save old data
			grow();
			data = new T[capacity];

			// Transfer data before the index into the new array
			for(int j = 0; j < i; j ++)
			{
				data[j] = old[j];
			}

			//Add new value at index
			data[i] = v;
			used++;

			// Add rest of values from old array after index
			for(int j = i + 1; j < used; j++)
			{
				data[j] = old[j-1];
			}

			delete [] old;
		}
		// Array still has room
		else
		{
			T* old = data;
			data = new T[capacity];

			// Transfer data before the index into the new array
			for(int j = 0; j < i; j ++)
			{
				data[j] = old[j];
			}

			//Add new value at index
			data[i] = v;
			used++;

			// Add rest of values from old array after index
			for(int j = i + 1; j < used; j++)
			{
				data[j] = old[j-1];
			}
			delete [] old;
		}
	}

	// Remove an item from the end of the array
	void removeEnd()
	{
		used--;
	}

	// Remove an item from the start of the array and shift all the other items
	void removeStart()
	{
		T* old = data;
		data = new T[capacity];

		for(int i = 0; i < used; i++)
		{
			data[i] = old[i+1];
		}

		used--;
		delete [] old;
	}

	// Remove the item at the specified index
	void remove(int i)
	{
		T* old = data;
		data = new T[capacity];

		for(int j = 0; j < used; j++)
		{
			if(j < i)
			{
				data[j] = old[j];
			}
			else
			{
				data[j] = old[j+1];
			}
		}
		used--;
		delete [] old;
	}

	void displayData()
	{
		for(int i = 0; i < used; i++)
		{
			cout << "(" << data[i].x << ", " << data[i].y << ") ";
		}
		cout << "\n";
	}

	// return how many elements in the list
	int size() const
	{
		return used;
	}
};

// Gets the minimum and maximum x and y valuesand store them in passed in locations
void getMaxAndMin(double* x_min, double* x_max, double* y_min, double* y_max)
{
	fstream file;
	file.open("convexhullpoints.dat");

	double x;
	double y;

	//Get initial values
	file >> *x_min;
	*x_max = *x_min;
	file >> *y_min;
	*y_max = *y_min;

	// Loop through file and constantly update the min and max values
	while(file >> x >> y)
	{
		*x_min = min(x, *x_min);
		*x_max = max(x, *x_max);
		*y_min = min(y, *y_min);
		*y_max = max(y, *y_max);
	}
	file.close();
}


int main(int argc, char **argv)
{
	GrowArray<double> arr;

	double* x_min = new double;
	double* x_max = new double;
	double* y_min = new double;
	double* y_max = new double;

	getMaxAndMin(x_min, x_max, y_min, y_max);

	// Find range of values so even divisions can be made
	double x_range = *x_max - *x_min;
	double y_range = *y_max - *y_min;

	// Create 8x8 array of GrowArrays that contain Point Objects
	GrowArray<Point> rect[8][8];

	Point p;

	fstream file;
	file.open("convexhullpoints.dat");

	// Sort the points into their proper GrowArrays
	while(file >> p.x >> p.y)
	{
		int i = ((p.y - *y_min)/(y_range))*(8-1) + .5;
		int j = ((p.x - *x_min)/((x_range))*(8-1)) + .5;

		// cout << p.x << ", " << p.y << " placed in box: (" << i << ", " << j << ") \n";

		rect[i][j].addEnd(p);
	}

	file.close();

	// Display max and min
	cout << "X min = " << *x_min << "		X max = " << *x_max << "\n";
	cout << "Y min = " << *y_min << "		Y max = " << *y_max << "\n";

	// Display perimeter arrays
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			// First or last row
			if(i == 0 or i == 7)
			{
				cout << "Box: (" << i << ", " << j << ") 	";
				rect[i][j].displayData();
			}

			// First or last column
			else if(j == 0 or j == 7)
			{
				cout << "Box: (" << i << ", " << j << ") 	";
				rect[i][j].displayData();
			}
		}
	}


}
