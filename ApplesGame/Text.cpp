#include "Text.h"
#include "Game.h"
#include <sstream>

namespace CatAndApples
{
	void ScoreTextGame(Text& text, Game& game)
	{
		text.gameFont.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-ThinItalic.ttf");

		text.scoreText.setFont(text.gameFont);
		text.scoreText.setCharacterSize(25);
		text.scoreText.setFillColor(sf::Color::White);
		text.scoreText.setString("Score: " + std::to_string(game.numEatenApples));

		sf::FloatRect scoreFloatRect = text.scoreText.getLocalBounds();
		text.scoreText.setOrigin(scoreFloatRect.width / 2.f, scoreFloatRect.height / 2.f);
		text.scoreText.setPosition(SCREEN_WIDTH / 15.f, SCREEN_HEIGHT / 30.f);

	}

	void GameOverTextGame(Text& text, Game& game)
	{
		text.gameFont.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-ThinItalic.ttf");

		text.gameOverText.setFont(text.gameFont);
		text.gameOverText.setCharacterSize(60);
		text.gameOverText.setStyle(sf::Text::Bold);
		text.gameOverText.setFillColor(sf::Color::Red);
		text.gameOverText.setString("GAME OVER");

		sf::FloatRect gameOverFloatRect = text.gameOverText.getLocalBounds();
		text.gameOverText.setOrigin(gameOverFloatRect.width / 2.f, gameOverFloatRect.height / 2.f);
		text.gameOverText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 3.3f);
	}

	void ManualTextGame(Text& text, Game& game)
	{
		text.gameFont.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-ThinItalic.ttf");

		text.manualText.setFont(text.gameFont);
		text.manualText.setCharacterSize(20);
		text.manualText.setFillColor(sf::Color::White);
		text.manualText.setString("Movements:\nW - Up\nA - Left\nD - Right\nS - Down\nEscape - Exit");

		sf::FloatRect ManualFloatRect = text.manualText.getLocalBounds();
		text.manualText.setOrigin(ManualFloatRect.width / 2.f, ManualFloatRect.height / 2.f);
		text.manualText.setPosition(SCREEN_WIDTH / 15.f, SCREEN_HEIGHT / 1.15f);
	}

	void ExitOrContTextGame(Text& text, Game& game)
	{
		text.gameFont.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-ThinItalic.ttf");

		text.exitOrContText.setFont(text.gameFont);
		text.exitOrContText.setCharacterSize(30);
		text.exitOrContText.setStyle(sf::Text::Bold);
		text.exitOrContText.setFillColor(sf::Color::Green);
		text.exitOrContText.setString("press ENTER to continue or ESCAPE to exit");

		sf::FloatRect ExitOrContFloatRect = text.exitOrContText.getLocalBounds();
		text.exitOrContText.setOrigin(ExitOrContFloatRect.width / 2.f, ExitOrContFloatRect.height / 2.f);
		text.exitOrContText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 1.4f);
	}

	void MenuText(Text& text, Game& game)
	{
		text.gameFont.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-ThinItalic.ttf");

		text.menuText.setFont(text.gameFont);
		text.menuText.setCharacterSize(40);
		text.menuText.setStyle(sf::Text::Bold);
		text.menuText.setFillColor(sf::Color::White);
		text.menuText.setOutlineThickness(3);
		text.menuText.setOutlineColor(sf::Color::Green);
	

		sf::FloatRect menuTextRect = text.menuText.getLocalBounds();
		text.menuText.setOrigin(menuTextRect.width / 2.f, menuTextRect.height / 2.f);
		text.menuText.setPosition(SCREEN_WIDTH / 5.f, SCREEN_HEIGHT / 5.f);
	}

	void LeaderboardTextGame(Text& text, Game& game)
	{
		text.gameFont.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-ThinItalic.ttf");
		
		std::ostringstream leaderboardStr;
		leaderboardStr << "===== LEADERBOARD =====\n";

		const auto& records = game.leaderboard.GetSortedRecords();
		for (int i = 0; i < records.size(); ++i)
		{
			leaderboardStr << i + 1 << "." << records[i].name << " ";


			int dotsCount = 15 - records[i].name.length();
			for (int j = 0; j < dotsCount; ++j)
			{
				leaderboardStr << ".";
			}

			leaderboardStr << " " << records[i].score << "\n";
		}

		leaderboardStr << "===========================\n";
		leaderboardStr << "You score: "<<game.numEatenApples;

		text.leaderboardText.setFont(text.gameFont);
		text.leaderboardText.setCharacterSize(25);
		text.leaderboardText.setFillColor(sf::Color::Yellow);
		text.leaderboardText.setOutlineThickness(1);
		text.leaderboardText.setOutlineColor(sf::Color::White);
		text.leaderboardText.setString(leaderboardStr.str());

		sf::FloatRect leaderboardRect = text.leaderboardText.getLocalBounds();
		text.leaderboardText.setOrigin(leaderboardRect.width / 2.f, leaderboardRect.height / 2.f);
		text.leaderboardText.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);

	}

	void DrawStaticText(Text& text,sf::RenderWindow& window)
	{
		window.draw(text.scoreText);
		window.draw(text.manualText);
	}

	void DrawDinamicText(Text& text, sf::RenderWindow& window)
	{
		window.draw(text.gameOverText);
		window.draw(text.exitOrContText);
	}

	void DrawLeaderboardText(Text& text, sf::RenderWindow& window)
	{
		window.draw(text.leaderboardText);
	}

}