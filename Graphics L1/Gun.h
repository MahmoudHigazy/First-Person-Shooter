#pragma once

#ifndef Gun_h__
#define Gun_h__

#include "../middleware/includes/gl/glew.h"
#include "../middleware/includes/gl/glfw3.h"

#include "Shaders/shader.hpp"
#include "Model.h"
#include <memory>
#include "FirstPersonCamera.h"
#include "Model3D.h"
#include "ShaderProgram.h"
#include "BaseObject.h"
#include "Model3D.h"
#include "CollisionManager.h"

class Gun :public BaseObject, public Model3D
{
public:
	int health;
	virtual void Collided(ObjectType fObject);
	virtual void Rotate(float, vec3);
	virtual void Translate(vec3 );
	virtual void Scale(glm::vec3 scale);
	virtual void SetRotationMat(glm::mat4 mat);
	virtual void SetTranslationMat(glm::mat4 mat);
	virtual void SetScaleMat(glm::mat4 mat);
	Gun();
	Gun(Gun*);
	Gun(glm::vec3 fPosition, glm::vec3 fDirection);
	~Gun();
};

#endif // Gun_h__