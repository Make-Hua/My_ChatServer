#ifndef USERMODEL_H
#define USERMODEL_H

#include "user.hpp"

// User 表的数据操作类
class UserModel
{
public:

    // 提供插入接口
    bool insert(User &user);

    // 根据用户号码查找用户信息
    User query(int id);

    // 刷新用户数据(更新用户状态信息)
    bool updateState(User user);

    // 重置用户状态信息
    void resetState();

private:
    /* data */
};




#endif