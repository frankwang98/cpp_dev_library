// networklib.cc
#include "networklib.hpp"

UdpNet::UdpNet() {}

UdpNet::~UdpNet()
{
    close(socket_id);
}

int UdpNet::UdpServerInit(const int port)
{
    sockaddr_in addr;
    int socket_id;
    socket_id = socket(AF_INET, SOCK_DGRAM, 0);
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);
    bind(socket_id, (struct sockaddr *)&addr, sizeof(addr)); // Server need bind

    /* 设置接收超时 */
    timeval tv = {0, 200 * 1000}; // configurable，当前配置为200ms，第一个参数为s，第二个参数为us
    if (0 != setsockopt(socket_id, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv, sizeof(timeval)))
    {
        printf("setsockopt timeval error: %s\n", strerror(errno));
    }

    /* 设置端口复用 */
    int reuse = 1; // allows multiple sockets to be bound to the same address and port
    if (0 != setsockopt(socket_id, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)))
    {
        printf("setsockopt reuse error: %s\n", strerror(errno));
    }

    return socket_id;
}

int UdpNet::UdpClientInit()
{
    int socket_id;
    socket_id = socket(AF_INET, SOCK_DGRAM, 0);

    return socket_id;
}

int UdpNet::ListenMessage(const int socket_id, unsigned char *data)
{
    char source_ip[INET_ADDRSTRLEN];
    int data_length;
    socklen_t sockadd_length;
    sockadd_length = sizeof(sockaddr_in);
    data_length = recvfrom(socket_id, data, 300000, MSG_WAITALL, (struct sockaddr *)&source_addr_, &sockadd_length);

    /* inet_ntoa和inet_ntop都是将ip从二进制转为字符串，由于inet_ntoa会覆盖静态缓冲区，因此建议在多线程或异步环境中使用inet_ntop */
    recv_ip = inet_ntop(AF_INET, &source_addr_.sin_addr, source_ip, sizeof(source_ip));

    return data_length;
}

bool UdpNet::SendMessage(const int socket_id, const char *ip, const int port, unsigned char *data, unsigned int data_len)
{
    sockaddr_in addr; // socket struct
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;            // 设置协议族
    addr.sin_addr.s_addr = inet_addr(ip); // 接收端 ip
    addr.sin_port = htons(port);          // 接收端 port

    /* Check the return value to determine whether the transmission was successful */
    if (-1 == sendto(socket_id, data, data_len, 0, (struct sockaddr *)&addr, sizeof(addr)))
    {
        std::cout << "SendMessage strerror: " << strerror(errno) << std::endl;
        return false;
    }
    return true;
}

/*-------------------------------------------------------------------*/

TcpNet::TcpNet() : serverSocket(0), clientSocket(0) {}

TcpNet::~TcpNet()
{
    close(serverSocket);
    close(clientSocket);
}

int TcpNet::TcpServerInit(int port)
{
    /* server socket */
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Failed to create socket" << std::endl;
    }

    /* address */
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);

    /* bind to address */
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Failed to bind socket" << std::endl;
    }

    /* start listen */
    if (listen(serverSocket, 10) < 0) {
        std::cerr << "Failed to listen" << std::endl;
    }

    int addrLength = sizeof(struct sockaddr_in);
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, (socklen_t*)&addrLength);
    if (clientSocket < 0) {
        std::cerr << "Failed to accept connection" << std::endl;
    }

    return serverSocket;
}

void TcpNet::ReConnect()
{
    int addrLength = sizeof(struct sockaddr_in);
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, (socklen_t*)&addrLength);
    if (clientSocket < 0) {
        std::cerr << "Failed to accept connection" << std::endl;
    }
}

int TcpNet::TcpClientInit(const std::string& ip, int port)
{
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Failed to create socket" << std::endl;
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    int retry_num = 0;
    const int MAX_RETRY_NUM = 5;

    /* 将IP地址从文本转换为网络字节序 */ 
    if (inet_pton(AF_INET, ip.c_str(), &(serverAddress.sin_addr)) <= 0) {
        std::cerr << "Invalid address/Address not supported" << std::endl;;
    }

    /* connect to server */
    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "TcpClient connection failed" << std::endl;
        client_connect = false;
    }
    else
    {
        client_connect = true;
    }

    return clientSocket;
}

int TcpNet::ListenMessage(std::string& message)
{
    char buffer[1024] = {0};
    int data_len = read(clientSocket, buffer, sizeof(buffer));
    if (data_len < 0) {
        std::cerr << "Failed to receive message" << std::endl;
    }
    message = buffer;

    return data_len;
}

bool TcpNet::SendMessage(const std::string& message)
{
    if (send(clientSocket, message.c_str(), message.size(), 0) < 0) {
        std::cerr << "Failed to send message" << std::endl;
        return false;
    }

    return true;
}

/*-------------------------------------------------------------------*/

int getPingTime2(const std::string& ip)
{
    std::ostringstream commandStream;
    commandStream << "ping -c 1 " << ip << " > ping_tmp.txt";
    std::system(commandStream.str().c_str());

    std::ifstream file("ping_tmp.txt");
    if (!file.good()) {
        std::cerr << "Failed to open ping result file" << std::endl;
        return 0;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.find("time=") != std::string::npos) {
            int startIndex = line.find("time=") + 5;
            int endIndex = line.find(" ms", startIndex);
            return std::stoi(line.substr(startIndex, endIndex - startIndex));
        } else {
            std::cerr << "Failed to find delay time in ping result" << std::endl;
            return -1;
        }
    }
    
    return 0;
}

int getPingTime(const std::string& ipAddress)
{
    std::string command = "ping -c 1 " + ipAddress;
    std::array<char, 128> buffer;
    std::ostringstream result;

    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) {
        throw std::runtime_error("Failed to execute the ping command.");
    }

    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result << buffer.data();
    }

    pclose(pipe);

    std::string pingOutput = result.str();

    // 使用正则表达式匹配延迟信息
    std::regex pattern("time=(\\d+)");
    std::smatch match;
    if (std::regex_search(pingOutput, match, pattern)) {
        std::string delayStr = match[1].str();
        int delay = std::stoi(delayStr);
        return delay;
    } else {
        // throw std::runtime_error("Failed to get the ping delay.");
        return -1;
    }
}
