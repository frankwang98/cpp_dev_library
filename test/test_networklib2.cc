#include "../src/networklib/networklib.hpp"
#include <iostream>

void UdpTest()
{
    /* UdpNet class instantiation */
    UdpNet udpNet;
    /* UDP Client init */
    int socket2 = udpNet.UdpClientInit();
    std::cout << "socket2: " << socket2 << std::endl;

    /* define buffer(message) and buffer's length  */
    unsigned char Buffer[1024];
    memset(Buffer, 0, sizeof(Buffer));
    unsigned int BufferLen = 0;

    std::string message = "Hello, server! I am a wicri's developer.";
    BufferLen = message.length();
    memcpy(Buffer, message.c_str(), BufferLen);

    /* send message to ip/port */
    while (true)
    {
        udpNet.SendMessage(socket2, "127.0.0.1", 8080, Buffer, BufferLen);
        std::cout << "SendMessage: " << Buffer << std::endl;
        sleep(1);
    }
}

void TcpTest()
{
    std::cout << "Start tcpclient..." << std::endl;
    TcpNet tcpNet;
    int socket2 = tcpNet.TcpClientInit("127.0.0.1", 8080);
    std::cout << "socket2: " << socket2 << std::endl;

    std::string message = "Hello, server! I am a wicri's developer.";

    while(true)
    {
        if (tcpNet.client_connect)
        {
            bool send_ok = tcpNet.SendMessage(message);
            std::cout << "SendMessage: " << message << " " << send_ok << std::endl;

            /* 是否需要接收服务端回复 */
            // std::string responseMessage;
            // tcpNet.ListenMessage(responseMessage);
            // std::cout << "Received message from server: " << responseMessage << std::endl;
            sleep(1);
        }
        else
        {
            int socket3 = tcpNet.TcpClientInit("127.0.0.1", 8080);
            std::cout << "Reconnect ing!!! client_connect: " << tcpNet.client_connect << std::endl;
            sleep(1);
        }
    }
}

int main(int argc, char** argv)
{
    // UdpTest();

    // TcpTest();

    return 0;
}