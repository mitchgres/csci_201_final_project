#ifndef __USER_H__
#define __USER_H__

#include <string>
#include <sstream>

using namespace std;
/// @brief Data class used to interact with User objects from the Database.
class User
{
    public:
        User();
        /// @brief Custom Constructor for User Object
        /// @param id 
        User(int id, int password);
        User(int id);
        /// @brief Accessor Methods for ID of User Object
        /// @return ID
        int getID();
        /// @return String Represenation of the User Object
        int getPassword();
        string toString();
    private:
        /// @brief ID of User
        int id;
        int password;
};

// $--- CLASS IMPLEMENTATION ---$
User::User(){ }
User::User(int id)
{
    this->id = id;
}
User::User(int id, int password)
{
    this->id = id;
    this->password = password;
}
int User::getID()
{
    return this->id;
}
int User::getPassword()
{
    return this->password;
}
string User::toString()
{
    ostringstream outputStream;
    outputStream << "ID: " << getID() << endl;
    return outputStream.str();
}

#endif // __USER_H__