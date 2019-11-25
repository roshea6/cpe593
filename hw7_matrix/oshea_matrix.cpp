/*
	 Author: Ryan O'Shea

	 Description: Matrix class with matrix mulitplication using partial pivoting

	 cite: 

	 "I pledge my honor that I have abided by the Stevens Honor System"
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Matrix {
private:
    int rows,cols;
	double* m;
    Matrix(int r, int c) : rows(r), cols(c), m(new double[r*c]) {        
    }
public:
	// Initialize all indexes in matrix with value passed in
    Matrix(int r, int c, double val) : rows(r), cols(c), m(new double[r*c]) {
        for (int i = 0; i < r*c; i++)
            m[i] = val;
    }
    ~Matrix() {
        delete [] m; //O(1)
    }

	// Copy constructor
    Matrix(const Matrix& orig) : rows(orig.rows), cols(orig.cols), m(new double[rows*cols]) {
        for (int i = 0; i < rows*cols; i++)
            m[i] = orig.m[i]; //O(r*c)        
    }

    // move constructor
    Matrix(Matrix&& orig) : rows(orig.rows),    cols(orig.cols) {
        m = orig.m;
        orig.m = nullptr;
    }

	// () operator. Pass in the (col, row) position that you want the value of 
	double operator()(int i, int j) const 
	{
    	return m[i*cols+j];
  	}

	// Use the passed in stream object to read rowsxcols many elements out of the file 
	// into the array
	void read_in_file(fstream &file)
	{
		int x;
		int i = 0;

		// Loop until all desired elements have been read into the array
		while(i < rows*cols)
		{
			file >> x;

			m[i] = x;
			
			i++;
			
		}
	}

	// Finds the pivot for a given row number and bring it to the correct place
	void partialPivot(int i)
	{
		cout << "Pivot \n";
		int largest_row = i;
		double largest_val = m[i*cols+i]; // Starts with th starting value as biggest val

		// Check the ith value in each row to find the maximum value
		for(int j = i; j < rows; j++)
		{
			// If its bigger than the current val
			if(m[j*cols+i] > largest_val)
			{
				largest_val = m[j*cols+i];
				largest_row = j;
			}
		}

		// Now that the row with the largest value has been found we need to swap the rows
		if(largest_val != i) // Only need to swap if a row with a larger value was found
		{
			for(int j = i; j < cols; j++)
			{
				// Swap value in ith row with the value from the largest_row row
				swap(m[i*cols+j], m[largest_row*cols+j]);
			}
		}
	}
	
	// Work from the bottom of the array up and solve for each variable then substitute it back
	// into the rest of the array so the next variable can be solved for
	vector<double> back_substitute(vector<double> B)
	{
		// Answer vector that will contain the value of each variable
		vector<double> x;
		x.reserve(rows);

		for(int n = rows; n > 0; n--)
		{
			// Get the value of the variable
			x[n-1] = B[n-1]/m[(n-1)*cols+(n-1)];

			// Substitute the new variable value back into the rest of the matrix
			for(int j = n-2; j > 0; j--)
			{
				B[j] -= x[n-1] * m[j*cols + n];
			}
		}
		return x;
	}

	// Uses Gaussian elimination with partial pivoting to solve the matrix for the 
	// passed in solution vector
	vector<double> solve(vector<double> B)
	{
		// Check to make its actually solvable
		if(rows != cols)
		{
			cout << "Rows must equal columns to solve!";
			vector<double> temp;
			temp[0] = 0;
			return temp;
		}

		for(int i = 0; i < rows; i++)
		{
			// Find the pivot and bring it to the correct place
			partialPivot(i);
			// The pivot row is now in row i

			// Wipe out the rows below the pivot row using the pivot row
			for(int k = i + 1; k < rows; k++)
			{
				double s = -m[k*cols+i]/m[i*cols+i];
				m[k*cols+i] = 0; // Eliminate the ith element in row k. Directly set to 0 to avoid
				// float accuracy problems

				// Loop through rest of the row and update their values
				for(int j = i+1; j < cols; j++)
				{
					m[k*cols+j] += s * m[i*cols+j];
				}
				
				// Update answer vector
				B[k] += s * B[i];
			}

		}

		// Matrix should now be in a form where back substitution will solve for each
		// variable one by one
		return back_substitute(B);
	}

	// Print out the matrix
	void display()
	{
		for(int i = 0; i < rows; i++)
		{
			for(int j = 0; j < cols; j++)
			{
				cout << m[i*cols+j] << " ";
			}
			cout << "\n";
		}
	}


};

int main(int argc, char** argv)
{
	fstream file;
	file.open("mat.dat");

	if(!file)
	{
		cout << "File not found \n";
		return -1;
	}

	int rows;

	file >> rows;

	cout << "Creating a " << rows << " x " << rows << " matrix \n";

	Matrix mat(rows, rows, 0);

	mat.read_in_file(file);

	vector<double> B;
	B.reserve(rows);

	int x;

	for(int i = 0; i < 10; i ++)
	{
		file >> B[i];
	}

	vector<double> sol = mat.solve(B);

	for(int i = 0; i < rows; i++)
	{
		cout << sol[i] << " ";
	}

	return 0;
}
