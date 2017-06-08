#include "House.h"


void House::Initialize()
{
	
	//LoadFromFile("data/models/3DS/House/house.obj", true);
	objectType = ObjectType::House;
	//Model3D::Initialize();
	//Model3D::computeVertexData();
	model->Initialize();
	model->computeVertexData();
	model->SetBoundingBox(model->CalculateBoundingBox(model->AllVertexData));
	this->SetBoundingBox(model->GetBoundingBox());

	SetModelMatrix(GetModelMatrix() * glm::scale(glm::vec3(2.0f, 2.0f, 2.0f)));
}

House::House(ShaderProgram * fShader)
{
	shader = fShader;
	Initialize();
	
}

House::House(ShaderProgram * fShader, glm::vec3 fPosition, glm::vec3 fDirection,Model3D* mode) :BaseObject(fPosition, fDirection)
{

	model = mode;
	shader = fShader;
	Initialize();
	auto temp = model->GetBoundingBox();
	printf("Center: %f %f %f \n", temp.GetCenter().x, temp.GetCenter().y, temp.GetCenter().z);
	temp.Transform(GetModelMatrix());
	printf("Center: %f %f %f \n", temp.GetCenter().x, temp.GetCenter().y, temp.GetCenter().z);
	model->SetBoundingBox(temp);
	this->SetBoundingBox(model->GetBoundingBox());
}

void House::Collided(ObjectType fObject)
{
	printf("House Collided\n");
}


void House::Render(glm::mat4 VP, glm::vec3 ambientLight, glm::vec3 lightPosition, glm::vec3 eyePosition)
{
	shader->BindVPMatrix(&VP[0][0]);
	shader->BindAmbientLight(&ambientLight[0]);
	shader->BindLightPosition(&lightPosition[0]);
	shader->BindEyePosition(&eyePosition[0]);
	auto temp = GetModelMatrix();
	model->Render(shader, temp);
}

void House::Rotate(float angle, glm::vec3 axis)
{
	SetModelMatrix(GetModelMatrix() *= glm::rotate(angle, axis));
	auto temp = model->GetBoundingBox();
	temp.Transform(GetModelMatrix());
	model->SetBoundingBox(temp);
	this->SetBoundingBox(model->GetBoundingBox());

}

void House::Translate(glm::vec3 translation)
{
	SetModelMatrix(GetModelMatrix() *= glm::translate(translation));
	auto temp = model->GetBoundingBox();
	temp.Transform(GetModelMatrix());
	model->SetBoundingBox(temp);
	this->SetBoundingBox(model->GetBoundingBox());

}

void House::Scale(glm::vec3 scale)
{
	SetModelMatrix(GetModelMatrix() *= glm::scale(scale));
	auto temp = model->GetBoundingBox();
	temp.Transform(GetModelMatrix());
	model->SetBoundingBox(temp);
	this->SetBoundingBox(model->GetBoundingBox());

}

void House::SetRotationMat(glm::mat4 mat) {}
void House::SetTranslationMat(glm::mat4 mat) {}
void House::SetScaleMat(glm::mat4 mat) {}
House::~House()
{
}
