#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>

using namespace muduo;
using namespace muduo::net;

/* 基于 muduo 网络库开发基本流程
1. 组合 TcpServer 对象 、 创建 EventLoop 事件循环对象的指针
2. 明确 TcpServer 构造函数需要什么参数， 输出 ChatServer 的构造函数
3. 在当前服务器类的构造函数中，注册处理连接的回调函数和读写事件的回调函数
4. 设置合适的服务端线程数量， muduo 库会自动划分 IO线程 和 worker线程数量
*/

// 聊天服务器主类
class ChatServer
{
public:
    ChatServer(EventLoop *loop,
               const InetAddress &listenAddr,
               const string &nameAge);

    // 开启事件循环(启动服务)
    void start();

private:

    // 上报连接相关信息的回调函数
    void onConnection(const TcpConnectionPtr &);

    // 上报读写相关信息的回调函数
    void onMessage(const TcpConnectionPtr &,      // 连接
                   Buffer *,                      // 缓冲区
                   Timestamp);                    // 接受到数据的时间信息


    TcpServer _server;                            // 创建组合 TcpServer 对象
    EventLoop *_loop;                             // 指向事件循环对象的指针

};





#endif