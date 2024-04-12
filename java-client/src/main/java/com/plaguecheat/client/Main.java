package com.plaguecheat.client;

import com.google.inject.Guice;
import com.google.inject.Injector;
import com.plaguecheat.client.connection.ServerConnector;
import com.plaguecheat.client.guice.ClientGuiceModule;
import com.plaguecheat.client.message.MessageSender;
import com.plaguecheat.client.message.MessageSenderImpl;

import java.net.Socket;
import java.util.logging.Level;
import java.util.logging.Logger;

public final class Main {
    private static final Logger LOGGER = Logger.getLogger(Main.class.getName());


    public static void main(final String[] args) {
        final Injector injector = Guice.createInjector(new ClientGuiceModule());

        final ServerConnector serverConnector = injector.getInstance(ServerConnector.class);

        final MessageSender messageSender = new MessageSenderImpl(serverConnector);

        messageSender.sendMessage("Heller heller heller!");

        Runtime.getRuntime().addShutdownHook(new Thread(() -> {
            final Socket socket = serverConnector.getSocket();

            LOGGER.log(Level.INFO, "Closing Client Socket");
            try
            {
                socket.close();
            }
            catch (final Exception exception)
            {
                LOGGER.log(Level.SEVERE, "Failed to Close Client Socket", exception);
            }
        }));
    }
}