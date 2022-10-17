/**
 * @file TCPClient.hpp
 * @author Mitchell M. Gresham
 * @brief Acts as the interface for the database, and connects with the server on port provided. 
 * @version 0.1
 * @date 2022-10-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __TCPCLIENT_H__
#define __TCPCLIENT_H__

// User-Defined Constants
#define LOCAL_HOST_IP "127.0.0.1"

// C++ Defined Included Files
#include <sstream>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "boost/algorithm/string.hpp"
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// User-Defined Included Files
#include "TCPSocket.hpp"
#include "Class.hpp"
#include "Student.hpp"
#include "User.hpp"
#include "System.hpp"

class TCPClient: TCPSocket
{
    public:
        TCPClient(int port);
        void useClient(string message);
    private:
        int serverPort;
        sockaddr_in getPotentialConnection(string serverIdentification);
        void clientConnect(int descriptor, sockaddr_in addressPort);
};

TCPClient::TCPClient(int port):TCPSocket()
{
    this->serverPort = port;
    clientConnect(this->getSocketDescriptor(), getPotentialConnection(LOCAL_HOST_IP));
}
void TCPClient::useClient(string message)
{
    try 
    {
        sendData(this->getSocketDescriptor(), message);

        sleep(1); // Wait is required or it's too quick for the server to be able to reply. 
        string recievedData = recieveData(this->getSocketDescriptor());

        if(recievedData[0] == 'R' && recievedData[2] == '=')
        {
            if (recievedData[1] == 'S')
            {
                // Splits the inputted string based on the "=" delimiters
                vector<string> splitResult;
                boost::split(splitResult, recievedData, boost::is_any_of("="));
                System::println
                (
                    Student
                    (
                        stoi(splitResult.at(1)),
                        splitResult.at(2),
                        splitResult.at(3),
                        stoi(splitResult.at(4))
                    ).toString()
                );
            }
            else if(recievedData[1] == 'U')
            {
                // Splits the inputted string based on the "=" delimiters
                vector<string> splitResult;
                boost::split(splitResult, recievedData, boost::is_any_of("="));
                System::println
                (
                    User
                    (
                        stoi(splitResult.at(1)),
                        stoi(splitResult.at(2))
                    ).toString()
                );
            }
            else if (recievedData[1] == 'C')
            {
                // Splits the inputted string based on the "=" delimiters
                vector<string> splitResult;
                boost::split(splitResult, recievedData, boost::is_any_of("="));
                System::println
                (
                    Class
                    (
                        stoi(splitResult.at(1)),
                        splitResult.at(2),
                        splitResult.at(3),
                        stoi(splitResult.at(4))
                    ).toString()
                );
            }
        }
        close(this->getSocketDescriptor());
    }
    catch(...)
    {
        close(this->getSocketDescriptor());
        throw runtime_error("Error Sending Message To Server");
    }
}
sockaddr_in TCPClient::getPotentialConnection(string serverIdentification)
{
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(this->serverPort);

    if (inet_pton(AF_INET, serverIdentification.c_str(), &serverAddress.sin_addr) > 0)
    {
        return serverAddress;
    }
	else
	{
		throw invalid_argument("Server Identification Is Unavialable"); 
	}
}
void TCPClient::clientConnect(int descriptor, sockaddr_in addressPort)
{
    if (connect(descriptor, (struct sockaddr*) &addressPort, sizeof(addressPort)) < 0)
    {
        throw runtime_error("Client Connection Failed");
    }
    else
    {
        System::println("Client Connection Sucessful");
    }
}

#endif // __TCPCLIENT_H__