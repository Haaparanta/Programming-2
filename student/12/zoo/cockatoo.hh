#ifndef COCKATOO_HH
#define COCKATOO_HH
#include "bird.hh"


class Cockatoo : public Bird
{
public:
    Cockatoo();
    void sing(std::ostream& output);
};

#endif // COCKATOO_HH
