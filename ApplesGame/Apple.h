#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
			
	};

	void InitApple(Apple& apple);
	void AppleSound(Apple& apple);
	void CollisionWithApple(Apple* apples, int numApples, Player& player, int& numEatenApples, unsigned int gameMode);
	void DrawApple(Apple* apples, int numApples, sf::RenderWindow& window);
}
