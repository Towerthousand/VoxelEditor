#ifndef CHUNK_HPP
#define CHUNK_HPP
#include "../tools.hpp"

class Camera;
class Model { //16*16*128
	public:
		Model();
		~Model();
		//main
		void update(float deltaTime);
		void draw() const;

		//Getters & consultors
		bool getOutOfBounds(int x, int y, int z) const;
		Cube getCube(int x, int y, int z) const;
		void setCube(int x, int y, int z, Cube c);
		void traceView(const vec3f &pos, const vec2f &rot, float tMax);

		bool markedForRedraw;
		bool playerTargetsCube; //is the view of the player colliding with a Cube that's not air?
		vec3i targetedCube; //if playerTargetsCube, targetedCube = first Cube in player's view that is not air
		vec3i last; //if playerTargetsCube, last = the Cube next to targetedCube at the face that the view ray entered
		std::vector<std::vector<std::vector<Cube> > > cubes;
	private:
		void drawWireCube(int x, int y, int z) const;
		void pushCubeToArray(int x, int y, int z);
		void makeVbo();
		void drawCube(int x, int y, int z) const;
		void drawWorldBox() const;

		int VBOID;

		std::vector<Vertex> renderData;
		static const int vertexPoints[24][3]; //ESTO ES SIDA, A.K.A LAS LINEAS DE LOS VERTICES DE UN CUBO
};

#endif // CHUNK_HPP
