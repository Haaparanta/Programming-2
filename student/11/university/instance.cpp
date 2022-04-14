#include "instance.hh"
#include "course.hh"

Instance::Instance(const std::string course, const std::string name,
                   const Date* date, Course* pointer_to_course):
    date_(date), ins_name_(name), course_(course), pointer_to_course_(pointer_to_course)
{
    name_of_course_ = pointer_to_course->get_name();
}
Instance::~Instance(){
    delete date_;
}
void Instance::print()
{
    std::cout << ins_name_ << std::endl;
    std::cout << INDENT << "Starting date: ";
    date_->print();
    std::cout << std::endl;
    std::cout << INDENT << "Amount of students: ";
    std::cout << students_.size() << std::endl;
}

void Instance::print_students()
{
    if (students_.size() > 0){
        for (auto student : i_students_){
            std::cout << INDENT;
            student->print();
        }
    }
}

void Instance::print_course_long_info()
{
    std::cout << course_ << " : " << name_of_course_ << " " << ins_name_ << std::endl;
}

bool Instance::is_named(const std::string &name)
{
    if (name == ins_name_) {
        return true;
    }
    return false;
}

bool Instance::checking_date(const Date* date) const
{
    if ((!date_->operator <(date)) or date_->operator ==(date)) {
        return true;
    }
    return false;
}

Course *Instance::get_course()
{
    return pointer_to_course_;
}

bool Instance::sign_up(std::string student_id, const Date* date, Account* student)
{
    for (unsigned int i = 0; i < students_.size(); ++i) {

        if (students_.at(i) == student_id) {
            delete date;
            std::cout << ALREADY_REGISTERED << std::endl;
            return false;
        }
    }
    if (checking_date(date)) {

        students_.push_back(student_id);
        i_students_.push_back(student);
        delete date;
        return true;
    }

    delete date;
    std::cout << LATE << std::endl;
    return false;
}

bool Instance::is_enrolled_to_insta(std::string student_id)
{
    for (unsigned int i = 0; i < students_.size(); ++i) {
        if (students_.at(i) == student_id) {
            return true;
        }
    }
    return false;
}

