#include "Game.hpp"

//extern'd in tools.hpp
int WORLDHEIGHT = 64;
int WORLDWIDTH = 64;
int SCRHEIGHT = 0;
int SCRWIDTH = 0;

//implement random functions here
std::string toString(float num) {
	std::stringstream ss;
	ss << num;
	return ss.str();
}
