#ifndef GROUPMODEL_H
#define GROUPMODEL_H

#include "group.hpp"
#include <string>
#include <vector>

using namespace std;

class GroupModel
{
public:
    // 创建群组
    bool createGroup(Group &group);

    // 加入群组
    void addGroup(int userid, int groupid, string role);

    // 查询用户所在群组的消息
    vector<Group> queryGroups(int userid);

    // 根据指定的 groupid 查询群组用户 id 列表，除了自己，
    // 用来给用户群聊其他群组成员发消息
    vector<int> queryGroupUsers(int userid, int groupid);

};





#endif