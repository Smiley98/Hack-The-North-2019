#pragma once
#include "GameEngine\EntitySystem\Entity.h"
#include <SFML/System/Vector2.hpp>

#include <vector>

namespace Game
{
	//Used for storing and controling all game related entities, as well as providing an entry point for the "game" side of application	
	class PlayerEntity;

	class GameBoard
	{
	public:
		GameBoard();
		virtual ~GameBoard();


		void Update();		
		bool IsGameOver() { return false; }
		sf::Vector2i GetPlayerPosition() { return sf::Vector2i(static_cast<int>(m_player->GetPos().x), static_cast<int>(m_player->GetPos().y)); }

	private:
		void CreatePlayer();
		GameEngine::Entity* m_player;
	};
}

