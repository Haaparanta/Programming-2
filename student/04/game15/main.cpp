/* Game15 (or puzzle 15) : Template code
 *
 * Desc:
 *  This program generates a 15 puzzle. The board is SIZE x SIZE,
 * (original was 4x4) and every round the player chooses a direction and
 * a number tile, making the given tile to be moved to the given direction.
 *  Game will end when the numbers 1-15 (1-16) are in the ascending order,
 * starting from top left and proceeding row by row.
 * Empty space is represented by the number 16 in the code (constant EMPTY)
 * and by dot when printing the game board.
 *
 * Program author ( Fill with your own info )
 * Name: Vesa Haaparanta
 * Student number: 290336
 * UserID: pvveha ( Necessary due to gitlab folder naming. )
 * E-Mail: vesa.haaparanta@tuni.fi
 *
 * Notes about the program and it's implementation:
 *
 * */

#include "board.hh"
#include <random>
#include <iostream>
#include <algorithm>
#include <string>

// More functions
int if_all_numbers(vector<int> numbers) {
// check if all numbers from 1 to 16 are present
    int summa = 0;
    sort(numbers.begin(), numbers.end());
    for (int i = 0; i < 16; ++i) {
        int number = numbers.at(i);
        if (i + 1 == number) {
        } else {
            summa = i;
        }
    }
    return summa;
}

vector<int> split(string line) {
// Splits string to vector
    const char separator = ' ';
    string::size_type apu = 0;
    vector<int> lopputulos;
    apu = line.length();
    int koko = apu;
    string rivi = "";
    for (int i = 0; i < koko; ++i) {
        char merkki = line.at(i);
        if (merkki == separator) {
            lopputulos.push_back(stoi(rivi));
            rivi = "";
        } else {
            rivi.push_back(merkki);
        }
    }
    apu = rivi.length();
    int leveys = apu;
    if (leveys > 0) {
        lopputulos.push_back(stoi(rivi));
    }
    return lopputulos;
}

vector<int> my_shuffle()
// suffles all numbers
{
    vector<int> numbers = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    cout << "Give a seed value or an empty line: ";
    string seed = "";
    cin.ignore();
    getline(cin, seed);
    default_random_engine randomEng;
    if( seed == "" ) {
        // If the user did not give a seed value, use computer time as the seed value.
        randomEng.seed( time(NULL) );
    } else {
        randomEng.seed(stoi(seed));
    }
    uniform_int_distribution<int> distr(0, numbers.size() - 1);
    for(unsigned int i = 0; i < numbers.size(); ++i)
    {
        unsigned int random_index = distr(randomEng);
        unsigned int temp = numbers.at(i);
        numbers.at(i) = numbers.at(random_index);
        numbers.at(random_index) = temp;
    }
    return numbers;
}


int main()
{
    // More functionality

    string choice;
    bool truth = true;
    vector<int>numbers;
    while (truth) {
        cout << "Random initialization (y/n): ";
        cin >> choice;
        if (choice == "y") {
            numbers = my_shuffle();
            truth = false;
        } else if (choice == "n") {
            cout << "Enter the numbers 1-16 in a desired order (16 means empty):" << endl;
            unsigned int temp = 0;
            for (int i = 0; i < 16; ++i) {
                cin >> temp;
                numbers.push_back(temp);
            }
            for (unsigned int j = 1; j < numbers.size(); ++j) {
                if (find(numbers.begin(), numbers.end(), j)
                        == numbers.end()) {
                    cout << "Number " << j << " is missing" << endl;
                    return 1;
                }
            }
            truth = false;
        } else {
            cin.ignore();
            cout << "Unknown choice: " << choice << endl;
        }
    }
    Board lauta(numbers);
    bool solvable = lauta.is_solvable();
    if (solvable) {
        cout << "Game is solvable: Go ahead!" << endl;
    } else {
       cout << "Game is not solvable. What a pity." << endl;
       return 0;
    }
    lauta.print();
    int play = 0;
    while (play == 0) {
        cout << "Dir (command, number): ";
        cin.ignore();
        string command;
        cin >> command;
        if (command == "q") {
            return 0;
        }
        int number;
        cin >> number;
        if (number > 15) {
            cout << "Invalid number: " << number << endl;
            lauta.print();
        } else if (command == "a" or command == "s" or command == "w" or command == "d"){
            lauta.move(command, number);
            lauta.print();
            play = lauta.has_won();
        } else {
            cout << "Unknown command: " << command << endl;
            command = "";
            lauta.print();
        }
    }
    cout << "You won!" << endl;
}
