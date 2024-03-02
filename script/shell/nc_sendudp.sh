#!/bin/bash

# nc命令UDP测试脚本

# UDP 目标主机和端口
IP="10.10.4.133"
PORT=8888

# 发送的消息内容
MESSAGE="Hello, UDP!"

# 循环发送消息
for ((i=1; i<=10; i++))
do
    echo "Sending message: $MESSAGE"
    echo "$MESSAGE" | nc -u -w 1 $IP $PORT &
    sleep 0.2  # 可选，添加延迟以控制发送速率
done

# 接收端用 nc -ulp 8888
