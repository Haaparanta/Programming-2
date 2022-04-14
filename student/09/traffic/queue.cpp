#include "queue.hh"
#include <iostream>

// Implement the member functions of Queue here

Queue::Queue(unsigned int cycle)
{
    cycle_ = cycle;
    normal_cycle_ = cycle;
    first_ = nullptr;
    last_ = nullptr;
    is_green_ = false;
}

Queue::~Queue()
{
    while ( first_ != nullptr ) {
       Vehicle* item_to_be_released = first_;
       first_ = first_->next;

       delete item_to_be_released;
    }
}

void Queue::enqueue(string reg)
{
    if (is_green_) {
        std::cout << "GREEN: The vehicle " << reg << " need not stop to wait" << std::endl;
        cycle_ -= 1;
        if (cycle_ == 0) {
            switch_light();
        }
    } else {
        Vehicle* new_item = new Vehicle{reg, nullptr};

        if ( first_ == nullptr ) {
           first_ = new_item;
           last_ = new_item;
        } else {
           last_->next = new_item;
           last_ = new_item;
        }
    }
}

void Queue::switch_light()
{
    if(is_green_) {
        is_green_ = false;
    } else {
        is_green_ = true;
    }
    reset_cycle(normal_cycle_);
    print();
}

void Queue::reset_cycle(unsigned int cycle)
{
    cycle_ = cycle;
    normal_cycle_ = cycle;
}

void Queue::print()
{
    Vehicle* item_to_be_printed = first_;
    if (is_green_) {
        if (item_to_be_printed == nullptr) {
            std::cout << "GREEN: No vehicles waiting in traffic lights" << std::endl;
        } else {
            std::cout << "GREEN: Vehicle(s)";
            while ( item_to_be_printed != nullptr and cycle_ > 0) {
               cout << " " << item_to_be_printed->reg_num;
               item_to_be_printed = item_to_be_printed->next;
               dequeue();
               --cycle_;
            }
            std::cout << " can go on" << std::endl;
        }
    } else {
        if (item_to_be_printed == nullptr) {
            std::cout << "RED: No vehicles waiting in traffic lights" << std::endl;
        } else {
            std::cout << "RED: Vehicle(s)";
            while ( item_to_be_printed != nullptr and cycle_ > 0) {
               cout << " " << item_to_be_printed->reg_num;
               item_to_be_printed = item_to_be_printed->next;
            }
            std::cout << " waiting in traffic lights" << std::endl;
        }
    }
    if (cycle_ < normal_cycle_) {
        is_green_ = false;
        cycle_ = normal_cycle_;
    }
}

void Queue::dequeue()
{

    Vehicle* item_to_be_removed = first_;
    if ( first_ == last_ ) {
       first_ = nullptr;
       last_ = nullptr;
    } else {
       first_ = first_->next;
    }

    delete item_to_be_removed;
}
