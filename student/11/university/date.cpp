#include "date.hh"
#include <iostream>

Date::Date(unsigned int day, unsigned int month, unsigned int year):
    day_(day), month_(month), year_(year)
{
    if ( month_ > 12 || month_ < 1){
        month_ = 1;
    }
    if ( day_ > month_sizes[month_ - 1]
         || (month_ == 2 && is_leap_year()
             && day > month_sizes[month - 1 ] + 1) ){
        day_ = 1;
    }

}

Date::~Date()
{

}

void Date::advance_by_period_length()
{
    advance_by(PERIOD_LENGTH);
}

void Date::advance_by(unsigned int days)
{
    day_ = day_ + days;
    while ( day_ > month_sizes[month_ - 1] ){
        if ( month_ == 2 && day_ == 29 ){
            return;
        }
        day_ = day_ - month_sizes[month_ - 1];
        if ( month_ == 2 && is_leap_year() ){
            day_--;
        }
        month_++;

        if ( month_ > 12 ){
            month_ = month_ - 12;
            year_++;
        }
    }
}

void Date::print() const
{
    std::cout << day_ << "." << month_ << "." << year_;
}

unsigned int Date::get_day() const
{
    return day_;
}

unsigned int Date::get_month() const
{
    return month_;
}

unsigned int Date::get_year() const
{
    return year_;
}

bool Date::operator==(const Date *rhs) const
{
    return day_ == rhs->get_day() && month_ == rhs->get_month() && year_ == rhs->get_year() ;
}

bool Date::operator<(const Date *rhs) const
{
    return (year_ * 10000 + month_ * 100 + day_ ) <
            ( rhs->get_year() * 10000 + rhs->get_year() * 100 + rhs->get_day());
}

bool Date::is_leap_year() const
{
    return (year_ % 4 == 0) && (!(year_ % 100 == 0) || (year_ % 400 == 0));
}

