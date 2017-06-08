#ifndef Renderer_h__
#define Renderer_h__

#include "../middleware/includes/gl/glew.h"
#include "../middleware/includes/gl/glfw3.h"

#include "Shaders/shader.hpp"
#include "Model.h"
#include <memory>
#include "FirstPersonCamera.h"
#include"KeyFrameAnimationShader.h"
#include"md2model.h"
#include "Model3D.h"
#include "ShaderProgram.h"
#include "Enemy.h"
#include "CollisionManager.h"
#include "House.h"
#include "Fruit.h"
#include "Player.h"
#include "Bullet.h"
#include "Tree.h"
#include "Gun.h"

#define PI 3.14159265359


class Renderer
{
	ShaderProgram shader;

	GLuint programID;
	GLuint VPID;
	GLuint ModelMatrixID;
	GLuint TexID;

	float Env_Size = 1000.0f;
	float Env_Height = 200.0f;
	float jmpCount= 0;
	float jmpValue = 0.05;
	bool jmpUp = 0;
	bool jmpDown = 0;
	float jmpDownWait = 0;

	std::unique_ptr<Model> mySquare;
	std::unique_ptr<Model> mySquare1;
	std::unique_ptr<FirstPersonCamera> myCamera;
	std::unique_ptr<Player> Hero;
	//std::unique_ptr<Model3D> Gun;
	std::unique_ptr<Model> myRoom, Cursor, Square;

	glm::mat4 GunMat;
	glm::mat4 floorM;
	glm::mat4 RoomMat;
	glm::mat4 CursorMat;
	glm::mat4 R, T, S;

	Texture * CursorTexture;
	Texture * face1;
	Texture * face2;
	Texture * face3;
	Texture * face4;
	Texture * face5;
	Texture * face6;
	Texture * GameOverTexture;
	Texture * YouWonTexture;

	int ApplyTexOnlY ;
	int EnemiesCount;
	int TreesCnt;
	int HouseCount;
	int ZombieMinX;
	int ZombieMaxX;
	int TreeMinX;
	int TreeMaxX;
	int TreeMinZ;
	int TreeMaxZ;

	bool GameOver = 0;
	bool YouWon = 0;


	Model3D* staticModel;
	Model3D* model3D;
	
	
	vector<Bullet*>bullets;
	vector< Fruit* > fruits;
	vector < House * > Houses;
	vector<Tree*> Trees;
	vector<Enemy* > Enemies;

	KeyFrameAnimationShader animatedModelShader;

	vec3 ambientLight;
	vec3 lightPosition;
	vec3 eyePosition;


	CollisionManager collisionManager;

public:
	Renderer();
	~Renderer();
	bool coll;
	void Initialize();
	void InitRoom(std::unique_ptr<Model> &);
	void InitCursor(std::unique_ptr<Model> &);
	void InitSquare(std::unique_ptr<Model>&);

	bool Draw();

	void HandleKeyboardInput(int key, int action);
	void HandleMouse(double deltaX, double deltaY);

	void Update(double deltaTime);
	void Cleanup();

	int Randomize(int index, int now, float posX, float posZ);
	void Tree_Coord(int i,int &x, int &z);
	void MoveAnimatedModel(int index);
	void HandleMouseClick(double MouseXPos, double MouseYPos);
};

#endif 