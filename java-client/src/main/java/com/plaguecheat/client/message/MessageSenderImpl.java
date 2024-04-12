package com.plaguecheat.client.message;

import com.google.inject.Inject;
import com.plaguecheat.client.connection.ServerConnector;

import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.concurrent.Executor;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.logging.Level;
import java.util.logging.Logger;

public final class MessageSenderImpl implements MessageSender {

    private final ServerConnector serverConnector;

    private static final Logger LOGGER = Logger.getLogger(MessageSenderImpl.class.getName());

    private static final ExecutorService EXECUTOR = Executors.newSingleThreadExecutor();

    @Inject
    public MessageSenderImpl(final ServerConnector serverConnector) {
        this.serverConnector = serverConnector;
    }


    @Override
    public void sendMessage(final String message) {
        // asynchronous message sending so the main thread is not blocked and the application is responsive and jvm doesn't terminate.
        // could do a empty while loop to keep it running but that would look ugly
        EXECUTOR.execute(() -> {

            // get socket from serverConnector
            final Socket socket = this.serverConnector.getSocket();

            // if socket is null, return
            if (socket == null || socket.isClosed()) {
                return;
            }

            // log message
            LOGGER.log(Level.INFO, "Sending Message: " + message);

            // send the message
            try {
                final ObjectOutputStream objectOutputStream = new ObjectOutputStream(this.serverConnector.getOutputStream());

                objectOutputStream.writeObject(message);
                objectOutputStream.flush();
            } catch (final Exception exception) {
                LOGGER.log(Level.SEVERE, "Failed to send message", exception);
            }
        });
    }
}
