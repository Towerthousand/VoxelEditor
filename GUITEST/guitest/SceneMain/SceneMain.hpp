#ifndef SCENEMAIN_HPP
#define SCENEMAIN_HPP
#include "../Scene.hpp"
#include "Camera.hpp"
#include "Model.hpp"

class SceneMain : public Scene {
	public:
		//virtual overrides
		SceneMain(Game &parent);
		~SceneMain();
		bool init();
		void update(float deltaTime);
		void draw() const;
		void onKeyPressed(float deltaTime, const Qt::Key &key);
		void onKeyDown(float deltaTime, const Qt::Key &key);
		void onKeyReleased(float deltaTime, const Qt::Key &key);
		void onMouseButtonPressed(float deltaTime, const Qt::MouseButton &button);
		void onMouseButtonDown(float deltaTime, const Qt::MouseButton &button);
		void onMouseButtonReleased(float deltaTime, const Qt::MouseButton &button);
		void onMouseMoved(float deltaTime, float dx, float dy);
		void onClose(); //close scene-wide stuff

	private:
		bool loadResources();

		Model world;
		Camera player;
		float debugCounter;
		int fpsCount;
};

#endif // SCENEMAIN_HPP
