 /* Game15 (or puzzle 15) : Template code
 *
 * Class: Board
 *
 * Program author ( Fill with your own info )
 * Name: Vesa Haaparanta
 * Student number: 290336
 * UserID: pvveha ( Necessary due to gitlab folder naming. )
 * E-Mail: vesa.haaparanta@tuni.fi
 **/

#include "board.hh"
#include <iostream>
#include <string>
#include <iomanip>

const int EMPTY = 16;
const unsigned int PRINT_WIDTH = 5;
const int SIZE = 4;

Board::Board(vector<int> numbers):
    numbers_(numbers) {
// Initilaizes class
    int i = 0;
    for( int y = 0; y < SIZE; ++y ) {
        vector<unsigned int> line;
        for( int x = 0; x < SIZE; ++x ) {
            line.push_back(numbers_.at(i));
            ++i;
        }
        grid_.push_back(line);
    }
}


void Board::print()
{
// prints everything
    for(unsigned int x = 0; x < SIZE; ++x)
    {
        std::cout << std::string(PRINT_WIDTH * SIZE + 1, '-') << std::endl;
        for(unsigned int y = 0; y < SIZE; ++y)
        {
            std::cout << "|" << std::setw(PRINT_WIDTH - 1);
            if (grid_.at(x).at(y) != EMPTY)
            {
                std::cout << grid_.at(x).at(y);
            }
            else
            {
                std::cout << ".";
            }
        }
        std::cout << "|" << std::endl;
    }
    std::cout << std::string(PRINT_WIDTH * SIZE + 1, '-') << std::endl;
}

void Board::move(string command, int number) {
// moves everything in the board
    int index_x = 0;
    int index_y = 0;
    for( int y = 0; y < SIZE; ++y ) {
        for( int x = 0; x < SIZE; ++x ) {
            int score = grid_.at(y).at(x);
            if (score == number) {
                index_x = x;
                index_y = y;
            }
        }
    }
    if (command == "s") {
        if (index_y > 0 and grid_.at(index_y + 1).at(index_x) == 16) {
            grid_.at(index_y + 1).at(index_x) = number;
            grid_.at(index_y).at(index_x) = 16;
        } else {
            cout << "Impossible direction: " << command << endl;
        }
    } else if (command == "a") {
        if (index_x > 0 and grid_.at(index_y).at(index_x - 1) == 16) {
            grid_.at(index_y).at(index_x) = 16;
            grid_.at(index_y).at(index_x - 1) = number;
        } else {
            cout << "Impossible direction: " << command << endl;
        }
    } else if (command == "w") {
        if (index_y < 4 and grid_.at(index_y - 1).at(index_x) == 16) {
            grid_.at(index_y - 1).at(index_x) = number;
            grid_.at(index_y).at(index_x) = 16;
        } else {
            cout << "Impossible direction: " << command << endl;
        }
    } else if (command == "d") {
        if (index_x < 4 and grid_.at(index_y).at(index_x + 1) == 16) {
            grid_.at(index_y).at(index_x + 1) = number;
            grid_.at(index_y).at(index_x) = 16;
        } else {
            cout << "Impossible direction: " << command << endl;
        }
    }
}

int Board::has_won() {
// check if is game won
    int number = 0;
    for (int i = 0; i < 16; ++i) {
        int y = i / 4;
        int x = i % 4;
        int score = grid_.at(y).at(x);
        if (score == i + 1) {
            number += 1;
        }
    }
    if (number == 16) {
        return 1;
    } else {
        return 0;
    }
}

bool Board::is_solvable() {
// check if game is solvable
    int inversio = 0;
    int index_x = 0;
    int index_y = 0;
    for( int y = 0; y < SIZE; ++y ) {
        for( int x = 0; x < SIZE; ++x ) {
            int score = grid_.at(y).at(x);
            if (score == 16) {
                index_x = x;
                index_y = y;
            }
        }
    }
    int x_x_x = index_x;
    while (index_y < 3) {
        int temp = grid_.at(index_y + 1).at(index_x);
        grid_.at(index_y).at(index_x) = temp;
        grid_.at(index_y + 1).at(index_x) = 16;
        index_y += 1;
    }
    for (int i = 0; i < 16; ++i) {
        int y = i / 4;
        int x = i % 4;
        int number_at = grid_.at(y).at(x);
        for (int j = i + 1; j < 16; ++j) {
            int y_y = j / 4;
            int x_x = j % 4;
            int number_at_above = grid_.at(y_y).at(x_x);
            if (number_at > number_at_above) {
                inversio += 1;
            }
        }
    }
    if (inversio == 1 and x_x_x == 2) {
        return true;
    } else if (inversio % 2 == 1) {
        return false;
    } else {
        return true;
    }
}
