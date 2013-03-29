#ifndef TOOLS_HPP
#define TOOLS_HPP

#define GL_GLEXT_PROTOTYPES 1
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <cmath>
#include <queue>
#include <Qt>
#include <algorithm>
#include "Math.hpp"

typedef sf::Vector3<float> vec3f;
typedef sf::Vector3<int> vec3i;
typedef sf::Vector2<float> vec2f;
typedef sf::Vector2<int> vec2i;

struct Vertex {
		Vertex(float vx = 0.0, float vy = 0.0, float vz = 0.0,
			   float nx = 0.0, float ny = 0.0, float nz = 0.0,
			   float cr = 1.0, float cg = 1.0, float cb = 1.0, float ca = 1.0) :
			vx(vx), vy(vy), vz(vz),
			nx(nx), ny(ny), nz(nz),
			cr(cr), cg(cg), cb(cb), ca(ca)
		{}
		float vx,vy,vz,
		nx,ny,nz,
		cr,cg,cb,ca;
};

struct Cube {
		Cube (bool isAir, vec3f color) : isAir(isAir), color(color) {}
		bool isAir;
		vec3f color;
};

//prototype random functions here (define in tools.cpp). Inlines go here too
inline void outLog(const std::string& msg) {
	std::cout << msg << std::endl;
}
std::string toString(float num);

#define MINLIGHT 1
#define DEG_TO_RAD ((2*M_PI)/360.0)
#define FOV 60.0 //degrees
#define ZNEAR 0.01f
#define ZFAR 500.0f
extern int SCRHEIGHT;
extern int SCRWIDTH;
extern int WORLDHEIGHT;
extern int WORLDWIDTH;

#endif // TOOLS_HPP
