

#ifndef CLIENTSOCKET_CLIENT_H
#define CLIENTSOCKET_CLIENT_H

#include "string"
#include "winsock2.h"


class Client {
public:
    void SendMessage(const std::string &message, const SOCKET &clientSocket);
};


#endif //CLIENTSOCKET_CLIENT_H
