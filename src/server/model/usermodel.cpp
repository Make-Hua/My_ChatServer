#include "usermodel.hpp"
#include "db.h"
#include <iostream>

using namespace std;

bool UserModel::insert(User &user) 
{
    // 组装 sql 语句
    char sql[1024] = {0};
    sprintf(sql, "insert into user(name, password, state) values('%s', '%s', '%s')",
            user.getName().c_str(), user.getPassword().c_str(), user.getState().c_str());

    // 出作用域 MySQL 会自动析构，释放连接资源
    MySQL mysql;

    // 连接数据库
    if (mysql.connect())
    {
        // 数据插入成功
        if (mysql.update(sql))
        {
            // 获取插入成功的用户数据生成的主键id
            user.setId(mysql_insert_id(mysql.getConnection()));
            return true;
        }
    }
    return false;
}


// 根据用户号码查找用户信息
User UserModel::query(int id)
{
    // 组装 sql 语句
    char sql[1024] = {0};
    sprintf(sql, "select * from user where id = %d", id);

    // 出作用域 MySQL 会自动析构，释放连接资源
    MySQL mysql;

    // 连接数据库
    if (mysql.connect())
    {
        MYSQL_RES* res = mysql.query(sql);

        // 不为空则表示查询成功
        if (nullptr != res) 
        {
            // typedef char **MYSQL_ROW;		/* return data as array of strings */         MYSQL_ROW ---> 一维数组，数组中存着字符串  
            MYSQL_ROW row = mysql_fetch_row(res);
            if (nullptr != row)
            {
                User user;
                user.setId(atoi(row[0]));
                user.setName(row[1]);
                user.setPassword(row[2]);
                user.setState(row[3]);

                mysql_free_result(res);    // 释放资源，否则会造成内存泄漏
                return user;
            }
        }
    }

    return User();
}


// 刷新用户数据(更新用户状态信息)
bool UserModel::updateState(User user)
{
    // 组装 sql 语句
    char sql[1024] = {0};
    sprintf(sql, "update user set state = '%s' where id = %d",
            user.getState().c_str(), user.getId());

    // 出作用域 MySQL 会自动析构，释放连接资源
    MySQL mysql;
    
    // 连接数据库
    if (mysql.connect())
    {
        if (mysql.update(sql))
        {
            return true;
        }
    }
    return false;
}



// 重置用户状态信息
void UserModel::resetState()
{
    // 组装 sql 语句
    char sql[1024] = "update user set state = 'offline' where state = 'online'";

    // 出作用域 MySQL 会自动析构，释放连接资源
    MySQL mysql;
    
    // 连接数据库
    if (mysql.connect())
    {
        // 更新
        mysql.update(sql);
    }
}
