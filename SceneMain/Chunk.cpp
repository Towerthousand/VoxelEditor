#include "Chunk.hpp"
#include "Camera.hpp"

Chunk::Chunk() :
	outOfView(false), markedForRedraw(false),
	playerTargetsBlock(false), last(0,0,0), targetedBlock(0,0,0),
	cubes(WORLDWIDTH,std::vector<std::vector<Cube> >
		  (WORLDHEIGHT,std::vector<Cube>
		   (WORLDWIDTH,Cube(true,vec3f(0,0,0))))),
	VBOID(1) {
}

Chunk::~Chunk() {
}

bool Chunk::getOutOfBounds(int x, int y, int z) const {
	if (x >= WORLDWIDTH || x < 0
		|| y >= WORLDHEIGHT || y < 0
		|| z >= WORLDWIDTH || z< 0)
		return true;
	return false;
}

Cube Chunk::getCube(int x, int y, int z) const {
	if (getOutOfBounds(x,y,z))
		return Cube(true,vec3f(0,0,0));
	return cubes[x][y][z];
}

void Chunk::setCube(int x, int y, int z, Cube c) {
	if (getOutOfBounds(x,y,z))
		return;
	markedForRedraw = true;
	cubes[x][y][z] = c;
}

void Chunk::update(float deltaTime) {
	//empty arrays and re-do them
	markedForRedraw = false;
	renderData.resize(0);
	for(int z = 0; z < WORLDWIDTH; ++z) {
		for(int y = 0; y < WORLDHEIGHT; ++y) {
			for(int x = 0; x < WORLDWIDTH; ++x) {
				if (!getCube(x,y,z).isAir) { // only draw if it's not air
					pushCubeToArray(x,y,z);
				}
			}
		}
	}
	makeVbo();
}

void Chunk::draw() const {
	glBindBuffer(GL_ARRAY_BUFFER, VBOID);
	glPushMatrix();
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), 0);
	glNormalPointer(GL_FLOAT, sizeof(Vertex),(GLvoid*)(3*sizeof(float)));
	glColorPointer(4, GL_FLOAT, sizeof(Vertex), (GLvoid*)(6*sizeof(float)));

	glDrawArrays(GL_TRIANGLES, 0, renderData.size());

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Chunk::pushCubeToArray(int x,int y, int z) { //I DON'T KNOW HOW TO MAKE THIS COMPACT
	float lindA = 1.0,lindB = 1.0,lindC = 1.0,lindD = 1.0, lindE = 1.0;
	//STRUCTURE PER VERTEX: Vx,Vy,Vz,
	//						Nx,Ny,Nz,
	//						Tx,Ty,
	//						Cr,Cg,Cb,Ca
	if(getCube(x,y,z+1).isAir) { // front face
		//if it's not a ID (ID should be fully lit) calculate the average of the adjacent
		//air blocks and assign max(max(average,adjacentBlock.isAir/2),MINID)
		lindA = (getCube(x,y,z+1).isAir + getCube(x,y+1,z+1).isAir +
				 getCube(x-1,y,z+1).isAir + getCube(x-1,y+1,z+1).isAir)/4.0;
		lindB = (getCube(x,y,z+1).isAir + getCube(x,y-1,z+1).isAir +
				 getCube(x-1,y,z+1).isAir + getCube(x-1,y-1,z+1).isAir)/4.0;
		lindC = (getCube(x,y,z+1).isAir + getCube(x,y-1,z+1).isAir +
				 getCube(x+1,y,z+1).isAir + getCube(x+1,y-1,z+1).isAir)/4.0;
		lindD = (getCube(x,y,z+1).isAir + getCube(x,y+1,z+1).isAir +
				 getCube(x+1,y,z+1).isAir + getCube(x+1,y+1,z+1).isAir)/4.0;
		lindA = std::fmax(lindA,getCube(x+1,y,z).isAir/3.0);
		lindB = std::fmax(lindB,getCube(x+1,y,z).isAir/3.0);
		lindC = std::fmax(lindC,getCube(x+1,y,z).isAir/3.0);
		lindD = std::fmax(lindD,getCube(x+1,y,z).isAir/3.0);
		lindE = (lindA+lindB+lindC+lindD)/4.0;
		//t1
		renderData.push_back(Vertex(x+1.0, y+1.0, z+1.0, 0,0,-1, lindD*getCube(x,y,z).color.x,lindD*getCube(x,y,z).color.y,lindD*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x    , y+1.0, z+1.0, 0,0,-1, lindA*getCube(x,y,z).color.x,lindA*getCube(x,y,z).color.y,lindA*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x+0.5, y+0.5, z+1.0, 0,0,-1, lindE*getCube(x,y,z).color.x,lindE*getCube(x,y,z).color.y,lindE*getCube(x,y,z).color.z,1.0));
		//t2
		renderData.push_back(Vertex(x+1.0, y    , z+1.0, 0,0,-1, lindC*getCube(x,y,z).color.x,lindC*getCube(x,y,z).color.y,lindC*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x+1.0, y+1.0, z+1.0, 0,0,-1, lindD*getCube(x,y,z).color.x,lindD*getCube(x,y,z).color.y,lindD*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x+0.5, y+0.5, z+1.0, 0,0,-1, lindE*getCube(x,y,z).color.x,lindE*getCube(x,y,z).color.y,lindE*getCube(x,y,z).color.z,1.0));
		//t3
		renderData.push_back(Vertex(x    , y    , z+1.0, 0,0,-1, lindB*getCube(x,y,z).color.x,lindB*getCube(x,y,z).color.y,lindB*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x+1.0, y    , z+1.0, 0,0,-1, lindC*getCube(x,y,z).color.x,lindC*getCube(x,y,z).color.y,lindC*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x+0.5, y+0.5, z+1.0, 0,0,-1, lindE*getCube(x,y,z).color.x,lindE*getCube(x,y,z).color.y,lindE*getCube(x,y,z).color.z,1.0));
		//t4
		renderData.push_back(Vertex(x    , y+1.0, z+1.0, 0,0,-1, lindA*getCube(x,y,z).color.x,lindA*getCube(x,y,z).color.y,lindA*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x    , y    , z+1.0, 0,0,-1, lindB*getCube(x,y,z).color.x,lindB*getCube(x,y,z).color.y,lindB*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x+0.5, y+0.5, z+1.0, 0,0,-1, lindE*getCube(x,y,z).color.x,lindE*getCube(x,y,z).color.y,lindE*getCube(x,y,z).color.z,1.0));
	}
	if(getCube(x,y,z-1).isAir) { // back face
		lindA = (getCube(x,y,z-1).isAir + getCube(x,y+1,z-1).isAir +
				 getCube(x+1,y,z-1).isAir + getCube(x+1,y+1,z-1).isAir)/4.0;
		lindB = (getCube(x,y,z-1).isAir + getCube(x,y-1,z-1).isAir +
				 getCube(x+1,y,z-1).isAir + getCube(x+1,y-1,z-1).isAir)/4.0;
		lindC = (getCube(x,y,z-1).isAir + getCube(x,y-1,z-1).isAir +
				 getCube(x-1,y,z-1).isAir + getCube(x-1,y-1,z-1).isAir)/4.0;
		lindD = (getCube(x,y,z-1).isAir + getCube(x,y+1,z-1).isAir +
				 getCube(x-1,y,z-1).isAir + getCube(x-1,y+1,z-1).isAir)/4.0;
		lindA = std::fmax(lindA,getCube(x+1,y,z).isAir/3.0);
		lindB = std::fmax(lindB,getCube(x+1,y,z).isAir/3.0);
		lindC = std::fmax(lindC,getCube(x+1,y,z).isAir/3.0);
		lindD = std::fmax(lindD,getCube(x+1,y,z).isAir/3.0);
		lindE = (lindA+lindB+lindC+lindD)/4.0;
		//t1
		renderData.push_back(Vertex(x    , y+1.0, z    , 0,0,-1, lindD*getCube(x,y,z).color.x,lindD*getCube(x,y,z).color.y,lindD*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x+1.0, y+1.0, z    , 0,0,-1, lindA*getCube(x,y,z).color.x,lindA*getCube(x,y,z).color.y,lindA*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x+0.5, y+0.5, z    , 0,0,-1, lindE*getCube(x,y,z).color.x,lindE*getCube(x,y,z).color.y,lindE*getCube(x,y,z).color.z,1.0));
		//t2
		renderData.push_back(Vertex(x+1.0, y+1.0, z    , 0,0,-1, lindA*getCube(x,y,z).color.x,lindA*getCube(x,y,z).color.y,lindA*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x+1.0, y    , z    , 0,0,-1, lindB*getCube(x,y,z).color.x,lindB*getCube(x,y,z).color.y,lindB*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x+0.5, y+0.5, z    , 0,0,-1, lindE*getCube(x,y,z).color.x,lindE*getCube(x,y,z).color.y,lindE*getCube(x,y,z).color.z,1.0));
		//t3
		renderData.push_back(Vertex(x+1.0, y    , z    , 0,0,-1, lindB*getCube(x,y,z).color.x,lindB*getCube(x,y,z).color.y,lindB*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x    , y    , z    , 0,0,-1, lindC*getCube(x,y,z).color.x,lindC*getCube(x,y,z).color.y,lindC*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x+0.5, y+0.5, z    , 0,0,-1, lindE*getCube(x,y,z).color.x,lindE*getCube(x,y,z).color.y,lindE*getCube(x,y,z).color.z,1.0));
		//t4
		renderData.push_back(Vertex(x    , y    , z    , 0,0,-1, lindC*getCube(x,y,z).color.x,lindC*getCube(x,y,z).color.y,lindC*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x    , y+1.0, z    , 0,0,-1, lindD*getCube(x,y,z).color.x,lindD*getCube(x,y,z).color.y,lindD*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x+0.5, y+0.5, z    , 0,0,-1, lindE*getCube(x,y,z).color.x,lindE*getCube(x,y,z).color.y,lindE*getCube(x,y,z).color.z,1.0));
	}
	if(getCube(x+1,y,z).isAir) { // left face
		lindA = (getCube(x+1,y,z).isAir + getCube(x+1,y+1,z).isAir +
				 getCube(x+1,y,z+1).isAir + getCube(x+1,y+1,z+1).isAir)/4.0;
		lindB = (getCube(x+1,y,z).isAir + getCube(x+1,y-1,z).isAir +
				 getCube(x+1,y,z+1).isAir + getCube(x+1,y-1,z+1).isAir)/4.0;
		lindC = (getCube(x+1,y,z).isAir + getCube(x+1,y-1,z).isAir +
				 getCube(x+1,y,z-1).isAir + getCube(x+1,y-1,z-1).isAir)/4.0;
		lindD = (getCube(x+1,y,z).isAir + getCube(x+1,y+1,z).isAir +
				 getCube(x+1,y,z-1).isAir + getCube(x+1,y+1,z-1).isAir)/4.0;
		lindA = std::fmax(lindA,getCube(x+1,y,z).isAir/3.0);
		lindB = std::fmax(lindB,getCube(x+1,y,z).isAir/3.0);
		lindC = std::fmax(lindC,getCube(x+1,y,z).isAir/3.0);
		lindD = std::fmax(lindD,getCube(x+1,y,z).isAir/3.0);
		lindE = (lindA+lindB+lindC+lindD)/4.0;
		//t1
		renderData.push_back(Vertex(x+1.0, y+1.0, z    , -1,0,0, lindD*getCube(x,y,z).color.x,lindD*getCube(x,y,z).color.y,lindD*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x+1.0, y+1.0, z+1.0, -1,0,0, lindA*getCube(x,y,z).color.x,lindA*getCube(x,y,z).color.y,lindA*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x+1.0, y+0.5, z+0.5, -1,0,0, lindE*getCube(x,y,z).color.x,lindE*getCube(x,y,z).color.y,lindE*getCube(x,y,z).color.z,1.0));
		//t2
		renderData.push_back(Vertex(x+1.0, y    , z    , -1,0,0, lindC*getCube(x,y,z).color.x,lindC*getCube(x,y,z).color.y,lindC*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x+1.0, y+1.0, z    , -1,0,0, lindD*getCube(x,y,z).color.x,lindD*getCube(x,y,z).color.y,lindD*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x+1.0, y+0.5, z+0.5, -1,0,0, lindE*getCube(x,y,z).color.x,lindE*getCube(x,y,z).color.y,lindE*getCube(x,y,z).color.z,1.0));
		//t3
		renderData.push_back(Vertex(x+1.0, y    , z+1.0, -1,0,0, lindB*getCube(x,y,z).color.x,lindB*getCube(x,y,z).color.y,lindB*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x+1.0, y    , z    , -1,0,0, lindC*getCube(x,y,z).color.x,lindC*getCube(x,y,z).color.y,lindC*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x+1.0, y+0.5, z+0.5, -1,0,0, lindE*getCube(x,y,z).color.x,lindE*getCube(x,y,z).color.y,lindE*getCube(x,y,z).color.z,1.0));
		//t4
		renderData.push_back(Vertex(x+1.0, y+1.0, z+1.0, -1,0,0, lindA*getCube(x,y,z).color.x,lindA*getCube(x,y,z).color.y,lindA*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x+1.0, y    , z+1.0, -1,0,0, lindB*getCube(x,y,z).color.x,lindB*getCube(x,y,z).color.y,lindB*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x+1.0, y+0.5, z+0.5, -1,0,0, lindE*getCube(x,y,z).color.x,lindE*getCube(x,y,z).color.y,lindE*getCube(x,y,z).color.z,1.0));
	}
	if(getCube(x-1,y,z).isAir) { // right face
		lindA = (getCube(x-1,y,z).isAir + getCube(x-1,y+1,z).isAir +
				 getCube(x-1,y,z-1).isAir + getCube(x-1,y+1,z-1).isAir)/4.0;
		lindB = (getCube(x-1,y,z).isAir + getCube(x-1,y-1,z).isAir +
				 getCube(x-1,y,z-1).isAir + getCube(x-1,y-1,z-1).isAir)/4.0;
		lindC = (getCube(x-1,y,z).isAir + getCube(x-1,y-1,z).isAir +
				 getCube(x-1,y,z+1).isAir + getCube(x-1,y-1,z+1).isAir)/4.0;
		lindD = (getCube(x-1,y,z).isAir + getCube(x-1,y+1,z).isAir +
				 getCube(x-1,y,z+1).isAir + getCube(x-1,y+1,z+1).isAir)/4.0;
		lindA = std::fmax(lindA,getCube(x+1,y,z).isAir/3.0);
		lindB = std::fmax(lindB,getCube(x+1,y,z).isAir/3.0);
		lindC = std::fmax(lindC,getCube(x+1,y,z).isAir/3.0);
		lindD = std::fmax(lindD,getCube(x+1,y,z).isAir/3.0);
		lindE = (lindA+lindB+lindC+lindD)/4.0;
		//t1
		renderData.push_back(Vertex(x    , y+1.0, z+1.0, -1,0,0, lindD*getCube(x,y,z).color.x,lindD*getCube(x,y,z).color.y,lindD*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x    , y+1.0, z    , -1,0,0, lindA*getCube(x,y,z).color.x,lindA*getCube(x,y,z).color.y,lindA*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x    , y+0.5, z+0.5, -1,0,0, lindE*getCube(x,y,z).color.x,lindE*getCube(x,y,z).color.y,lindE*getCube(x,y,z).color.z,1.0));
		//t2
		renderData.push_back(Vertex(x    , y+1.0, z    , -1,0,0, lindA*getCube(x,y,z).color.x,lindA*getCube(x,y,z).color.y,lindA*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x    , y    , z    , -1,0,0, lindB*getCube(x,y,z).color.x,lindB*getCube(x,y,z).color.y,lindB*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x    , y+0.5, z+0.5, -1,0,0, lindE*getCube(x,y,z).color.x,lindE*getCube(x,y,z).color.y,lindE*getCube(x,y,z).color.z,1.0));
		//t3
		renderData.push_back(Vertex(x    , y    , z    , -1,0,0, lindB*getCube(x,y,z).color.x,lindB*getCube(x,y,z).color.y,lindB*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x    , y    , z+1.0, -1,0,0, lindC*getCube(x,y,z).color.x,lindC*getCube(x,y,z).color.y,lindC*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x    , y+0.5, z+0.5, -1,0,0, lindE*getCube(x,y,z).color.x,lindE*getCube(x,y,z).color.y,lindE*getCube(x,y,z).color.z,1.0));
		//t4
		renderData.push_back(Vertex(x    , y    , z+1.0, -1,0,0, lindC*getCube(x,y,z).color.x,lindC*getCube(x,y,z).color.y,lindC*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x    , y+1.0, z+1.0, -1,0,0, lindD*getCube(x,y,z).color.x,lindD*getCube(x,y,z).color.y,lindD*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x    , y+0.5, z+0.5, -1,0,0, lindE*getCube(x,y,z).color.x,lindE*getCube(x,y,z).color.y,lindE*getCube(x,y,z).color.z,1.0));
	}
	if(getCube(x,y-1,z).isAir) { // bottom face
		lindA = (getCube(x,y-1,z).isAir + getCube(x+1,y-1,z).isAir +
				 getCube(x,y-1,z+1).isAir + getCube(x+1,y-1,z+1).isAir)/4.0;
		lindB = (getCube(x,y-1,z).isAir + getCube(x-1,y-1,z).isAir +
				 getCube(x,y-1,z+1).isAir + getCube(x-1,y-1,z+1).isAir)/4.0;
		lindC = (getCube(x,y-1,z).isAir + getCube(x-1,y-1,z).isAir +
				 getCube(x,y-1,z-1).isAir + getCube(x-1,y-1,z-1).isAir)/4.0;
		lindD = (getCube(x,y-1,z).isAir + getCube(x+1,y-1,z).isAir +
				 getCube(x,y-1,z-1).isAir + getCube(x+1,y-1,z-1).isAir)/4.0;
		lindA = std::fmax(lindA,getCube(x+1,y,z).isAir/3.0);
		lindB = std::fmax(lindB,getCube(x+1,y,z).isAir/3.0);
		lindC = std::fmax(lindC,getCube(x+1,y,z).isAir/3.0);
		lindD = std::fmax(lindD,getCube(x+1,y,z).isAir/3.0);
		lindE = (lindA+lindB+lindC+lindD)/4.0;
		//t1
		renderData.push_back(Vertex(x    , y    , z    , 0,-1,0, lindC*getCube(x,y,z).color.x,lindC*getCube(x,y,z).color.y,lindC*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x+1.0, y    , z    , 0,-1,0, lindD*getCube(x,y,z).color.x,lindD*getCube(x,y,z).color.y,lindD*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x+0.5, y    , z+0.5, 0,-1,0, lindE*getCube(x,y,z).color.x,lindE*getCube(x,y,z).color.y,lindE*getCube(x,y,z).color.z,1.0));
		//t2
		renderData.push_back(Vertex(x+1.0, y    , z    , 0,-1,0, lindD*getCube(x,y,z).color.x,lindD*getCube(x,y,z).color.y,lindD*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x+1.0, y    , z+1.0, 0,-1,0, lindA*getCube(x,y,z).color.x,lindA*getCube(x,y,z).color.y,lindA*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x+0.5, y    , z+0.5, 0,-1,0, lindE*getCube(x,y,z).color.x,lindE*getCube(x,y,z).color.y,lindE*getCube(x,y,z).color.z,1.0));
		//t3
		renderData.push_back(Vertex(x+1.0, y    , z+1.0, 0,-1,0, lindA*getCube(x,y,z).color.x,lindA*getCube(x,y,z).color.y,lindA*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x    , y    , z+1.0, 0,-1,0, lindB*getCube(x,y,z).color.x,lindB*getCube(x,y,z).color.y,lindB*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x+0.5, y    , z+0.5, 0,-1,0, lindE*getCube(x,y,z).color.x,lindE*getCube(x,y,z).color.y,lindE*getCube(x,y,z).color.z,1.0));
		//t4
		renderData.push_back(Vertex(x    , y    , z+1.0, 0,-1,0, lindB*getCube(x,y,z).color.x,lindB*getCube(x,y,z).color.y,lindB*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x    , y    , z    , 0,-1,0, lindC*getCube(x,y,z).color.x,lindC*getCube(x,y,z).color.y,lindC*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x+0.5, y    , z+0.5, 0,-1,0, lindE*getCube(x,y,z).color.x,lindE*getCube(x,y,z).color.y,lindE*getCube(x,y,z).color.z,1.0));
	}
	if(getCube(x,y+1,z).isAir) { // top face
		lindA = (getCube(x,y+1,z).isAir + getCube(x-1,y+1,z).isAir +
				 getCube(x,y+1,z+1).isAir + getCube(x-1,y+1,z+1).isAir)/4.0;
		lindB = (getCube(x,y+1,z).isAir + getCube(x+1,y+1,z).isAir +
				 getCube(x,y+1,z+1).isAir + getCube(x+1,y+1,z+1).isAir)/4.0;
		lindC = (getCube(x,y+1,z).isAir + getCube(x+1,y+1,z).isAir +
				 getCube(x,y+1,z-1).isAir + getCube(x+1,y+1,z-1).isAir)/4.0;
		lindD = (getCube(x,y+1,z).isAir + getCube(x-1,y+1,z).isAir +
				 getCube(x,y+1,z-1).isAir + getCube(x-1,y+1,z-1).isAir)/4.0;
		lindA = std::fmax(lindA,getCube(x+1,y,z).isAir/3.0);
		lindB = std::fmax(lindB,getCube(x+1,y,z).isAir/3.0);
		lindC = std::fmax(lindC,getCube(x+1,y,z).isAir/3.0);
		lindD = std::fmax(lindD,getCube(x+1,y,z).isAir/3.0);
		lindE = (lindA+lindB+lindC+lindD)/4.0;
		//t1
		renderData.push_back(Vertex(x+1.0, y+1.0, z    , 0,1,0 , lindC*getCube(x,y,z).color.x,lindC*getCube(x,y,z).color.y,lindC*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x    , y+1.0, z    , 0,1,0 , lindD*getCube(x,y,z).color.x,lindD*getCube(x,y,z).color.y,lindD*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x+0.5, y+1.0, z+0.5, 0,1,0 , lindE*getCube(x,y,z).color.x,lindE*getCube(x,y,z).color.y,lindE*getCube(x,y,z).color.z,1.0));
		//t2
		renderData.push_back(Vertex(x    , y+1.0, z    , 0,1,0 , lindD*getCube(x,y,z).color.x,lindD*getCube(x,y,z).color.y,lindD*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x    , y+1.0, z+1.0, 0,1,0 , lindA*getCube(x,y,z).color.x,lindA*getCube(x,y,z).color.y,lindA*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x+0.5, y+1.0, z+0.5, 0,1,0 , lindE*getCube(x,y,z).color.x,lindE*getCube(x,y,z).color.y,lindE*getCube(x,y,z).color.z,1.0));
		//t3
		renderData.push_back(Vertex(x    , y+1.0, z+1.0, 0,1,0 , lindA*getCube(x,y,z).color.x,lindA*getCube(x,y,z).color.y,lindA*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x+1.0, y+1.0, z+1.0, 0,1,0 , lindB*getCube(x,y,z).color.x,lindB*getCube(x,y,z).color.y,lindB*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x+0.5, y+1.0, z+0.5, 0,1,0 , lindE*getCube(x,y,z).color.x,lindE*getCube(x,y,z).color.y,lindE*getCube(x,y,z).color.z,1.0));
		//t4
		renderData.push_back(Vertex(x+1.0, y+1.0, z+1.0, 0,1,0 , lindB*getCube(x,y,z).color.x,lindB*getCube(x,y,z).color.y,lindB*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x+1.0, y+1.0, z    , 0,1,0 , lindC*getCube(x,y,z).color.x,lindC*getCube(x,y,z).color.y,lindC*getCube(x,y,z).color.z,1.0));
		renderData.push_back(Vertex(x+0.5, y+1.0, z+0.5, 0,1,0 , lindE*getCube(x,y,z).color.x,lindE*getCube(x,y,z).color.y,lindE*getCube(x,y,z).color.z,1.0));
	}
}

void Chunk::makeVbo() {
	glGenBuffers(1, (GLuint*) &VBOID);
	glBindBuffer(GL_ARRAY_BUFFER, VBOID);
	glBufferData(GL_ARRAY_BUFFER, renderData.size()*sizeof(Vertex), &renderData[0], GL_STATIC_DRAW);
}

//Based on: Fast Voxel Traversal Algorithm for Ray Tracing
//By: John Amanatides et al.
//Implemented by Jordi "BuD" Santiago Provencio
void Chunk::traceView(const Camera& player, float tMax) {
	if (!getOutOfBounds(floor(player.pos.x),floor(player.pos.y),floor(player.pos.z)) &&
		!getCube(floor(player.pos.x),floor(player.pos.y),floor(player.pos.z)).isAir) {
		playerTargetsBlock = true;
		targetedBlock = vec3f(floor(player.pos.x),floor(player.pos.y),floor(player.pos.z));
		return;
	}

	vec3f   pos(player.pos.x,player.pos.y,player.pos.z),
			dir(cos(-player.rot.x*DEG_TO_RAD)*(-sin(-player.rot.y*DEG_TO_RAD)),
				sin(-player.rot.x*DEG_TO_RAD),
				-cos(-player.rot.x*DEG_TO_RAD)*cos(-player.rot.y*DEG_TO_RAD)),
			vox(floor(pos.x), floor(pos.y), floor(pos.z)),
			step(0,0,0),
			next(0,0,0),
			tMaxc(tMax,tMax,tMax),
			tDelta(tMax,tMax,tMax);

	if (dir.x < 0) step.x = -1;
	else step.x = 1;
	if (dir.y < 0) step.y = -1;
	else step.y = 1;
	if (dir.z < 0) step.z = -1;
	else step.z = 1;

	next.x = vox.x + (step.x > 0 ? 1 : 0);
	next.y = vox.y + (step.y > 0 ? 1 : 0);
	next.z = vox.z + (step.z > 0 ? 1 : 0);

	if (dir.x != 0) {
		tDelta.x = step.x/dir.x;
		tMaxc.x = (next.x - pos.x)/dir.x;
	}
	if (dir.y != 0) {
		tDelta.y = step.y/dir.y;
		tMaxc.y = (next.y - pos.y)/dir.y;
	}
	if (dir.z != 0) {
		tDelta.z = step.z/dir.z;
		tMaxc.z = (next.z - pos.z)/dir.z;
	}

	float tCurr = 0;
	while (tCurr < tMax) {
		last = vox;
		if(tMaxc.x < tMaxc.y) {
			if(tMaxc.x < tMaxc.z) {
				tCurr = tMaxc.x;
				tMaxc.x = tMaxc.x + tDelta.x;
				vox.x = vox.x + step.x;
			}
			else {
				tCurr = tMaxc.z;
				vox.z = vox.z + step.z;
				tMaxc.z = tMaxc.z + tDelta.z;

			}
		}
		else {
			if(tMaxc.y < tMaxc.z) {
				tCurr = tMaxc.y;
				vox.y = vox.y + step.y;
				tMaxc.y = tMaxc.y + tDelta.y;
			}
			else {
				tCurr = tMaxc.z;
				vox.z = vox.z + step.z;
				tMaxc.z= tMaxc.z + tDelta.z;
			}
		}
		if(!getOutOfBounds(vox.x,vox.y,vox.z) && !getCube(vox.x,vox.y,vox.z).isAir) {
			playerTargetsBlock = true;
			targetedBlock = vox;
			return;
		}
	}
	playerTargetsBlock = false;
}
