package com.plaguecheat.client.guice;

import com.google.inject.AbstractModule;
import com.plaguecheat.client.connection.ServerConnector;
import com.plaguecheat.client.connection.ServerConnectorImpl;
import com.plaguecheat.client.message.MessageSender;
import com.plaguecheat.client.message.MessageSenderImpl;

public final class ClientGuiceModule extends AbstractModule {

    @Override
    protected void configure() {
        super.bind(ServerConnector.class).to(ServerConnectorImpl.class);
        super.bind(MessageSender.class).to(MessageSenderImpl.class);
    }
}