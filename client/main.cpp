#include <iostream>
#include "winsock2.h"
#include "client.h"
#include "broadcaster.h"

struct ServerInfo
{

private:
    int port;
    std::string ip;

public:
    ServerInfo(const int &port, const std::string &ip)
    {
        this->port = port;
        this->ip = ip;
    }


    int GetPort() const
    {
        return this->port;
    }

    std::string GetIp() const
    {
        return this->ip;
    }
};


int main() {
    WSADATA wsaData;
    const Broadcaster broadcaster;
    Client client;

    const int result = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (result != 0)
    {
        broadcaster.BroadcastError("Failed to initialize Winsock!");
        return 1;
    }


    // create a socket
    const SOCKET &clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (clientSocket == INVALID_SOCKET)
    {
        broadcaster.BroadcastError("Failed to create client socket!");
        return 1;
    }

    // server address
    const ServerInfo serverInfo(8080, "127.0.0.1");


    sockaddr_in serverAddress{};

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(serverInfo.GetIp().c_str());
    serverAddress.sin_port = htons(serverInfo.GetPort());

    const int connectionResult = connect(clientSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress));

    // connect to the server
    if (connectionResult == SOCKET_ERROR)
    {
        broadcaster.BroadcastError("Failed to connect to the server!");
        return 1;
    }


    broadcaster.Broadcast("Connected to the server!");

    client.SendMessage("Hello from C++ Client!", clientSocket);

    return 0;
}
