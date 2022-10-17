#ifndef __CLIENT_MAIN_H__
#define __CLIENT_MAIN_H__

#include "System.hpp"
#include "TCPSocket.hpp"
#include "TCPServer.hpp"

using namespace std;


int main()
{

    // Binds Server To Inputted Port
    System::println("Please Enter Port Number To Bind Server To: ");
    TCPServer server(stoi(
        System::getInput()
    ));

    // Start Server
    server.startServer();

    return 0;
}
#endif // __CLIENT_MAIN_H__

