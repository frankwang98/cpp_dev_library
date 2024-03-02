#include <iostream>
#include <string>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

int udpMulticastServerRecv(std::string multicast_group, int port)
{
    int socket_id;
    socket_id = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in local_addr{};
    memset(&local_addr, 0, sizeof(local_addr));
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(port);
    local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(socket_id, (struct sockaddr *)&local_addr, sizeof(local_addr)) < 0)
    {
        std::cerr << "Failed to bind." << std::endl;
        return -1;
    }

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

    /* 加入组播组 */ 
    struct ip_mreq mreq{};
    mreq.imr_multiaddr.s_addr = inet_addr(multicast_group.c_str());
    mreq.imr_interface.s_addr = htonl(INADDR_ANY);
    if (setsockopt(socket_id, IPPROTO_IP, IP_ADD_MEMBERSHIP, (void *)&mreq, sizeof(mreq)) < 0)
    {
        std::cerr << "Failed to join multicast group." << std::endl;
        return -1;
    }

    return socket_id;
}

int main()
{
    std::string MULTICAST_GROUP = "239.0.0.1"; // 组播地址
    int PORT = 8888;                           // 端口
    int socket_id = udpMulticastServerRecv(MULTICAST_GROUP, PORT);
    std::cout << "Server started: " << socket_id << std::endl;
    std::cout << "Start Listen..." << std::endl;

    unsigned char buffer[999999];
    memset(buffer, 0, sizeof(buffer));
    struct sockaddr_in multicast_addr{};
    socklen_t addr_len = sizeof(struct sockaddr_in);
    std::string recvMessage;

    while (true)
    {
        int data_length = recvfrom(socket_id, buffer, sizeof(buffer), MSG_WAITALL, (struct sockaddr *)&multicast_addr, &addr_len);
        if (data_length < 0)
        {
            std::cerr << "Failed to receive data." << std::endl;
        }
        else
        {
            for (int i = 0; i < data_length; i++)
            {
                recvMessage = recvMessage + (char)buffer[i];
            }
            std::cout << "Received message: " << recvMessage << std::endl;
            std::cout << "Received message length: " << recvMessage.length() << std::endl;
        }
        
        recvMessage.clear();
    }

    return 0;
}
