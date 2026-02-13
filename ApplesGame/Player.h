#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Constants.h"
#include "Math.h"

namespace CatAndApples
{

	enum class PlayerDirection
	{
		Right = 0,
		Up,
		Left,
		Down
	};

	struct Player
	{
		Position2D position;
		float speed = INITIAL_SPEED;
		PlayerDirection direction = PlayerDirection::Right;
		sf::Sprite sprite;
		sf::Texture texture;
		sf::SoundBuffer buffer;
		sf::Sound sound;
	};

	void InitPlayer(Player& player);
	void PlayerControl(Player& player, float deltaTime);
	void PlayerSoung(Player& player);
	void CollisionPlayerWithBounds(Player& player, bool& isGameFinished, float& timeSinceGameFinish);
	void DrawPlayer(Player& player, sf::RenderWindow& window);
}
