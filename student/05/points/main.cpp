#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <fstream>

using namespace std;

void print (map<string, int> data)
{
    cout << "Final scores:" << endl;
    for (pair<string, int> wordpair : data) {
        cout << wordpair.first;
        cout << ": " ;
        cout << wordpair.second << endl;
    }
}

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
    string filename;
    cout << "Input file: ";
    getline(cin, filename);
    ifstream file(filename);
    if (not file) {
        cout << "Error! The file " << filename << " cannot be opened." << endl;
        return 1;
    }
    string row;
    map<string, int> wordcounts = {};
    string word;
    int number;
    while (getline(file, row)) {
        vector <string> split_row = split(row, ':', true);
        word = split_row.at(0);
        number = stoi(split_row.at(1));
        if (wordcounts.find(word) == wordcounts.end()) {
            wordcounts[word] = {number};
        } else {
            wordcounts.at(word) += number;
        }
    }
    print(wordcounts);
}
