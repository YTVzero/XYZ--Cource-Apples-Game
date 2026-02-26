#pragma once
#include<SFML/Graphics.hpp>

namespace CatAndApples
{
	struct Game;
	struct Text
	{
		sf::Font gameFont;
		sf::Text gameOverText;
		sf::Text scoreText;
		sf::Text manualText;
		sf::Text exitOrContText;
		sf::Text menuText;
		sf::Text leaderboardText;
		sf::Text playerScoreText;
		sf::Text pauseExitText;
	};
	void ScoreTextGame(Text& text, Game& game);
	void GameOverTextGame(Text& text, Game& game);
	void MenuText(Text& text, Game& game);
	void ManualTextGame(Text& text, Game& game);
	void ExitOrContTextGame(Text& text, Game& game);
	void LeaderboardTextGame(Text& text, Game& game);
	void PauseExitText(Text& text, Game& game);
	void DrawStaticText(Text& text, sf::RenderWindow& window);
	void DrawDinamicText(Text& text, sf::RenderWindow& window);
	void DrawLeaderboardText(Text& text, sf::RenderWindow& window);
	void DrawPauseExitText(Text& text, sf::RenderWindow& window);
}