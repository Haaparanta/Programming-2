#include <iostream>

// Write here a function counting the mean value

int main()
{
    std::cout << "From how many integer numbers you want to count the mean value? ";
    int number;
    double summa = 0;
    std::cin >> number;
    if (number == 0) {
        std::cout << "Cannot count mean value from 0 numbers" << std::endl;
    } else {
        for (int luku = 1; luku <= number; ++luku) {
            std::cout << "Input " << luku << ". number: ";
            double vali = 0;
            std::cin >> vali;
            summa += vali;
        }
        double osamaara;
        osamaara = summa / number;
        std::cout << "Mean value of the given numbers is " << osamaara << std::endl;
    }

}
