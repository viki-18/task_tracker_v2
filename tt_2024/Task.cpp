#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<chrono>
#include<string>
#include <iomanip>
#include "Task.h"

using namespace std;
using namespace chrono;

Task::Task() : Entity() {}

Task::Task(int tt, string na, string de, string st, time_t dead, string est) : Entity() {
	ttid = tt;
	name = na;
	details = de;
	stage = st;
	deadline = dead;
	estimate_time = est;
}

Task::Task(int id, int tt, string na, string de, string st, time_t dead, string est): Entity(id) {
	ttid = tt;
	name = na;
	details = de;
	stage = st;
	deadline = dead;
	estimate_time = est;
}

string Task::deadlineString() {
	struct tm* timeinfo = localtime(&deadline);
	char buffer[80];
	strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
	string deadlineString(buffer);
	return deadlineString;
}

string Task::tostring() {
	return "(" + to_string(ttid) + ", \"" + name + "\", \"" +
		details + "\", \"" + stage + "\", \"" + deadlineString() + "\", \"" + estimate_time + "\")";
}

string Task::post() {
	return "INSERT INTO " + table + " " + attributes + " VALUES " + tostring();
}

string Task::get(string searched_name) {
	return "SELECT * FROM " + table + " WHERE name = \"" + searched_name + "\"";
}

string Task::erase(string searched_name) {
	return "DELETE FROM " + table + " WHERE name = \"" + searched_name + "\"";
}

string Task::update_stage(string searched_name, string new_stage) {
	return "UPDATE " + table + " SET stage = \"" + new_stage + "\" WHERE name = \"" + searched_name + "\"";
}
