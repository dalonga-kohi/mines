#include "areaController.h"

AreaController::AreaController(size_t c, size_t r, size_t b)
	:bombs_(b)
	,cols_(c)
	,rows_(r)
{
	grid_.reserve(rows_);
	
	std::vector<Node> row;
	Node* np = new Node;
	row.reserve(cols_);
	for (size_t i = 0; i < cols_; i++)
		row.push_back(*np);
	for (size_t i = 0; i < rows_; i++)
		grid_.push_back(row);
	delete np;

	//set neighbours
	for (size_t y = 0; y < rows_; y++)
		for (size_t x = 0; x < cols_; x++) {
			if (x >= 1)
				grid_[y][x].neighbours_[Node::LEFT] = &grid_[y][x - 1];
			if ((x + 1) < cols_)
				grid_[y][x].neighbours_[Node::RIGHT] = &grid_[y][x + 1];
			if (y >= 1)
				grid_[y][x].neighbours_[Node::UP] = &grid_[y - 1][x];
			if ((y + 1) < rows_)
				grid_[y][x].neighbours_[Node::DOWN] = &grid_[y + 1][x];

			if ((y >= 1) && (x >= 1))
				grid_[y][x].neighbours_[Node::UPL] = &grid_[y - 1][x - 1];
			if ((y >= 1) && x < (cols_ - 1))
				grid_[y][x].neighbours_[Node::UPR] = &grid_[y - 1][x + 1];
			if ((y + 1) < rows_ && (x >= 1))
				grid_[y][x].neighbours_[Node::DOWNL] = &grid_[y + 1][x - 1];
			if ((y + 1) < rows_ && (x + 1) < cols_)
				grid_[y][x].neighbours_[Node::DOWNR] = &grid_[y + 1][x + 1];
		}
}

void AreaController::placeBombs(unsigned int seed, olc::vi2d clickPos)
{
	srand(seed);
	for (size_t i = 0; i < bombs_; i++)
	{
		int prevy = 1, prevx = 1;
		int locy = (rand() + (static_cast<unsigned long long>(prevx)*(prevy | prevx))) % rows_;
		int locx = (static_cast<unsigned long long>(rand()) + ((prevx | prevy)<prevy)) % cols_;
		if ((grid_[locy][locx].value_ == -1) || ((locx == clickPos.x)&&(locy == clickPos.y)))
			i--;
		else
			grid_[locy][locx].value_ = -1;
		prevy = locy;
		prevx = locx;
	}

	for (auto& row : grid_) {
		for (auto& n : row) {
			if (n.value_ == -1) continue;
			n.value_ = (int16_t)std::count_if(n.neighbours_, n.neighbours_ + 8, [&](Node* node) {
				if (!node) return false;
				return node->value_ == -1;
			});
		}
	}
}

bool AreaController::reveal(olc::vi2d coords)
{
	Node* n = &grid_[coords.y][coords.x];
	if (n->revealed_ || n->flaged_) return false;

	n->revealed_ = true;
	if (n->value_ == -1) return true;

	if (n->value_ == 0) {	
		for (auto& neigh : n->neighbours_)
			if(neigh) AreaController::reveal(neigh);
	}
	return false;
}

void AreaController::reveal(Node* n)
{
	if (n->revealed_) return;
	n->revealed_ = true;
	if (n->value_ == 0) {
		for (auto& neigh : n->neighbours_)
			if (neigh) AreaController::reveal(neigh);
	}
}

void AreaController::mark(olc::vi2d coords)
{
	grid_[coords.y][coords.x].flaged_ = !grid_[coords.y][coords.x].flaged_;
	if (!grid_[coords.y][coords.x].flaged_) grid_[coords.y][coords.x].recentlyUpdated_ = true;
}