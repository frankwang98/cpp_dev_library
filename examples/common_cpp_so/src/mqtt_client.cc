/**
 * mqtt_client_so src
*/

#include "mqtt_client.h"

std::string recvMessage;

void mosquittoInit(struct mosquitto*& mosq) 
{
    mosquitto_lib_init();
    mosq = mosquitto_new("mosq_cpp_example", true, nullptr);
    if (!mosq) {
        std::cerr << "Error: Unable to initialize Mosquitto library." << std::endl;
        exit(EXIT_FAILURE);
    }
}

void mosquittoConnect(struct mosquitto* mosq) 
{
    int ret = mosquitto_connect(mosq, MQTT_BROKER_ADDRESS.c_str(), MQTT_BROKER_PORT, 60);
    if (ret != MOSQ_ERR_SUCCESS) {
        std::cerr << "Error: Unable to connect to Mosquitto broker. Return code: " << ret << std::endl;
        exit(EXIT_FAILURE);
    }
}

void mosquittoPublish(struct mosquitto* mosq, const std::string& topic, const std::string& message)
{
    int ret = mosquitto_publish(mosq, nullptr, topic.c_str(), message.size(), message.c_str(), 0, false);
    if (ret != MOSQ_ERR_SUCCESS) {
        std::cerr << "Error: Unable to publish message. Return code: " << ret << std::endl;
    }
}

void mosquittoSubscribe(struct mosquitto* mosq, const std::string& topic)
{
    int ret = mosquitto_subscribe(mosq, nullptr, topic.c_str(), 0);
    if (ret != MOSQ_ERR_SUCCESS) {
        std::cerr << "Error: Unable to subscribe to topic. Return code: " << ret << std::endl;
    }
}

void onMessage(struct mosquitto* mosq, void* userdata, const struct mosquitto_message* message)
{
    std::string receivedMessage((char*)message->payload, message->payloadlen); // char* -> string
    // std::cout << "received Topic: " << message->topic << ", Message: " << receivedMessage << std::endl;
    recvMessage = receivedMessage;
}
