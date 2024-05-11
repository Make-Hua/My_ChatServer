#ifndef PUBLIC_H
#define PUBLIC_H

// server 以及 client 的公共文件

/* 
* @ LOGIN_MSG               登陆消息
* @ LOGIN_MSG_ACK           登陆响应消息
* @ REG_MSG                 注册消息
* @ REG_MSG_ACK             注册响应消息
* @ ONE_CHAT_MSG            聊天消息（1对1）
* @ ADD_FRIEND_MSG          添加好友消息
* @ CREATE_GROUP_MSG        创建群组消息
* @ ADD_GROUP_MSG           加入群组消息
* @ GROUP_CHAT_MSG          群聊天消息
* @ LOGINOUT_MSG            注销消息
*/

// 当发生登陆时自动回调 void login() 函数       注册同理
enum EnMsgType
{
    LOGIN_MSG = 1,
    LOGIN_MSG_ACK,
    LOGINOUT_MSG,
    REG_MSG,
    REG_MSG_ACK,
    ONE_CHAT_MSG,
    ADD_FRIEND_MSG,
    CREATE_GROUP_MSG,
    ADD_GROUP_MSG,
    GROUP_CHAT_MSG,
};



#endif