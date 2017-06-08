#include "Bullet.h"


void Bullet::Initialize()
{
	LoadFromFile("data/models/sphere.3ds", true);
	Model3D::Initialize();
	Model3D::computeVertexData();
	objectType = ObjectType::Bullet;
	SetBoundingBox(CalculateBoundingBox(AllVertexData));
	SetModelMatrix(GetModelMatrix() * glm::scale(glm::vec3(0.009f, 0.009f, 0.009f)));
}

Bullet::Bullet(ShaderProgram * fShader)
{
	shader = fShader;
	Initialize();
	Distance = 0.0;
}

Bullet::Bullet(ShaderProgram * fShader, glm::vec3 fPosition, glm::vec3 fDirection) :BaseObject(fPosition, fDirection)
{
	shader = fShader;
	Initialize();
	auto temp = GetBoundingBox();
	temp.Transform(GetModelMatrix());
	SetBoundingBox(temp);
	Distance = 0.0;
}

void Bullet::Update(float deltaTime) {
	if (Destroyed())return;
	float step = deltaTime * 100.7 /*(speed)*/;
	Distance += step;
	if (Distance > 10000.7) {
		SetDestroyed(true);
	}
	else {
		glm::vec3 newPosition = GetPosition() + step * GetDirection();
		SetPosition(newPosition);
		UpdateModelMatrixForBullet();
		SetModelMatrix(GetModelMatrix() * glm::scale(glm::vec3(0.009f, 0.009f, 0.009f)));

		auto temp = GetBoundingBox();
		glm::vec3 translate = step * GetDirection();
		temp.Transform(GetModelMatrix());
		SetBoundingBox(temp);
	}
}

void Bullet::Collided(ObjectType fObject)
{
	if (Destroyed())return;
	if (fObject == Enemy)SetDestroyed(true);
	printf("Bullet Collided\n");
}


void Bullet::Render(glm::mat4 VP, glm::vec3 ambientLight, glm::vec3 lightPosition, glm::vec3 eyePosition)
{
	//shader->UseProgram();
	if (Destroyed()) {
		return;
	}
	shader->BindVPMatrix(&VP[0][0]);
	shader->BindAmbientLight(&ambientLight[0]);
	shader->BindLightPosition(&lightPosition[0]);
	shader->BindEyePosition(&eyePosition[0]);
	auto temp = GetModelMatrix();
	Model3D::Render(shader, temp);
}

void Bullet::Rotate(float angle, glm::vec3 axis)
{
	SetModelMatrix(GetModelMatrix() *= glm::rotate(angle, axis));
	auto temp = GetBoundingBox();
	temp.Transform(GetModelMatrix());
	SetBoundingBox(temp);
}

void Bullet::Translate(glm::vec3 translation)
{
	SetModelMatrix(GetModelMatrix() *= glm::translate(translation));
	auto temp = GetBoundingBox();
	temp.Transform(GetModelMatrix());
	SetBoundingBox(temp);
}

void Bullet::Scale(glm::vec3 scale)
{
	SetModelMatrix(GetModelMatrix() *= glm::scale(scale));
	auto temp = GetBoundingBox();
	temp.Transform(GetModelMatrix());
	SetBoundingBox(temp);
}

void Bullet::SetRotationMat(glm::mat4 mat) {}
void Bullet::SetTranslationMat(glm::mat4 mat) {}
void Bullet::SetScaleMat(glm::mat4 mat) {}

Bullet::~Bullet()
{
}
