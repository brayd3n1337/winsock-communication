package com.plaguecheat.client.connection;

import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;

public interface ServerConnector {
    Socket getSocket();

    OutputStream getOutputStream();

    InputStream getInputStream();
}
