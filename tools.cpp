#include "Game.hpp"

//extern'd in tools.hpp
int WORLDHEIGHT = 1;
int WORLDWIDTH = 1;
int WORLDDEPTH = 1;
int SCRHEIGHT = 0;
int SCRWIDTH = 0;

//implement random functions here
std::string toString(float num) {
	std::stringstream ss;
	ss << num;
	return ss.str();
}

Cube::Cube(bool isAir, vec3f color) : isAir(isAir), color(color) {
}

Cube::Cube (const CubeFileFormat& c) : isAir(c.isAir) , color(c.r/255.0,c.g/255.0,c.b/255.0){
}

CubeFileFormat::CubeFileFormat(const Cube &c): r(c.color.x*255), g(c.color.y*255), b(c.color.z*255), isAir(c.isAir){
}
