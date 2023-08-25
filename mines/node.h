#pragma once
#include <cstdint>
class Node
{
public:
	int16_t value_;
	bool revealed_, flaged_, recentlyUpdated_;
	
	Node* neighbours_[8] = {nullptr};
	enum Directions {
		LEFT,
		RIGHT,
		DOWN,
		UP,
		DOWNR,
		DOWNL,
		UPL,
		UPR
	};
public:
	Node();
	bool operator==(int num) {
		return this->value_ == num;
	}
};

