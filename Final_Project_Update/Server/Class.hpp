#ifndef __CLASS_H__
#define __CLASS_H__

#include <string>
#include <sstream>

using namespace std;
/// @brief Data Class used for interaction with Class Database Object.
class Class
{
    public:
        Class();
        /// @brief Custom Contructor for Class Object
        /// @param id 
        /// @param name 
        /// @param dept 
        /// @param roomNumber 
        Class(int id, string name, string dept, int roomNumber);
        /// @brief Accessor Method for Class ID
        /// @return Class ID
        int getID();
        /// @brief Accessor Method for Class Name
        /// @return Class Name
        string getName();
        /// @brief Accessor Method for the Class Dept.
        /// @return Class Dept.
        string getDept();
        /// @brief Accessor Method for the Class Room Number
        /// @return Room Number
        int getRoomNumber();
        /// @return String Representation of the Class Object
        string toString();
    private:
        int id;
        string name;
        string dept;
        int roomNumber;
};

// $--- CLASS IMPLEMENTATION ---$
Class::Class(){ }
Class::Class(int id, string name, string dept, int roomNumber)
{
    this->id = id;
    this->name = name;
    this->dept = dept;
    this->roomNumber = roomNumber;
}
int Class::getID()
{
    return this->id;
}
string Class::getName()
{
    return this->name;
}
string Class::getDept()
{
    return this->dept;
}
int Class::getRoomNumber()
{
    return this->roomNumber;
}
string Class::toString()
{
    ostringstream outputStream;
    outputStream << "ID: " << getID() << endl;
    outputStream << "Name: " << getName() << endl;
    outputStream << "Dept: " << getDept() << endl;
    outputStream << "Room Number: " << getRoomNumber() << endl;
    return outputStream.str();
}

#endif // __CLASS_H__