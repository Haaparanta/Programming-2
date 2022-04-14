#include <iostream>
#include <vector>

using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    string line = "aqs";
    for (auto part : line) {
        cout << part << endl;
    }
    vector<int> numbers = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    int index = numbers.end(4);
    cout << index;
    return 0;
}
