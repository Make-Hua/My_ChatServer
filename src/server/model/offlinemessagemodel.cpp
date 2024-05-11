#include "offlinemessagemodel.hpp"
#include "db.h"



// 存储用户离线消息
void OfflineMsgModel::insert(int userid, string msg)
{
    // 组装 sql 语句
    char sql[1024] = {0};
    sprintf(sql, "insert into offlinemessage values(%d, '%s')", userid, msg.c_str());

    // 出作用域 MySQL 会自动析构，释放连接资源
    MySQL mysql;

    // 连接数据库
    if (mysql.connect())
    {
        mysql.update(sql);
    }
}

// 删除用户的离线消息
void OfflineMsgModel::remove(int userid)
{
    // 组装 sql 语句
    char sql[1024] = {0};
    sprintf(sql, "delete from offlinemessage where userid=%d", userid);

    // 出作用域 MySQL 会自动析构，释放连接资源
    MySQL mysql;

    // 连接数据库
    if (mysql.connect())
    {
        mysql.update(sql);
    }
}

// 查询用户的离线消息
vector<string> OfflineMsgModel::query(int userid)
{
    // 组装 sql 语句
    char sql[1024] = {0};
    sprintf(sql, "select message from offlinemessage where userid=%d", userid);

    // 出作用域 MySQL 会自动析构，释放连接资源
    MySQL mysql;

    vector<string> vec;
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
                vec.push_back(row[0]);
            }

            mysql_free_result(res);
            return vec;
        }
    }
    return vec;
}