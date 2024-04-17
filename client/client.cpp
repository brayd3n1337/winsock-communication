#include "client.h"
#include <iostream>


void Client::SendMessage(const std::string &message, const SOCKET &clientSocket)
{

    bool messageSent = false;

    while (clientSocket != INVALID_SOCKET)
    {
        if (message.empty())
        {
            break;
        }

        if (!messageSent)
        {
            const int result = send(clientSocket, message.c_str(), int(message.size()), 0);

            if (result == SOCKET_ERROR)
            {
                std::cerr << "Failed to send message!" << '\n';
                break;
            }

            std::cout << "Sent message: " << message << '\n';

            messageSent = true;
        }
    }

    // cleanup when loop breaks/ends
    // loop ends/breaks when the client disconnects or server shutdowns.
    closesocket(clientSocket);
    WSACleanup();
}