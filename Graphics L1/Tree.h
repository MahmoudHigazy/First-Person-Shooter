#pragma once
#include "BaseObject.h"
#include "Model3D.h"

class Tree :public BaseObject, public CollidableModel
{
public:
	Model3D* model;
	ShaderProgram* shader;
	void Initialize(glm::vec3);
	Tree(ShaderProgram* fShader, glm::vec3);
	Tree(Model3D*,ShaderProgram* fShader, glm::vec3 fPosition, glm::vec3 fDirection, glm::vec3);
	virtual void Collided(ObjectType fObject);
	void Render(glm::mat4 VP, glm::vec3 ambientLight, glm::vec3 lightPosition, glm::vec3 eyePosition);
	virtual void Rotate(float angle, glm::vec3 axis);
	virtual void Translate(glm::vec3 translation);
	virtual void Scale(glm::vec3 scale);
	virtual void SetRotationMat(glm::mat4 mat);
	virtual void SetTranslationMat(glm::mat4 mat);
	virtual void SetScaleMat(glm::mat4 mat);
	~Tree();
};

