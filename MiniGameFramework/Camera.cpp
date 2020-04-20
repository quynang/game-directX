#include "Camera.h"

Camera::Camera() {}

Camera::Camera(D3DXVECTOR2 position, int camWidth, int camHeight) {
	this->position = position;
	this->camWidth = camWidth;
	this->camHeight = camHeight;
}

Camera::~Camera() {}

D3DXVECTOR2 Camera::getPostion() {
	return this->position;
}

void Camera::setPostion(float x, float y) {
	this->position.x = x;
	this->position.y = y;
}

float Camera::getWidth() {
	return this->camWidth;
}

float Camera::getHeight() {
	return this->camHeight;
}

RECT Camera::getBound() {
	RECT bound;
	bound.left = (int)position.x;
	bound.right = bound.left + camWidth;
	bound.top = (int)position.y;
	bound.bottom = bound.top + camHeight;
	return bound;
}