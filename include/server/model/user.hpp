#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

// 映射 user 表的 ORM 类
class User {
public:
    User(int id_ = -1, string name_ = "", string password_ = "", string state_ = "offline")
        : id(id_),
          name(name_),
          password(password_),
          state(state_)
    {}

    void setId(int id_) { id = id_; }
    void setName(string name_) { name = name_; }
    void setPassword(string pwd_) { password = pwd_; }
    void setState(string state_) { state = state_; }

    int getId() { return id; }
    string getName() { return name; }
    string getPassword() { return password; }
    string getState() { return state; }


private:
    int id;
    string name;
    string password;
    string state;
};


#endif