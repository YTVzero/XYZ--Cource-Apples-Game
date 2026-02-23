#include "Apple.h"
#include "Game.h"

namespace CatAndApples
{

	void InitApple(Apple& apple)
	{
		apple.position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);

		AppleSound(apple);
		
		apple.texture.loadFromFile(RESOURCES_PATH + "apple.png");

		apple.sprite.setTexture(apple.texture);
		apple.sprite.setOrigin(apple.texture.getSize().x /2.f, apple.texture.getSize().y/2.f);
		apple.sprite.setPosition(apple.position.x, apple.position.y);
		sf::Vector2f targetSize(APPLE_SIZE, APPLE_SIZE);
		apple.sprite.setScale(targetSize.x / apple.sprite.getLocalBounds().width,
			targetSize.y / apple.sprite.getLocalBounds().height);
	}
	
	void AppleSound(Apple& apple)
	{
		apple.buffer.loadFromFile(RESOURCES_PATH + "apple_eat.wav");
		apple.sound.setBuffer(apple.buffer);
	}

	void CollisionWithApple(std::vector<Apple>& apples, Player& player, int& numEatenApples, unsigned int gameMode)
	{
		for (Apple& apple : apples)
		{
			if (IsCirclesCollide(player.position, PLAYER_SIZE / 2.f,
				apple.position, APPLE_SIZE / 4.f))
			{
				apple.position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
				++numEatenApples;
				if ((gameMode & MODE_ACCELERATION) && !(gameMode & MODE_WITHOUT_ACCELERATION))
				{
					player.speed += ACCELERATION;
				}
				apple.sound.play();
			}
		}
	}

	void DrawApple(std::vector<Apple>& apples, sf::RenderWindow& window)
	{
		for (Apple& apple : apples)
		{
			apple.sprite.setPosition(apple.position.x, apple.position.y);
			window.draw(apple.sprite);
		}

	}
}
