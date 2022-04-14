#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    cout << "Enter a number: ";
    int number, result;
    cin >> number;
    result = pow(number, 3 );
    if (result >= 0 and result >= number * number) {
        cout << "The cube of " << number << " is " << result << "." << endl;
    } else {
         cout << "Error! The cube of " << number << " is not " << result << "." << endl;
    }
}
