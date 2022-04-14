#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    string input_file;
    string output_file;
    cout << "Input file: ";
    cin >> input_file;
    cout << "Output file: ";
    cin >> output_file;
    ifstream luku(input_file);
    if (not luku) {
        cout << "Error! The file " << input_file << " cannot be opened." << endl;
        return 1;
    } else {
        string rivi;
        vector <string> temp;
        while (getline(luku, rivi)) {
            temp.push_back(rivi);
        }
        luku.close();
        ofstream kirjoitus(output_file);
        int koko = temp.size();
        for (int i = 0; i < koko; ++i) {
            kirjoitus << i + 1 << " " << temp.at(i) << endl;
        }
        kirjoitus.close();
    }
}
