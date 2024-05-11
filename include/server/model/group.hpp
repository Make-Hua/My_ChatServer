#ifndef GROUP_H
#define GROUP_H

#include "groupuser.hpp"
#include <string>
#include <vector>

using namespace std;

// allgroup 表的操作类
class Group
{
public:
    Group(int id_ = -1, string name_ = "", string desc_ = "")
        : id(id_),
          name(name_),
          desc(desc_)
    {}

    void setId(int id) { this->id = id; };
    void setName(string name) { this->name = name; };
    void setDesc(string desc) { this->desc = desc; };

    int getId() { return id; }
    string getName() { return name; }
    string getDesc() { return this->desc; }
    vector<GroupUser>& getUsers() { return users; }

private:
    int id;
    string name;
    string desc;
    vector<GroupUser> users;     // 存储某个组对应的成员
};






#endif