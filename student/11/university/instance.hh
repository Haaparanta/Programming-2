/* Class: Instance
 * ----------
 * TIE-02201/TIE-02207 SPRING 2020
 * ----------
 * Class that represent a single instance.
 * Vesa Haaparanta
 * vesa.haaparanta@tuni.fi
 * student id 290336
 * Note: Students should make changes to this class, and add their info and
 * specifics of the class to this comment.
 * */
#ifndef INSTANCE_HH
#define INSTANCE_HH

#include "account.hh"
#include "date.hh"
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

// Forward-declaration of Course,
// so that instance can point to the course it belongs to.
class Course;

const std::string ALREADY_REGISTERED =
        "Error: Student has already registered on this course.";
const std::string LATE =
        "Error: Can't sign up on instance after the starting date.";
const std::string INDENT = "    ";


class Instance
{
public:
    /**
     * @brief Instance construct instance
     * @param course
     * @param name
     * @param date
     * @param pointer_to_course
     */
    Instance(const std::string course, const std::string name,
             const Date* date, Course* pointer_to_course);

    // destruct date
    ~Instance();

    /**
     * @brief print how many students
     */
    void print();

    /**
     * @brief print_students prints students info
     */
    void print_students();

    /**
     * @brief print_course_long_info prints course info
     */
    void print_course_long_info();

    /**
     * @brief is_named
     * @return truth if named like that truth otherwise false
     */
    bool is_named(const std::string&);

    /**
     * @brief sign_up
     * @param student_id
     * @param date
     * @param student
     * @return if succesfull return true
     */
    bool sign_up(std::string student_id, const Date* date, Account* student);

    /**
     * @brief is_enrolled_to_insta
     * @param student_id
     * @return true if student is enrolled to this instance
     */
    bool is_enrolled_to_insta(std::string student_id);

    /**
     * @brief get_course
     * @return pointer to course
     */
    Course* get_course();
    

private:

    /**
     * @brief date_ starting day
     */
    const Date* date_;

    /**
     * @brief ins_name_ instance name
     */
    const std::string ins_name_;

    /**
     * @brief course_ course name
     */
    const std::string course_;

    /**
     * @brief name_of_course_ long name of the course
     */
    std::string name_of_course_;

    /**
     * @brief pointer_to_course_ pointer of this instances course
     */
    Course* pointer_to_course_;

    /** I choseto use two vector rather then map
     * @brief students_ vector of student ids
     */
    std::vector<std::string> students_;

    /**
     * @brief i_students_ pointer for students
     */
    std::vector<Account*> i_students_;

    /**
     * @brief checking_date helper functio for sign_up
     * @param date
     * @return truth if date are right.
     */
    bool checking_date(const Date* date) const;
};

#endif // INSTANCE_HH
