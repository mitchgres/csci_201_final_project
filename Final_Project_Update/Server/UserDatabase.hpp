#ifndef __USERDATABASE_H__
#define __USERDATABASE_H__

#include <stdio.h>
#include <stdexcept>
#include <stdlib.h>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sys/stat.h>
#include <unistd.h>

#include "User.hpp"

using namespace boost::algorithm;
using namespace std;

class UserDatabase
{
    public:
        static void addUser(User inputUser);
        static void removeUser(int id);
        static bool hasUser(int id);
        static User getUser(int id);
    private:
        static string toServerFile(int id);
        static void createServerFile(ofstream& outputFile, User serverObject);
};

// $--- CLASS IMPLEMENTATION ---$
void UserDatabase::addUser(User inputUser)
{
    ofstream outputFile(toServerFile(inputUser.getID()));
    createServerFile(outputFile, inputUser);
}
void UserDatabase::removeUser(int id)
{
    if (hasUser(id) != false)
    {
        remove(toServerFile(id).c_str());
    }
}
bool UserDatabase::hasUser(int id)
{
    struct stat buffer;   
    return (stat(toServerFile(id).c_str(), &buffer) == 0); 
}
User UserDatabase::getUser(int id)
{
    int file_id;
    int password;
    User retrievedUser;
    ifstream inputFile(toServerFile(id));

    string line;
    int counter = 0;
    while (getline(inputFile, line, '\n')) 
    {
        switch (counter)
        {
        case 0:
            file_id = stoi(line);
            counter++;
            break;
        case 1:
            password = stoi(line);
            counter++;
            break;
        }
    }

    retrievedUser = User(file_id, password);

    inputFile.close();

    return retrievedUser;

}
string UserDatabase::toServerFile(int id)
{
    return ("U" + to_string(id) + ".txt");
}
 
void UserDatabase::createServerFile(ofstream& outputFile, User serverObject)
{
    outputFile << serverObject.getID() << endl;
    outputFile << serverObject.getPassword() << endl;
    outputFile.close();
}
#endif // __USERDATABASE_H__