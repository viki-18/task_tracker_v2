#include"User.h"

User::User() : Entity() {}

User::User(string us, string pas) : Entity(){
	username = us;
	password = pas;
}

User::User(int id, string us, string pas) : Entity(id) {
	username = us;
	password = pas;
}

string User::post() {
	return "INSERT INTO " + table + " " + attributes + " VALUES " + tostring();
}

string User::get() {
	return "SELECT * FROM " + table + " WHERE user_name = \"" + username + "\" AND password = \"" + password + "\"";
}

string User::tostring() {
	return "(\"" + username + "\", \"" + password + "\")";
}

int User::getid() {
	return id;
}
