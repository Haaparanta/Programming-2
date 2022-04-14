#include <iostream>


int main()
{
    int number;
    std::cout << "How many numbers would you like to have? ";
    std::cin >> number;
    for (int count = 1; count <= number; ++count) {
        if (count % 3 == 0 and count % 7 == 0) {
            std::cout << "zip boing" << std::endl;
        } else if (count % 7 == 0) {
            std::cout << "boing" << std::endl;
        } else if (count % 3 == 0) {
            std::cout << "zip" << std::endl;
        } else {
            std::cout << count << std::endl;
        }
    }
}
