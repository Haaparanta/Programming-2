/*
 * This is small program where you can input a file and this program analyses
 * it. You can get info what products are in shop selection.
 * What chains and where are they located. You can also search where you can
 * find cheapest item.
 * Vesa Haaparanta 290336
 * vesa.haaparanta@tuni.fi
 * pvveha
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <set>

using namespace std;

struct Product {
    string product_name;
    double price;
};

// Choosing structure for program.
using Products = vector<Product> ;
using Stores = map<string, Products>;
using Chains = map<string, Stores>;

// Making some const values for program which used most.
const double OUT_OF_STOCK = -1.0;
const string NOT_AVAIBLE = "out-of-stock";
const string P_NOT_AVAIBLE = "out of stock";
const string ERROR_IN_LINE = "Error: the input file has an erroneous line";

// Simple functio to check if there are empty spots in file.
bool is_spaces(string word)
{ // parameter: string word.
    for (char c : word) {

        if ( c != ' ') {

            return false;
        }
    }
    return true;
}

// Split functio copied from earlier task.
vector<string> split(const string& s, const char delimiter,
                               bool ignore_empty = false){
    vector<string> result;
    string tmp = s;

    while(tmp.find(delimiter) != string::npos)
    {
        string new_part = tmp.substr(0, tmp.find(delimiter));
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

// Adding info to datastructure functio was entirely done in cource trainings.
bool add_info(Chains& chains, string row)
{ // parameters: Data structure and one row of line.
    vector<string> split_row = split(row, ';', true);

    if (split_row.size()!= 4) {
        cout << ERROR_IN_LINE << endl;
        return false;
    }
    for (string part : split_row) {

        if (is_spaces(part)) {
            cout << ERROR_IN_LINE << endl;
            return false;
        }
    }
    string chain = split_row.at(0);
    string location = split_row.at(1);
    string product_name = split_row.at(2);
    string price = split_row.at(3); // notice price is string because
    // price can be double or string

    double new_price = 0.0;
    if (price == NOT_AVAIBLE) { // if price is equal to "out-of-stock".
        new_price = OUT_OF_STOCK; // new price is const variable -1.
    } else {
        new_price = stod(price); // changing string to double.
    }

    if (chains.find(chain) == chains.end()) { // if not find chain.
        chains.insert(pair<string, Stores>(chain,{})); // insert new chain.
    }
    if (chains.at(chain).find(location) == chains.at(chain).end()) { // same.
        chains.at(chain).insert(pair<string, Products>(location, {}));
    }
    for (Product& prod: chains.at(chain).at(location)) {

        if (prod.product_name == product_name) {
            prod.price = new_price;
            return true;
        }
    }
    chains.at(chain).at(location).push_back({product_name, new_price});
    return true;
}

// Reading a file and adding info in
// functio add_info also done course trainings.
bool read_file(string filename, Chains& chains)
{ // parameters: name of the file and datastructure.
    ifstream fileobject(filename);

    if (not fileobject) {
        cout << "Error: the input file cannot be opened" << endl;
        return false;
        
    }
    string row = "";
    while (getline(fileobject, row)) {

        if (not add_info(chains, row)) { // adds info to datastructure.
            fileobject.close();
            return false;
        }
    }
    fileobject.close();
    return true;
}

// Stores functio which prints out every stores location
// by parameter chain_name.
void stores(const Chains& chains, string chain_name)
{ // parameters: Data structure and name of the chain
    if (chains.find(chain_name) != chains.end()) {
        // checks if chain_name is in data structure.

        for (pair<string, Products> stores : chains.at(chain_name)) {
            cout << stores.first << endl;
        }
    } else {
        cout << "Error: unknown chain name" << endl;
    }
}

// Prints out all chains from the file.
void chains(const Chains& chains)
{ // parameter: Data structure
    for ( auto iter : chains) {
        cout << iter.first << endl;
    }
}

// Tells what items are avaible by chain and location
// and also tells if out of stock or if not
// out of stock tells price of the object.
void selection(const Chains& chains, string chain, string location)
{ // parameters: Data structure, name of the chain and name of the store.
    map<string, double> info; // map where to store all info.
    if (chains.find(chain) != chains.end()) { // if chain is in sata structure.

        if (chains.at(chain).find(location) != chains.at(chain).end()) {
            // if location is in data structure.

            for (auto iter : chains.at(chain).at(location)) {
                info.insert({iter.product_name, iter.price});
                // insert product details to info map
            }
            for (auto iter : info) { // printing
                if (iter.second == OUT_OF_STOCK) {
                    cout << iter.first << " " << P_NOT_AVAIBLE << endl;

                } else {
                    cout << fixed << iter.first << " " <<
                            setprecision(2) << iter.second << endl;
                }
            }
        } else {
            cout << "Error: unknown store" << endl;
        }
    } else {
        cout << "Error: unknown chain name" << endl;
    }
}

// Prints out every posible product ones.
void products(const Chains& chains)
{ // parameter: Data structure.
    set<string> product; // data structure where to store info.
    for (auto chain : chains) {
        string chain_of_stores = chain.first; // making code more readable.

        for (auto location : chains.at(chain_of_stores)) {
            string market = location.first;

            for (auto produ : chains.at(chain_of_stores).at(market)) {
                string commodity = produ.product_name;

                if (product.find(commodity) == product.end()) {
                    product.insert(commodity);
                    // if product is not in data structure add it.
                }
            }
        }
    }
    for (string article : product) { // printing
        cout << article << endl;
    }
}

// Tells where you can find cheapest product and in what price.
void cheapest(const Chains& chains, string product)
{ // parameters: Data structure and name of the product.
    set<string> info; // data structure where to store all info
    vector<double> cost = {OUT_OF_STOCK};
    // data structure where to add lowest price.
    for (auto chain : chains) {
        string chain_of_stores = chain.first;

        for (auto location : chains.at(chain_of_stores)) {
            string market = location.first;

            for (auto commodity : chains.at(chain_of_stores).at(market)) {
                string article = commodity.product_name;
                double fare = commodity.price;

                if (product == article) {

                    if (cost.at(0) == fare) {
                        info.insert(chain_of_stores + " " + market);

                    } else if (cost.at(0) > fare and
                               OUT_OF_STOCK < fare) {
                        info.clear();
                        cost.clear();
                        cost.push_back(fare);
                        info.insert(chain_of_stores + " " + market);

                    } else if (fare > OUT_OF_STOCK and
                               cost.at(0) == OUT_OF_STOCK) {
                        cost.clear();
                        cost.push_back(fare);
                        info.insert(chain_of_stores + " " + market);
                    }
                }
            }
        }
    }
    if (cost.at(0) != OUT_OF_STOCK) {
        double price = cost.at(0);
        cout << fixed << setprecision(2) << price << " euros" << endl;

        for (auto market_info : info) {
            string shop = market_info;
            cout << shop << endl;
        }
    } else if (cost.at(0) == OUT_OF_STOCK and info.size() > 0) {
        cout << "The product is temporarily"
                " out of stock everywhere" << endl;

    } else if (cost.at(0) == OUT_OF_STOCK and info.size() == 0) {
        cout << "The product is not part of product selection" << endl;
    }
}

// Main functio where program asks for input file
// and for commands until command "quit".
int main()
{
    Chains chain_info; // initalizing data structure.
    cout << "Input file: ";
    string filename = "";
    getline(cin, filename);
    
    if (!read_file(filename, chain_info)) {
        // reading file and adding info to data structure
        return EXIT_FAILURE;
    }

    while(true) { // user interface and errors of user interface.
        string line;
        cout << "> ";
        getline(cin, line);
        vector<string> parts = split(line, ' ', true);
        string command = parts.at(0);

        if (command == "stores" and parts.size() == 2){
            stores(chain_info, parts.at(1));

        } else if(command == "chains" and parts.size() == 1){
            chains(chain_info);

        } else if(command == "selection" and parts.size() == 3){
            selection(chain_info, parts.at(1), parts.at(2));

        } else if(command == "cheapest" and parts.size() == 2){
            cheapest(chain_info, parts.at(1));

        } else if(command == "products" and parts.size() == 1){
            products(chain_info);

        } else if(command == "quit" and parts.size() == 1){
           return EXIT_SUCCESS;

        } else {
            if (command == "stores" or command == "chains" or
                    command == "selection" or command == "cheapest"
                    or command == "products" or command == "quit") {
                cout << "Error: error in command " << command << endl;

            } else {
                cout << "Error: unknown command: " << command << endl;
            }
        }
    }
}
