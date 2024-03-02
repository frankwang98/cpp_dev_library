#include <iostream>
#include <cstring>
#include <unistd.h>
#include <mosquitto.h>
#include <string>

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
}

int main() {
    struct mosquitto* mosq = nullptr;

    mosquittoInit(mosq);
    mosquittoConnect(mosq);

    // 订阅主题
    mosquittoSubscribe(mosq, "test");

    // 发布主题
    while (true) {
        mosquittoPublish(mosq, "test", "Hello, Mosquitto!");
        std::cout << "Published message." << std::endl;
        usleep(1000 * 1000);
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
