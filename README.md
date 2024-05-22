## 基于 muduo 实现的集群聊天服务器(ChatServer)

### 一、项目说明

项目是在 Linux 环境下基于 muduo 网络库 和 json 通信协议实现的集群聊天服务器，其中使用了 nginx 和 redis 中间件，项目主要实现了注册、登录、添加好友和添加群组、好友聊天、群组聊天、离线消息、nginx配置tcp负载均衡、集群聊天系统支持客户端跨服务器通信。

### 二、项目特点

- Json 序列化和反序列化
- muduo 网络库开发
- nginx 源码编译安装和环境部署以及 nginx 的 TCP 负载均衡器配置
- redis 缓存服务器编程实践以及基于发布-订阅的服务器中间件 redis 消息队列编程实践
- MySQL 数据库编程

### 三、开发环境

- 操作系统：`Ubuntu 18.04.2`
- 编译器：`g++ 7.5.0`
- 编译器：`vscode`
- 版本控制：`git`
- 项目构建：`cmake 3.10.2`

### 四、构建项目

直接运行脚本即可自动编译项目

```shell
./autobuild.sh
```

### 五、项目启动

#### 配置 nginx 

```shell
# nginx TCP loadbalance config
stream {
       upstream MyServer {
               # 服务器 名称  ip:端口  算法权重(默认1)  心跳机制次数(达到3次既认定断开连接)   
               server 127.0.0.1:6000 weight=1 max_fails=3 fail_timeout=30s;
               server 127.0.0.1:6002 weight=1 max_fails=3 fail_timeout=30s;
       }

       server {
               proxy_connect_timeout 1s;
                #proxy_timeout 3s;
               listen 8000;          # 让客户端往 8000 端口发送数据，进行负载均衡
               proxy_pass MyServer;
               tcp_nodelay on;
       }
}
# over！
```



#### 启动 Server 服务端

由于项目中使用 zookeeper 实现分布式一致性协调服务，所以我们需要先在 Linux 下启动 zookeeper

```shell
# 由于 nginx 配置了两台服务器，我们就开启两台
ubuntu@ ~/My_Server/bin$ ./ChatServer 127.0.0.1 6000
ubuntu@ ~/My_Server/bin$ ./ChatServer 127.0.0.1 6002
```

#### 启动 Client 客户端

验证是否开启项目，如若开启成功，则可以在进程中找到 zookeeper

```shell
# nginx 中配置了 listen 监听8000端口，则我们客户端连 8000 端口
# 通过 nginx 负载均衡给客户端分配服务器
ubuntu@ ~/My_Server/bin$ ./ChatClient 127.0.0.1 8000
```
