#ifndef INPUTMANAGER_HPP
#define INPUTMANAGER_HPP
#include "../tools.hpp"

class InputManager {
	public:
		InputManager();
		~InputManager();
		void pressKey(Qt::Key key);
		void releaseKey(Qt::Key key);
		void pressMouse(Qt::MouseButton key);
		void releaseMouse(Qt::MouseButton key);
		void moveMouse(int dx, int dy);
		void setMousePos(int x, int y);
		void gainFocus();
		void loseFocus();

		void resizeWindow(int newHeight, int newWidth);

		void update();

		std::set<Qt::Key> keysPressed;
		std::set<Qt::Key> keysDown;
		std::set<Qt::Key> keysReleased;

		std::set<Qt::MouseButton> mouseButtonsPressed;
		std::set<Qt::MouseButton> mouseButtonsDown;
		std::set<Qt::MouseButton> mouseButtonsReleased;

		vec2i lastMousePos;
		vec2i mouseDisplacement;

		bool focus;

		std::vector<vec3f> colors;
		int selectedColor;
};

#endif // INPUTMANAGER_HPP
