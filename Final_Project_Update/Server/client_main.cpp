/**
 * @file client_main.cpp
 * @author Mitchell M. Gresham 
 * @brief Client driver program which run until user doesn't input one of the available menu items, then program will end. The client 
 *        will connect over and over again in the while-loop.
 * @version 0.1
 * @date 2022-10-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __CLIENT_MAIN_H__
#define __CLIENT_MAIN_H__

#include <string>

#include "System.hpp"
#include "Class.hpp"
#include "TCPClient.hpp"

using namespace std;

void outputClassSelection();

string addClass(Class inputClass);
string getClass(int id);
string deleteClass(int id);

string addUser(User inputUser);
string getUser(int id);
string deleteUser(int id);

string addStudent(Student inputStudent);
string getStudent(int id);
string deleteStudent(int id);

int main()
{
    System::println("Please Enter Port Number To Connect To: ");

    int portNumber = stoi(System::getInput());
    
    while (true)
    {
        TCPClient client(portNumber);

        string userInput;

        // Show user their options.
        System::println("What Would You Like To Do?...");
        System::println("1 -- Add To Database");
        System::println("2 -- Query From Database");
        System::println("3 -- Remove From Database");
        System::println("4 -- Exit Program");

        userInput = System::getInput();

        if (userInput == "1")
        {
            outputClassSelection();
            userInput = System::getInput();
            if(userInput == "1")
            {
                int id;
                int password;

                System::println("Please Enter ID For User: ");
                id = stoi(System::getInput());

                System::println("Please Enter Password For User: ");
                password = stoi(System::getInput());

                client.useClient
                (
                    addUser
                    (
                        User
                        (
                            id,
                            password
                        )
                    )
                );
            }
            else if(userInput == "2")
            {
                int id;
                string f_name;
                string l_name;
                int year;

                System::println("Please Enter ID For Student: ");
                id = stoi(System::getInput());

                System::println("Please Enter First Name For Student: ");
                f_name = System::getInput();

                System::println("Please Enter Last Name For Student: ");
                l_name = System::getInput();

                System::println("Please Enter Year For Student: ");
                year = stoi(System::getInput());

                client.useClient
                (
                    addStudent
                    (
                        Student
                        (
                            id, 
                            f_name,
                            l_name,
                            year
                        )
                    )
                );
            }
            else if(userInput == "3")
            {
                int id;
                string name;
                string dept;
                int roomNumber;

                System::println("Please Enter ID For Class: ");
                id = stoi(System::getInput());

                System::println("Please Enter Name For Class: ");
                name = System::getInput();

                System::println("Please Enter Dept. Name For Class: ");
                dept = System::getInput();

                System::println("Please Enter Room Number For Class: ");
                roomNumber = stoi(System::getInput());

                client.useClient
                (
                    addStudent
                    (
                        Student
                        (
                            id, 
                            name,
                            dept,
                            roomNumber
                        )
                    )
                );
            }
        }
        else if (userInput == "2")
        {
            outputClassSelection();
            userInput = System::getInput();
            if(userInput == "1")
            {
                System::println("Please Enter ID For User: ");
                client.useClient
                (
                    getUser
                    (
                        stoi(System::getInput())
                    )
                );
            }
            else if(userInput == "2")
            {
                System::println("Please Enter ID For Student: ");
                client.useClient
                (
                    getStudent
                    (
                        stoi(System::getInput())
                    )
                );               
            }
            else if(userInput == "3")
            {
                System::println("Please Enter ID For Class: ");
                client.useClient
                (
                    getClass
                    (
                        stoi(System::getInput())
                    )
                ); 
            }
        }
        else if (userInput == "3")
        {
            outputClassSelection();
            userInput = System::getInput();
            if(userInput == "1")
            {
                System::println("Please Enter ID For User: ");
                client.useClient
                (
                    deleteClass
                    (
                        stoi(System::getInput())
                    )
                ); 
            }
            else if(userInput == "2")
            {
                System::println("Please Enter ID For Student: ");
                client.useClient
                (
                    deleteStudent
                    (
                        stoi(System::getInput())
                    )
                ); 
            }
            else if(userInput == "3")
            {
                System::println("Please Enter ID For Class: ");
                client.useClient
                (
                    deleteClass
                    (
                        stoi(System::getInput())
                    )
                ); 
            }
        }
        else
        {
            System::println("Application Closing...");
            return 0;
        }
        continue;
    }
    return 0;
}

string addClass(Class inputClass)
{
    return ("C-" + to_string(inputClass.getID()) + "-" + inputClass.getName() + "-" + inputClass.getDept() + "-" + to_string(inputClass.getRoomNumber()) + "-");
}
string getClass(int id)
{
    return ("C*" + to_string(id) + "*");
}
string deleteClass(int id)
{
    return ("C+" + to_string(id) + "+");
}
string addUser(User inputUser)
{
    return ("U-" + to_string(inputUser.getID()) + "-" + to_string(inputUser.getPassword()) + "-");
}
string getUser(int id)
{
    return ("U*" + to_string(id) + "*");
}
string deleteUser(int id)
{
    return ("U+" + to_string(id) + "+");
}
string addStudent(Student inputStudent)
{
    return ("S-" + to_string(inputStudent.getID()) + "-" + inputStudent.getFirstName() + "-" + inputStudent.getLastName() + "-" + to_string(inputStudent.getYear()) + "-");
}
string getStudent(int id)
{
    return ("S*" + to_string(id) + "*");
}
string deleteStudent(int id)
{
    return ("S+" + to_string(id) + "+");
}
void outputClassSelection()
{
    System::println("What Option You Like To Edit?...");
    System::println("1 -- User");
    System::println("2 -- Student");
    System::println("3 -- Class");
}
#endif // __CLIENT_MAIN_H__