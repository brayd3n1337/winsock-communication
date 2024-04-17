package com.plaguecheat.client.message;

public interface MessageSender {
    void sendMessage(final String message);

    void shutdown();
}
