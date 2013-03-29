#include "Game.hpp"

Game::Game() : currentScene(NULL), nextScene(NULL) {
}

Game::~Game() {
}

// Init non-resource, general game frame stuff here.
bool Game::init() {
	outLog("* INIT GAME" );

	//Load game-wide resources
	if (!loadResources())
		return false;
	isRunning = true;

	//GL stuff..
	glClearColor(180.0/255.0,205.0/255.0,205.0/255.0,1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_CULL_FACE); //enable backface culling
	glCullFace(GL_BACK);

	//initialise game-wide logic and objects
	outLog("* INIT GAME SUCCESFUL" );
	return true;
}

// Load scene-independent resources here, return false if failed to load
bool Game::loadResources () {
	return true;
}

// 1: Change scene if necessary
// 2: Update game-wide logic
// 3: Process input
// 4: Update scene
void Game::update(float deltaTime) {
	//Change scene, initialize it and close if it fails to initialize
	if (nextScene != NULL) {
		if (currentScene != NULL)
			delete currentScene;
		currentScene = nextScene;
		nextScene = NULL;
		if (!currentScene->init()) {
			delete currentScene;
			currentScene = NULL;
			close();
		}
	}

	//pass the key input to the scene
	for (std::set<Qt::Key>::iterator it=inputManager.keysPressed.begin(); it!=inputManager.keysPressed.end(); ++it) {
			onKeyPressed(deltaTime,*it);
	}
	for (std::set<Qt::Key>::iterator it=inputManager.keysDown.begin(); it!=inputManager.keysDown.end(); ++it) {
			onKeyDown(deltaTime,*it);
	}
	for (std::set<Qt::Key>::iterator it=inputManager.keysReleased.begin(); it!=inputManager.keysReleased.end(); ++it) {
			onKeyReleased(deltaTime,*it);
	}
	//pass the mouse input to the scene
	if(inputManager.mouseDisplacement != vec2i(0,0))
		onMouseMoved(deltaTime,inputManager.mouseDisplacement.x,inputManager.mouseDisplacement.y);
	for (std::set<Qt::MouseButton>::iterator it=inputManager.mouseButtonsPressed.begin();
		 it!=inputManager.mouseButtonsPressed.end(); ++it) {
			onMouseButtonPressed(deltaTime,*it);
	}
	for (std::set<Qt::MouseButton>::iterator it=inputManager.mouseButtonsDown.begin();
		 it!=inputManager.mouseButtonsDown.end(); ++it) {
			onMouseButtonDown(deltaTime,*it);
	}
	for (std::set<Qt::MouseButton>::iterator it=inputManager.mouseButtonsReleased.begin();
		 it!=inputManager.mouseButtonsReleased.end(); ++it) {
			onMouseButtonReleased(deltaTime,*it);
	}
	//Scene logic updating
	if (currentScene != NULL)
		currentScene->update(deltaTime);
	inputManager.update(); //reset input states
}

// Draw scene
void Game::draw() {
	if (currentScene != NULL)
		currentScene->draw();
}

void Game::onKeyPressed(float deltaTime, const Qt::Key &key) {
	if (currentScene != NULL)
		currentScene->onKeyPressed(deltaTime, key);
}

void Game::onKeyDown(float deltaTime, const Qt::Key &key) {
	if (currentScene != NULL)
		currentScene->onKeyDown(deltaTime, key);
}

void Game::onKeyReleased(float deltaTime, const Qt::Key &key) {
	if (currentScene != NULL)
		currentScene->onKeyReleased(deltaTime, key);
}

void Game::onMouseButtonPressed(float deltaTime, const  Qt::MouseButton &button) {
	if (currentScene != NULL)
		currentScene->onMouseButtonPressed(deltaTime, button);
}

void Game::onMouseButtonDown(float deltaTime, const Qt::MouseButton &button) {
	if (currentScene != NULL)
		currentScene->onMouseButtonDown(deltaTime, button);
}

void Game::onMouseButtonReleased(float deltaTime, const Qt::MouseButton &button) {
	if (currentScene != NULL)
		currentScene->onMouseButtonReleased(deltaTime, button);
}

void Game::onMouseMoved(float deltaTime, float dx, float dy) {
	if (currentScene != NULL)
		currentScene->onMouseMoved(deltaTime,dx,dy);
}

// Whenever you wnat to end the game, you must call this function, not the Scene's onClose(); method
// End game-wide stuff here
void Game::close() {
	if (currentScene != NULL)
	{
		currentScene->onClose();
		delete currentScene;
		currentScene = NULL;
	}
	outLog("* EXITING GAME" );
	isRunning = false;
}

// Change scene so that on next this->update(), this->currentScene will be replaced
void Game::setScene (Scene * scene) {
	if(nextScene != NULL)
		delete nextScene;
	nextScene = scene;
}
