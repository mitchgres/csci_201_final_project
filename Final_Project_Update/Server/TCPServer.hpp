/**
 * @file TCPServer.hpp
 * @author Mitchell M. Gresham
 * @brief Server object which uses a TCP connection on IPv4 to connect with a client, and provides an interface by which the client
 *        can interact with the database. 
 * @version 0.1
 * @date 2022-10-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__

// C++ Defined Included Files
#include <sstream>
#include <iostream>
#include <regex>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include "boost/algorithm/string.hpp"
#include <arpa/inet.h>

// User Defined Included Files
#include "ClassDatabase.hpp"
#include "UserDatabase.hpp"
#include "StudentDatabase.hpp"
#include "System.hpp"
#include "TCPSocket.hpp"
#include "User.hpp"

#define MAX_AMOUNT_IN_QUEUE 5
#define MESSAGE_BUFFER_SIZE 64

using namespace std;

class TCPServer : TCPSocket
{
public:
    TCPServer(int port) : TCPSocket()
    {
        // Sets family to IPv4.
        // Sets address to whatever that local machine uses.
        this->setAddressPortFamily(AF_INET);
        this->setAddressPortPort(port);
        this->setAddressPortAddress(INADDR_ANY);

        // Bind Server
        bindServer(this->getSocketDescriptor(), this->getAddressPort());

        // Make Server Listen
        listenServer(this->getSocketDescriptor(), MAX_AMOUNT_IN_QUEUE);
    }
    void startServer()
    {
        while (true)
        {
            // Accepts new connection and then takes the data given to the server from the client.
            int clientSocket = acceptServerConnections(this->getSocketDescriptor());
            string receivedData = recieveData(clientSocket);

            // Output Information Recieved From Client
            System::println("Client Input: " + receivedData);

            // Attempt Communication With Client
            try
            {
                if (receivedData[0] == 'C')
                {
                    if (receivedData[1] == '-')
                    {
                        // Request To Create New Class

                        // Splits the inputted string based on the "-" delimiters
                        vector<string> splitResult;
                        boost::split(splitResult, receivedData, boost::is_any_of("-"));
                        ClassDatabase::addClass(
                            Class(
                                stoi(splitResult.at(1)),
                                splitResult.at(2),
                                splitResult.at(3),
                                stoi(splitResult.at(4))));
                    }
                    else if(receivedData[1] == '+')
                    {
                        // Delete Class
                        vector<string> splitResult;
                        boost::split(splitResult, receivedData, boost::is_any_of("+"));
                        ClassDatabase::removeClass(stoi(splitResult.at(1)));
                    }
                    else
                    {
                        // Query Class
                        vector<string> splitResult;
                        boost::split(splitResult, receivedData, boost::is_any_of("*"));
                        Class returnedClass = ClassDatabase::getClass(
                            stoi(splitResult.at(1)));
                        sendData(clientSocket, ("RC=" + to_string(returnedClass.getID()) + "=" + returnedClass.getName() + "=" + returnedClass.getDept() + "=" + to_string(returnedClass.getRoomNumber()) + "="));
                    }
                }
                else if (receivedData[0] == 'S')
                {
                    if (receivedData[1] == '-')
                    {
                        // Request To Create New Class

                        // Splits the inputted string based on the "-" delimiters
                        vector<string> splitResult;
                        boost::split(splitResult, receivedData, boost::is_any_of("-"));
                        StudentDatabase::addStudent(
                            Student(
                                stoi(splitResult.at(1)),
                                splitResult.at(2),
                                splitResult.at(3),
                                stoi(splitResult.at(4))));
                    }
                    else if(receivedData[1] == '+')
                    {
                        // Delete Class
                        vector<string> splitResult;
                        boost::split(splitResult, receivedData, boost::is_any_of("+"));
                        StudentDatabase::removeStudent(stoi(splitResult.at(1)));
                    }
                    else
                    {
                        // Query Class
                        vector<string> splitResult;
                        boost::split(splitResult, receivedData, boost::is_any_of("*"));
                        Student returnedStudent = StudentDatabase::getStudent(
                            stoi(splitResult.at(1)));
                        sendData(clientSocket, ("RS=" + to_string(returnedStudent.getID()) + "=" + returnedStudent.getFirstName() + "=" + returnedStudent.getLastName() + "=" + to_string(returnedStudent.getYear()) + "="));
                    }
                }
                else if (receivedData[0] == 'U')
                {
                    if (receivedData[1] == '-')
                    {
                        // Request To Create New Class

                        // Splits the inputted string based on the "-" delimiters
                        vector<string> splitResult;
                        boost::split(splitResult, receivedData, boost::is_any_of("-"));
                        UserDatabase::addUser
                        (
                            User
                            (
                                stoi(splitResult.at(1)),
                                stoi(splitResult.at(2)) 
                            )
                        );
                    }
                    else if(receivedData[1] == '+')
                    {
                        // Delete Class
                        vector<string> splitResult;
                        boost::split(splitResult, receivedData, boost::is_any_of("+"));
                        UserDatabase::removeUser(stoi(splitResult.at(1)));
                    }
                    else
                    {
                        // Query Class
                        vector<string> splitResult;
                        boost::split(splitResult, receivedData, boost::is_any_of("*"));
                        User returnedUser = UserDatabase::getUser(stoi(splitResult.at(1)));

                        sendData(clientSocket, ("RU=" + to_string(returnedUser.getID()) + "=" + to_string(returnedUser.getPassword()) + "="));
                    }
                }
                else
                {
                    throw runtime_error("Input Not Formatted Correctly");
                }
                // Closes connection with client
                close(clientSocket);
            }
            catch (runtime_error)
            {
                sendData(clientSocket, "Error Incorrect Input");
                close(clientSocket);
            }
        }
    }

private:
    /// @brief Binds the server to itself and prepares itself for connection from client. Upon sucess message returned else runtime_error is thrown.
    /// @param socketDescriptor
    /// @param addressPort
    void bindServer(int socketDescriptor, sockaddr_in addressPort)
    {
        if (bind(socketDescriptor, (struct sockaddr *)&addressPort, sizeof(addressPort)) == -1)
        {
            throw runtime_error("Server Socket Cannot Be Binded");
        }
        else
        {
            System::println("Sucessful Server Bind");
        }
    }
    /// @brief Forces the server to listen for connections.
    /// @param socketDescriptor
    /// @param queueLimit
    void listenServer(int socketDescriptor, int queueLimit)
    {
        if (listen(socketDescriptor, queueLimit) == -1)
        {
            throw runtime_error("Server Socket Cannot Be Forced To Listen");
        }
        else
        {
            System::println("Sucessful Server Forced To Listen");
        }
    }
    /// @brief Accepts the connections that are found, and also prints to console the client that has connected.
    /// @param serverSocket
    /// @return clientSocket
    int acceptServerConnections(int serverSocket)
    {
        struct sockaddr_in clientAddress;
        socklen_t clientAddressLength = sizeof(clientAddress);
        int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientAddressLength);

        if (clientSocket < 0)
        {
            throw runtime_error("Server Was Unable To Accept Client");
        }
        else
        {
            char clientName[INET_ADDRSTRLEN];

            // Updates console that new conenction has occured and retuns client information before data is taken.
            System::println("Sucessful Connection Has Occured With Client & Server");
            System::print("Client: ");

            inet_ntop(AF_INET, &clientAddress.sin_addr.s_addr, clientName, sizeof(clientName));
            System::println(clientName);
            return clientSocket;
        }
    }
};
#endif // __TCPSERVER_H__