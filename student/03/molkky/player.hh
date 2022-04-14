#ifndef PLAYER_HH
#define PLAYER_HH
#include <string>

#endif // PLAYER_HH

using namespace std;
class Player {

public:
    Player(string nimi);
    string get_name();
    void add_points(int pts);
    int get_points();
    bool has_won();
private:
    string nimi_;
    int pts_;
};
