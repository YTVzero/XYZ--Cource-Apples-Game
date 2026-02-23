#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Math.h"
#include "Constants.h"

struct Player;

namespace CatAndApples
{
	
	struct Apple
	{
		Position2D position;
		sf::Sprite sprite;
		sf::Texture texture;
		sf::SoundBuffer buffer;
		sf::Sound sound;

		Apple() = default;
		Apple(const Apple&) = delete;
		Apple& operator=(const Apple&) = delete;
		Apple(Apple&&) = default;
		Apple& operator=(Apple&&) = default;
			
	};

	void InitApple(Apple& apple);
	void AppleSound(Apple& apple);
	void CollisionWithApple(std::vector<Apple>& apples, Player& player, int& numEatenApples, unsigned int gameMode);
	void DrawApple(std::vector<Apple>& apples, sf::RenderWindow& window);
}
