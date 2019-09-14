/*
	 Author: Ryan O'Shea

	 Description: Takes in integer through the command line and displays whether
	 it is a prime or a composite number

	 cite: http://www.cplusplus.com/reference/cstdlib/rand/ for random numbers
	 http://www.cplusplus.com/reference/bitset/bitset/	 converting int to binary
	 http://www.cplusplus.com/reference/string/string/pop_back/ for string element pop

	 "I pledge my honor that I have abided by the Stevens Honor System"
*/

#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <bitset>
#include <string>
#include <time.h>

using namespace std;

// Raise a to the power of b and then return the result of (a^b) mod r
long powermod(long a, int b, int r)
{
	long prod = 1;

	while(b > 0)
	{
		//If the power is Odd
		if(b%2 != 0)
		{
			prod = (prod * a) % r; // Multiply the product by a so we now have an even power then mod it by r
		}

		a = (a*a) % r; // square a then mod it by r
		b /= 2; // Since we've square a we can divide the exponent it needs to be
		// raised to by 2
	}
	return prod;
}

// Returns whether a number is not prime or most likely prime
bool millerRabin(long num, int trials)
{
	// Loop for number of trials
	for(int i = 1; i <= trials; i ++)
	{
		// Generate random witness number between 2 and num - 2
		// TODO: Fix random number generation
		long a = 2 + (rand() % ((num - 1) - 2));
		cout << "a = " << a << "\n";

		long s = 0;
		long d;

		// turn n-1 into binary and then split it into s and d based on its trailing 0s
		string binary = bitset<64>(num-1).to_string();
		cout << binary << "\n";
		for(long j = binary.length(); j > 0; j--)
		{
			// If we hit a non zero then we are out of trailing 0s
			if(binary[j-1] != '0')
			{
				break; //Break out of loop
			}

			// Otherwise increment s because we have another trailing 0
			else
			{
				s++;
				binary.pop_back(); // Remove the last element in the string
			}
		}

		cout << "s = " << s << "\n";
		cout << "cut binary = " << binary << "\n";

		// Store the result in d
		d = bitset<64>(binary).to_ulong();

		cout << "d = " << d << "\n";

		// Use powermod to see if the number is most likely prime
		long x = powermod(a, d, num);

		// Check if result from powermod is good
		if(x == 1 || x == num -1)
		{
			// Test passed continue through trials
			continue;
		}

		// Bad result need to manually check
		for(long k = 1; k < s -1; k++)
		{
			x = x*x % num;

			// Carmichael number found return false
			if(x == 1)
			{
				return false;
			}

			// Number checks out continue with trials
			if(x == num -1)
			{
				continue;
			}

			return false;
		}
	}
	// All trials passed the number is most likely prime
	return true;
}

int main(int argc, char *argv[])
{
	// Set seed for random numbers
	srand(time(NULL));

	// Get the number from the command line
	long num_to_check = atoi(argv[1]);

	cout << num_to_check << "\n";

	bool check = millerRabin(num_to_check, 100);

	if(check)
	{
		cout << num_to_check << " is most likely prime. \n";
	}

	else
	{
		cout << num_to_check << " is composite. \n";
	}
}
