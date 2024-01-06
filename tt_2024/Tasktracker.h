#pragma once
#ifndef TASKTRACKER_H
#define TASKTRACKER_H

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "Entity.h"
using namespace std;

class Tasktracker : public Entity {
protected:
	string attributes = "(uid, name)";
	string table = "task_tracker";
	string linked_table = "task";
	int id;
	int uid;
	string name;

public:
	Tasktracker();
	Tasktracker(int uid, string na);
	Tasktracker(int id, int uid, string na);

	string tostring();
	string post();
	string get(int userid);
	string getall(int TTid);
	string getbydd(int TTid);
};

#endif // TASKTRACKER_H
