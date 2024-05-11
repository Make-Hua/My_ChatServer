#ifndef GROUPUSER_H
#define GROUPUSER_H

#include "user.hpp"

// GroupUser 表对应的操作类
class GroupUser : public User
{
public:

    void setRole(string role) {}
    string getRole() { return role; }

private:
    string role;

};




#endif //GROUPUSER_H