#include "university.hh"

University::University():running_number_(111111)
{
}

University::~University()
{
    for ( auto course : courses_ ){
        delete course.second;
    }

    for ( auto account : accounts_ ){
        delete account.second;
    }

}

void University::add_course(Params params)
{
    if ( courses_.find(params.at(0)) != courses_.end() ){
        std::cout << ALREADY_EXISTS << std::endl;
        return;
    } else {
        std::cout << NEW_COURSE << std::endl;
    }

    Course* n_course = new Course(params.at(0), params.at(1));
    courses_.insert({n_course->get_code(), n_course});
}

void University::print_courses(Params)
{
    for ( auto course : courses_ ){
        course.second->print_info(true);
    }
}

void University::print_course(Params params)
{
    if ( courses_.find(params.at(0)) == courses_.end() ){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }

    courses_.at(params.at(0))->print_long_info();
}

void University::add_account(Params params)
{
    for( std::map<int, Account*>::iterator iter = accounts_.begin(); iter != accounts_.end(); ++iter ) {
        if( iter->second->get_email() == params.at(1) ) {
            std::cout << ALREADY_EXISTS << std::endl;
            return;
        }
    }

    int account_number = running_number_++;
    Account* n_account = new Account(params.at(0), params.at(1), account_number);
    accounts_.insert({account_number, n_account});
    std::cout << NEW_ACCOUNT << std::endl;
    n_account->print();
}

void University::print_accounts(Params)
{
    for ( auto account : accounts_ ){
        account.second->print();
    }
}

void University::print_account_info(Params params)
{
    std::map<int, Account*>::iterator iter = accounts_.find(std::stoi(params.at(0)));
    if ( iter == accounts_.end() ){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }
    iter->second->print();
}

void University::add_staff_to_course(Params params)
{
    if ( courses_.find(params.at(0)) == courses_.end() ){
        std::cout << CANT_FIND << params.at(0) << std::endl;
        return;
    }
    if ( accounts_.find(std::stoi(params.at(1))) == accounts_.end() ){
        std::cout << CANT_FIND << params.at(1) << std::endl;
        return;
    }

    courses_.at(params.at(0))->add_staff(accounts_.at(std::stoi(params.at(1))));
}

void University::add_instance(Params params)
{
    if (course_not_exist(params.at(0))){
        // helper functio
        return;
    }
    if (courses_.at(params.at(0))->has_instance(params.at(1))) {
        std::cout << INSTANCE_EXISTS << std::endl;
        return;
    }

    Date* date_new = new Date(utils::today);
    Instance* inst_new = new Instance(params.at(0),params.at(1), date_new, courses_.at(params.at(0)));
    courses_.at(params.at(0))->new_instance(inst_new);
}

void University::sign_up_on_course(Params params)
{
    if (course_not_exist(params.at(0))){
        return;
    }

    if (instance_not_exist(params.at(0), params.at(1))) {
        return;
    }

    if (account_not_exist(params.at(2))){
        return;
    }

    Instance* inst = courses_.at(params.at(0))->get_instance(params.at(1));
    const Date* date_new = new Date(utils::today);



    if (inst->sign_up(params.at(2), date_new, accounts_.at(std::stoi(params.at(2))))) {
        accounts_.at(std::stoi(params.at(2)))->add_current(inst);
    }
}

void University::complete_course(Params params)
{
    if (course_not_exist(params.at(0))){
        return;
    }

    if (instance_not_exist(params.at(0), params.at(1))) {
        return;
    }

    if (account_not_exist(params.at(2))){
        return;
    }
    Instance* inst = courses_.at(params.at(0))->get_instance(params.at(1));
    accounts_.at(std::stoi(params.at(2)))->add_comp(courses_.at(params.at(0)), inst);
}

void University::print_signups(Params params)
{
    if (course_not_exist(params.at(0))) {
        return;
    }
    courses_.at(params.at(0))->print_signups();
}

void University::print_study_state(Params params)
{
    if (account_not_exist(params.at(0))) {
        return;
    }
    accounts_.at(std::stoi(params.at(0)))->print_courses(true);
}

void University::print_completed(Params params)
{
    if (account_not_exist(params.at(0))) {
        return;
    }
    accounts_.at(std::stoi(params.at(0)))->print_courses(false);
}

void University::set_date(Params params)
{
    utils::today = Date(std::stoi(params.at(0)), std::stoi(params.at(1)), std::stoi(params.at(2)));
    std::cout << "Date has been set to ";
    utils::today.print();
    std::cout << std::endl;
}

void University::advance_date(Params params)
{
    utils::today.advance_by(std::stoi(params.at(0)));
    std::cout << "New date is ";
    utils::today.print();
    std::cout << std::endl;
}

void University::advance_by_period(Params)
{
    utils::today.advance_by_period_length();
    std::cout << "New date is ";
    utils::today.print();
    std::cout << std::endl;
}

bool University::course_not_exist(std::string course)
{
    if ( courses_.find(course) == courses_.end() ){
        std::cout << CANT_FIND << course << std::endl;
        return true;
    }
    return false;
}

bool University::account_not_exist(std::string account)
{
    if ( accounts_.find(std::stoi(account)) == accounts_.end() ){
        std::cout << CANT_FIND << account << std::endl;
        return true;
    }
    return false;
}

bool University::instance_not_exist(std::string course, std::string instance)
{
    if (! courses_.at(course)->has_instance(instance)) {
        std::cout << CANT_FIND << instance << std::endl;
        return true;
    }
    return false;
}
