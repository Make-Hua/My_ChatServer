#include "chatserver.hpp"
#include "chatservice.hpp"
#include <iostream>
#include <signal.h>

using namespace std;

// 处理服务器 ctrl + c 结束后，重置 user 的状态信息
void ressetHandler(int) 
{
    ChatService::instance()->reset();
    exit(0);
}

int main() 
{
    // 重启服务的时候，此时肯定不存在有用户在线，则用户状态直接全部变成 "offline"
    signal(SIGINT, ressetHandler);

    // 事件循环对象
    EventLoop loop;

    // 配置  IP  prot 
    InetAddress addr("127.0.0.1", 6000);

    // 创建服务器
    ChatServer server(&loop, addr, "ChatServer");

    server.start();
    loop.loop();

    return 0;
}