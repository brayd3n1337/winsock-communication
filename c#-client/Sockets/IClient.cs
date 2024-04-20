namespace Sockets;

public interface IClient
{
    void SendMessage(string message);

    void ReceiveMessages();
}