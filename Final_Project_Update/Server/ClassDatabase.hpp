#ifndef __CLASSDATABASE_H__
#define __CLASSDATABASE_H__

#include <stdio.h>
#include <stdexcept>
#include <stdlib.h>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sys/stat.h>
#include <unistd.h>

#include "Class.hpp"

using namespace boost::algorithm;
using namespace std;

class ClassDatabase
{
    public:
        /// @brief Takes a Class data class as input and then stores it into local database.
        /// @param id 
        /// @param name 
        /// @param department 
        /// @param roomNumber 
        static void addClass(Class inputClass);
        /// @brief Given the ID of the Class, destroys it in the database. If cannot be found then nothing occurs. 
        /// @param id 
        static void removeClass(int id);
        /// @brief Given the ID of the Class all informarion on the class is returned
        /// @param id 
        static Class getClass(int id);
        /// @brief Given the ID of the Class searches the database to see if a class with that ID exists. 
        /// @param id 
        /// @return 
        static bool hasClass(int id);
    private:
        static string toServerFile(int id);
        static void createServerFile(ofstream& outputFile, Class serverObject);
};

// $--- CLASS IMPLEMENTATION ---$
void ClassDatabase::addClass(Class inputClass)
{
    ofstream outputFile(toServerFile(inputClass.getID()));
    createServerFile(outputFile, inputClass);
}
void ClassDatabase::removeClass(int id)
{
    if (hasClass(id) != false)
    {
        remove(toServerFile(id).c_str());
    }
}
bool ClassDatabase::hasClass(int id)
{
    struct stat buffer;   
    return (stat(toServerFile(id).c_str(), &buffer) == 0); 
}
Class ClassDatabase::getClass(int id)
{
    int file_id;
    string name;
    string dept;
    int roomNumber;
    Class retrievedClass;
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
            name = line;
            counter++;
            break;
        case 2: 
            dept = line;
            counter++;
            break;
        case 3:
            roomNumber = stoi(line);
            counter++;
            break;
        }
    }

    retrievedClass = Class(file_id, name, dept, roomNumber);

    inputFile.close();

    return retrievedClass;

}
string ClassDatabase::toServerFile(int id)
{
    return ("C" + to_string(id) + ".txt");
}

void ClassDatabase::createServerFile(ofstream& outputFile, Class serverObject)
{
    outputFile << serverObject.getID() << endl;
    outputFile << serverObject.getName() << endl;
    outputFile << serverObject.getDept() << endl;
    outputFile << serverObject.getRoomNumber();
    outputFile.close();
}
#endif // __CLASSDATABASE_H__