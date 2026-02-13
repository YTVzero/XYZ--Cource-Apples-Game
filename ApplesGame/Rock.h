#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "Math.h"

struct Player;

namespace CatAndApples
{

	struct Rock
	{
		Position2D position;
		sf::Sprite sprite;
		sf::Texture texture;
	};

	void InitRock(Rock& rock);
	void CollisionWithRock(Rock* rock, Player& player, bool& isGameFinished, float& timeSinceGameFinish);
	void DrawRock(Rock* rock, sf::RenderWindow& window);
}
