#pragma once
#include <string>

namespace CatAndApples
{
	//initial data
	const std::string RESOURCES_PATH = "Resources/";

	const int SCREEN_WIDTH = 1000;
	const int SCREEN_HEIGHT = 800;

	const float INITIAL_SPEED = 100.f;
	const float PLAYER_SIZE = 80.f;
	const float ACCELERATION = 50.f;

	const float APPLE_SIZE = 70.f;

	const int NUM_ROCKS = 10;
	const float ROCK_SIZE = 150.f;

	const float PAUSE_LENGTH = 0.5f;

	//bit flags
	constexpr unsigned int MODE_NORMAL_APPLES = 1 << 0;
	constexpr unsigned int MODE_MANY_APPLES = 1 << 1;
	constexpr unsigned int MODE_RANDOM_APPLES = 1 << 2;
	constexpr unsigned int MODE_ACCELERATION = 1 << 3;
	constexpr unsigned int MODE_WITHOUT_ACCELERATION = 1 << 4;
	
}