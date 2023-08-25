#pragma once
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "areaController.h"
#include "assetLoader.h"

class MinesGame : public olc::PixelGameEngine
{
private:
	uint16_t columns_, rows_, nodeSize_, bombs_;
	std::unique_ptr<AreaController> area_;
	olc::Sprite* tileset_;
	AssetLoader loader_;
	bool hasFirstClick_, exploded_;
	time_t* seed_;

private:
	olc::vi2d convertToCoords(int x, int y)
	{
		return olc::vu2d((x / nodeSize_ ), (y / nodeSize_));
	}
public:
	MinesGame(uint16_t cols = 10, uint16_t rows = 8, uint16_t nodeSize = 40, uint16_t bombs = 10, const std::string& title = "game", time_t* seed = NULL)
		:columns_(cols)
		, rows_(rows)
		, nodeSize_(nodeSize)
		, bombs_(bombs)
		, area_(new AreaController(columns_, rows_, bombs_))
		, hasFirstClick_(true)
		, seed_(seed)
		, exploded_(false)
	{
		if (bombs > (cols * rows))
			throw std::exception("Number of bombs is greater than numbers of nodes");

		area_ = std::make_unique<AreaController>(columns_, rows_, bombs_);
		loader_.loadGraphics();
		tileset_ = loader_.getSprite("baseTileSet");
		sAppName = title;
	}
	MinesGame(uint16_t cols = 10, uint16_t rows = 8, uint16_t nodeSize = 40, uint16_t bombs = 10, std::string&& title = "game", time_t* seed = NULL)
		:columns_(cols)
		, rows_(rows)
		, nodeSize_(nodeSize)
		, bombs_(bombs)
		, area_(new AreaController(columns_, rows_, bombs_))
		, hasFirstClick_(true)
		, seed_(seed)
		, exploded_(false)
	{
		if (bombs > (cols * rows))
			throw std::exception("Number of bombs is greater than numbers of nodes");

		area_ = std::make_unique<AreaController>(columns_, rows_, bombs_);
		loader_.loadGraphics();
		tileset_ = loader_.getSprite("baseTileSet");
		sAppName = title;
	}

	~MinesGame() {
		area_.reset();
		delete tileset_;
	}







	//Game functions
	bool OnUserCreate() override
	{
		Clear(olc::GREY);

		return true;
	}
	bool OnUserUpdate(float deltaTime) override
	{
		if (hasFirstClick_) {
			if (GetMouse(0).bReleased) {
				hasFirstClick_ = false;
				olc::vi2d coords = convertToCoords(GetMouseX(), GetMouseY());
				area_->placeBombs((unsigned int)time(seed_), coords);
				area_->reveal(coords);
				return true;
			}
			for (int y = 0; y < rows_; y++) {
				for (int x = 0; x < columns_; x++)
					DrawPartialSprite(x * nodeSize_, y * nodeSize_, tileset_, 0, nodeSize_, nodeSize_, nodeSize_);
			}
			return true;
		}

		realGameUpdate();
		return true;
	}
	
	void init()
	{
		if (this->Construct(columns_ * (nodeSize_), rows_ * (nodeSize_), 2, 2))
			this->Start();
	}
	void realGameUpdate()
	{
		if (exploded_) {
			renderGrid();
			return;
		}

		if (GetMouse(0).bReleased && area_->reveal(convertToCoords(GetMouseX(), GetMouseY()))) {
			
			for (int y = 0; y < rows_; y++) {
				for (int x = 0; x < columns_; x++)
					if (area_->getGrid()[y][x].value_ == -1)area_->getGrid()[y][x].revealed_ = true;
			}
			exploded_ = true;
		}
			

		else if(GetMouse(1).bReleased) area_->mark(convertToCoords(GetMouseX(), GetMouseY()));
		renderGrid();
		
	}
	void renderGrid()
	{
		for (int y = 0; y < rows_; y++) {
			for (int x = 0; x < columns_; x++) {
				if (!area_->getGrid()[y][x].revealed_) {
					if (area_->getGrid()[y][x].flaged_) DrawPartialSprite(x * nodeSize_, y * nodeSize_, tileset_, nodeSize_, nodeSize_, nodeSize_, nodeSize_);
					else if (area_->getGrid()[y][x].recentlyUpdated_) {
						area_->getGrid()[y][x].recentlyUpdated_ = false;
						DrawPartialSprite(x * nodeSize_, y * nodeSize_, tileset_, 0, nodeSize_, nodeSize_, nodeSize_);
					}
					continue;
				}
				if (area_->getGrid()[y][x].value_ == -1) {
					DrawPartialSprite(x * nodeSize_, y * nodeSize_, tileset_, 2 * nodeSize_, nodeSize_, nodeSize_, nodeSize_);
					continue;
				}

				DrawPartialSprite(x * nodeSize_, y * nodeSize_, tileset_, area_->getGrid()[y][x].value_ * nodeSize_, 0, nodeSize_, nodeSize_);
			}
		}
	}
};
