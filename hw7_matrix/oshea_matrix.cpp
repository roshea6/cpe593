/*
	 Author: Ryan O'Shea

	 Description: Matrix class with matrix mulitplication using partial pivoting

	 cite: 

	 "I pledge my honor that I have abided by the Stevens Honor System"
*/

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Matrix {
private:
    int rows,cols;
	double* m;
    Matrix(int r, int c) : rows(r), cols(c), m(new double[r*c]) {        
    }
public:
    Matrix(int r, int c, double val) : rows(r), cols(c), m(new double[r*c]) {
        for (int i = 0; i < r*c; i++)
            m[i] = val;
    }
    ~Matrix() {
        delete [] m; //O(1)
    }
    Matrix(const Matrix& orig) : rows(orig.rows), cols(orig.cols), m(new double[rows*cols]) {
        for (int i = 0; i < rows*cols; i++)
            m[i] = orig.m[i]; //O(r*c)        
    }

    // move constructor
    Matrix(Matrix&& orig) : rows(orig.rows),    cols(orig.cols) {
        m = orig.m;
        orig.m = nullptr;
    }

    // friend Matrix operator *(const Matrix& a, const Matrix& b) {
    //     if (a.cols != b.rows)
    //         throw "Bad matrix size";
    //     Matrix ans(a.rows, b.cols);
    //     for (int i = 0; i < a.rows; ++i)
    //         for (int j = 0; j < b.cols; ++j) {
	// 			double dot = 0;
	// 			for (int k = 0; k < a.cols; k++)
	// 				dot += a(i, k) * b(k, j);
	// 			ans(i,j) = dot;
    //         }
    //     return ans;
    // }

};

int main(int argc, char** argv)
{
	return 0;
}
