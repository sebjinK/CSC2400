#ifndef project_H
#define project_H
#include <iostream>

using namespace std;
/*
int euclidsAlgo(int m, int n)
{
    int remainder;
    do
    {
        remainder = m % n;
        cout << "\ngcd(" << m << ", " << n << ") = gcd (" << n << ", " << "(" << m << " % " << n << "))";
        m = n;
        n = remainder;
    } while (n != 0);
    cout << endl << m;
    return m;
}
*/
int extendedEuclidsAlgo(int m, int n, int *x, int *y)
{
    if (n == 0) //base case
    {
        *x = 1;
        *y = 0;
        return m;
    }
    /*
    recursive call to find the GCD of two numbers
    and store their values in variables x and y.
    The value returned by this function is the greatest common divisor of a and b
    which can be found using the formula: g=gcd(a,b)=gcd(b%a,a).
    */
    int xStorage, yStorage; //stores the resulting coefficients

    int gcd = extendedEuclidsAlgo(n, m % n, &xStorage, &yStorage); // euclid's takes over--does this multiple times until it reaches the base case
    //recursive calls for calculating the new coefficients

    *x = yStorage;
    *y = xStorage - (n / m) * yStorage;
    return gcd;
}

int consecutiveIntCheckAlgorithm(int m, int n)
{
    if (m == 0 && n == 0)
        return 0;
    if (m < 0 || n < 0)
        return -1;
    int smaller = min(m, n);
    for (int i = smaller; i >= 1; i--)
    {
        if (m % i == 0 && n % i == 0)
        {
            if (m < 0 || n < 0)
                return -1 * i;
            return i;
        }
    }

    return 1; //if no common factor is found
}






   










                            
use function to implement sieve twice
use a varaible (ans = 1) and multiply the common primes by it 
return the primes and output the GCD
*/
#endif
