#pragma once
#include <vector>
#include "node.h"
#include "olcPixelGameEngine.h"

class AreaController
{
private:
	std::vector<std::vector<Node>> grid_;
	size_t rows_, cols_, bombs_;
	void reveal(Node* node);

public:
	AreaController(size_t columns, size_t rows, size_t bombsAmount);
	
	//returns true state if the node is a bomb, otherwise return false
	bool reveal(olc::vi2d clickedPos);
	void mark(olc::vi2d clickedPos);
	void placeBombs(unsigned int seed, olc::vi2d clickedPos);
	inline std::vector<std::vector<Node>> getGrid() const { return grid_; };
};

