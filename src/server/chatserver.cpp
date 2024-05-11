#include "chatserver.hpp"
#include "json.hpp"
#include "chatservice.hpp"

#include <iostream>
#include <functional>
#include <string>

using namespace std;
using namespace placeholders;
using json = nlohmann::json;

ChatServer::ChatServer(EventLoop *loop,
                       const InetAddress &listenAddr,
                       const string &nameAge)
    : _server(loop, listenAddr, nameAge), _loop(loop)
{
    // 给服务器注册用户连接和断开（连接）的回调函数
    _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1));

    // 给服务器注册用户读写事件(消息)回调
    _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));

    // 设置服务端的线程数量  1 个 IO线程  3 个 worker 线程
    _server.setThreadNum(4);
}

// 开启事件循环
void ChatServer::start()
{
    _server.start();
}

// 专门处理用户连接创建和断开的(每当连接或断开时，都会触发该函数)
void ChatServer::onConnection(const TcpConnectionPtr &conn)
{
    // 客户端断开连接
    if (!conn->connected())
    {
        // 异常退出该连接 (需要处理已登陆账号的状态)
        ChatService::instance()->clientCloseException(conn);

        conn->shutdown();
    }
}

// 专门处理用户读写事件的
void ChatServer::onMessage(const TcpConnectionPtr &conn,       // 连接
                           Buffer *buffer,                     // 缓冲区
                           Timestamp time)                     // 接受到数据的时间信息
{
    string buf = buffer->retrieveAllAsString();

    // 数据反序列化
    json js = json::parse(buf);

    // 通过js
    auto msgHandler = ChatService::instance()->getHandler(js["msgid"].get<int>());
    
    // 回调消息对应绑定好的事件处理器，从而执行相应的业务处理
    msgHandler(conn, js, time);
}
