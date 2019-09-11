#include "stdafx.h"


int Placeable::getSlot() {
	return this->slot_num;
}

std::string Placeable::getName() {
	return name;
}

void Placeable::upgrade() {
	level++;
}

int Placeable::getLevel() {
	return level;
}