#include "Map.h"
#include "GameEngine/GameEngineMain.h"
#include "GameEngine/EntitySystem/Entity.h"
#include "GameEngine/EntitySystem/Components/SpriteRenderComponent.h"
#include <cassert>
#include <cstdio>

namespace {
	const unsigned int g_rows = 16;
	const unsigned int g_cols = 16;
	/*TileType*/unsigned int g_tiles[g_rows][g_cols] = {
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	};
}

Map& Map::getInstance()
{
	static Map map;
	return map;
}

eTileType Map::getTileType(unsigned int x, unsigned int y)
{
	assert(x >= 0 && y >= 0 && x < g_cols && y < g_rows);
	return static_cast<eTileType>(g_tiles[y][x]);
}

/*
GameEngine::eTexture::type Map::getTileTexture(unsigned int x, unsigned int y)
{
	return getTypeShared(x, y).m_texture;
}

sf::Color Map::getTileColor(unsigned int x, unsigned int y)
{
	return getTypeShared(x, y).m_color;
}
*/

sf::Vector2u Map::getTilePosition(unsigned int x, unsigned int y)
{
	//Do this just to ensure we don't go out of bounds.
	getTileType(x, y);
	return sf::Vector2u{ Tile::s_allShared.m_width * x, Tile::s_allShared.m_height * y };
}

//Call this at the start of MainGame::Update().
void Map::render()
{
	sf::RenderTarget * target = const_cast<sf::RenderTarget*>(GameEngine::GameEngineMain::GetInstance()->getRenderTarget());
	const TileAllShared& allShared = Tile::s_allShared;
	for (unsigned int i = 0; i < g_rows; i++) {
		for (unsigned int j = 0; j < g_cols; j++) {
			getTypeShared(j, i).m_sprite.setPosition((sf::Vector2f(getTilePosition(j, i))));
			target->draw(getTypeShared(j, i).m_sprite);
		}
	}
}

Map::Map()
{
	//Define different globally shared tile attributes here.
	TileAllShared& allShared = Tile::s_allShared;
	// allShared.m_width = GameEngine::GameEngineMain::WINDOW_WIDTH / g_cols;
	// allShared.m_height = GameEngine::GameEngineMain::WINDOW_HEIGHT / g_rows;
	allShared.m_width = 100;
	allShared.m_height = 100;

	//Define and wire different type-shared tile attributes here.
	Tile::s_typeShared[GRASS].m_sprite.setTexture(*GameEngine::TextureManager::GetInstance()->GetTexture(GameEngine::eTexture::Tile_grass));
	Tile::s_typeShared[FOREST].m_sprite.setTexture(*GameEngine::TextureManager::GetInstance()->GetTexture(GameEngine::eTexture::Tile_forest));
	Tile::s_typeShared[MOUNTAIN].m_sprite.setTexture(*GameEngine::TextureManager::GetInstance()->GetTexture(GameEngine::eTexture::Tile_mountain));
}

Map::~Map()
{
}

inline TileTypeShared& Map::getTypeShared(unsigned int x, unsigned int y)
{
	return Tile::s_typeShared[getTileType(x, y)];
}
