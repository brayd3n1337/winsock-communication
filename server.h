#ifndef SOCKETS_SERVER_H
#define SOCKETS_SERVER_H

#include "winsock2.h"
#include "string"
#include "broadcaster.h"

class Server {
public:
    /**
     * Accepts a client connection
     * @param serverSocket hmm i wonder what this is
     * @param client the clients socket information
     * @param clientAddressSize the size of the clients address
     * @return the client socket if accepted if else invalid socket return invalid socket
     */
    SOCKET AcceptClientConnection(const SOCKET &serverSocket, sockaddr_in &client, int &clientAddressSize);

    /**
     * Gets the client's ip address
     * @param client the client
     * @return the client ip
     */
    char* GetClientIP(const sockaddr_in &client);

    /**
     * Creates a server address
     * @param protocolFamily the protocol family
     * @param ipAddress the ip address of the server
     * @param port the port of the server
     * @return the server address
     */
    sockaddr_in CreateServerAddress(const short &protocolFamily, const std::string &ipAddress, const int &port);

    /**
     * Creates a server socket
     * @param protocolFamily the protocol family
     * @param type the type of socket
     * @param TCP if the socket is TCP
     * @return the server socket
     */
    SOCKET CreateServerSocket(const int &protocolFamily, const int &type, const bool &TCP);

    /**
     * Reads incoming messages from the client
     * @param clientSocket hmm i wonder what this is
     * @param clientIp the clients ip address
     * @param broadcaster the broadcaster
     * @param clientAddress  the clients address
     * @param closeServer whether to close the server
     * @param serverSocket the server socket
     */
    void ReadIncomingMessages(const SOCKET &clientSocket, const char *clientIp, Broadcaster &broadcaster, const sockaddr_in &clientAddress, const bool &closeServer, const SOCKET &serverSocket);
};


#endif //SOCKETS_SERVER_H
