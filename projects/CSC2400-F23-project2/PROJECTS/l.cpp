#include <iostream>
#include <fstream>
#include <cmath>
#include <utility>
#include "GraphMatrix.h"
using namespace std;

const int SIZE = 10;
const string COUNTRY_CODES[SIZE]={"AU", "BR", "CA", "CN", "GL", "IT", "NA", "RU", "US", "US"};

/*
	Use the following structure to store each tour & its cost
	You will create an array of Tour variables in your program
*/
struct Tour
{
	string tour[SIZE];
	int cost;
};


void lexicographic(string* countriesArray, int arrSize, Tour* tourOptions, GraphMatrix* matrixOfCosts)
{
    
}