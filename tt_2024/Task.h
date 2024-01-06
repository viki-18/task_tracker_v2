#pragma once
#ifndef TASK_H
#define TASK_H

#include "Entity.h"
#include <iostream>
#include <chrono>
#include <string>
#include <iomanip>

using namespace std;
using namespace chrono;

class Task : public Entity {
protected:
	string attributes = "(ttid, name, details, stage, deadline, estimate_time)";
	string table = "task";
	int id;
	int ttid;
	string name;
	string details;
	string stage;
	time_t deadline;
	string estimate_time;

public:
	Task();
	Task(int tt, string na, string de, string st, time_t dead, string est);
	Task(int id, int tt, string na, string de, string st, time_t dead, string est);

	string deadlineString();
	string tostring();

	string get(string searched_name);
	string post();
	string erase(string searched_name);
	string update_stage(string searched_name, string new_stage);
};

#endif // TASK_H
