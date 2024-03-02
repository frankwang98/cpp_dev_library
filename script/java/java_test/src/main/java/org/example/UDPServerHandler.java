package org.example;

import io.netty.buffer.Unpooled;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.SimpleChannelInboundHandler;
import io.netty.channel.socket.DatagramPacket;
import io.netty.util.CharsetUtil;

public class UDPServerHandler extends SimpleChannelInboundHandler<DatagramPacket> {
    @Override
    protected void channelRead0(ChannelHandlerContext ctx, DatagramPacket msg) throws Exception {
        // 处理接收到的数据
        String receivedMessage = msg.content().toString(CharsetUtil.UTF_8);
        System.out.println("Received message: " + receivedMessage);

        // 响应客户端
        String responseMessage = "Hello, client!";
        DatagramPacket responsePacket = new DatagramPacket(Unpooled.copiedBuffer(responseMessage, CharsetUtil.UTF_8),
                msg.sender());
        ctx.writeAndFlush(responsePacket);
    }
}
