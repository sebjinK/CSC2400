/*
     Title:     project2.cpp
     Author:    Sebjin Kennedy
     Date:   	Due November 8, 2023
     Purpose:   Traveling Salesman - find the lowest cost
                tour when traveling from US to 8 other countries
                and then back to US.
*/

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

//Function Prototypes
int searchCountryCode(string); // checking for the country code using binary search while passing the the main string
GraphMatrix* readFileMakeMatrix(); 
void printStringArray(string* arr, int size);
void lexicographic(string*, int, Tour *, GraphMatrix*); //print out EVERY single tour
void saveTour(Tour&, string * arr, GraphMatrix*); //save EVERY single tour to their own individual tour struct
void findLowest(Tour*);//use the tour array to grab the one tour that we need


int main()
{	
	Tour *tourOptions = new Tour[40320];
	//read in the flight information from the file and then create the weight matrix
	GraphMatrix * matrix = readFileMakeMatrix();
	string * countries = new string[SIZE-2];
	
	cout << "\n\n*************************COUNTRIES*******************\n";
	for(int x=0; x < SIZE-2; x++)
	{
		countries[x] = COUNTRY_CODES[x];
		cout << countries[x] << endl;
	}
	
	
	//generate all possible tours (starting & ending with "US") using lexicographic permute algorithm
	//you will need to call your lexicographic function, sending the modified countries array with the 8 country codes
	lexicographic(countries, 8, tourOptions, matrix); //passing size = 8 and tourOptions to fill the tourOptions array
	delete [] countries;//make sure we release countries
	cout << "\n\n*************************SOLUTION*******************\n";
	//find the lowest cost tour and print it out (including the cost)
	findLowest(tourOptions);
	
	cout << "\nHappy Traveling!\n";
	
	//don't forget to release anything that was dynamically allocated!
	delete [] tourOptions;
	return 0;
}
/*
	Function: searchCountryCode
	Parameters: a string with the country code like "BR"
	Returns: an integer representing this country's index in the GraphMatrix.
	For example, if the parameter is "BR", it should return index 1.  If the parameter is "CA", it should return index 3
	It is returning the index value in the COUNTRY_CODES array.	
	Implement this search function with the binary search algorithm!
*/
int searchCountryCode(string searchKey)
{
	int l = 0;
	int r = SIZE - 1;
	while(l <= r) //we have to use less than or equals otherwise the while loop would be skipped altogether
	{//the goal of this is to advance l(left) and r(right) until we find the search key
		int m = (l + r)/2; // what we're using to check through the array
		if(searchKey == COUNTRY_CODES[m]) //final check to find the searchKey 
			return m;
		else if (searchKey < COUNTRY_CODES[m])//if the array element at index m is bigger than the search key, we have to change our scope by making m smaller
			r = m - 1;
		else// if the array element at index m is smaller than the search key, we have to change our scope by limiting m's range across the array
			l = m + 1; //we can limit's m's range across the array by limiting the availiable pool of indexes it could have access to
	}
	return -1; // final default return in the case we don't find the search key -- we probably won't reach this point due to having a set array
	//in the case we ever do reach this point, addEdge would have to make an exception
}

/*
	Title: readFileMakeMatrix
	Purpose:  this function will read the data in flights.txt and create an
	adjacency matrix with the couuntry codes.  The matrix values will be the
	cost of the flights.
*/
GraphMatrix* readFileMakeMatrix()
{
	ifstream inFile;
	GraphMatrix * matrix = new GraphMatrix(SIZE-1);
	cout << "\nCreated the matrix.";
	string country1, country2;
	int price;
	inFile.open("flights.txt");
	cout << "\nReading from flights.txt\n";
	if(inFile)
	{
		while(inFile >> country1)
		{
			inFile >> country2;
			inFile >> price;
			//add price to graph matrix
			matrix->addEdge(searchCountryCode(country1), searchCountryCode(country2), price);
			cout << "\nAdded edge from " << country1 << " to " << country2 << " with cost of $" << price;
		}
	}
	else
		cout << "\nSorry, I am unable to open the file.\n";
	inFile.close();
	cout << "\n\nFLIGHT PRICE GRAPH MATRIX\n";
	matrix->printGraph();
	cout << endl;
	return matrix;
}

/*
	Title: printStringArray
	Purpose:  this function will print the array of strings with a space
		between each string
	Parameters:	the array and the array size
	Returns:	None
*/
void printStringArray(string* arr, int size)
{
	for(int x=0; x<size; x++)
	{
		cout << arr[x] << " ";
	}//modified print string array to not print out an newline every time
}
/*
	Title: saveTour
	Purpose: this funciton will save the string array to the tour array AND print out the costs associated with the tour
	Parameters: a single tour passed by reference that will go back into the tourOptions array, 
				the string array carrying the current permutation of what order the countries were visited
				the matrix of costs that holds the cost-to-cost of each trip
	Returns:	nothing to return
*/
void saveTour(Tour& singleTour, string * arr, GraphMatrix* matrixOfCosts)
{
	singleTour.cost = 0;//we set the tour cost
	//first--shift the elements of the string array so that it adds the US in front and the back
	string * newArr = new string[SIZE]; //create a new array that will hold the ENTIRE array

	newArr[0] = "US"; //start at US
	for (int i = 1; i < SIZE - 1; ++i) {
		newArr[i] = arr[i-1];
	}
	newArr[SIZE-1] = "US"; //end at US


	for (int i = 0; i < SIZE - 1; i++) ///output the string array
	{
		singleTour.tour[i] = newArr[i];// set up the tour to be passed back to the tourOptions array
		//output the cost and send it to the tourOptions array using singleTour
		cout << matrixOfCosts->getWeight(searchCountryCode(newArr[i]), searchCountryCode(newArr[i + 1])) << " ";
		singleTour.cost += matrixOfCosts->getWeight(searchCountryCode(newArr[i]), searchCountryCode(newArr[i + 1]));
	}

	singleTour.tour[SIZE - 1] = "US"; //end at US
	//cout << endl << arr[SIZE - 1];
	cout << " has tour weight " << singleTour.cost;
	delete [] newArr; //newArray was dynamically allocated and we gotta release it
	
}
/*
	Title:	lexicographic
	Purpose: this funciton will print all possible perumations of the tour using printStringArray
				//find a way to print all possible costs associated with each trip 
			 this function will then call saveTour, which will pass this string of trips into the tour array
	Parameters:	the initial countries array ordered alphabetically
				the size of the modifiable array [8]
				the tourOptions array where we are going to save EVERY permutation/tour
				the graph matrix holding the weights between countries
	Returns:	nothing to return
*/
void lexicographic(string* countriesArray, int arrSize, Tour* tourOptions, GraphMatrix* matrixOfCosts)
{
	string * tempCountryCodesArray = new string[arrSize];//first we dynamically allocate and fill tempCountryCodesArray
	for (int i = 0; i < arrSize; i++) {
		tempCountryCodesArray[i] = countriesArray[i];
	}

	bool isDone = false; //we set up the variables of lexicographic function --booleann will checkwhen all possible permutationns have been tried
	int iterationCount = 1; //get an iteration count for storing into tourOptions
	int lowBound = 0;	//the "i" value
	int uppBound = 0;	//the "j" value

	string * swapArray = new string[arrSize]; //need a quick array that will swap for me

	Tour singleTour;//make a tour that will hold the current iteration's string array and weight

	while (!isDone)//a check against all possible permutations
	{
		//////////////////PRINT OUT AND SAVE THE LAST PERMUTATION///////////////////
		cout << endl << iterationCount << ": ";//GET THE THE ITERATION
		printStringArray(tempCountryCodesArray, arrSize);//print out the array
		saveTour(singleTour, tempCountryCodesArray, matrixOfCosts); //print out the tour's array and send the country codes too
		tourOptions[iterationCount - 1] = singleTour; // save the singular tour to the tourOptions array

		
		////////////////CREATE NEW PERMUTATION/////////////////////////
		iterationCount++;//advance the idteration count after saving the last permutation


		isDone = true;//we set isDone to true

		for(int i = 0; i < arrSize - 1; i++)//we go through the entire
		{
			if(tempCountryCodesArray[i] < tempCountryCodesArray[i + 1]) //we move i around the array using lowBound
			{
				isDone = false;
				lowBound = i;//set the lowerBound
			}
		}
		if (isDone)//skip one iteration of the while loop if we have nothing to move around
			continue;
		for (int j = arrSize - 1; j > 0; j--)
		{
			if (tempCountryCodesArray[j] > tempCountryCodesArray[lowBound])//we check against the lowBound this time to find the upperBound
			{
				uppBound = j;//we also have to set the upper bound
				break;
			}
		}
		//swap the lower and the upper bound
		swap(tempCountryCodesArray[lowBound], tempCountryCodesArray[uppBound]);

		//set the DYNAMICALLY ALLOCATED swap array 
		for (int i = 0; i < arrSize; i++)
			swapArray[i] = tempCountryCodesArray[i];
	

		//we swap between the two arrays
		for (int i = 1; i < arrSize - lowBound; i++)
			swapArray[lowBound + i] = tempCountryCodesArray[arrSize - i];
		for (int i = 1; i < arrSize - lowBound; i++)
			tempCountryCodesArray[lowBound + i] = swapArray[lowBound + i];
		
	}
	delete [] tempCountryCodesArray;//release the two temporary arrays created for this function
	delete [] swapArray;
}

/*
	Title:		findLowest
	Purpose:	search the tour array for the array with the lowest associated weight(cost)
				do this by comparing weights 
	Parameters:	tourList which holds every possible tour
	Returns:	none
*/
void findLowest(Tour* tourList)
{
	Tour lowest;
	lowest = tourList[0]; //INITIATE THE LOWEST AT 0TH INDEX

	for (int i = 1; i < 40320; i++)//for loop through the whole array
	{
		if (lowest.cost > tourList[i].cost) //if statement to check each time
		{
			lowest = tourList[i]; //make if statement the newer lowest value
			cout << "\nNew Lowest is: " << lowest.cost << " with tour " << i << " ";
			printStringArray(tourList[i].tour, SIZE); //use print string array to print out the new lowesst we can go

		}
	}

	cout << "\n\n\n******************************************************" << endl;
	cout << "The tour with the lowest cost of $" << lowest.cost << " is ";//do a final print 
	printStringArray(lowest.tour, SIZE); //output the lowest tour using printStringArray
}