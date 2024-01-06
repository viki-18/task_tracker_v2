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

string Tasktracker::get(int userid) {
	return "SELECT * FROM " + table + " WHERE uid = " + to_string(userid);
}

string Tasktracker::getall(int TTid) {
	return "SELECT * FROM " + linked_table + " WHERE ttid = " + to_string(TTid);
}

string Tasktracker::getbydd(int TTid) {
	return "SELECT * FROM " + linked_table + " WHERE ttid = " + to_string(TTid) + " ORDER BY deadline";
}
