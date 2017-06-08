#include "BaseObject.h"



BaseObject::BaseObject()
{
	position = glm::vec3(0);
	direction = glm::vec3(1.0f, 0.0f, 0.0f);
	directionAngle = 0;
	modelMatrix = glm::mat4(1);
	isDestroyed = false;
}

BaseObject::BaseObject(glm::vec3 fposition, glm::vec3 fdirection)
{
	position = fposition;
	direction = fdirection;
	isDestroyed = false;
	if (direction.x != 0.0f)
	directionAngle = glm::atan(direction.z/direction.x);
	else { directionAngle = 0.0f; }
	modelMatrix = glm::translate(position)*glm::rotate(directionAngle, 0.0f, 1.0f, 0.0f);
}

glm::mat4 BaseObject::GetModelMatrix()
{
	return modelMatrix;
}

glm::mat4 BaseObject::GetModelMatrixGun()
{
	return T*R*S;
}

glm::vec3 BaseObject::GetPosition()
{
	return position;
}

glm::vec3 BaseObject::GetDirection() {
	return direction;
}

void BaseObject::SetModelMatrix(glm::mat4 fModelMatrix)
{
	modelMatrix = fModelMatrix;
}

void BaseObject::UpdateModelMatrix()
{
	modelMatrix = T*R*S;
}

void BaseObject::UpdateModelMatrixForBullet() {
	if (direction.x != 0.0f)
		directionAngle = glm::atan(direction.z / direction.x);
	else { directionAngle = 0.0f; }
	modelMatrix = glm::translate(position)*glm::rotate(directionAngle, 0.0f, 1.0f, 0.0f);
}

void BaseObject::SetPosition(glm::vec3 fposition) {
	position = fposition;
}

void BaseObject::SetDestroyed(bool b) {
	isDestroyed = b;
}

bool BaseObject::Destroyed() {
	return isDestroyed;
}

BaseObject::~BaseObject()
{
}
