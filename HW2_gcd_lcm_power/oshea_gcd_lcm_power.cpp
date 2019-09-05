/*
	 Author: Ryan O'Shea

	 Description: Takes in three integers through the command line and returns
	 the greatest common denominato and least common multiple of the first two and
	 powermod of all three

	 cite:

	 "I pledge my honor that I have abided by the Stevens Honor System"
*/

#include <iostream>

using namespace std;

// Function that returns the greatest common denominator of two numbers
// Uses Euclid's method for determining gcd
int gcd(int a, int b)
{
	int temp;

	// Loop until b is 0. After it is 0 the remainder will be stored in a
	while(b != 0)
	{
		temp = a % b; // Save the value of a mod b to be stored in b later
		a = b; // Make b the new a
		b = temp;
	}
	return a; // Return the gcd
}

// Function that returns the least common multiple of two numbers.
int lcm(int a, int b)
{
	return (a * b)/gcd(a,b);
}

// Raise a to the power of b and then return the result of (a^b) mod r
int powermod(int a, int b, int r)
{
	int prod = 1;

	while(b > 0)
	{
		// Odd power
		if(b%2 != 0)
		{
			prod = (prod * a) % r; // Multiply the product by a so we now have an even power then mod it by r
		}

		a = (a * a) % r; // square a then mod it by r
		b /= 2; // Since we've square a we can divide the exponent it needs to be
		// raised to by 2
	}
	return prod;
}

int main(int arc, char *argv[])
{
	int a, b, r;
    // Converting string type to integer type
    // using function "atoi( argument)"*

    a = atoi(argv[1]);
    b = atoi(argv[2]);
	r = atoi(argv[3]);

	cout << "The gcd of " << a << " and " << b << " is " << gcd(a,b) << "\n";
	cout << "The lcm of " << a << " and " << b << " is " << lcm(a,b) << "\n";
	cout << "The powermod of " << a << ", " << b << " and " << r << " is " << powermod(a,b,r) << "\n";
}
