#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

int main() {
    // 打开串口设备文件
    int fd = open("/dev/ttyUART_485_422_A", O_RDWR | O_NOCTTY);

    if (fd == -1) {
        std::cerr << "无法打开串口设备文件" << std::endl;
        return 1;
    }

    // 配置串口参数
    struct termios serialPortSettings;
    tcgetattr(fd, &serialPortSettings);
    cfsetispeed(&serialPortSettings, B9600);  // 设置输入波特率为9600
    cfsetospeed(&serialPortSettings, B9600);  // 设置输出波特率为9600
    serialPortSettings.c_cflag &= ~PARENB;    // 禁用奇偶校验位
    serialPortSettings.c_cflag &= ~CSTOPB;    // 使用1位停止位
    serialPortSettings.c_cflag &= ~CSIZE;     // 清除数据位设置
    serialPortSettings.c_cflag |= CS8;        // 设置数据位为8位
    tcsetattr(fd, TCSANOW, &serialPortSettings);

    // 读取串口数据
    char buffer[255];
    ssize_t bytesRead = read(fd, buffer, sizeof(buffer));

    if (bytesRead == -1) {
        std::cerr << "读取串口数据时发生错误" << std::endl;
        close(fd);
        return 1;
    }

    // 输出读取到的数据
    std::cout << "读取到的数据：";
    for (int i = 0; i < bytesRead; i++) {
        std::cout << buffer[i];
    }
    std::cout << std::endl;

    // 关闭串口设备文件
    close(fd);

    return 0;
}

