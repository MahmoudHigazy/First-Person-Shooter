#ifndef Player_h__
#define Player_h__

#include "../middleware/includes/gl/glew.h"
#include "../middleware/includes/gl/glfw3.h"

#include "Shaders/shader.hpp"
#include "Model.h"
#include <memory>
#include "FirstPersonCamera.h"
#include "Model3D.h"
#include "ShaderProgram.h"
#include "CollisionManager.h"

#include"Gun.h"
#include "Bullet.h"


class Player
{
public:
	int Health;
	Gun*  myGun;
	//std::unique_ptr<Model3D> Gun;
	glm::mat4 TranslateMat;
	glm::mat4 RotateMat;
	glm::mat4 ScaleMat;
	glm::mat4 GunMat;
	std::unique_ptr<FirstPersonCamera> myCamera;

	bool CheckHealth();
	// GUN
	void UpdateGunModelMatrix();
	void UpdateGunTranslateMat();
	void UpdateGunRotateMat(double deltaY, double deltaX);
	void InitializeModelMatrix();
	void InitializeGunModel();
	void DrawGun( ShaderProgram & shader);
	void RotateGun();
	Bullet* Shoot(ShaderProgram* fShader);

	// Camera
	void InitializeCamera(double Width, double Height);
	void UpdateCamera();//check walls and update view matrix
	void MoveForward(double value);//call camera walk
	void MoveRight(double value); // call strafe
	bool RotateCamera(double deltaY, double deltaX);
	glm::mat4 GetCameraVP();
	
	
	glm::vec3 Position;
	glm::vec3 Direction;
	Player(glm::vec3 fPosition, glm::vec3 fDirection);
	
	~Player();
};

#endif // Player_h__