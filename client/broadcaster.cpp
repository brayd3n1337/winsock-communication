#include "broadcaster.h"
#include <iostream>

void Broadcaster::Broadcast(const std::string& message) const {
    std::cout << message << '\n';
}

void Broadcaster::BroadcastError(const std::string& message) const {
    std::cerr << message << '\n';
}