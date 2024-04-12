#include <stdexcept>
#include "winsock2.h"
#include "broadcaster.h"
#include "server.h"

struct ServerInfo
{

private:
    int port;
    std::string ip;
    bool tcp, ipv4, shutdownServer;

public:
    ServerInfo(const int &port, const std::string &ip, const bool &tcp, const bool &ipv4, const bool &shutdownServer)
    {
        this->port = port;
        this->ip = ip;
        this->tcp = tcp;
        this->ipv4 = ipv4;
        this->shutdownServer = shutdownServer;
    }


    int GetPort() const
    {
        return this->port;
    }

    std::string GetIp() const
    {
        return this->ip;
    }

    bool IsTCP() const
    {
        return this->tcp;
    }

    bool IsIPV4() const
    {
        return this->ipv4;
    }

    bool GetShutdownServer() const
    {
        return this->shutdownServer;
    }
};


void cleanup(const SOCKET &serverSocket)
{
    // close the server socket
    closesocket(serverSocket);


    // cleanup the Winsock library
    WSACleanup();
}


void InitializeWinsock(WSAData &wsaData)
{
    // initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        throw std::runtime_error("Error initializing Winsock: " + std::to_string(WSAGetLastError()));
    }
}

void BindSocket(const SOCKET &serverSocket, const sockaddr_in &serverAddress)
{
    // bind the server socket to the server address
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
    {
        throw std::runtime_error("Error binding socket: " + std::to_string(WSAGetLastError()));
    }
}

int main() {
    const int &port = 8080;
    const std::string &ip = "127.0.0.1";

    // contains info about the server (e.g. IP)
    // we aren't going to shut down server for now, but im going to implement a way to do it if we have no connections left.
    ServerInfo serverInfo(port, ip, true, true, false);

    const int &protocolFamily = serverInfo.IsIPV4() ? AF_INET : AF_INET6;
    const int &type = serverInfo.IsTCP() ? SOCK_STREAM : SOCK_DGRAM;

    // data structure that contains information about winsocks
    WSADATA wsaData;

    // broadcaster / logger
    Broadcaster broadcaster;

    // server object, helps us easily create server addresses and accept connections
    Server server;

    InitializeWinsock(wsaData);

    // create a server socket
    const SOCKET serverSocket = server.CreateServerSocket(protocolFamily, type, serverInfo.IsTCP());

    // if the server socket is invalid, print an error message and cleanup
    if (serverSocket == INVALID_SOCKET)
    {
        broadcaster.BroadcastError("Error creating socket: " + std::to_string(WSAGetLastError()));
        cleanup(serverSocket);
        return 1;
    }

    // at this point, the server socket is not invalid, so we can announce that the socket was created successfully
    broadcaster.Broadcast("Socket created successfully!");


    // create a sockaddr_in struct that contains information about the server
    const sockaddr_in &serverAddress = server.CreateServerAddress(short(protocolFamily), serverInfo.GetIp(), serverInfo.GetPort());


    BindSocket(serverSocket, serverAddress);



    while (true)
    {
        if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR)
        {
            cleanup(serverSocket);
            break;
        }

        // accept client socket
        sockaddr_in clientAddress{};

        // size of the client address
        int clientAddressSize = sizeof(clientAddress);

        const SOCKET clientSocket = server.AcceptClientConnection(serverSocket, clientAddress, clientAddressSize);

        struct hostent *host = gethostbyaddr((char*) &clientAddress.sin_addr, sizeof(clientAddress.sin_addr), AF_INET);

        // at this point, the client socket is not invalid so we can announce that a client has connected
        const char *clientIP = server.GetClientIP(clientAddress);

        // if the client socket is invalid, print an error message and break the loop
        if (clientSocket == INVALID_SOCKET)
        {
            broadcaster.BroadcastError("Error accepting client connection: " + std::to_string(WSAGetLastError()));
            cleanup(serverSocket);
            break;
        }


        if (host != nullptr)
        {
            const std::string &name = std::string(host->h_name);
            const std::string &address = std::string(inet_ntoa(*(struct in_addr*) host->h_addr_list[0]));

            broadcaster.BroadcastError(name + " connected from: " + std::string(clientIP) + " with info {" + name + ", " + address + "}");
        }


        // my current purpose for this socket communication is for my injectable client, the server is hosted on the users computer so when the client disconnects so will the server.
        // a scenario where we would NOT do this is for a VPS/Server where it needs to be always online for multiple users
        // each user will have their own instance of the socket communication hosted on their pc.
        server.ReadIncomingMessages(clientSocket, clientIP, broadcaster, clientAddress, serverInfo.GetShutdownServer(), serverSocket);
    }

    closesocket(serverSocket);
    WSACleanup();

    return 0;
}