#include "InputManager.hpp"

InputManager::InputManager() :
	lastMousePos(0,0), mouseDisplacement(0,0), focus(false),
	colors(12,vec3f(0,0,0)), selectedColor(0){ //12 is the number of color buttons
}

InputManager::~InputManager() {
}

void InputManager::update() {
	keysPressed = std::set<Qt::Key>();
	keysReleased = std::set<Qt::Key>();
	mouseButtonsPressed = std::set<Qt::MouseButton>();
	mouseButtonsReleased = std::set<Qt::MouseButton>();
	lastMousePos += mouseDisplacement;
	mouseDisplacement = vec2i(0,0);
}

void InputManager::pressKey(Qt::Key key) {
	keysPressed.insert(key);
	keysDown.insert(key);
}

void InputManager::releaseKey(Qt::Key key) {
	keysReleased.insert(key);
	keysDown.erase(key);
}

void InputManager::pressMouse(Qt::MouseButton key) {
	mouseButtonsPressed.insert(key);
	mouseButtonsDown.insert(key);
}

void InputManager::releaseMouse(Qt::MouseButton key) {
	mouseButtonsReleased.insert(key);
	mouseButtonsDown.erase(key);
}

void InputManager::gainFocus() {
	focus = true;
}

void InputManager::loseFocus() {
	focus = false;
}

void InputManager::moveMouse(int dx, int dy) {
	mouseDisplacement = vec2i(dx,dy) - lastMousePos;
}

void InputManager::setMousePos(int x, int y) {
	lastMousePos = vec2i(x,y);
	mouseDisplacement = vec2i(0,0);
}

void InputManager::resizeWindow(int newHeight, int newWidth) {
	SCRWIDTH = newWidth;
	SCRHEIGHT = newHeight;
	glViewport(0, 0, SCRWIDTH, SCRHEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(FOV, float(SCRWIDTH)/float(SCRHEIGHT), ZNEAR, ZFAR);
}
