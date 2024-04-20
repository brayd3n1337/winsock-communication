using System.Net.Sockets;
using System.Text;

namespace Sockets;

public sealed class Client : IClient
{

    private readonly Socket _socket;

    public Client(Socket socket)
    {
        _socket = socket;
    }
    
    public void SendMessage(string message)
    {
        
        Console.WriteLine("Sending message: " + message + " to server.");
        
        NetworkStream networkStream = new NetworkStream(_socket);

        bool sentMessage = false;
        
        // while socket is connected
        while (_socket.Connected)
        {
            if (!sentMessage)
            {
                using (StreamWriter writer = new StreamWriter(networkStream, Encoding.UTF8, 1024, true))
                {
                    writer.WriteLine(message);
                    writer.Flush();
                }
                
                sentMessage = true;
            }
        }
    }

    
    public void ReceiveMessages()
    {
    }

}