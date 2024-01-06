#include "Entity.h"

Entity::Entity() {}

Entity::Entity(int entityId) {
	id = entityId;
}

string Entity::post() {
	return "INSERT INTO " + table + " " + attributes + " VALUES " + tostring();
}

string Entity::get() {
	return string();
}

string Entity::tostring() {
	return string();
}
