/**
 * @file StudentDatabase.hpp
 * @author Mitchell M. Gresham 
 * @brief Abstract class which contains methods for interaction with the Student Object of the Database files.
 * @version 0.1
 * @date 2022-10-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __STUDENTDATABASE_H__
#define __STUDENTDATABASE_H__

#include <stdio.h>
#include <stdexcept>
#include <stdlib.h>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sys/stat.h>
#include <unistd.h>

#include "Student.hpp"

using namespace boost::algorithm;
using namespace std;

class StudentDatabase
{
    public:
        static void addStudent(Student inputStudent);
        static void removeStudent(int id);
        static Student getStudent(int id);
        static bool hasStudent(int id);
    private:
        static string toServerFile(int id);
        static void createServerFile(ofstream& outputFile, Student studentObject);
};

// $--- CLASS IMPLEMENTATION ---$
void StudentDatabase::addStudent(Student inputStudent)
{
    ofstream outputFile(toServerFile(inputStudent.getID()));
    createServerFile(outputFile, inputStudent);
}
void StudentDatabase::removeStudent(int id)
{
    if (hasStudent(id) != false)
    {
        remove(toServerFile(id).c_str());
    }
}
bool StudentDatabase::hasStudent(int id)
{
    struct stat buffer;   
    return (stat(toServerFile(id).c_str(), &buffer) == 0); 
}
Student StudentDatabase::getStudent(int id)
{
    int file_id;
    string f_name;
    string l_name;
    int year;
    Student retrievedStudent;
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
            f_name = line;
            counter++;
            break;
        case 2: 
            l_name = line;
            counter++;
            break;
        case 3:
            year = stoi(line);
            counter++;
            break;
        }
    }

    retrievedStudent = Student(file_id, f_name, l_name, year);

    inputFile.close();

    return retrievedStudent;

}
string StudentDatabase::toServerFile(int id)
{
    return ("S" + to_string(id) + ".txt");
}
void StudentDatabase::createServerFile(ofstream& outputFile, Student serverObject)
{
    outputFile << serverObject.getID() << endl;
    outputFile << serverObject.getFirstName() << endl;
    outputFile << serverObject.getLastName() << endl;
    outputFile << serverObject.getYear();
    outputFile.close();
}
#endif // __STUDENTDATABASE_H__