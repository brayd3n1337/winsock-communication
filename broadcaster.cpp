#include "broadcaster.h"
#include <iostream>

void Broadcaster::Broadcast(const std::string& message)
{
    std::cout << message << '\n';
}

void Broadcaster::BroadcastError(const std::string& message)
{
    std::cerr << message << '\n';
}
