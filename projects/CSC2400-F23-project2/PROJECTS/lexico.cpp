#include <iostream>
#include <array>
#include <algorithm>
using namespace std;

void lexicographic(std::array<std::string, 10>& strings) {
    bool isDone = false;
    int iterationCount = 1;
    int lowBound = 0; // The "i" value
    int uppBound = 0; // The "j" value

    std::array<std::string, 10> tempArray;

    std::cout << "\nLEXICOGRAPHIC ALGORITHM";

    while (!isDone) {
        // Make a copy of the input array
        tempArray = strings;

        /*
            ---PRINT TEMPSTRING---
        */
        std::cout << "\n" << iterationCount << ":\t";
        for (const std::string& s : tempArray) {
            std::cout << s << " ";
        }
        iterationCount++;

        /*
            ---FIND lowBound OR DETERMINE IF DONE---
        */
        isDone = true;
        for (int i = 0; i < strings.size() - 1; i++) {
            if (tempArray[i] < tempArray[i + 1]) {
                isDone = false;
                lowBound = i;
            }
        }
        if (isDone) {
            continue; // Break one iteration of the while loop
        }

        /*
            ---FIND uppBound---
        */
        for (int j = strings.size() - 1; j > 0; j--) {
            if (tempArray[j] > tempArray[lowBound]) {
                uppBound = j;
                break;
            }
        }

        /*
            ---SWAP ELEMENTS---
        */
        std::swap(tempArray[lowBound], tempArray[uppBound]);

        /*
            ---REVERSE ELEMENTS FROM lowBound+1 TO l-1---
        */
        for (int i = 1; i < strings.size() - lowBound; i++) {
            std::swap(tempArray[lowBound + i], tempArray[strings.size() - i]);
        }

        // Update the original array with the new permutation
        strings = tempArray;

        /*
            ---PRINT lowBound AND uppBound---
        */
        std::cout << "\ti = " << lowBound << "\tj = " << uppBound;
    }
}

int main() {
    std::array<std::string, 10> arr = {"US", "AU", "BR", "CA", "CN", "GL", "IT", "NA", "RU", "US"};

    lexicographic(arr);

    std::cout << "\nFinal permutation: ";
    for (const std::string& s : arr) {
        std::cout << s << " ";
    }

    return 0;
}