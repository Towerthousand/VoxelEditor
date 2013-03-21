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
	parent.font().makeText("colorR","",20,vec2f(10,110),sf::Color::White,sf::Text::Bold,false);
	parent.font().makeText("colorG","",20,vec2f(10,130),sf::Color::White,sf::Text::Bold,false);
	parent.font().makeText("colorB","",20,vec2f(10,150),sf::Color::White,sf::Text::Bold,false);
	parent.font().makeText("posX","",20,vec2f(10,10),sf::Color::White,sf::Text::Bold,false);
	parent.font().makeText("posY","",20,vec2f(10,30),sf::Color::White,sf::Text::Bold,false);
	parent.font().makeText("posZ","",20,vec2f(10,50),sf::Color::White,sf::Text::Bold,false);
	parent.font().makeText("rotX","",20,vec2f(10,90),sf::Color::White,sf::Text::Bold,false);
	parent.font().makeText("rotY","",20,vec2f(10,70),sf::Color::White,sf::Text::Bold,false);
	//Set up GL view
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(FOV, float(SCRWIDTH)/float(SCRHEIGHT), ZNEAR, ZFAR);
	//Center mouse
	mouse.setPosition(vec2i(SCRWIDTH/2,SCRHEIGHT/2),parent.getWindow());

	world.setCube(1,1,1,Cube(false,vec3f(1,0,0)));
	world.setCube(1,2,1,Cube(false,vec3f(0,1,0)));
	world.setCube(1,3,1,Cube(false,vec3f(0,0,1)));
	outLog("* Init was succesful" );
	return true;
}

void SceneMain::update(float deltaTime) {
	++fpsCount;
	debugCounter += deltaTime;
	if (debugCounter > 1) {
		parent.font().getText("FPS").setString("FPS: " + toString(fpsCount));
		debugCounter -= 1;
		fpsCount = 0;
	}

	if(world.markedForRedraw)
		world.update(deltaTime);
	world.traceView(player,100);
}

void SceneMain::draw() const {
	//Move matrix to position (according to player)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(player.rot.x, 1, 0, 0);
	glRotatef(player.rot.y, 0, 1, 0);
	glTranslatef(-player.pos.x, -player.pos.y, -player.pos.z);

	//draws here (openGL)
	world.draw();
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glFlush();

	parent.font().getText("colorR").setString("R: " + toString(player.selectedColor.x));
	parent.font().getText("colorG").setString("G: " + toString(player.selectedColor.y));
	parent.font().getText("colorB").setString("B: " + toString(player.selectedColor.z));
	parent.font().getText("posX").setString("X: " + toString(player.pos.x));
	parent.font().getText("posY").setString("Y: " + toString(player.pos.y));
	parent.font().getText("posZ").setString("Z: " + toString(player.pos.z));
	parent.font().getText("rotY").setString("Rot Y: " + toString(player.rot.y));
	parent.font().getText("rotX").setString("Rot X: " + toString(player.rot.x));

	//SFML draws (until window.popGLStates())
	glDisable(GL_CULL_FACE);
	parent.getWindow().pushGLStates();
	parent.getWindow().draw(parent.font().getText("colorR"));
	parent.getWindow().draw(parent.font().getText("colorG"));
	parent.getWindow().draw(parent.font().getText("colorB"));
	parent.getWindow().draw(parent.font().getText("posX"));
	parent.getWindow().draw(parent.font().getText("posY"));
	parent.getWindow().draw(parent.font().getText("posZ"));
	parent.getWindow().draw(parent.font().getText("rotX"));
	parent.getWindow().draw(parent.font().getText("rotY"));
	parent.getWindow().popGLStates();
	parent.getWindow().popGLStates();
	glEnable(GL_CULL_FACE);
}

void SceneMain::onKeyPressed(float deltaTime, const sf::Keyboard::Key& key) {
	switch(key) {
		case sf::Keyboard::Escape:
			parent.close();
			break;
		default:
			break;
	}
}

void SceneMain::onKeyDown(float deltaTime, const sf::Keyboard::Key &key) {
	const float vel = 5.0f;
	vec2f dir(sin(player.rot.y*DEG_TO_RAD), -cos(player.rot.y*DEG_TO_RAD));
	switch(key) {
		case sf::Keyboard::W:
			player.pos.x += dir.x*vel*deltaTime;
			player.pos.z += dir.y*vel*deltaTime;
			break;
		case sf::Keyboard::S:
			player.pos.x += -dir.x*vel*deltaTime;
			player.pos.z += -dir.y*vel*deltaTime;
			break;
		case sf::Keyboard::A:
			player.pos.x += dir.y*vel*deltaTime;
			player.pos.z += -dir.x*vel*deltaTime;
			break;
		case sf::Keyboard::D:
			player.pos.x += -dir.y*vel*deltaTime;
			player.pos.z += dir.x*vel*deltaTime;
			break;
		case sf::Keyboard::Space:
			player.pos.y += vel*deltaTime;
			break;
		case sf::Keyboard::LShift:
			player.pos.y -= vel*deltaTime;
			break;
		case sf::Keyboard::Numpad1:
			player.selectedColor.x -= 0.001;
			break;
		case sf::Keyboard::Numpad2:
			player.selectedColor.y -= 0.001;
			break;
		case sf::Keyboard::Numpad3:
			player.selectedColor.z -= 0.001;
			break;
		case sf::Keyboard::Numpad7:
			player.selectedColor.x += 0.001;
			break;
		case sf::Keyboard::Numpad8:
			player.selectedColor.y += 0.001;
			break;
		case sf::Keyboard::Numpad9:
			player.selectedColor.z += 0.001;
			break;
		default:
			break;
	}
}

void SceneMain::onKeyReleased(float deltaTime, const sf::Keyboard::Key &key) {
	switch(key) {
		default:
			break;
	}
}

void SceneMain::onMouseButtonPressed(float deltaTime, const sf::Mouse::Button& button) {
	switch(button) {
		case sf::Mouse::Left: //delete block
			if(world.playerTargetsBlock)
				world.setCube(world.targetedBlock.x,world.targetedBlock.y,world.targetedBlock.z,Cube(true,vec3f(0,0,0)));
			break;
		case sf::Mouse::Right: //place block
			if(world.playerTargetsBlock)
				world.setCube(world.last.x,world.last.y,world.last.z,Cube(false,player.selectedColor));
			break;
		default:
			break;
	}
}

void SceneMain::onMouseButtonDown(float deltaTime, const sf::Mouse::Button& button) {
	switch(button) {
		default:
			break;
	}
}

void SceneMain::onMouseButtonReleased(float deltaTime, const sf::Mouse::Button& button) {
	switch(button) {
		default:
			break;
	}
}

void SceneMain::onMouseMoved(float deltaTime) {
	vec2i mousePos = mouse.getPosition(parent.getWindow());//vec2i(event.mouseMove.x,event.mouseMove.y);
	if ((mousePos.x != SCRHEIGHT/2 || mousePos.y != SCRWIDTH/2) && WINDOWFOCUS){
		player.rotateX(((float)mousePos.y - SCRHEIGHT/2)*0.5);
		player.rotateY(((float)mousePos.x - SCRWIDTH/2)*0.5);
		mouse.setPosition(vec2i(SCRWIDTH/2, SCRHEIGHT/2),parent.getWindow());
	}
}

void SceneMain::onClose() {
	outLog("* Closing scene: Main" );
}
