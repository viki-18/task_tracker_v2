#pragma once
#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include "Entity.h"
using namespace std;

class User : public Entity {
protected:
	string attributes = "(user_name, password)";
	string table = "user";
	string linked_table = "task_tracker";
	int id;
	string username;
	string password;

public:
	User();
	User(string us, string pas);
	User(int id, string us, string pas);

	string tostring();
	string post();
	string get();
	int getid();
};

#endif // USER_H
