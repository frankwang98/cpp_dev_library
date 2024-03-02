#include "../src/networklib/networklib.hpp"
#include <iostream>

void UdpTest()
{
    /* UdpNet class instantiation */
    UdpNet udpNet;
    /* UDP Server init */
    int socket1 = udpNet.UdpServerInit(8080);
    std::cout << "socket1: " << socket1 << std::endl;

    /* define buffer and receive message */
    unsigned char buffer_[1024];
    std::string recv_buffer;
    while(true)
    {
        int length = udpNet.ListenMessage(socket1, buffer_);
        if (length > 0)
        {
            for (int i = 0; i < length; i++)
            {
                recv_buffer = recv_buffer + (char)buffer_[i];
            }
        }
        std::cout << "Recv_ip: " << udpNet.recv_ip << " Server recv_buffer: " << recv_buffer << std::endl;
        recv_buffer = "";
    }
}

void TcpTest()
{
    std::cout << "Start tcpserver..." << std::endl;
    TcpNet tcpNet;
    int socket1 = tcpNet.TcpServerInit(8080);
    std::cout << "socket1: " << socket1 << std::endl;

    std::string receivedMessage;
    while(true)
    {
        receivedMessage = "";
        int length = tcpNet.ListenMessage(receivedMessage);
        if (length > 0)
        {
            std::cout << "TcpServer received message: " << receivedMessage << std::endl;

            /* 是否需要发送 */
            // tcpNet.SendMessage("Hello, client!");
        }
        else
        {
            std::cout << "TcpServer received nothing!" << std::endl;
            tcpNet.ReConnect();
        }

        sleep(1);
    }
}

void pingValue()
{
    std::string ipAddress = "10.10.8.40";
    int pingTime = getPingTime(ipAddress);
    std::cout << "Ping time: " << pingTime << " ms" << std::endl;
}

int main(int argc, char** argv)
{
    // UdpTest();

    // TcpTest();

    pingValue();

    return 0;
}