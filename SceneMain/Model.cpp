#include "Model.hpp"
#include "Camera.hpp"

Model::Model() :
	markedForRedraw(false),
	playerTargetsCube(false), targetedCube(0,0,0), last(0,0,0),
	cubes(WORLDWIDTH,std::vector<std::vector<Cube> >
		  (WORLDHEIGHT,std::vector<Cube>
		   (WORLDDEPTH,Cube(true,vec3f(0,0,0))))),
	VBOID(1) {
}

Model::~Model() {
}

void Model::update(float deltaTime) {
	//empty arrays and re-do them
	if(markedForRedraw) {
		selection.markedForRedraw = true;
		markedForRedraw = false;
		renderData.resize(0);
		for(int x = 0; x < WORLDWIDTH; ++x) {
			for(int y = 0; y < WORLDHEIGHT; ++y) {
				for(int z = 0; z < WORLDDEPTH; ++z) {
					if (!getCube(x,y,z).isAir) { // only draw if it's not air
						pushCubeToArray(x,y,z);
					}
				}
			}
		}
		makeVbo();
	}
	selection.update(deltaTime);
}

void Model::draw() const {
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

bool Model::getOutOfBounds(int x, int y, int z) const {
	if (x >= WORLDWIDTH || x < 0
		|| y >= WORLDHEIGHT || y < 0
		|| z >= WORLDDEPTH || z< 0)
		return true;
	return false;
}

Cube Model::getCube(int x, int y, int z) const {
	if (getOutOfBounds(x,y,z))
		return Cube(true,vec3f(0,0,0));
	return cubes[x][y][z];
}

void Model::setCube(int x, int y, int z, Cube c) {
	if (getOutOfBounds(x,y,z)) {
		if (x < 0) {
			WORLDWIDTH += 1;
			std::vector<std::vector<std::vector<Cube> > > newCubes
					(WORLDWIDTH,std::vector<std::vector<Cube> >
					 (WORLDHEIGHT,std::vector<Cube>
					  (WORLDDEPTH,Cube(true,vec3f(0,0,0)))));
			for(int i = 0; i < WORLDWIDTH-1; ++i)
				newCubes[i+1] = cubes[i];
			cubes = newCubes;
			x = 0;
		}
		else if (x > WORLDWIDTH-1) {
			WORLDWIDTH += 1;
			std::vector<std::vector<std::vector<Cube> > > newCubes
					(WORLDWIDTH,std::vector<std::vector<Cube> >
					 (WORLDHEIGHT,std::vector<Cube>
					  (WORLDDEPTH,Cube(true,vec3f(0,0,0)))));
			for(int i = 0; i < WORLDWIDTH-1; ++i)
				newCubes[i] = cubes[i];
			cubes = newCubes;
		}
		else if (y < 0) {
			WORLDHEIGHT += 1;
			std::vector<std::vector<std::vector<Cube> > > newCubes
					(WORLDWIDTH,std::vector<std::vector<Cube> >
					 (WORLDHEIGHT,std::vector<Cube>
					  (WORLDDEPTH,Cube(true,vec3f(0,0,0)))));
			for(int i = 0; i < WORLDWIDTH; ++i)
				for(int j = 0; j < WORLDHEIGHT-1; ++j)
					newCubes[i][j+1] = cubes[i][j];
			cubes = newCubes;
			y = 0;
		}
		else if (y > WORLDHEIGHT-1) {
			WORLDHEIGHT += 1;
			std::vector<std::vector<std::vector<Cube> > > newCubes
					(WORLDWIDTH,std::vector<std::vector<Cube> >
					 (WORLDHEIGHT,std::vector<Cube>
					  (WORLDDEPTH,Cube(true,vec3f(0,0,0)))));
			for(int i = 0; i < WORLDWIDTH; ++i)
				for(int j = 0; j < WORLDHEIGHT-1; ++j)
					newCubes[i][j] = cubes[i][j];
			cubes = newCubes;
		}
		else if (z < 0) {
			WORLDDEPTH += 1;
			std::vector<std::vector<std::vector<Cube> > > newCubes
					(WORLDWIDTH,std::vector<std::vector<Cube> >
					 (WORLDHEIGHT,std::vector<Cube>
					  (WORLDDEPTH,Cube(true,vec3f(0,0,0)))));
			for(int i = 0; i < WORLDWIDTH; ++i)
				for(int j = 0; j < WORLDHEIGHT; ++j)
					for(int k = 0; k < WORLDDEPTH-1; ++k)
						newCubes[i][j][k+1] = cubes[i][j][k];
			cubes = newCubes;
			z = 0;
		}
		else if (z > WORLDDEPTH-1) {
			WORLDDEPTH += 1;
			std::vector<std::vector<std::vector<Cube> > > newCubes
					(WORLDWIDTH,std::vector<std::vector<Cube> >
					 (WORLDHEIGHT,std::vector<Cube>
					  (WORLDDEPTH,Cube(true,vec3f(0,0,0)))));
			for(int i = 0; i < WORLDWIDTH; ++i)
				for(int j = 0; j < WORLDHEIGHT; ++j)
					for(int k = 0; k < WORLDDEPTH-1; ++k)
						newCubes[i][j][k] = cubes[i][j][k];
			cubes = newCubes;
		}
	}
	markedForRedraw = true;
	cubes[x][y][z] = c;
}

//Based on: Fast Voxel Traversal Algorithm for Ray Tracing
//By: John Amanatides et al.
//Implemented by Jordi "BuD" Santiago Provencio
void Model::traceView(const vec3f &pos, float tMax, float xMousePos, float yMousePos) {
	if (!getOutOfBounds(floor(pos.x),floor(pos.y),floor(pos.z)) &&
		!getCube(floor(pos.x),floor(pos.y),floor(pos.z)).isAir) {
		playerTargetsCube = true;
		targetedCube = vec3i(floor(pos.x),floor(pos.y),floor(pos.z));
		return;
	}

	vec3f   step(0,0,0),
			next(0,0,0),
			tMaxc(tMax,tMax,tMax),
			tDelta(tMax,tMax,tMax);
	vec3i   vox(floor(pos.x), floor(pos.y), floor(pos.z));

	float m[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, m);
	vec3f	dir(-m[2],-m[6],-m[10]),
			side(m[0], m[4], m[8]),
			up(m[1], m[5], m[9]);

	float tfov = (float)tan(DEG_TO_RAD * FOV * 0.5);
	float ratio = float(SCRWIDTH)/float(SCRHEIGHT);
	float px = (float(xMousePos) - SCRWIDTH/2)/float(SCRWIDTH)*2*ratio*tfov;
	float py = (float(yMousePos) - SCRHEIGHT/2)/float(SCRHEIGHT)*2*tfov;
	dir += vec3f(side.x*px, side.y*px, side.z*px);
	dir -= vec3f(up.x*py, up.y*py, up.z*py);

	normalize(dir);
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
			playerTargetsCube = true;
			targetedCube = vox;
			return;
		}
	}
	playerTargetsCube = false;
}

bool Model::saveVoxelization(std::string filePath) {
	std::ofstream file;
	file.open(filePath.c_str(),std::ios::binary|std::ios::out|std::ios::trunc);
	if(!file) {
		outLog("#ERROR Could not save voxelization \"" + filePath + "\"");
		return false;
	}
	CubeFileFormat c(Cube(false,vec3f(0,0,0)));
	int ww,wh,wd;
	ww = WORLDWIDTH;
	wh = WORLDHEIGHT;
	wd = WORLDDEPTH;
	file.write((const char *)&ww,sizeof(int));
	file.write((const char *)&wh,sizeof(int));
	file.write((const char *)&wd,sizeof(int));
	if (file.is_open()) {
		for(int x = 0; x < ww; ++x) {
			for(int y = 0; y < wh; ++y) {
				for(int z = 0; z < wd; ++z) {
					c = CubeFileFormat(getCube(x,y,z));
					file.write((const char *)&c,sizeof(CubeFileFormat));
				}
			}
		}
	}
	else return false;
	return true;
}

bool Model::loadVoxelization(std::string filePath) {
	std::ifstream file;
	file.open(filePath.c_str());
	if(!file) {
		outLog("#ERROR Could not load voxelization \"" + filePath + "\"");
		return false;
	}
	int ww,wh,wd;
	file.read((char *) &ww, sizeof(int));
	file.read((char *) &wh, sizeof(int));
	file.read((char *) &wd, sizeof(int));
	cubes.resize(ww);
	for(int i = 0; i < ww; ++i)
		cubes[i].resize(wh);
	for(int i = 0; i < ww; ++i)
		for(int j = 0; j < wh; ++j)
			cubes[i][j].resize(wd);
	WORLDWIDTH = ww;
	WORLDHEIGHT = wh;
	WORLDDEPTH = wd;
	CubeFileFormat c(Cube(false,vec3f(0,0,0)));
	for(int x = 0; x < WORLDWIDTH; ++x) {
		for(int y = 0; y < WORLDHEIGHT; ++y) {
			for(int z = 0; z < WORLDDEPTH; ++z) {
				file.read((char *) &c,sizeof(CubeFileFormat));
				cubes[x][y][z] = Cube(c);
			}
		}
	}
	markedForRedraw = true;
	return true;
}

void Model::paintCube(int x, int y, int z, vec3f newColor) {
	if (!getCube(x,y,z).isAir && !getOutOfBounds(x,y,z))
		cubes[x][y][z] = Cube(false,newColor);
}

void Model::paintCubePatch(int x, int y, int z, vec3f newColor) {
	std::queue<vec3i> nodes;
	vec3f lastColor = getCube(x,y,z).color;
	paintCube(x,y,z,newColor);
	nodes.push(vec3i(x,y,z));
	while(!nodes.empty()) {
		vec3i curr = nodes.front();
		nodes.pop();
		processCubePaintBFS(curr, vec3i(1,0,0),lastColor,nodes);
		processCubePaintBFS(curr, vec3i(-1,0,0),lastColor,nodes);
		processCubePaintBFS(curr, vec3i(0,1,0),lastColor,nodes);
		processCubePaintBFS(curr, vec3i(0,-1,0),lastColor,nodes);
		processCubePaintBFS(curr, vec3i(0,0,1),lastColor,nodes);
		processCubePaintBFS(curr, vec3i(0,0,-1),lastColor,nodes);
	}
	markedForRedraw = true;
}

void Model::processCubePaintBFS(vec3i src,vec3i offset, vec3f lastColor, std::queue<vec3i>& nodes) {
	vec3i sub = src+offset;
	Cube subCube = getCube(sub.x,sub.y,sub.z);
	Cube srcCube = getCube(src.x,src.y,src.z);
	if(!subCube.isAir && subCube.color == lastColor && subCube.color != srcCube.color) {
		nodes.push(sub);
		paintCube(sub.x,sub.y,sub.z,srcCube.color);
	}
}

void Model::pushCubeToArray(int x,int y, int z) { //I DON'T KNOW HOW TO MAKE THIS COMPACT
	float lindA = 1.0,lindB = 1.0,lindC = 1.0,lindD = 1.0, lindE = 1.0;
	//STRUCTURE PER VERTEX: Vx,Vy,Vz,
	//						Nx,Ny,Nz,
	//						Cr,Cg,Cb,Ca
	vec3f color = getCube(x,y,z).color;
	if(getCube(x,y,z+1).isAir) { // front face
		lindA = (getCube(x,y,z+1).isAir + getCube(x,y+1,z+1).isAir +
				 getCube(x-1,y,z+1).isAir + getCube(x-1,y+1,z+1).isAir)/4.0;
		lindB = (getCube(x,y,z+1).isAir + getCube(x,y-1,z+1).isAir +
				 getCube(x-1,y,z+1).isAir + getCube(x-1,y-1,z+1).isAir)/4.0;
		lindC = (getCube(x,y,z+1).isAir + getCube(x,y-1,z+1).isAir +
				 getCube(x+1,y,z+1).isAir + getCube(x+1,y-1,z+1).isAir)/4.0;
		lindD = (getCube(x,y,z+1).isAir + getCube(x,y+1,z+1).isAir +
				 getCube(x+1,y,z+1).isAir + getCube(x+1,y+1,z+1).isAir)/4.0;
		lindE = (lindA+lindB+lindC+lindD)/4.0;
		//t1
		renderData.push_back(Vertex(x+1.0, y+1.0, z+1.0, 0,0,1, lindD*color.x,lindD*color.y,lindD*color.z,1.0));
		renderData.push_back(Vertex(x    , y+1.0, z+1.0, 0,0,1, lindA*color.x,lindA*color.y,lindA*color.z,1.0));
		renderData.push_back(Vertex(x+0.5, y+0.5, z+1.0, 0,0,1, lindE*color.x,lindE*color.y,lindE*color.z,1.0));
		//t2
		renderData.push_back(Vertex(x+1.0, y    , z+1.0, 0,0,1, lindC*color.x,lindC*color.y,lindC*color.z,1.0));
		renderData.push_back(Vertex(x+1.0, y+1.0, z+1.0, 0,0,1, lindD*color.x,lindD*color.y,lindD*color.z,1.0));
		renderData.push_back(Vertex(x+0.5, y+0.5, z+1.0, 0,0,1, lindE*color.x,lindE*color.y,lindE*color.z,1.0));
		//t3
		renderData.push_back(Vertex(x    , y    , z+1.0, 0,0,1, lindB*color.x,lindB*color.y,lindB*color.z,1.0));
		renderData.push_back(Vertex(x+1.0, y    , z+1.0, 0,0,1, lindC*color.x,lindC*color.y,lindC*color.z,1.0));
		renderData.push_back(Vertex(x+0.5, y+0.5, z+1.0, 0,0,1, lindE*color.x,lindE*color.y,lindE*color.z,1.0));
		//t4
		renderData.push_back(Vertex(x    , y+1.0, z+1.0, 0,0,1, lindA*color.x,lindA*color.y,lindA*color.z,1.0));
		renderData.push_back(Vertex(x    , y    , z+1.0, 0,0,1, lindB*color.x,lindB*color.y,lindB*color.z,1.0));
		renderData.push_back(Vertex(x+0.5, y+0.5, z+1.0, 0,0,1, lindE*color.x,lindE*color.y,lindE*color.z,1.0));
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
		lindE = (lindA+lindB+lindC+lindD)/4.0;
		//t1
		renderData.push_back(Vertex(x    , y+1.0, z    , 0,0,-1, lindD*color.x,lindD*color.y,lindD*color.z,1.0));
		renderData.push_back(Vertex(x+1.0, y+1.0, z    , 0,0,-1, lindA*color.x,lindA*color.y,lindA*color.z,1.0));
		renderData.push_back(Vertex(x+0.5, y+0.5, z    , 0,0,-1, lindE*color.x,lindE*color.y,lindE*color.z,1.0));
		//t2
		renderData.push_back(Vertex(x+1.0, y+1.0, z    , 0,0,-1, lindA*color.x,lindA*color.y,lindA*color.z,1.0));
		renderData.push_back(Vertex(x+1.0, y    , z    , 0,0,-1, lindB*color.x,lindB*color.y,lindB*color.z,1.0));
		renderData.push_back(Vertex(x+0.5, y+0.5, z    , 0,0,-1, lindE*color.x,lindE*color.y,lindE*color.z,1.0));
		//t3
		renderData.push_back(Vertex(x+1.0, y    , z    , 0,0,-1, lindB*color.x,lindB*color.y,lindB*color.z,1.0));
		renderData.push_back(Vertex(x    , y    , z    , 0,0,-1, lindC*color.x,lindC*color.y,lindC*color.z,1.0));
		renderData.push_back(Vertex(x+0.5, y+0.5, z    , 0,0,-1, lindE*color.x,lindE*color.y,lindE*color.z,1.0));
		//t4
		renderData.push_back(Vertex(x    , y    , z    , 0,0,-1, lindC*color.x,lindC*color.y,lindC*color.z,1.0));
		renderData.push_back(Vertex(x    , y+1.0, z    , 0,0,-1, lindD*color.x,lindD*color.y,lindD*color.z,1.0));
		renderData.push_back(Vertex(x+0.5, y+0.5, z    , 0,0,-1, lindE*color.x,lindE*color.y,lindE*color.z,1.0));
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
		lindE = (lindA+lindB+lindC+lindD)/4.0;
		//t1
		renderData.push_back(Vertex(x+1.0, y+1.0, z    , 1,0,0, lindD*color.x,lindD*color.y,lindD*color.z,1.0));
		renderData.push_back(Vertex(x+1.0, y+1.0, z+1.0, 1,0,0, lindA*color.x,lindA*color.y,lindA*color.z,1.0));
		renderData.push_back(Vertex(x+1.0, y+0.5, z+0.5, 1,0,0, lindE*color.x,lindE*color.y,lindE*color.z,1.0));
		//t2
		renderData.push_back(Vertex(x+1.0, y    , z    , 1,0,0, lindC*color.x,lindC*color.y,lindC*color.z,1.0));
		renderData.push_back(Vertex(x+1.0, y+1.0, z    , 1,0,0, lindD*color.x,lindD*color.y,lindD*color.z,1.0));
		renderData.push_back(Vertex(x+1.0, y+0.5, z+0.5, 1,0,0, lindE*color.x,lindE*color.y,lindE*color.z,1.0));
		//t3
		renderData.push_back(Vertex(x+1.0, y    , z+1.0, 1,0,0, lindB*color.x,lindB*color.y,lindB*color.z,1.0));
		renderData.push_back(Vertex(x+1.0, y    , z    , 1,0,0, lindC*color.x,lindC*color.y,lindC*color.z,1.0));
		renderData.push_back(Vertex(x+1.0, y+0.5, z+0.5, 1,0,0, lindE*color.x,lindE*color.y,lindE*color.z,1.0));
		//t4
		renderData.push_back(Vertex(x+1.0, y+1.0, z+1.0, 1,0,0, lindA*color.x,lindA*color.y,lindA*color.z,1.0));
		renderData.push_back(Vertex(x+1.0, y    , z+1.0, 1,0,0, lindB*color.x,lindB*color.y,lindB*color.z,1.0));
		renderData.push_back(Vertex(x+1.0, y+0.5, z+0.5, 1,0,0, lindE*color.x,lindE*color.y,lindE*color.z,1.0));
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
		lindE = (lindA+lindB+lindC+lindD)/4.0;
		//t1
		renderData.push_back(Vertex(x    , y+1.0, z+1.0, -1,0,0, lindD*color.x,lindD*color.y,lindD*color.z,1.0));
		renderData.push_back(Vertex(x    , y+1.0, z    , -1,0,0, lindA*color.x,lindA*color.y,lindA*color.z,1.0));
		renderData.push_back(Vertex(x    , y+0.5, z+0.5, -1,0,0, lindE*color.x,lindE*color.y,lindE*color.z,1.0));
		//t2
		renderData.push_back(Vertex(x    , y+1.0, z    , -1,0,0, lindA*color.x,lindA*color.y,lindA*color.z,1.0));
		renderData.push_back(Vertex(x    , y    , z    , -1,0,0, lindB*color.x,lindB*color.y,lindB*color.z,1.0));
		renderData.push_back(Vertex(x    , y+0.5, z+0.5, -1,0,0, lindE*color.x,lindE*color.y,lindE*color.z,1.0));
		//t3
		renderData.push_back(Vertex(x    , y    , z    , -1,0,0, lindB*color.x,lindB*color.y,lindB*color.z,1.0));
		renderData.push_back(Vertex(x    , y    , z+1.0, -1,0,0, lindC*color.x,lindC*color.y,lindC*color.z,1.0));
		renderData.push_back(Vertex(x    , y+0.5, z+0.5, -1,0,0, lindE*color.x,lindE*color.y,lindE*color.z,1.0));
		//t4
		renderData.push_back(Vertex(x    , y    , z+1.0, -1,0,0, lindC*color.x,lindC*color.y,lindC*color.z,1.0));
		renderData.push_back(Vertex(x    , y+1.0, z+1.0, -1,0,0, lindD*color.x,lindD*color.y,lindD*color.z,1.0));
		renderData.push_back(Vertex(x    , y+0.5, z+0.5, -1,0,0, lindE*color.x,lindE*color.y,lindE*color.z,1.0));
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
		lindE = (lindA+lindB+lindC+lindD)/4.0;
		//t1
		renderData.push_back(Vertex(x    , y    , z    , 0,-1,0, lindC*color.x,lindC*color.y,lindC*color.z,1.0));
		renderData.push_back(Vertex(x+1.0, y    , z    , 0,-1,0, lindD*color.x,lindD*color.y,lindD*color.z,1.0));
		renderData.push_back(Vertex(x+0.5, y    , z+0.5, 0,-1,0, lindE*color.x,lindE*color.y,lindE*color.z,1.0));
		//t2
		renderData.push_back(Vertex(x+1.0, y    , z    , 0,-1,0, lindD*color.x,lindD*color.y,lindD*color.z,1.0));
		renderData.push_back(Vertex(x+1.0, y    , z+1.0, 0,-1,0, lindA*color.x,lindA*color.y,lindA*color.z,1.0));
		renderData.push_back(Vertex(x+0.5, y    , z+0.5, 0,-1,0, lindE*color.x,lindE*color.y,lindE*color.z,1.0));
		//t3
		renderData.push_back(Vertex(x+1.0, y    , z+1.0, 0,-1,0, lindA*color.x,lindA*color.y,lindA*color.z,1.0));
		renderData.push_back(Vertex(x    , y    , z+1.0, 0,-1,0, lindB*color.x,lindB*color.y,lindB*color.z,1.0));
		renderData.push_back(Vertex(x+0.5, y    , z+0.5, 0,-1,0, lindE*color.x,lindE*color.y,lindE*color.z,1.0));
		//t4
		renderData.push_back(Vertex(x    , y    , z+1.0, 0,-1,0, lindB*color.x,lindB*color.y,lindB*color.z,1.0));
		renderData.push_back(Vertex(x    , y    , z    , 0,-1,0, lindC*color.x,lindC*color.y,lindC*color.z,1.0));
		renderData.push_back(Vertex(x+0.5, y    , z+0.5, 0,-1,0, lindE*color.x,lindE*color.y,lindE*color.z,1.0));
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
		lindE = (lindA+lindB+lindC+lindD)/4.0;
		//t1
		renderData.push_back(Vertex(x+1.0, y+1.0, z    , 0,1,0 , lindC*color.x,lindC*color.y,lindC*color.z,1.0));
		renderData.push_back(Vertex(x    , y+1.0, z    , 0,1,0 , lindD*color.x,lindD*color.y,lindD*color.z,1.0));
		renderData.push_back(Vertex(x+0.5, y+1.0, z+0.5, 0,1,0 , lindE*color.x,lindE*color.y,lindE*color.z,1.0));
		//t2
		renderData.push_back(Vertex(x    , y+1.0, z    , 0,1,0 , lindD*color.x,lindD*color.y,lindD*color.z,1.0));
		renderData.push_back(Vertex(x    , y+1.0, z+1.0, 0,1,0 , lindA*color.x,lindA*color.y,lindA*color.z,1.0));
		renderData.push_back(Vertex(x+0.5, y+1.0, z+0.5, 0,1,0 , lindE*color.x,lindE*color.y,lindE*color.z,1.0));
		//t3
		renderData.push_back(Vertex(x    , y+1.0, z+1.0, 0,1,0 , lindA*color.x,lindA*color.y,lindA*color.z,1.0));
		renderData.push_back(Vertex(x+1.0, y+1.0, z+1.0, 0,1,0 , lindB*color.x,lindB*color.y,lindB*color.z,1.0));
		renderData.push_back(Vertex(x+0.5, y+1.0, z+0.5, 0,1,0 , lindE*color.x,lindE*color.y,lindE*color.z,1.0));
		//t4
		renderData.push_back(Vertex(x+1.0, y+1.0, z+1.0, 0,1,0 , lindB*color.x,lindB*color.y,lindB*color.z,1.0));
		renderData.push_back(Vertex(x+1.0, y+1.0, z    , 0,1,0 , lindC*color.x,lindC*color.y,lindC*color.z,1.0));
		renderData.push_back(Vertex(x+0.5, y+1.0, z+0.5, 0,1,0 , lindE*color.x,lindE*color.y,lindE*color.z,1.0));
	}
}

void Model::makeVbo() {
	glGenBuffers(1, (GLuint*) &VBOID);
	glBindBuffer(GL_ARRAY_BUFFER, VBOID);
	glBufferData(GL_ARRAY_BUFFER, renderData.size()*sizeof(Vertex), &renderData[0], GL_STATIC_DRAW);
}


void Model::drawWireCube(int x, int y, int z) const {
	glPushMatrix();
	glLineWidth(1.5);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColor4f(0.0,0.0,0.0,0.5);
	glVertexPointer(3, GL_INT, 0, &vertexPoints[0]);
	glTranslatef(x-0.0025,y-0.0025,z-0.0025);
	glScalef(1.005,1.005,1.005);
	glDrawArrays(GL_LINES,0,24);
	glDisableClientState(GL_VERTEX_ARRAY);
	glColor4f(1.0,1.0,1.0,1.0);
	glPopMatrix();
}

void Model::drawCube(int x, int y, int z) const{
	glPushMatrix();
	glTranslatef(x, y, z);
	glColor4f(0,0,0,0.3);
	glBegin(GL_QUADS);
	glNormal3f(0,-1,0);
	glVertex3f(1, 0, 0);
	glVertex3f(1, 0, 1);
	glVertex3f(0, 0, 1);
	glVertex3f(0, 0, 0);

	glNormal3f(0, 1,0);
	glVertex3f(0, 1, 0);
	glVertex3f(0, 1, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(1, 1, 0);

	glNormal3f(-1,0,0);
	glVertex3f(0, 0, 1);
	glVertex3f(0, 1, 1);
	glVertex3f(0, 1, 0);
	glVertex3f(0, 0, 0);

	glNormal3f(1,0,0);
	glVertex3f(1, 0, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(1, 1, 1);
	glVertex3f(1, 0, 1);

	glNormal3f(0,0,-1);
	glVertex3f(0, 1, 0);
	glVertex3f(1, 1, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(0, 0, 0);

	glNormal3f(0,0,1);
	glVertex3f(0, 0, 1);
	glVertex3f(1, 0, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(0, 1, 1);
	glEnd();

	glPopMatrix();
}

void Model::drawWorldBox() const{
	glPushMatrix();
	glLineWidth(1.5);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColor4f(0.0,0.0,0.0,0.2);
	glVertexPointer(3, GL_INT, 0, &vertexPoints[0]);
	glScalef(WORLDWIDTH,WORLDHEIGHT,WORLDDEPTH);
	glDrawArrays(GL_LINES,0,24);
	glDisableClientState(GL_VERTEX_ARRAY);
	glColor4f(1.0,1.0,1.0,1.0);
	glPopMatrix();
}

const int Model::vertexPoints[24][3] = {
	{0,0,0},
	{1,0,0},

	{1,0,0},
	{1,1,0},

	{1,1,0},
	{0,1,0},

	{0,1,0},
	{0,0,0},

	{0,0,1},
	{1,0,1},

	{1,0,1},
	{1,1,1},

	{1,1,1},
	{0,1,1},

	{0,1,1},
	{0,0,1},

	{0,0,0},
	{0,0,1},

	{1,0,0},
	{1,0,1},

	{1,1,0},
	{1,1,1},

	{0,1,0},
	{0,1,1},
};
