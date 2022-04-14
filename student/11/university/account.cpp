#include "account.hh"
#include "utils.hh"
#include "instance.hh"
#include "course.hh"

Account::Account(std::string full_name, std::string email, int account_number):
    full_name_(full_name),
    last_name_(""),
    first_name_(""),
    email_(email),
    account_number_(account_number)
{
    std::vector<std::string> name = utils::split(full_name_, ' ');
    last_name_ = name.back();
    first_name_ = name.front();
}


void Account::print() const
{
    std::cout << account_number_ << ": "
              << first_name_ << " "
              << last_name_  << ", "
              << email_ << std::endl;
}

std::string Account::get_email()
{
    return email_;
}

void Account::add_current(Instance* insta)
{
    current_.push_back(insta);
    std::cout << SIGNED_UP << std::endl;
}

void Account::add_comp(Course *course, Instance *instan)
{
    if (instan->is_enrolled_to_insta(std::to_string(account_number_))) {
        completed_.push_back(course);
        auto old_data = std::find(current_.begin(), current_.end(), instan);
        current_.erase(old_data);
        std::cout << COMPLETED << std::endl;               
    } else {
        std::cout << NO_SIGNUPS << std::endl;
    }
}

void Account::print_courses(bool print_all)
{
    if (print_all) {
        // if true prints both for study slate and if false prints
        // bottom half of functio for compeated functio
        std::cout << "Current:" << std::endl;
        for (Instance* insta : current_) {
            insta->print_course_long_info();
        }
    std::cout << "Completed:" << std::endl;
    }
    int ects = 0;
    for (Course* course : completed_) {
        course->print_info(true);
        ects += course->get_credits();
    }
    std::cout << "Total credits: " << ects << std::endl;
}

