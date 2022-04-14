#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;
using Network = map<string, vector<string>>;

const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";


std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false){
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

int Depht(Network n, string id) {

    int largest_depht = 0;
    for (unsigned int i = 0; i < n[id].size(); ++i) {
        int depht = Depht(n, n[id][i]);
        if (depht > largest_depht) {
            largest_depht = depht;
        }
    }
    return largest_depht + 1;
}

int Count(Network n, string id) {
    if (n.find(id) == n.end()) {
        return 0;
    } else {
        int result = 0;
        for (string person : n.at(id)) {
            ++result;
            result += Count(n, person);
        }
        return result;
    }
}

void print(Network n, string id, int indent = 0) {

    for (int i = 0; i < indent; ++i) {
        cout << "..";
    }

    cout << id << endl;

    if (n.find(id) != n.end()) {

        for (string person : n.at(id)) {
            print(n, person, indent + 1);
        }
    }
}

int main()
{
    // TODO: Implement the datastructure here

    Network network;

    while(true){
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        std::string command = parts.at(0);

        if(command == "S" or command == "s"){
            if(parts.size() != 3){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            // TODO: Implement the command here!
            if (network.find(id1) == network.end()) {
                network.insert(pair<string,vector<string>>(id1, {id2}));
            } else {
                network.at(id1).push_back(id2);
            }

        } else if(command == "P" or command == "p"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            print(network, id);

        } else if(command == "C" or command == "c"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            int result = Count(network, id);
            cout << result << endl;

        } else if(command == "D" or command == "d"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            int result = Depht(network, id);
            cout << result << endl;

        } else if(command == "Q" or command == "q"){
           return EXIT_SUCCESS;
        } else {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
