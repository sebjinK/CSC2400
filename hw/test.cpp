#include <iostream>
using namespace std;


int main()
{
    int sum = 0;
    for (int i = 2; i < 1025; i++)
    {
        if (i % 2 == 0)
            sum += i;
    }
    cout << "\n\n\t" << sum;








    return 0;
}
