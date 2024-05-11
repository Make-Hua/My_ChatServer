#include "friendmodel.hpp"
#include "db.h"

// 添加好友关系
void FriendModel::insert(int userid, int friendid)
{
    // 组装 sql 语句
    char sql[1024] = {0};
    sprintf(sql, "insert into friend values(%d, %d)", userid, friendid);

    // 出作用域 MySQL 会自动析构，释放连接资源
    MySQL mysql;

    // 连接数据库
    if (mysql.connect())
    {
        // 数据插入成功
        mysql.update(sql);
    }

}

/*
    select a.id,a.name,a.state from user a inner join friend b on b.userid=a.id where b.userid=%d
*/
// 返回用户的好友列表 
vector<User> FriendModel::query(int userid)
{
    // 组装 sql 语句
    char sql[1024] = {0};
    sprintf(sql, "select a.id,a.name,a.state from user a inner join friend b on b.userid=a.id where b.userid=%d", userid);

    // 出作用域 MySQL 会自动析构，释放连接资源
    MySQL mysql;

    vector<User> vec;
    // 连接数据库
    if (mysql.connect())
    {
        MYSQL_RES* res = mysql.query(sql);

        // 不为空则表示查询成功
        if (nullptr != res) 
        {
            // 把 userid 用户的所有离线消息放入 vec 中返回
            MYSQL_ROW row;

            // 查询数据库中存储的所有数据（一行一行拿）
            while ((row = mysql_fetch_row(res)) != nullptr)
            {   
                User user;
                user.setId(atoi(row[0]));
                user.setName(row[1]);
                user.setState(row[2]);
                vec.push_back(user);


            }

            // 释放资源
            mysql_free_result(res);
            return vec;
        }
    }
    return vec;

}


