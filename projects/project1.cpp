/*
Name:           project1.cpp
Author:         Sebjin Kennedy
Date:           September 1st, 2023
Description:    This program will implement the extended euclidean algorithm and the consectuive 
                integer checking algorithm for computing GCD
*/

#include "project1.h"
#include <iostream>

using namespace std;

int main()
{
    int choice;

    int m;
    int n;
    int x;
    int y;
    int GCD;
  
    do
    {
        cout << "\n\nWhat algorithim do you want to use?\n";
        cout << "1. Extended Euclid's Algorithm\n";
        cout << "2. Consecutive Integer checking algorithm\n";
        cout << "3. Leave";
        cout << "\n\nPLEASE CHOOSE 1 OR 2. Press any other number to leave\n";
        cin >> choice;

        if (choice == 1)
        {
            cout <<"\n\tWhat are the two numbers you want the gcd of?";
            cin >> m;
            cin >> n;
            cout << "\n//Extended Euclid's Algorithm//\n";
            GCD = extendedEuclidsAlgo(m, n, &x, &y);
            cout << "\nFormat:\n(m)(x) + (n)(y) to a GCD of (GCD)";
            cout <<  "\n(" << m << ")(" << x << ") + (" << n << ")(" << y <<") = to a GCD of " << GCD;
        }

        else if(choice == 2)
        {
            cout <<"\n\tWhat are the two numbers you want the gcd of?";
            cin >> m;
            cin >> n;
            cout << "\n//Consecutive INteger Checking Algorithm//\n";
            GCD = consecutiveIntCheckAlgorithm(m, n);
            cout << "\nGCD(" << m << ", " << n << ") = " << GCD; 
        }

    } while (choice == 1 || choice == 2);
    
    return 0;
}