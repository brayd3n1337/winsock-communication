

#ifndef SOCKETS_BROADCASTER_H
#define SOCKETS_BROADCASTER_H

#include <string>

class Broadcaster {
public:
    void Broadcast(const std::string& message) const;
    void BroadcastError(const std::string& message) const;
};


#endif //SOCKETS_BROADCASTER_H
