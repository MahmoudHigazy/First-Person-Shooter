#include "Player.h"


Player::Player(glm::vec3 fPosition, glm::vec3 fDirection)
{
	Position = fPosition;
	Direction = fDirection;

}

Player::~Player()
{
}

void Player::InitializeModelMatrix()
{

	TranslateMat = glm::translate(myCamera->mPosition + myCamera->GetLookDirection() - (myCamera->mUp *glm::vec3(0.5f, 0.5f, 0.5f)));
	RotateMat = glm::rotate(-90.0f, glm::vec3(0, 1, 0));
	ScaleMat = glm::scale(vec3(0.004, 0.004, 0.004));
	

	
	myGun->SetTranslationMat(TranslateMat);
	myGun->SetRotationMat(RotateMat);
	myGun->SetScaleMat(ScaleMat);
	GunMat = TranslateMat*RotateMat*ScaleMat;
	
	
	myGun->UpdateModelMatrix();
	auto temp = myGun->GetBoundingBox();
	temp.Transform(myGun->GetModelMatrixGun());
	myGun->SetBoundingBox(temp);

}

void Player::InitializeGunModel()
{
	myGun = (new Gun( Position,  Direction));	
	InitializeModelMatrix();
}

void Player::UpdateGunRotateMat(double deltaY,double deltaX)
{
	RotateMat = glm::rotate((float)deltaY, myCamera->mRight)*glm::rotate((float)deltaX, myCamera->mUp)*RotateMat;
	glm::mat4 Rot = glm::rotate((float)deltaY, myCamera->mRight)*glm::rotate((float)deltaX, myCamera->mUp)*myGun->R;
	myGun->SetRotationMat(Rot);
}

void Player::UpdateGunTranslateMat()
{
	TranslateMat = glm::translate(myCamera->mPosition + myCamera->GetLookDirection() - (myCamera->mUp *glm::vec3(0.5f, 0.5f, 0.5f)));
	myGun->SetTranslationMat(TranslateMat);
}

void Player::UpdateGunModelMatrix()
{
	UpdateGunTranslateMat();
	GunMat = TranslateMat*RotateMat*ScaleMat;
	glm::mat4 Mat = myGun->GetModelMatrixGun();
	myGun->UpdateModelMatrix();
	auto temp = myGun->GetBoundingBox();
	temp.Transform(myGun->GetModelMatrixGun());
	myGun->SetBoundingBox(temp);


}

void Player::DrawGun(ShaderProgram & shader)
{
	myGun->Render(&shader, GunMat);

}

Bullet* Player::Shoot(ShaderProgram* fShader) {
	return new Bullet(fShader, myCamera->mPosition, myCamera->GetLookDirection());
}


void Player::InitializeCamera(double Width,double Height)
{
	myCamera = std::unique_ptr<FirstPersonCamera>(new FirstPersonCamera());

	// Projection matrix : 
	myCamera->SetPerspectiveProjection(45.0f, (float)Width / (float)Height, 0.1f, 20000.0f);

	// View matrix : 
	myCamera->Reset(
		+0.0f, -195.0f, +800.0f,// Camera Position
		+0.0f, -195.0f, +0.0f,// Look at Point
		+0.0f, +1.0f, +0.0f // Up Vector
		);
}
void Player::UpdateCamera()
{
	myCamera->CheckWalls();
	myCamera->UpdateViewMatrix();
}
void Player::MoveForward(double value)
{
	myCamera->Walk(value);
}
void Player::MoveRight(double value)
{
	myCamera->Strafe(value);
}

bool Player::RotateCamera(double deltaY, double deltaX)
{
	myCamera->Yaw(deltaX);
	return (myCamera->Pitch(deltaY));
}

glm::mat4 Player::GetCameraVP()
{
	glm::mat4 VP = myCamera->GetProjectionMatrix() * myCamera->GetViewMatrix();
	return VP;
}