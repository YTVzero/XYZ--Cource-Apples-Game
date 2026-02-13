#include "Player.h"
#include "Game.h"
#include <iostream>

namespace CatAndApples
{

	void InitPlayer(Player& player)
	{
		// Init player state
		player.position = { SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f };
		player.speed = INITIAL_SPEED;
		player.direction = PlayerDirection::Right;

		PlayerSoung(player);

		player.texture.loadFromFile(RESOURCES_PATH + "player.png");

		//Sprite player
		player.sprite.setTexture(player.texture);
		player.sprite.setOrigin(player.texture.getSize().x / 2.f, player.texture.getSize().y / 2.f);
		player.sprite.setPosition(player.position.x,player.position.y);
		sf::Vector2f targetSize(PLAYER_SIZE, PLAYER_SIZE);
		player.sprite.setScale(targetSize.x / player.sprite.getLocalBounds().width,
			targetSize.y / player.sprite.getLocalBounds().height);

	}

	void PlayerSoung(Player& player)
	{
		player.buffer.loadFromFile(RESOURCES_PATH + "punch.wav");
		player.sound.setBuffer(player.buffer);
	}

	void PlayerControl(Player& player, float deltaTime)
	{
		// Handle input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			player.direction = PlayerDirection::Right;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			player.direction = PlayerDirection::Up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			player.direction = PlayerDirection::Left;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			player.direction = PlayerDirection::Down;
		}
		// Update player state
		switch (player.direction)
		{
		case PlayerDirection::Right:
		{
			player.position.x += player.speed * deltaTime;
			player.sprite.setRotation(90);
			break;
		}
		case PlayerDirection::Up:
		{
			player.position.y -= player.speed * deltaTime;
			player.sprite.setRotation(0);
			break;
		}
		case PlayerDirection::Left:
		{
			player.position.x -= player.speed * deltaTime;
			player.sprite.setRotation(-90);
			break;
		}
		case PlayerDirection::Down:
		{
			player.position.y += player.speed * deltaTime;
			player.sprite.setRotation(0);
			break;
		}
		}
	}
	void CollisionPlayerWithBounds(Player& player, bool& isGameFinished, float& timeSinceGameFinish)
	{
		if (player.position.x - PLAYER_SIZE / 2.f < 0.f || player.position.x + PLAYER_SIZE / 2.f > SCREEN_WIDTH ||
			player.position.y - PLAYER_SIZE / 2.f < 0.f || player.position.y + PLAYER_SIZE / 2.f > SCREEN_HEIGHT)
		{
			isGameFinished = true;
			timeSinceGameFinish = 0.f;
			player.sound.play();
		}
	}

	void DrawPlayer(Player& player, sf::RenderWindow& window)
	{
		player.sprite.setPosition(player.position.x, player.position.y);
		window.draw(player.sprite);
	}
	
}