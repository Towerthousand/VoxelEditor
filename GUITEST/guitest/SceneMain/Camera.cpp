#include "Camera.hpp"

//
// This implementation of "camera" has no z rotation (fuck quaternions)
// and is thougt of as a no-fly, fps kind of view. Tweak it!
//

Camera::Camera() : rot(0,125), pos(-1,1.3,-1) {
}

Camera::~Camera() {
}

void Camera::rotateX(float deg) {
	rot.x += deg;

	//Euler fix
	if (rot.x > 89.9)
		rot.x = 89.9;
	else if (rot.x < -89.9)
		rot.x = -89.9;
}

void Camera::rotateY(float deg) {
	rot.y += deg;

	//prevent overflow of float rot.y
	if (rot.y > 360)
		rot.y = rot.y - 360;
	else if (rot.y < -360)
		rot.y = rot.y + 360;
}
