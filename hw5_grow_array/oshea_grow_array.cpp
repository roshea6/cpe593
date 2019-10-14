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
 	void grow() {}
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
			capacity *= 2;
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
			capacity *= 2;
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
			capacity *= 2;
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
			cout << data[i].x << " " << data[i].y << "\n";
		}
		cout << "\n";
	}

	// return how many elements in the list
	int size() const
	{
		cout << "capacity: " << capacity << "\n";
		cout << "used: " << used << "\n";
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

	*x_min = 0.0;
	*x_max = 0.0;
	*y_min = 0.0;
	*y_max = 0.0;

	getMaxAndMin(x_min, x_max, y_min, y_max);

	cout << *x_min << "\n";
	cout << *x_max << "\n";
	cout << *y_min << "\n";
	cout << *y_max << "\n";

	// Find range of values so even divisions can be made
	double x_range = *x_max - *x_min;
	double y_range = *y_max - *y_min;

	double x_divs[9];
	double y_divs[9];

	x_divs[0] = *x_min;
	y_divs[0] = *y_min;

	// Create divisions based on range of x and y points
	for(int i = 1; i <= 8; i++)
	{
		x_divs[i] = x_divs[i-1] + x_range/8;
		y_divs[i] = y_divs[i-1] + y_range/8;
	}

	// for(int i = 0; i <= 8; i++)
	// {
	// 	cout << x_divs[i] << " ";
	// }
	// cout << "\n";
	//
	// for(int i = 0; i <= 8; i++)
	// {
	// 	cout << y_divs[i] << " ";
	// }
	//
	// cout << "\n";

	// Create 8x8 array of GrowArrays that contain Point Objects
	GrowArray<Point> rect[8][8];

	// Point p;
	//
	// p.x = 6;
	// p.y = 7;
	//
	// cout << p.x << " " << p.y << "\n";
	//
	// rect[0][0].addStart(p);
	//
	// rect[0][0].displayData();

	Point p;

	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			p.x = i;
			p.y = j;

			rect[i][j].addStart(p);
		}
	}

	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			cout << "Box (" << i << ", " << j << "): ";

			rect[i][j].displayData();
		}
	}

}
