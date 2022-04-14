#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <fstream>
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
void print (map<string, set<int>> data)
{
    for (pair<string, set<int>> wordpair : data) {
        cout << wordpair.first;
        cout << " " << wordpair.second.size();
        cout << ": ";
        for (set<int>::iterator iter = wordpair.second.begin(); iter != wordpair.second.end(); ++ iter) {
            if (iter == wordpair.second.begin()) {
                cout << *iter;
            } else {
                 cout << ", " << *iter;
            }
        }
        cout << endl;
    }
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
    int row_number = 1;
    map<string,set<int>> wordcounts = {};
    while (getline(file, row)) {
        vector <string> split_row = split(row, ' ', true);
        for (string word:split_row) {
            if (wordcounts.find(word) == wordcounts.end()) {
                wordcounts[word] = {row_number};
            } else {
                wordcounts.at(word).insert(row_number);
            }
        }
        ++ row_number;
    }
    file.close();

    print(wordcounts);
}
