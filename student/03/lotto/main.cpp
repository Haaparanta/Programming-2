#include <iostream>

using namespace std;

unsigned long int fact(int n) {
  unsigned long int answer = 1;

  if (n == 0) return 1; // ei käy täälläkään
  while (n > 0)
    answer *= n--;
  return answer;
}

int main()
{
    int total, drawn;
    cout << "Enter the total number of lottery balls: ";
    cin >> total;
    cout << "Enter the number of drawn balls: ";
    cin >> drawn;
    if (total < 0 or drawn < 0) {
        cout << "The number of balls must be a positive number." << endl;
    } else if (total < drawn) {
        cout << "The maximum number of drawn balls is the total amount of balls." << endl;
    } else {
        unsigned long int number = fact(total)/(fact(total - drawn) * fact(drawn));
        cout << "The probability of guessing all " << drawn << " balls correctly is 1/" << number << endl;
    }
}

