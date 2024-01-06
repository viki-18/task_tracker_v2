#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <string>
using namespace std;

class Entity {
protected:
	string attributes;
	string table;
	int id;

public:
	Entity();
	Entity(int entityId);

	string post();
	string get();
	string tostring();
};

#endif // ENTITY_H
