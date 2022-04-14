#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<string> split(string line, char separator, bool truth = false) {
    string::size_type apu = 0;
    vector<string> lopputulos;
    apu = line.length();
    int koko = apu;
    string rivi = "";
    for (int i = 0; i < koko; ++i) {
        char merkki = line.at(i);
        if (merkki == separator) {
            string::size_type apu = 0;
            apu = rivi.length();
            int pituus = apu;
            if (truth == true and pituus > 0) {
                lopputulos.push_back(rivi);
                rivi = "";
            } else if ((truth == false)) {
                lopputulos.push_back(rivi);
                rivi = "";
            }
        } else {
            rivi.push_back(merkki);
        }
    }
    apu = rivi.length();
    int leveys = apu;
    if (leveys > 0 or truth == false) {
        lopputulos.push_back(rivi);
    }
    return lopputulos;
}

int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }
    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
