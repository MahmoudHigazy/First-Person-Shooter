#pragma once
#include "BaseObject.h"
#include "Model3D.h"

class House : public BaseObject,public CollidableModel//, public Model3D
{
	Model3D* model;
	ShaderProgram* shader;
	void Initialize();
public:
	House(ShaderProgram* fShader);
	House(ShaderProgram* fShader, glm::vec3 fPosition, glm::vec3 fDirection,Model3D *);
	virtual void Collided(ObjectType fObject);
	void Render(glm::mat4 VP, glm::vec3 ambientLight, glm::vec3 lightPosition, glm::vec3 eyePosition);
	virtual void Rotate(float angle, glm::vec3 axis);
	virtual void Translate(glm::vec3 translation);
	virtual void Scale(glm::vec3 scale);
	virtual void SetRotationMat(glm::mat4 mat);
	virtual void SetTranslationMat(glm::mat4 mat);
	virtual void SetScaleMat(glm::mat4 mat);
	~House();
};

