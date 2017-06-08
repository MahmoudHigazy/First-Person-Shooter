#include "Enemy.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void Enemy::Initialize(int mode)
{
	if (mode == 0) LoadExportedModel("data/models/md2/zombie.md2"), health = 2;
	else LoadExportedModel("data/models/md2/zombie1.md2"), health = 3;
	counter = 75;
	objectType = ObjectType::Enemy;
	animationState = this->StartAnimation(animType_LOL::STAND);
	MD2LeagueOfLegend::SetBoundingBox(MD2LeagueOfLegend::CalculateBoundingBox(MD2LeagueOfLegend::mVertices));
	SetModelMatrix(GetModelMatrix() *glm::translate(glm::vec3(0,-1.7,0))* glm::scale(glm::vec3(0.1f, 0.1f, 0.1f))*glm::rotate(-90.0f, glm::vec3(1, 0, 0))/*glm::rotate(-90.0f, glm::vec3(0, 0, 1))*/);
	//SetModelMatrix(GetModelMatrix()*glm::rotate(90.0f, glm::vec3(0.0f, 0.0f, 1.0f)));
}

Enemy::Enemy(ShaderProgram* fShader) : BaseObject()
{
	shader = fShader;
	Initialize(0);
}

Enemy::Enemy(int mode, ShaderProgram* fShader, glm::vec3 fPosition, glm::vec3 fDirection) : BaseObject(fPosition, fDirection)
{
	rateX = 0.9000000000, posX = 0, posZ = 0, now = 4;
	shader = fShader;
	Initialize(mode);
	auto temp = GetBoundingBox();
	temp.Transform(GetModelMatrix());
	SetBoundingBox(temp);
	//MoveAnimatedModel();
}


Enemy::~Enemy()
{
}

void Enemy::Collided(ObjectType fObject)
{
	int minx = -75;
	int maxx = 75;
	//glm::mat4 modelMatrix = GetModelMatrix();
	if (fObject == ObjectType::Bullet)
	{
		health--;
		PlaySound(TEXT("Pain.wav"), NULL, SND_ASYNC);

		if (health == 0) {
			if (animationState.type != animType_LOL::DEATH) {
				animationState = this->StartAnimation(animType_LOL::DEATH);
				Rotate(90.0f, glm::vec3(1, 0, 0));
				Rotate(90.0f, glm::vec3(0, 0, 1));
				glm::vec3 tmp = glm::vec3(0.0, -50.0, 0.0);
				Translate(tmp);
			}
			SetDestroyed(true);

		}
	}
	else
	{
		if(animationState.type == animType_LOL::RUN)
			animationState = this->StartAnimation(animType_LOL::RUN);
		srand(time(NULL));
		int random;
		while (1)
		{
			random = rand() % 100000 + 1;
			random %= 4;
			random++;
			if (random != now)
			{
				if (random == 3 && posZ > minx) break;
				if (random == 4 && posZ < maxx) break;
				if (random == 1 && posX < maxx) break;
				if (random == 2 && posX > minx) break;
			}
		}
		if (random == 1)
		{
			if (now == 2) Enemy::Rotate(180.0f, glm::vec3(0, 0, 1));
			if (now == 3) Enemy::Rotate(90.0f, glm::vec3(0, 0, 1));
			if (now == 4) Enemy::Rotate(270.0f, glm::vec3(0, 0, 1));
		}
		else if (random == 2)
		{
			if (now == 1) Enemy::Rotate(180.0f, glm::vec3(0, 0, 1));
			if (now == 3) Enemy::Rotate(270.0f, glm::vec3(0, 0, 1));
			if (now == 4) Enemy::Rotate(90.0f, glm::vec3(0, 0, 1));
		}
		else if (random == 3)
		{
			if (now == 4) Enemy::Rotate(180.0f, glm::vec3(0, 0, 1));
			if (now == 2) Enemy::Rotate(90.0f, glm::vec3(0, 0, 1));
			if (now == 1) Enemy::Rotate(270.0f, glm::vec3(0, 0, 1));
		}
		else
		{
			if (now == 3) Enemy::Rotate(180.0f, glm::vec3(0, 0, 1));
			if (now == 1) Enemy::Rotate(90.0f, glm::vec3(0, 0, 1));
			if (now == 2) Enemy::Rotate(270.0f, glm::vec3(0, 0, 1));
		}
		now = random;
		//SetModelMatrix(modelMatrix);
	}
	("Enemy Collided\n");

}


void Enemy::UpdateAnimation(float deltaTime)
{
	if(!Destroyed())
		MD2LeagueOfLegend::UpdateExportedAnimation(&animationState, deltaTime);
}

void Enemy::Render(glm::mat4 VP, glm::vec3 ambientLight, glm::vec3 lightPosition, glm::vec3 eyePosition)
{
	glm::mat4 temp = GetModelMatrix();
	shader->UseProgram();
	shader->BindVPMatrix(&VP[0][0]);
	shader->BindModelMatrix(&temp[0][0]);
	shader->BindAmbientLight(&ambientLight[0]);
	shader->BindLightPosition(&lightPosition[0]);
	shader->BindEyePosition(&eyePosition[0]);
	RenderModel(&animationState);
	//MoveAnimatedModel();
	if (animationState.type != (animType_LOL::RUN) && animationState.type != (animType_LOL::DEATH) && animationState.type != (animType_LOL::ATTACK1))
		animationState = StartAnimation(animType_LOL::RUN);
}

void Enemy::Rotate(float angle, glm::vec3 axis)
{
	SetModelMatrix(GetModelMatrix() *= glm::rotate(angle, axis));
	auto temp = GetBoundingBox();
	temp.Transform(GetModelMatrix());
	SetBoundingBox(temp);
}

void Enemy::Translate(glm::vec3 translation)
{
	SetModelMatrix(GetModelMatrix() *= glm::translate(translation));
	auto temp = GetBoundingBox();
	//printf("Center: %f %f %f \n", temp.GetCenter().x, temp.GetCenter().y, temp.GetCenter().z);
	temp.Transform(GetModelMatrix());
	SetBoundingBox(temp);
}

void Enemy::Scale(glm::vec3 scale)
{
	SetModelMatrix(GetModelMatrix() *= glm::scale(scale));
	auto temp = GetBoundingBox();
	temp.Transform(GetModelMatrix());
	SetBoundingBox(temp);
}

void Enemy::SetRotationMat(glm::mat4 mat) {}
void Enemy::SetTranslationMat(glm::mat4 mat) {}
void Enemy::SetScaleMat(glm::mat4 mat) {}