#pragma once
#include <map>
#include "olcPixelGameEngine.h"

class AssetLoader
{
public:
	AssetLoader(AssetLoader const&) = delete;
	void operator=(AssetLoader const&) = delete;

	AssetLoader();
	inline olc::Sprite* getSprite(std::string&& name) { return sprites_[name]; }
	void loadGraphics();
private:
	std::map<std::string, olc::Sprite*> sprites_;
	
};

