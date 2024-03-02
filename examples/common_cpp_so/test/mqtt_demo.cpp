#include <iostream>
#include "mqtt_client.h"

using namespace std;

struct mosquitto* mosq = nullptr;

int main()
{
    // 初始化 连接服务端
    mosquittoInit(mosq);
    mosquittoConnect(mosq);

    string topic = "test";
    string message = "Hello, MQTT!";

    mosquittoPublish(mosq, topic, message); // publish

    mosquittoSubscribe(mosq, topic); // subscribe and callback
    mosquitto_message_callback_set(mosq, onMessage);

    while (true)
    {
        mosquitto_loop(mosq, -1, 1); // similar to ros::spinOnce

        if (recvMessage != "")
        {
            cout << "recvMessage: " << recvMessage; // target to recvMessage(unified)
        }

        recvMessage = "";
        usleep(10 * 1000);
    }

    // 断开连接并清理资源
    mosquitto_disconnect(mosq);
    mosquitto_destroy(mosq);
    mosquitto_lib_cleanup();

    return 0;
}

