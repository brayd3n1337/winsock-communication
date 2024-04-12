package com.plaguecheat.client.connection;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.net.SocketException;
import java.util.logging.Level;
import java.util.logging.Logger;

public final class ServerConnectorImpl implements ServerConnector {

    private Socket socket;

    private static final String HOST = "127.0.0.1";

    private static final int PORT = 8080;

    private static final Logger LOGGER = Logger.getLogger(ServerConnectorImpl.class.getName());

    public ServerConnectorImpl() {
        try {
            this.socket = new Socket(HOST, PORT);

            this.socket.setTcpNoDelay(true);
        } catch (final IOException exception) {
            LOGGER.log(Level.SEVERE, "Failed to connect to server", exception);
        }
    }

    @Override
    public Socket getSocket()
    {
        return this.socket;
    }

    @Override
    public OutputStream getOutputStream() {
        try {
            return this.socket.getOutputStream();
        } catch (final IOException exception) {
            LOGGER.log(Level.SEVERE, "Failed to get output stream", exception);
        }


        return null;
    }

    @Override
    public InputStream getInputStream() {
        try {
            return this.socket.getInputStream();
        } catch (final IOException exception) {
            LOGGER.log(Level.SEVERE, "Failed to get input stream", exception);
        }

        return null;
    }
}
