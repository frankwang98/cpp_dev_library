#include <iostream>
#include <string>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

bool udpMulticastClientSend(std::string multicast_group, int port, std::string message)
{
    int socket_id;
    socket_id = socket(AF_INET, SOCK_DGRAM, 0);

    /* 设置组播TTL（Time-To-Live） */ 
    int ttl = 1; // 默认情况下，数据包只能在本地网络传递
    if (setsockopt(socket_id, IPPROTO_IP, IP_MULTICAST_TTL, (void *)&ttl, sizeof(ttl)) < 0)
    {
        std::cerr << "Failed to set TTL." << std::endl;
        return -1;
    }

    /* 设置组播组信息 */ 
    struct sockaddr_in multicast_addr{};
    memset(&multicast_addr, 0, sizeof(multicast_addr));
    multicast_addr.sin_family = AF_INET;
    multicast_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, multicast_group.c_str(), &(multicast_addr.sin_addr)) <= 0)
    {
        std::cerr << "Invalid multicast group address." << std::endl;
        return -1;
    }

    // 发送数据
    if (sendto(socket_id, message.c_str(), message.length(), 0, (struct sockaddr *)&multicast_addr, sizeof(multicast_addr)) < 0)
    {
        std::cerr << "Failed to send data." << std::endl;
        return false;
    }

    return true;
}

int main()
{
    std::string MULTICAST_GROUP = "239.0.0.1"; // 组播地址
    int PORT = 8888;                           // 端口
    std::string message = "12345678901234567890";

    // 发送数据
    while (true)
    {
        bool sendStatus = udpMulticastClientSend(MULTICAST_GROUP, PORT, message);
        std::cout << "Send data: " << message << std::endl;
        sleep(1);
    }

    return 0;
}
