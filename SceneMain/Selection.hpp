#ifndef SELECTION_HPP
#define SELECTION_HPP
#include "tools.hpp"

class Selection
{
	public:
		Selection();
		~Selection();

		void update(float deltaTime);
		void draw() const;

		void addCube(int x, int y, int z);
		void deleteCube(int x, int y, int z);
		void deleteAll();

		void pushCubeToArray(int x, int y, int z);
		void makeVbo();

		bool markedForRedraw;
		vec3i firstSelected;
		vec3i secondSelected;

	private:
		int VBOID;
		std::vector<vec3i> cubes;
		std::vector<Vertex> renderData;
};

#endif // SELECTION_HPP
