#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
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

		Rock() = default;
		Rock(const Rock&) = delete;
		Rock& operator=(const Rock&) = delete;
		Rock(Rock&&) = default;
		Rock& operator=(Rock&&) = default;
	};

	void InitRock(Rock& rock);
	void CollisionWithRock(std::vector<Rock>& rocks, Player& player, bool& isGameFinished, float& timeSinceGameFinish);
	void DrawRock(std::vector<Rock>& rocks, sf::RenderWindow& window);
}
