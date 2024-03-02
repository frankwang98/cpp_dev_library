// networklib.hpp
#ifndef NETWORKLIB_HPP
#define NETWORKLIB_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <assert.h>
#include <stdexcept>
#include <array>
#include <regex>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
// #include <boost/asio.hpp>

/**
 * @brief UDP通信类
*/
class UdpNet {
public:
    /**
     * @brief 构造函数
    */
    UdpNet();
    
    /**
     * @brief 析构函数
    */
    ~UdpNet();

    /**
     * @brief UDP服务端初始化
     * @param port 监听端口
     * @return socket_id
    */
    int UdpServerInit(const int port);

    /**
     * @brief UDP客户端初始化
     * @return socket_id
    */
    int UdpClientInit();

    /**
     * @brief 消息监听函数
     * @param socket_id socket描述符
     * @param data 数据
     * @return data_len
    */
    int ListenMessage(const int socket_id, unsigned char *data);

    /**
     * @brief 消息发送函数
     * @param socket_id socket描述符
     * @param ip ip地址
     * @param port 端口
     * @param data 数据
     * @param data_len 数据长度
    */
    bool SendMessage(const int socket_id, const char *ip, const int port, unsigned char *data, unsigned int data_len);

public:
    std::string recv_ip; // Server received ip

private:
    int socket_id;
    sockaddr_in source_addr_;
};

/*-------------------------------------------------------------------*/

/**
 * @brief TCP通信类
*/
class TcpNet
{
public:
    /**
     * @brief 构造函数
    */
    TcpNet();

    /**
     * @brief 析构函数
    */
    ~TcpNet();

    /**
     * @brief TCP服务端接收
     * @param port 端口
     * @return socket_id
    */
    int TcpServerInit(int port);

    /**
     * @brief TCP重连函数
    */
    void ReConnect();

    /**
     * @brief TCP客户端连接
     * @param ip
     * @param port
     * @return socket_id
    */
    int TcpClientInit(const std::string& ip, int port);

    /**
     * @brief 消息接收函数
     * @param message
     * @return data_len
    */
    int ListenMessage(std::string& message);

    /**
     * @brief 消息发送函数
     * @param message
     * @return send_ok
    */
    bool SendMessage(const std::string& message);

public:
    bool client_connect;

private:
    int serverSocket;
    int clientSocket;
    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;
};

/*-------------------------------------------------------------------*/

/**
 * @brief 获取ping延迟值
 * @return ping_time
*/
int getPingTime2(const std::string& ip);

/**
 * @brief 获取ping延迟值-正则表达式
 * 更安全，建议放在单独线程
 * @param ipAddress 
 * @return int 
 */
int getPingTime(const std::string& ipAddress);

#endif