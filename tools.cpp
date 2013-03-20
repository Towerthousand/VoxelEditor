#include "Game.hpp"

//extern'd in tools.hpp
int SCRWIDTH = sf::VideoMode::getFullscreenModes()[0].width; //1366
int SCRHEIGHT = sf::VideoMode::getFullscreenModes()[0].height; //768
bool WINDOWFOCUS = false;
int WORLDHEIGHT = 16;
int WORLDWIDTH = 16;

//implement random functions here
std::string toString(float num) {
	std::stringstream ss;
	ss << num;
	return ss.str();
}
