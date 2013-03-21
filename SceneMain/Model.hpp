#ifndef CHUNK_HPP
#define CHUNK_HPP
#include "tools.hpp"

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
		void traceView(const Camera& player, float tMax);

		bool outOfView;
		bool markedForRedraw;
		bool playerTargetsBlock;
		vec3f last;
		vec3f targetedBlock;
		std::vector<std::vector<std::vector<Cube> > > cubes;
	private:
		void pushCubeToArray(int x, int y, int z);
		void makeVbo();

		int VBOID;

		static const float colorIndexes[9][3];
		std::vector<Vertex> renderData;
};

#endif // CHUNK_HPP
