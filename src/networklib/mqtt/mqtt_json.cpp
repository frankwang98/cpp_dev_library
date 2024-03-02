#include <iostream>
#include <cstring>
#include <unistd.h>
#include <mosquitto.h>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

const std::string MQTT_BROKER_ADDRESS = "10.10.8.9";  // Mosquitto broker 的地址
const int MQTT_BROKER_PORT = 1883;  // Mosquitto broker 的端口号

// Mosquitto库初始化
void mosquittoInit(struct mosquitto*& mosq) {
    mosquitto_lib_init();
    mosq = mosquitto_new("mosq_cpp_example", true, nullptr);
    if (!mosq) {
        std::cerr << "Error: Unable to initialize Mosquitto library." << std::endl;
        exit(EXIT_FAILURE);
    }
}

// 连接到Mosquitto broker
void mosquittoConnect(struct mosquitto* mosq) {
    int ret = mosquitto_connect(mosq, MQTT_BROKER_ADDRESS.c_str(), MQTT_BROKER_PORT, 60);
    if (ret != MOSQ_ERR_SUCCESS) {
        std::cerr << "Error: Unable to connect to Mosquitto broker. Return code: " << ret << std::endl;
        exit(EXIT_FAILURE);
    }
}

// 发布消息到指定主题
void mosquittoPublish(struct mosquitto* mosq, const std::string& topic, const std::string& message) {
    int ret = mosquitto_publish(mosq, nullptr, topic.c_str(), message.size(), message.c_str(), 0, false);
    if (ret != MOSQ_ERR_SUCCESS) {
        std::cerr << "Error: Unable to publish message. Return code: " << ret << std::endl;
    }
}

// 订阅指定主题
void mosquittoSubscribe(struct mosquitto* mosq, const std::string& topic) {
    int ret = mosquitto_subscribe(mosq, nullptr, topic.c_str(), 0);
    if (ret != MOSQ_ERR_SUCCESS) {
        std::cerr << "Error: Unable to subscribe to topic. Return code: " << ret << std::endl;
    }
}

// 回调函数处理接收到的消息
void onMessage(struct mosquitto* mosq, void* userdata, const struct mosquitto_message* message) {
    std::string receivedMessage((char*)message->payload, message->payloadlen); // char* -> string
    std::cout << "Received message on topic: " << message->topic << ", Message: " << receivedMessage << std::endl;

    // 解析 JSON 字符串
    boost::property_tree::ptree parsedPt;
    std::istringstream iss(receivedMessage);
    boost::property_tree::read_json(iss, parsedPt);

    // 从解析后的 property_tree 中获取数据
    std::string name = parsedPt.get<std::string>("name");
    int age = parsedPt.get<int>("age");
    std::string city = parsedPt.get<std::string>("city");
    // 从解析后的 property_tree 中获取数组
    std::vector<int> numbers;
    for (const auto& entry : parsedPt.get_child("numbers")) {
        int number = entry.second.get_value<int>();
        numbers.push_back(number);
    }

    std::cout << "Parsed JSON:\n"
              << "Name: " << name << "\n"
              << "Age: " << age << "\n"
              << "City: " << city << std::endl;
    std::cout << "Parsed JSON Array: " << numbers.size() << std::endl;
}

int main() {
    struct mosquitto* mosq = nullptr;

    mosquittoInit(mosq);
    mosquittoConnect(mosq);

    // 构建 JSON 数据
    boost::property_tree::ptree pt;
    pt.put("name", "John");
    pt.put("age", 30);
    pt.put("city", "New York");
    // 添加数组
    for (int i = 0; i < 3; i++)
    {
        pt.put("numbers." + std::to_string(i), i+1);
    }
    // pt.put("numbers.0", 1);
    // pt.put("numbers.1", 2);
    // pt.put("numbers.2", 3);

    // 将 property_tree 转换为 JSON 字符串
    std::ostringstream oss;
    boost::property_tree::write_json(oss, pt);
    std::string jsonString = oss.str();

    std::cout << "Generated JSON:\n" << jsonString << "\n\n";

    // 订阅主题
    mosquittoSubscribe(mosq, "test");

    // 发布主题
    while (true) {
        mosquittoPublish(mosq, "test", jsonString);
        std::cout << "Published message." << std::endl;
        usleep(1000 * 1000);
        break; // 收发一次示例，实际将收发分两个函数
    }
    
    // 设置消息接收回调函数
    mosquitto_message_callback_set(mosq, onMessage);

    // 循环处理消息
    mosquitto_loop_forever(mosq, -1, 1);

    // 断开连接并清理资源
    mosquitto_disconnect(mosq);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    return 0;
}
