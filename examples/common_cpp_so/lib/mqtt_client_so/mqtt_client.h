/**
 * mqtt_client_so inc
 * pre: sudo apt install libmosquitto-dev
 * usage: g++ -o main main.cpp -lmosquitto && ./main
*/
#ifndef MQTT_CLEINT_SO_H
#define MQTT_CLEINT_SO_H

#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <fstream>
#include <sstream>
#include <type_traits>
#include <functional>
#include <unistd.h>
#include <cstring>
#include <sys/wait.h>
#include <errno.h>
#include <assert.h>
#include <uuid/uuid.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <mosquitto.h>

const std::string MQTT_BROKER_ADDRESS = "10.10.8.9";
const int MQTT_BROKER_PORT = 1883;
extern std::string recvMessage;

void mosquittoInit(struct mosquitto*& mosq);

void mosquittoConnect(struct mosquitto* mosq);

void mosquittoPublish(struct mosquitto* mosq, const std::string& topic, const std::string& message);

void mosquittoSubscribe(struct mosquitto* mosq, const std::string& topic);

void onMessage(struct mosquitto* mosq, void* userdata, const struct mosquitto_message* message);

#endif
