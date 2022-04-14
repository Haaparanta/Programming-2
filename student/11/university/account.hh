/* Class: Account
  * ----------
  * Defines a student or a staff account in the university system.
  *
  * In the project, this class should be expanded to
  * include study history of the account.
  * Vesa Haaparanta
  * vesa.haaparanta@tuni.fi
  * student id 290336
  * */
#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include "date.hh"
#include <string>
#include <vector>
#include <map>
#include <iostream>

class Instance;
class Course;

const std::string NO_SIGNUPS = "No signups found on this instance.";
const std::string SIGNED_UP = "Signed up on the course instance.";
const std::string COMPLETED = "Course completed.";

class Account
{
public:
    /**
     * @brief Account constructor
     * @param full_name as "frontname lastname"
     * @param email
     * @param account_number
     */
    Account(std::string full_name, std::string email, int account_number);

    /**
     * @brief print account info on one line
     */
    void print() const;

    /**
     * @brief get_email
     * @return email linked to this account
     */
    std::string get_email();

    /**
     * @brief add_current: add new instance to accounts current vector
     * @param insta
     */
    void add_current(Instance* insta);

    /**
     * @brief is_named
     * @param id
     * @return truth if is named to id
     */
    bool is_named(const int id);

    /**
     * @brief add_comp add new course to compleated vector
     * @param course
     * @param insta
     */
    void add_comp(Course* course, Instance* insta);

    /**
     * @brief print_courses priint current and compleated courses
     * @param print_all if true prints both and if false
     * print compleated courses
     */
    void print_courses(bool print_all);

private:
    std::string full_name_;
    std::string last_name_;
    std::string first_name_;
    std::string email_;
    const int account_number_;
    std::vector<Instance*> current_;
    std::vector<Course*> completed_;
};

#endif // ACCOUNT_HH
