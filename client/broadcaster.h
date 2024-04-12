

#ifndef CLIENTSOCKET_BROADCASTER_H
#define CLIENTSOCKET_BROADCASTER_H


#include <string>

class Broadcaster {
public:
    void Broadcast(const std::string &message) const;
    void BroadcastError(const std::string &message) const;
};


#endif //CLIENTSOCKET_BROADCASTER_H
