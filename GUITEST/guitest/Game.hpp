#ifndef GAME_HPP
#define GAME_HPP

//  THIS IS THE QT BINDING OF MY ENGINE. SEVERAL THINGS MUST BE TAKEN INTO ACCOUNT
// - You must use the provided glwidget and enable mousetracking if necessary, focus, etc.
// - Events are checked by qt, so the have to be addressed in the glwidget's appropiate
//   methods, such as onKeyPressEvent(QKeyEvent *event); and then sent to the InputManager.
// - Main loop is no longer inside of a Game::run function, it is handled by the widget interface.
//   look at glwidget.cpp for an insight. As is, glwidget.cpp will correctly work as a normal
//   game (the SFML counterpart) while it has focus (if not, key input will not be registered)
//   and the mouse is on top of the widget. Otherwise it will keep updating and drawing, but
//   without input.
//
//  HOW TO USE:
// - Create a class MyScene that inherits from Scene.hpp
//	 It has all types of methods for input & game loop: Key & Mouse input,
//	 Update for logic, Draw for openGL and SFML calls to draw, init, loadResources
//	 to load stuff (use the managers as to load) and an onClose method. It is pretty
//	 straightforward.
// - Create your UI with QT as you please.
// - Add the glwidget class to your project.
// - Add a QWidget to your UI and promote it to "glwidget.h"
// - On glwidget.cpp, chane the initializeGL(); method so that it looks like this:
//  void GLWidget::initializeGL() {
//  	game.input().resizeWindow(this->height(),this->width());
//  	if (game.init()) {
//	    	game.setScene(new MyScene(game));
//		}
//	}

#include "graphics/TextureManager.hpp"
#include "audio/AudioManager.hpp"
#include "input/InputManager.hpp"
#include "SceneMain/SceneMain.hpp"

class Game {
	public:
		Game(); //creates window
		~Game();
		bool init(); // inits game-wide stuff here (init and resource loading)
		void setScene(Scene * scene); // sets nextScene to scene, which will
									  // move into currentScene on next update()
									  // so that there is no update() of one
									  // scene followed by a draw() method
									  // of a different scene.
		void close(); // closes app completely, closing the current scene (if there is)
					  // first, saves game-wide stuff first.
		void update(float deltaTime); // changes scene if necessary
									  // updates fps
									  // checks for window events
									  // updates input with
									  // Game::onMouseButtonPressed(); and
									  // Game::onKeyPressed();
									  // calls currentScene.update(deltaTime)
		void draw(); // calls currentScene.draw()

		TextureManager &textures() { return texManager; }
		AudioManager &audio() { return audioManager; }
		InputManager &input() { return inputManager; }

		bool isRunning;
	private:
		bool loadResources (); // loads game-wide resources. only called
							   // by init() once
		void onKeyPressed(float deltaTime, const Qt::Key &key);
										// currentScene.onKeyPressed
										// (deltaTime, key)
		void onKeyDown(float deltaTime, const Qt::Key &key);
										// currentScene.onKeyDown
										// (deltaTime, key)
		void onKeyReleased(float deltaTime, const Qt::Key &key);
										// currentScene.onKeyReleased
										// (deltaTime, key)
		void onMouseButtonPressed(float deltaTime, const Qt::MouseButton &button);
										// currentScene.onMouseButtonPressed
										// (deltaTime, button)
		void onMouseButtonDown(float deltaTime, const Qt::MouseButton &button);
										// currentScene.onMouseButtonDown
										// (deltaTime, button)
		void onMouseButtonReleased(float deltaTime, const Qt::MouseButton &button);
										// currentScene.onMouseButtonReleased
										// (deltaTime, button)
		void onMouseMoved(float deltaTime, float dx, float dy);
										// currentScene.onMouseMoved
										// (deltaTime)

		//context
		Scene* currentScene;
		Scene* nextScene;

		//managers
		TextureManager texManager;
		AudioManager audioManager;
		InputManager inputManager;
};

#endif //GAME_HPP
