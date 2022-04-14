#include "player.hh"
#include <string>

using namespace std;

Player::Player(string nimi):
    nimi_(nimi), pts_(0) {
}
string Player::get_name() {
    return nimi_;
}
void Player::add_points(int pts) {
    pts_ = pts + pts_;
    if (pts_ > 50) {
        pts_ = 25;
    }
}
int Player::get_points() {
    return pts_;
}
bool Player::has_won() {
    if (pts_ == 50) {
        return true;
    } else {
        return false;
    }
}
