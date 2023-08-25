#include "assetLoader.h"

AssetLoader::AssetLoader()
{
}

void AssetLoader::loadGraphics()
{
	auto load = [&](std::string name, std::string fname) {
		olc::Sprite* s = new olc::Sprite(fname);
		sprites_[name] = s;
	};

	//assets to load
	load("baseTileSet", "assets\\tileset.png");
	/*load("flagedTile", "");
	load("emptyTile", "");
	load("zero", "");
	load("one", "");
	load("three", "");
	load("four", "");
	load("five", "");
	load("six", "");
	load("seven", "");
	load("eight", "");
	load("bomb", "");
	*/
}