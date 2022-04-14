#include "cards.hh"

// TODO: Implement the methods here

Cards::Cards()
{
    top_= nullptr;
}

void Cards::add(int id)
{
    if (top_ ==nullptr) {
        top_ = new Card_data{id, nullptr};
        return;
    }
    Card_data* tmp = new Card_data{id, top_};
    top_ = tmp;
}

void Cards::print_from_top_to_bottom(std::ostream &s)
{
    Card_data* tmp = top_;
    int counter = 1;
    while (tmp != nullptr) {
        s << counter <<": " << tmp->data << std::endl;
        ++counter;
        tmp = tmp->next;
    }
}

bool Cards::remove(int &id)
{
    if (top_ == nullptr) {
        return false;
    }
    id = top_->data;
    Card_data* new_top = top_->next;
    delete top_;
    top_ = new_top;
    return true;
}

bool Cards::bottom_to_top()
{
    if(top_ == nullptr || top_->next == nullptr) {
        return false;
    }
    Card_data* last = top_;
    while (last->next != nullptr) {
        last = last->next;
    }
    Card_data* tmp = top_;
    while(tmp->next->next != nullptr) {
        tmp = tmp->next;
    }
    tmp->next = nullptr;
    last->next = top_;
    top_ = last;
    return true;
}

bool Cards::top_to_bottom()
{

    if( top_ == nullptr || top_->next == nullptr) {
       return false;
    }
    Card_data* new_top = top_->next;
    Card_data* last = top_;
    while( last->next != nullptr ) {
          last = last->next;
    }
    top_->next = nullptr;
    last->next = top_;
    top_ = new_top;

    return true;
}

void Cards::print_from_bottom_to_top(std::ostream &s)
{
   recursive_print(top_, s);
}


Cards::~Cards()
{
    Card_data* tmp = top_;
    while (tmp != nullptr) {
        top_ = top_->next;
        delete tmp;
        tmp = top_;
    }
}

int Cards::recursive_print(Cards::Card_data *top, std::ostream &s)
{
    if (top == nullptr) {
        return 1;
    }
    int number = recursive_print(top->next, s);
    s << number << ": " << top->data << std::endl;
    return number + 1;


}
