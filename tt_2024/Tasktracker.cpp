#include "Tasktracker.h"

Tasktracker::Tasktracker() : Entity() {}

Tasktracker::Tasktracker(int ui, string na) : Entity() {
	uid = ui;
	name = na;
}

Tasktracker::Tasktracker(int id, int ui, string na) : Entity(id) {
	uid = ui;
	name = na;
}

string Tasktracker::tostring() {
	return "(" + to_string(uid) + ", \"" + name + "\")";
}

string Tasktracker::post() {
	return "INSERT INTO " + table + " " + attributes + " VALUES " + tostring();
}

string Tasktracker::getall() {
	return "SELECT * FROM " + linked_table + " WHERE ttid = " + to_string(id);
}

string Tasktracker::getbydd() {
	return "SELECT * FROM " + linked_table + " WHERE ttid = " + to_string(id) + " ORDER BY deadline";
}

int Tasktracker::getid() {
	return id;
}