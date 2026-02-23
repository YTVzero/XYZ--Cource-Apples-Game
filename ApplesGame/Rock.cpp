#include "Rock.h"
#include "Game.h"

namespace CatAndApples
{

	void InitRock(Rock& rock)
	{
		rock.position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);


		rock.texture.loadFromFile(RESOURCES_PATH + "rock.png");

		rock.sprite.setTexture(rock.texture);
		rock.sprite.setOrigin(rock.texture.getSize().x / 2.f, rock.texture.getSize().y / 2.f);
		rock.sprite.setPosition(rock.position.x, rock.position.y);
		sf::Vector2f targetSize(ROCK_SIZE, ROCK_SIZE);
		rock.sprite.setScale(targetSize.x / rock.sprite.getLocalBounds().width,
			targetSize.y / rock.sprite.getLocalBounds().height);
	}

	void CollisionWithRock(std::vector<Rock>& rocks, Player& player, bool& isGameFinished, float& timeSinceGameFinish)
	{
		for (Rock& rock : rocks)
		{
			if (IsRectanglesCollide(player.position, { PLAYER_SIZE / 2.5f, PLAYER_SIZE / 2.5f },
				rock.position, { ROCK_SIZE / 3.f, ROCK_SIZE / 1.2f }))
			{
				isGameFinished = true;
				timeSinceGameFinish = 0.f;
				player.sound.play();
			}
		}
	}

	void DrawRock(std::vector<Rock>& rocks, sf::RenderWindow& window)
	{
		for (Rock& rock : rocks)
		{
			rock.sprite.setPosition(rock.position.x, rock.position.y);
			window.draw(rock.sprite);
		}
	}
}
