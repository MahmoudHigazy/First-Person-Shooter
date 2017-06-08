#include "Fruit.h"


void Fruit::Initialize()
{
	//LoadFromFile("data/models/3DS/jeep/jeep1.3ds", true);
	LoadFromFile("data/models/obj/Apple/wumpa_fruit.obj", true);

	objectType = ObjectType::Fruit;
	Model3D::Initialize();
	Model3D::computeVertexData();
	SetBoundingBox(CalculateBoundingBox(AllVertexData));
	SetModelMatrix(GetModelMatrix() *glm::translate(glm::vec3(0, 3, 0))* glm::scale(glm::vec3(0.7f, 0.7f, 0.7f)));
}
Fruit::Fruit(ShaderProgram * fShader)
{
	shader = fShader;
	Initialize();
}

Fruit::Fruit(ShaderProgram * fShader, glm::vec3 fPosition, glm::vec3 fDirection) :BaseObject(fPosition, fDirection)
{
	shader = fShader;
	Initialize();
	auto temp = GetBoundingBox();
	//printf("Center: %f %f %f \n", temp.GetCenter().x, temp.GetCenter().y, temp.GetCenter().z);
	temp.Transform(GetModelMatrix());
	//printf("Center: %f %f %f \n", temp.GetCenter().x, temp.GetCenter().y, temp.GetCenter().z);
	SetBoundingBox(temp);
}

void Fruit::Collided(ObjectType fObject)
{
	//printf("Fruit Collided\n");
	if (fObject == ObjectType::Gun) {
		SetDestroyed(true);
		printf("Fruit Destroyed\n");

	}
}


void Fruit::Render(glm::mat4 VP, glm::vec3 ambientLight, glm::vec3 lightPosition, glm::vec3 eyePosition)
{
	shader->BindVPMatrix(&VP[0][0]);
	shader->BindAmbientLight(&ambientLight[0]);
	shader->BindLightPosition(&lightPosition[0]);
	shader->BindEyePosition(&eyePosition[0]);
	auto temp = GetModelMatrix();
	Model3D::Render(shader, temp);
}

void Fruit::Rotate(float angle, glm::vec3 axis)
{
	SetModelMatrix(GetModelMatrix() *= glm::rotate(angle, axis));
	auto temp = GetBoundingBox();
	temp.Transform(GetModelMatrix());
	SetBoundingBox(temp);
}

void Fruit::Translate(glm::vec3 translation)
{
	SetModelMatrix(GetModelMatrix() *= glm::translate(translation));
	auto temp = GetBoundingBox();
	temp.Transform(GetModelMatrix());
	SetBoundingBox(temp);
}

void Fruit::Scale(glm::vec3 scale)
{
	SetModelMatrix(GetModelMatrix() *= glm::scale(scale));
	auto temp = GetBoundingBox();
	temp.Transform(GetModelMatrix());
	SetBoundingBox(temp);
}

Fruit::~Fruit()
{
}

void Fruit::SetRotationMat(glm::mat4 mat) {}
void Fruit::SetTranslationMat(glm::mat4 mat) {}
void Fruit::SetScaleMat(glm::mat4 mat) {}