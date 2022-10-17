/**
 * @file TCPSocket.hpp
 * @author Mitchell M. Gresham (mgresham4@ivytech.edu)
 * @brief File has decloration of the TCPSocket class, and the implementation further down into the file. 
 * @version 0.1
 * @date 2022-10-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __TCPSOCKET_H__
#define __TCPSOCKET_H__

// Preprocessor Constants
// Maximum Size of Message Can Be 32-Bytes.
#define MESSAGE_BUFFER 32

// C++ Defined Included Files
#include <sstream>
#include <iostream>
#include <regex>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// User Defined Included Files
#include "System.hpp"

class TCPSocket
{
    public:
        TCPSocket()
        {
            // Default Socket
            /*
                - The Default Socket used in application is an IPv4 domain that uses a stream of 
                  data across the TCP protocol to establish a connection. 
            */
            this->socketDescriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
            this->domain = AF_INET;
            this->type = SOCK_STREAM;
            this->protocol = IPPROTO_TCP;
        }
        /// @brief Accessor method used to get the socket descriptor returned when the Socket object was created.
        /// @return socketDescriptor
        int getSocketDescriptor()
        {
            return this->socketDescriptor;
        }
        /// @brief Accessor method used to get the domain that is used by the socket that was set when the Socket object was created. 
        /// @return domain
        int getDomain()
        {
            return this->type;
        }
        /// @brief Accessor method used to get the type that is used by the socket that was set when the Socket object was created.
        /// @return type
        int getType()
        {
            return this->type;
        }
        /// @brief Accessor method used to get the protocol that is used by the socket that was set when the Socket object was created.
        /// @return protocol
        int getProtocol()
        {
            return this->protocol;
        }
        /// @brief Accessor method used to get the address port that is declared as a member-level variables in the Socket object. 
        /// @return addressPort
        sockaddr_in getAddressPort()
        {
            return this->addressPort;
        }
        /// @brief Set the family used by the address port.
        /// @param family 
        void setAddressPortFamily(int family)
        {
            this->addressPort.sin_family = family;
        }
        /// @brief Set the port of the address port.
        /// @param port 
        void setAddressPortPort(int port)
        {
            this->addressPort.sin_port = htons(port);
        }
        /// @brief set the address of the address port.
        /// @param address 
        void setAddressPortAddress(int address)
        {
            this->addressPort.sin_addr.s_addr = htonl(address);
        }
        /// @brief Method which returns a string representation of the current object. 
        /// @return String Representation of Socket Object.
        string toString()
        {
            ostringstream stringOutput;
            stringOutput << "Socket Descriptor: " << getSocketDescriptor() << endl;
            stringOutput << "Domain: " << getDomain() << endl;
            stringOutput << "Type: " << getType() << endl;
            stringOutput << "Protocol: " << getProtocol() << endl;
            return stringOutput.str();
        }
        void sendData(int clientSocket, string message)
		  {
		  		send(clientSocket, message.c_str(), message.length(), 0);
				// Prompts that message has been sent. 
				System::println("Message Sent");
		  }
        string recieveData(int clientSocket)
        {
            char messageBuffer[MESSAGE_BUFFER];

            if(read(clientSocket, messageBuffer, MESSAGE_BUFFER) > 0)
            {
                System::println("Sucessfully Reading Data...");
            }
            else
            {
                System::println("No Data Recived...");
            }

            return System::ctos(messageBuffer, MESSAGE_BUFFER);
        }
    private:
        // Member Variables
        struct sockaddr_in addressPort;
        int socketDescriptor;
        int domain;
        int type;
        int protocol;
};

#endif // __TCPSOCKET_H__