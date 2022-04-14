#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    cout << "Input an expression in reverse Polish notation (end with #):" << endl;
    cout << "EXPR> ";
    char value;
    int number = -1;
    int stack[10];
    cin >> value;
    if (isdigit(value)) {
        while (value != '#') {
            if (value == '+' or value == '-' or value == '*' or value == '/') {
                if (number > 0) {
                    number--;
                    int second = stack[number];
                    int last = stack[number + 1];
                    cout << second << last << endl;
                    cout << stack[number] << stack[number + 1] << endl;
                    if (value == '/' and stack[number + 1] == 0) {
                        cout << "Error: Division by zero" << endl;
                        return 1;
                    } else if (value == '+') {
                        stack[number] = stack[number] + stack[number + 1];
                    } else if (value == '-') {
                        stack[number] = stack[number] - stack[number + 1];
                    } else if (value == '*') {
                        stack[number] = stack[number] * stack[number + 1];
                    } else if (value == '/') {
                        stack[number] = stack[number] / stack[number + 1];
                    }

                } else {
                    cout << "Error: Too few operands" << endl;
                    return 1;
                }
            } else if (int temp = value){
                number++;
                cout << temp << endl;
                stack[number] = temp;
            }
            cin >> value;
        }
    } else {
        cout << "Error: Expression must start with a number" << endl;
        return 1;
    }
    if (number > 0) {
        cout << "Error: Too few operators" << endl;
        return 1;
    } else {
        cout << "Correct: " << stack[0] << " is the result" << endl;
    }

}
