#include "Selection.hpp"

Selection::Selection() : markedForRedraw(false), firstSelected(-1,-1,-1), secondSelected(-1,-1,-1), VBOID(2){
}

Selection::~Selection() {
}

void Selection::update(float deltaTime) {
	if(markedForRedraw) {
		renderData.resize(0);
		for(uint i = 0; i != cubes.size(); ++i) {
			pushCubeToArray(cubes[i].x,cubes[i].y,cubes[i].z);
		}
		makeVbo();
	}
}

void Selection::draw() const {
	glBindBuffer(GL_ARRAY_BUFFER, VBOID);
	glPushMatrix();
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_POLYGON_OFFSET_FILL);
	//glPolygonOffset(1.0,1.0);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), 0);
	glNormalPointer(GL_FLOAT, sizeof(Vertex),(GLvoid*)(3*sizeof(float)));
	glColorPointer(4, GL_FLOAT, sizeof(Vertex), (GLvoid*)(6*sizeof(float)));

	glDrawArrays(GL_QUADS, 0, renderData.size());

	glPolygonOffset(0,0);
	glDisableClientState(GL_POLYGON_OFFSET_FILL);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Selection::addCube(int x, int y, int z) {
	for(uint i = 0; i < cubes.size(); ++i)
		if (cubes[i] == vec3i(x,y,z))
			return;
	cubes.push_back(vec3i(x,y,z));
	markedForRedraw = true;
}

void Selection::deleteCube(int x, int y, int z) {
	for(uint i = 0; i < cubes.size(); ++i)
		if (cubes[i] == vec3i(x,y,z)) {
			cubes.erase(cubes.begin()+i);
			markedForRedraw = true;
			return;
		}
}

void Selection::deleteAll() {
	cubes.resize(0);
	markedForRedraw = true;
}

//STRUCTURE PER VERTEX: Vx,Vy,Vz,
//						Nx,Ny,Nz,
//						Cr,Cg,Cb,Ca
void Selection::pushCubeToArray(int x, int y, int z) {
	vec3f color(0,0,0);
	float alpha = 0.3;
	bool paint = true;

	for(uint i = 0; i < cubes.size(); ++i)
		if (cubes[i] == vec3i(x,y-1,z)) {
			paint = false;
			break;
		}
	if(paint) {
		renderData.push_back(Vertex(x+1,y  ,z  , 0,-1,0,color.x,color.y,color.z,alpha));
		renderData.push_back(Vertex(x+1,y  ,z+1, 0,-1,0,color.x,color.y,color.z,alpha));
		renderData.push_back(Vertex(x  ,y  ,z+1, 0,-1,0,color.x,color.y,color.z,alpha));
		renderData.push_back(Vertex(x  ,y  ,z  , 0,-1,0,color.x,color.y,color.z,alpha));
	}
	paint = true;

	for(uint i = 0; i < cubes.size(); ++i)
		if (cubes[i] == vec3i(x,y+1,z)) {
			paint = false;
			break;
		}
	if(paint) {
		renderData.push_back(Vertex(x  ,y+1,z  , 0,1,0,color.x,color.y,color.z,alpha));
		renderData.push_back(Vertex(x  ,y+1,z+1, 0,1,0,color.x,color.y,color.z,alpha));
		renderData.push_back(Vertex(x+1,y+1,z+1, 0,1,0,color.x,color.y,color.z,alpha));
		renderData.push_back(Vertex(x+1,y+1,z  , 0,1,0,color.x,color.y,color.z,alpha));
	}
	paint = true;

	for(uint i = 0; i < cubes.size(); ++i)
		if (cubes[i] == vec3i(x-1,y,z)) {
			paint = false;
			break;
		}
	if(paint) {
		renderData.push_back(Vertex(x  ,y  ,z+1, -1,0,0,color.x,color.y,color.z,alpha));
		renderData.push_back(Vertex(x  ,y+1,z+1, -1,0,0,color.x,color.y,color.z,alpha));
		renderData.push_back(Vertex(x  ,y+1,z  , -1,0,0,color.x,color.y,color.z,alpha));
		renderData.push_back(Vertex(x  ,y  ,z  , -1,0,0,color.x,color.y,color.z,alpha));
	}
	paint = true;

	for(uint i = 0; i < cubes.size(); ++i)
		if (cubes[i] == vec3i(x+1,y,z)) {
			paint = false;
			break;
		}
	if(paint) {
		renderData.push_back(Vertex(x+1,y  ,z  , -1,0,0,color.x,color.y,color.z,alpha));
		renderData.push_back(Vertex(x+1,y+1,z  , -1,0,0,color.x,color.y,color.z,alpha));
		renderData.push_back(Vertex(x+1,y+1,z+1, -1,0,0,color.x,color.y,color.z,alpha));
		renderData.push_back(Vertex(x+1,y  ,z+1, -1,0,0,color.x,color.y,color.z,alpha));
	}
	paint = true;

	for(uint i = 0; i < cubes.size(); ++i)
		if (cubes[i] == vec3i(x,y,z-1)) {
			paint = false;
			break;
		}
	if(paint) {
		renderData.push_back(Vertex(x  ,y+1,z  , 0,0,-1,color.x,color.y,color.z,alpha));
		renderData.push_back(Vertex(x+1,y+1,z  , 0,0,-1,color.x,color.y,color.z,alpha));
		renderData.push_back(Vertex(x+1,y  ,z  , 0,0,-1,color.x,color.y,color.z,alpha));
		renderData.push_back(Vertex(x  ,y  ,z  , 0,0,-1,color.x,color.y,color.z,alpha));
	}
	paint = true;

	for(uint i = 0; i < cubes.size(); ++i)
		if (cubes[i] == vec3i(x,y,z+1)) {
			paint = false;
			break;
		}
	if(paint) {
		renderData.push_back(Vertex(x  ,y  ,z+1, 0,0,1,color.x,color.y,color.z,alpha));
		renderData.push_back(Vertex(x+1,y  ,z+1, 0,0,1,color.x,color.y,color.z,alpha));
		renderData.push_back(Vertex(x+1,y+1,z+1, 0,0,1,color.x,color.y,color.z,alpha));
		renderData.push_back(Vertex(x  ,y+1,z+1, 0,0,1,color.x,color.y,color.z,alpha));
	}
}

void Selection::makeVbo() {
	glGenBuffers(1, (GLuint*) &VBOID);
	glBindBuffer(GL_ARRAY_BUFFER, VBOID);
	glBufferData(GL_ARRAY_BUFFER, renderData.size()*sizeof(Vertex), &renderData[0], GL_STATIC_DRAW);
}

