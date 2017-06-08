#include "Tree.h"


void Tree::Initialize(glm::vec3 TreeSize)
{
	//LoadFromFile("data/models/3DS/tree6/Tree N161113.3ds", true);
	objectType = ObjectType::Tree;
	model->Initialize();
	model->computeVertexData();
	model->SetBoundingBox(model->CalculateBoundingBox(model->AllVertexData));
	
	this->SetBoundingBox(model->CalculateBoundingBox(model->AllVertexData));
	SetModelMatrix(GetModelMatrix() * glm::scale(TreeSize));
}

Tree::Tree(ShaderProgram * fShader, glm::vec3 TreeSize)
{
	shader = fShader;
	Initialize(TreeSize);
}

Tree::Tree(Model3D* mode,ShaderProgram* fShader, glm::vec3 fPosition, glm::vec3 fDirection, glm::vec3 TreeSize) :BaseObject(fPosition, fDirection)
{
	model = mode;
	shader = fShader;
	Initialize(TreeSize);
	auto temp = model->GetBoundingBox();
	printf("Center: %f %f %f \n", temp.GetCenter().x, temp.GetCenter().y, temp.GetCenter().z);
	glm::mat4 scalemat = glm::scale(glm::vec3(0.1, 1, 0.1));
	temp.Transform(GetModelMatrix()*scalemat);
	printf("Center: %f %f %f \n", temp.GetCenter().x, temp.GetCenter().y, temp.GetCenter().z);
	model->SetBoundingBox(temp);
	this->SetBoundingBox(temp);
}

void Tree::Collided(ObjectType fObject)
{
	//printf("Tree Collided\n");
}

void Tree::Render(glm::mat4 VP, glm::vec3 ambientLight, glm::vec3 lightPosition, glm::vec3 eyePosition)
{
	shader->BindVPMatrix(&VP[0][0]);
	shader->BindAmbientLight(&ambientLight[0]);
	shader->BindLightPosition(&lightPosition[0]);
	shader->BindEyePosition(&eyePosition[0]);
	auto temp = GetModelMatrix();
	model->Render(shader, temp);
}

void Tree::Rotate(float angle, glm::vec3 axis)
{
	SetModelMatrix(GetModelMatrix() *= glm::rotate(angle, axis));
	auto temp = model->GetBoundingBox();
	temp.Transform(GetModelMatrix());
	model->SetBoundingBox(temp);
	this->SetBoundingBox(temp);
}

void Tree::Translate(glm::vec3 translation)
{
	SetModelMatrix(GetModelMatrix() *= glm::translate(translation));
	auto temp = model->GetBoundingBox();
	temp.Transform(GetModelMatrix());
	model->SetBoundingBox(temp);
	this->SetBoundingBox(temp);
}

void Tree::Scale(glm::vec3 scale)
{
	SetModelMatrix(GetModelMatrix() *= glm::scale(scale));
	auto temp = model->GetBoundingBox();
	temp.Transform(GetModelMatrix());
	model->SetBoundingBox(temp);
	this->SetBoundingBox(temp);
}

void Tree::SetRotationMat(glm::mat4 mat) {}
void Tree::SetTranslationMat(glm::mat4 mat) {}
void Tree::SetScaleMat(glm::mat4 mat) {}

Tree::~Tree()
{
}

