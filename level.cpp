#include "level.h"
#include "graphics.h"
#include <SDL.h>
#include "globals.h"
#include "tinyxml2.h"
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace tinyxml2;

Level::Level()
{
}

Level::Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics) :
	mapName(mapName), 
	spawnPoint(spawnPoint),
	size(Vector2())
{
	loadMap(mapName, graphics);
}

Level::~Level()
{
}

void Level::update(int elapsedTime)
{

}

void Level::draw(Graphics & graphics)
{
	for (int i = 0; i < tileList.size(); i++)
	{
		tileList.at(i).draw(graphics);
	}
}

std::vector<Rectangle> Level::checkTileCollisions(const Rectangle & rectangle)
{
	std::vector<Rectangle> others;
	for (int i = 0; i < collisionRects.size(); i++)
	{
		if (collisionRects.at(i).collidesWith(rectangle)) {
			others.push_back(rectangle);
		}
	}
	return others;
}

const Vector2 Level::getPlayerSpawnPoint() const
{
	return spawnPoint;
}



void Level::loadMap(std::string mapName, Graphics & graphics)
{
	/*
	backgroundTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(),
		graphics.loadImage("bkBlue.png"));
	size = Vector2(1280, 960);
	*/
	XMLDocument doc;
	std::stringstream stream;
	stream << mapName << ".tmx";
	doc.LoadFile(stream.str().c_str());

	XMLElement* mapNode = doc.FirstChildElement("map");

	int width, height;
	mapNode->QueryIntAttribute("width", &width);
	mapNode->QueryIntAttribute("height", &height);
	size = Vector2(width, height);

	int tileWidth, tileHeight;
	mapNode->QueryIntAttribute("tilewidth", &tileWidth);
	mapNode->QueryIntAttribute("tileheight", &tileHeight);
	size = Vector2(tileWidth, tileHeight);

	XMLElement* pTileset = mapNode->FirstChildElement("tileset");
	if (pTileset != NULL) {
		while (pTileset) {
			int firstgid;
			const char* source = pTileset->FirstChildElement("image")->Attribute("source");
			std::stringstream stream;
			stream << source;
			pTileset->QueryIntAttribute("firstgid", &firstgid);
			SDL_Texture* texture = SDL_CreateTextureFromSurface(graphics.getRenderer(),
				graphics.loadImage(stream.str()));
			tilesets.push_back(Tileset(texture, firstgid));
			pTileset = pTileset->NextSiblingElement("tileset");
		}
	}

	XMLElement* pLayer = mapNode->FirstChildElement("layer");
	if (pLayer != NULL) {
		while (pLayer) {
			XMLElement* pData = pLayer->FirstChildElement("data");
			if (pData != NULL) {
				while (pData) {
					XMLElement* pTile = pData->FirstChildElement("tile");
					if (pTile != NULL) {
						int tileCounter = 0;
						while (pTile) {
							//build each tile
							if (pTile->IntAttribute("gid") == 0) {
								tileCounter++;
								if (pTile->NextSiblingElement("tile")) {
									pTile = pTile->NextSiblingElement("tile");
									continue;
								}
								else {
									break;
								}
							}

							int gid = pTile->IntAttribute("gid");
							Tileset tileset;
							for (int i = 0; i < tilesets.size(); i++)
							{
								if (tilesets[i].firstgid <= gid) {
									tileset = tilesets.at(i);
									break;
								}
							}

							if (tileset.firstgid == -1) {
								tileCounter++;
								if (pTile->NextSiblingElement("tile")) {
									pTile = pTile->NextSiblingElement("tile");
									continue;
								}
								else {
									break;
								}
							}

							int xx = 0;
							int yy = 0;
							xx = tileCounter % width;
							xx *= tileWidth;
							yy += tileHeight * (tileCounter / width);
							Vector2 finalTilePositin = Vector2(xx, yy);

							int tilesetWidth, tilesetHeight;
							SDL_QueryTexture(tileset.texture, NULL, NULL, &tilesetWidth, &tilesetHeight);
							int tsxx = gid % (tilesetWidth / tileWidth) - 1;
							tsxx *= tileWidth;
							int tsyy = 0;
							int amount = (gid / (tilesetWidth / tileWidth));
							tsyy = tileHeight * amount;
							Vector2 finalTilesetPosition = Vector2(tsxx, tsyy);

							Tile tile(tileset.texture, 
								Vector2(tileWidth, tileHeight), finalTilesetPosition, finalTilePositin);
							tileList.push_back(tile);
							tileCounter++;


							pTile = pTile->NextSiblingElement("tile");
						}
					}
					pData = pData->NextSiblingElement("data");
				}
			}
			pLayer = pLayer->NextSiblingElement("layer");
		}
	}


	XMLElement* pObjectGroup = mapNode->FirstChildElement("objectgroup");
	if (pObjectGroup != NULL) {
		while (pObjectGroup) {
			const char* name = pObjectGroup->Attribute("name");
			std::stringstream stream;
			stream << name;
			if (stream.str() == "collisions") {
				XMLElement* pObject = pObjectGroup->FirstChildElement("object");
				if (pObject != NULL) {
					while (pObject) {
						float x, y, width, height;
						x = pObject->FloatAttribute("x");
						y = pObject->FloatAttribute("y");
						width = pObject->FloatAttribute("width");
						height = pObject->FloatAttribute("height");
						collisionRects.push_back(Rectangle(
							std::ceil(x) * globals::SPRITESCALE, 
							std::ceil(y) * globals::SPRITESCALE,
							std::ceil(width) * globals::SPRITESCALE,
							std::ceil(height) * globals::SPRITESCALE
						));
						pObject = pObject->NextSiblingElement("object");
					}
				}
			}
			//other object groups
			else if (stream.str() == "spawnpoints") {
				XMLElement* pObject = pObjectGroup->FirstChildElement("object");
				if (pObject != NULL) {
					while (pObject) {
						float x = pObject->FloatAttribute("x");
						float y = pObject->FloatAttribute("y");
						const char* name = pObject->Attribute("name");
						std::stringstream stream;
						stream << name;
						if (stream.str() == "player") {
							spawnPoint = Vector2(
								std::ceil(x) * globals::SPRITESCALE,
								std::ceil(y) * globals::SPRITESCALE);
						}
						pObject = pObject->NextSiblingElement("object");
					}
				}
			}
			pObjectGroup = pObjectGroup->NextSiblingElement("objectgroup");
		}
	}

}
