/* Game15 (or puzzle 15) : Template code
 *
 * Class: Board
 * Describes a two-dimensional grid for puzzle 15 with necessary functions.
 *
 * Program author ( Fill with your own info )
 * Name: Vesa Haaparanta
 * Student number: 290336
 * UserID: pvveha ( Necessary due to gitlab folder naming. )
 * E-Mail: vesa.haaparanta@tuni.fi
 * */

#ifndef BOARD_HH
#define BOARD_HH
#include <vector>
#include <string>
using namespace std;


class Board
{

public:
    Board(vector<int> numbers);

    // Prints the game grid
    void print();

    // More methods
    void move(string command, int number);
    int has_won();
    bool is_solvable();

private:
    // Game grid for the 15 puzzle
    vector<vector<unsigned int>> grid_;

    // More attributes
    vector<int>numbers_;
    vector<int> numbers_row_;

};

#endif // BOARD_HH
