#pragma once

#include "ShaderProgram.h"
#include "../../middleware/includes/glm/glm.hpp"
#include "../../middleware/includes/gl/glew.h"
#include"../middleware/includes/glm/glm.hpp"
#include"../middleware/includes/glm/gtx/transform.hpp"
#include "../middleware/includes/glm/gtc/matrix_transform.hpp"

class BaseObject
{
	glm::mat4 modelMatrix;

	
	glm::vec3 direction;

	float directionAngle;
	glm::vec3 position;

	bool isDestroyed;
public:
	glm::mat4 R,T,S;
	BaseObject();
	BaseObject(glm::vec3 fposition, glm::vec3 fdirection);
	glm::mat4 GetModelMatrix();
	glm::mat4 GetModelMatrixGun();
	glm::vec3 GetPosition();
	glm::vec3 GetDirection();
	void SetModelMatrix(glm::mat4 fModelMatrix);
	void UpdateModelMatrix();
	void UpdateModelMatrixForBullet();
	void SetPosition(glm::vec3);
	void SetDestroyed(bool);
	bool Destroyed();
	virtual void Rotate(float fAngle, glm::vec3 fAxis)=0;
	virtual void Translate(glm::vec3 fTranslation)=0;
	virtual void Scale(glm::vec3 fScale)=0;

	virtual void SetRotationMat(glm::mat4 mat) = 0;
	virtual void SetTranslationMat(glm::mat4 mat) = 0;
	virtual void SetScaleMat(glm::mat4 mat) = 0;

	~BaseObject();

};

