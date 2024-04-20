// See https://aka.ms/new-console-template for more information

using System.Net.Sockets;
using System.Text;

namespace Sockets
{

    class Program
    {
        static void Main()
        {
            // Create a socket and connect to the server
            var socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            var client = new Client(socket);

            socket.Connect("127.0.0.1", 8080);
            
            while (socket.Connected)
            {
                NetworkStream networkStream = new NetworkStream(socket);

                byte[] buffer = new byte[1024];
                int bytesRead = networkStream.Read(buffer, 0, buffer.Length);

                if (bytesRead == 0)
                {
                    break;
                }

                string message = Encoding.UTF8.GetString(buffer, 0, bytesRead);

                Console.WriteLine("Received message: " + message);   

                client.SendMessage("Hello Server, from C# Client");

                networkStream.Close();
            }
        }
    }

}