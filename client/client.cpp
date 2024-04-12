#include "client.h"
#include <iostream>
#include "thread"


void Client::SendMessage(const std::string &message, const SOCKET &clientSocket)
{

    bool messageSent = false;

    while (clientSocket != INVALID_SOCKET)
    {
        if (message.empty())
        {
            return;
        }

        if (!messageSent)
        {

            const int result = send(clientSocket, message.c_str(), int(message.size()), 0);

            if (result == SOCKET_ERROR)
            {
                std::cerr << "Failed to send message!" << '\n';
                return;
            }

            std::cout << "Sent message: " << message << '\n';

            messageSent = true;
        }
    }

    WSACleanup();
    closesocket(clientSocket);
}