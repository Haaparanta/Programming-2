#ifndef SQUARE_HH
#define SQUARE_HH

#include <vector>
#include <iostream>


const int MAX_CAPACITY = 4;
const char CHARACTERS[] = {' ', '.', 'o', 'O', '@'};

class Square;
using Board = std::vector< std::vector< Square > >;

class Square {
 public:

   // location and amount of water as parameters to constructor
   Square( int x, int y, int drops, Board* board);
   ~Square();

   // adds water to the square, calls pop function if the square overflows
   void addWater();

   // tells if the square has water, to know if a drop is added to the square or should it pass the square
   bool hasWater() const;

   // prints the square (its amount of water) to the given stream
   void print( std::ostream& ) const;

 private:

   // adds water to each direction and disappears
   void pop();

   // location and the amount of water
   int x_;
   int y_;
   int drops_;

   // pointer to the board, where the water drop lies
   Board* board_;

};

#endif // SQUARE_HH
