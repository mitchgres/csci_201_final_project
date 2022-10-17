#ifndef __STUDENT_H__
#define __STUDENT_H__

#include <string>
#include <sstream>

#include "User.hpp"

using namespace std;
/// @brief Data Class used to interact with Student Database Object
class Student: public User
{
    public:
        Student();
        /// @brief Custom Constructor for Student Object
        /// @param id 
        /// @param f_name 
        /// @param l_name 
        /// @param year 
        Student(int id, string f_name, string l_name, int year);
        /// @brief Accessor Method for Student First Name
        /// @return First Name
        string getFirstName();
        /// @brief Accessor Method for Student Last Name
        /// @return Last Name
        string getLastName();
        /// @brief Accessor Method for Student Year
        /// @return Year
        int getYear();
        /// @return String Representation of the Student Object
        string toString();
    private:
        string f_name;
        string l_name;
        int year;
};

// $--- CLASS IMPLEMENTATION ---$
Student::Student(){ }
Student::Student(int id, string f_name, string l_name, int year): User(id)
{
    this->f_name = f_name;
    this->l_name = l_name;
    this->year = year;
}
string Student::getFirstName()
{
    return this->f_name;
}
string Student::getLastName()
{
    return this->l_name;
}
int Student::getYear()
{
    return this->year;
}
string Student::toString()
{
    ostringstream outputStream;
    outputStream << User::toString();
    outputStream << "First Name: " << getFirstName() << endl;
    outputStream << "Last Name: " << getLastName() << endl;
    outputStream << "Year: " << getYear() << endl;
    return outputStream.str();
}

#endif // __STUDENT_H__