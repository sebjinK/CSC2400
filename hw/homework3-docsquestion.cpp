#include <iostream>

using namespace std;

int main()
{
    char repeat = 'n';
    do{
    int ans = 0;
    double n;
    cout << "\nEnter a number: ";
    cin >> n;
    for (double i = 0; i < n/2 + 0.5; i += 1)
    {
        for (double j = i - 1; j < n; j += 1)
        {
            for (double k = i + 1; k < j; k += 1)
            {
                ans++;
            }
        }
    }
    cout << endl  << "\n\n\tYOUR RESULT NUMBER IS:\t"<< ans << endl;
    cout << "Repeat? y or n ";
    cin >> repeat;
    }while(repeat == 'y');
    return 0;
}