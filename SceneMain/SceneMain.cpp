#include "SceneMain.hpp"
#include "Game.hpp"

SceneMain::SceneMain(Game &parent) :
	Scene(parent),
	debugCounter(0.0), fpsCount(0) {
}

SceneMain::~SceneMain() {
}

bool SceneMain::loadResources() {
	return true;
}

bool SceneMain::init() {
	outLog("* Loading new scene: Main" );

	if (!loadResources())
		return false;

	world.setCube(1,1,1,Cube(false,vec3f(1,0,0)));
	world.setCube(1,2,1,Cube(false,vec3f(0,1,0)));
	world.setCube(1,3,1,Cube(false,vec3f(0,0,1)));
	outLog("* Init was succesful" );

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_COLOR_MATERIAL);
	GLfloat diffuse[] = {0.3, 0.3, 0.3, 1.f};
	GLfloat ambient[] = {0.2, 0.2, 0.2, 1.f};
	GLfloat specular[] = {0.1, 0.1, 0.1, 1.f};
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	return true;
}

void SceneMain::update(float deltaTime) {
	if (parent.input().mode != InputManager::SELECTION)
		world.selection.deleteAll();
	++fpsCount;
	debugCounter += deltaTime;
	if (debugCounter > 1) {
		outLog("FPS: " + toString(fpsCount));
		debugCounter -= 1;
		fpsCount = 0;
	}
	world.update(deltaTime);
	world.traceView(player.pos
					,player.rot,
					100000,
					parent.input().lastMousePos.x,
					parent.input().lastMousePos.y);
	manageUIMenuEvents();
}

void SceneMain::draw() const {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Move matrix to position (according to player)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(player.rot.x, 1, 0, 0);
	glRotatef(player.rot.y, 0, 1, 0);
	glTranslatef(-player.pos.x, -player.pos.y, -player.pos.z);

	GLfloat lightpos0[] = {-0.5, 0.7 , -0.3, 0.};
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos0);
	GLfloat lightpos1[] = {0.4, 0.3 , 0.9, 0.};
	glLightfv(GL_LIGHT1, GL_POSITION, lightpos1);

	//draws here (openGL)
	world.draw();
	if(world.playerTargetsCube) {
		world.drawWireCube(world.targetedCube.x,world.targetedCube.y,world.targetedCube.z);
		if(parent.input().mode == InputManager::STANDARD)
			if(!world.getOutOfBounds(world.last.x,world.last.y,world.last.z)) {
				world.drawWireCube(world.last.x,world.last.y,world.last.z);
				world.drawCube(world.last.x,world.last.y,world.last.z);
			}
	}
	world.selection.draw();
	world.drawWorldBox();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glFlush();
}

void SceneMain::onKeyPressed(float deltaTime, const Qt::Key& key) {
	switch(key) {
		default:
			break;
	}
}

void SceneMain::onKeyDown(float deltaTime, const Qt::Key &key) {
	const float vel = 5.0f;
	vec2f dir(sin(player.rot.y*DEG_TO_RAD), -cos(player.rot.y*DEG_TO_RAD));
	switch(key) {
		case Qt::Key_W:
			player.pos.x += dir.x*vel*deltaTime;
			player.pos.z += dir.y*vel*deltaTime;
			break;
		case Qt::Key_S:
			player.pos.x += -dir.x*vel*deltaTime;
			player.pos.z += -dir.y*vel*deltaTime;
			break;
		case Qt::Key_A:
			player.pos.x += dir.y*vel*deltaTime;
			player.pos.z += -dir.x*vel*deltaTime;
			break;
		case Qt::Key_D:
			player.pos.x += -dir.y*vel*deltaTime;
			player.pos.z += dir.x*vel*deltaTime;
			break;
		case Qt::Key_Space:
			player.pos.y += vel*deltaTime;
			break;
		case Qt::Key_Shift:
			player.pos.y -= vel*deltaTime;
			break;
		default:
			break;
	}
}

void SceneMain::onKeyReleased(float deltaTime, const Qt::Key &key) {
	switch(key) {
		default:
			break;
	}
}

void SceneMain::onMouseButtonPressed(float deltaTime, const Qt::MouseButton& button) {
	switch (parent.input().mode) {
		case InputManager::STANDARD:
			switch(button) {
				case Qt::LeftButton: //delete Cube
					if(world.playerTargetsCube)
						world.setCube(world.targetedCube.x,world.targetedCube.y,world.targetedCube.z,Cube(true,vec3f(0,0,0)));
					break;
				case Qt::RightButton: //place Cube
					if(world.playerTargetsCube)
						world.setCube(world.last.x,world.last.y,world.last.z,Cube(false,parent.input().colors[parent.input().selectedColor]));
					break;
				default:
					break;
			}
			break;
		case InputManager::SELECTION:
			switch(button) {
				case Qt::LeftButton: //delete Cube
					if(world.playerTargetsCube)
						world.selection.addCube(world.targetedCube.x,world.targetedCube.y,world.targetedCube.z);
					break;
				case Qt::RightButton: //place Cube
					if(world.playerTargetsCube)
						world.selection.deleteCube(world.targetedCube.x,world.targetedCube.y,world.targetedCube.z);
					break;
				default:
					break;
			}
			break;
		case InputManager::PAINT:
			switch(button) {
				case Qt::LeftButton: //paint batch
					if(world.playerTargetsCube)
						world.paintCubePatch(world.targetedCube.x,world.targetedCube.y,world.targetedCube.z,parent.input().colors[parent.input().selectedColor]);
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
}

void SceneMain::onMouseButtonDown(float deltaTime, const Qt::MouseButton& button) {
	switch(button) {
		default:
			break;
	}
}

void SceneMain::onMouseButtonReleased(float deltaTime, const Qt::MouseButton& button) {
	switch(button) {
		default:
			break;
	}
}

void SceneMain::onMouseMoved(float deltaTime, float dx, float dy) {
	if(parent.input().mouseButtonsDown.find(Qt::MiddleButton) != parent.input().mouseButtonsDown.end()) {
		player.rotateX(dy*0.5);
		player.rotateY(dx*0.5);
	}
}

void SceneMain::onClose() {
	outLog("* Closing scene: Main" );
}

void SceneMain::manageUIMenuEvents() {
	if(parent.input().openFileString != "") {
		world.loadVoxelization(parent.input().openFileString);
	}
	if(parent.input().saveFileString != "") {
		world.saveVoxelization(parent.input().saveFileString);
	}
}
