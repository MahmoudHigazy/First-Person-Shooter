#include "Gun.h"


Gun::Gun(glm::vec3 fPosition, glm::vec3 fDirection) :BaseObject(fPosition, fDirection)
{
	health = 10;
	objectType = ObjectType::Gun;
	LoadFromFile("data/models/obj/gun/Ak_47/Ak-47.obj", true);
	Model3D::Initialize();
	Model3D::computeVertexData();
	SetBoundingBox(CalculateBoundingBox(AllVertexData));
	SetModelMatrix(GetModelMatrix() * glm::scale(glm::vec3(0.5f, 0.5f, 0.5f)));
}

Gun::Gun(Gun* tmp)
{
	this->AllVertexData = tmp->AllVertexData;
	this->SetBoundingBox(tmp->GetBoundingBox());
	this->SetRotationMat(tmp->R);
	this->SetTranslationMat(tmp->T);
	this->SetScaleMat(tmp->S);
	this->SetModelMatrix(S*R*T);
	

}
Gun::~Gun()
{
}

void Gun::Collided(ObjectType fObject)
{
	printf("Gun Collided\n");
	if (fObject == ObjectType::Enemy) {
		health--;
		printf("injurd %d \n", health);
		PlaySound(TEXT("Pain.wav"), NULL, SND_ASYNC);

		if (health == 0) {
			printf("Player is Dead\n");
			//glfwTerminate();
		}
	}
	else if (fObject == ObjectType::Fruit)
	{
		health += 5;
		printf("Power Up %d \n",health);
	}
}

void Gun::Translate(glm::vec3 translation)
{
	SetModelMatrix(GetModelMatrix() *= glm::translate(translation));
	auto temp = GetBoundingBox();
	temp.Transform(GetModelMatrix());
	SetBoundingBox(temp);
	printf("hello center=%f %f %f\n", temp.GetCenter().x, temp.GetCenter().y, temp.GetCenter().z);
}

void Gun::Scale(glm::vec3 scale)
{
	SetModelMatrix(GetModelMatrix() *= glm::scale(scale));
	auto temp = GetBoundingBox();
	temp.Transform(GetModelMatrix());
	SetBoundingBox(temp);
}


void Gun::Rotate(float angle,glm::vec3 axis)
{
	SetModelMatrix(GetModelMatrix() * glm::rotate(angle, axis));
	auto temp = GetBoundingBox();
	temp.Transform(GetModelMatrix());
	SetBoundingBox(temp);
}

void Gun::SetTranslationMat(glm::mat4 Mat)
{
	T = Mat;
}

void Gun::SetScaleMat(glm::mat4 Mat)
{
	S = Mat;
}


void Gun::SetRotationMat(glm::mat4 Mat)
{
	R = Mat;
}
