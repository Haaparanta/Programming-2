#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a temperature: ";

    // Write your code here
    int number;
    cin >> number;
    cout << number << " degrees Celsius is " << number * 1.8 + 32 << " degrees Fahrenheit " << endl;
    cout << number << " degrees Fahrenheit is " << (number - 32) / 1.8 << " degrees Celsius" << endl;

    return 0;
}
