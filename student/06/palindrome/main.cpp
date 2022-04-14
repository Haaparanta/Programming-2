#include <iostream>
#include <string>
#ifndef RECURSIVE_FUNC
#define RECURSIVE_FUNC
#endif

bool palindrome_recursive(std::string s)
{
    RECURSIVE_FUNC
    // Do not remove RECURSIVE_FUNC declaration, it's necessary for automatic testing to work
    // ------------


    // Add your implementation here
    int pituus = s.size();
    if (pituus <= 1) {
        return true;
    }
    if (s.at(0) == s.at(pituus - 1)) {
        s.pop_back();
        s.substr(1);
        s.replace(0,1,"");
        return palindrome_recursive(s);
    } else {
        return false;
    }

}

// Do not modify rest of the code, or the automated testing won't work.
#ifndef UNIT_TESTING
int main()
{
    std::cout << "Enter a word: ";
    std::string word;
    std::cin >> word;

    if(palindrome_recursive(word)){
        std::cout << word << " is a palindrome" << std::endl;
    } else {
        std::cout << word << " is not a palindrome" << std::endl;
    }
}
#endif
