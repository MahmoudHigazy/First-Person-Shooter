#pragma once

#include "BaseObject.h"
#include "LoadingModel\md2LeagueOfLegend.h"


class Enemy : public BaseObject, public MD2LeagueOfLegend
{
public:
	//glm::mat4 modelMatrixClass;
	int counter;
	int health;
	ShaderProgram* shader;
	animState_t animationState;
	float posX, posZ,lastX,lastZ;
	float rateX;
	int now,noww;
	void Initialize(int mode);
	Enemy(ShaderProgram* fShader);
	Enemy(int mode, ShaderProgram* fShader, glm::vec3 fPosition, glm::vec3 fDirection);
	~Enemy();
	virtual void Collided(ObjectType fObject);
	void UpdateAnimation(float deltaTime);
	void Render(glm::mat4 VP, glm::vec3 ambientLight, glm::vec3 lightPosition, glm::vec3 eyePosition);
	virtual void Rotate(float angle, glm::vec3 axis);
	virtual void Translate(glm::vec3 translation);
	virtual void Scale(glm::vec3 scale);

	virtual void SetRotationMat(glm::mat4 mat);
	virtual void SetTranslationMat(glm::mat4 mat);
	virtual void SetScaleMat(glm::mat4 mat);
};

