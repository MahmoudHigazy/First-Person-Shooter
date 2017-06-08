#include"../middleware/includes/glm/glm.hpp"
#include"../middleware/includes/glm/gtx/transform.hpp"
#include "../middleware/includes/glm/gtc/matrix_transform.hpp"

#include "Renderer.h"
#include "Application Manager\ApplicationManager.h"

#include <stdio.h>     
#include <stdlib.h>     
#include <time.h> 


Renderer::Renderer()
{

}

Renderer::~Renderer()
{
	Cleanup();
}

void Renderer::Initialize()
{
	coll = 0;
	face1 = new Texture("forest_top.bmp", 0); //right
	face2 = new Texture("forest_top.bmp", 1); //left
	face3 = new Texture("forest_top.bmp", 2); //up
	face4 = new Texture("forest_bottom.bmp", 3); //down
	face5 = new Texture("forest_top.bmp", 4); //front
	face6 = new Texture("forest_top.bmp", 5); //back



	/////////////////////////
	CursorTexture = new Texture("Sniper.png", 6);
	GameOverTexture = new Texture("OVER.jpg", 7);
	YouWonTexture = new Texture("UWon.jpg", 8);

	InitCursor(Cursor);
	Cursor->Initialize();

	InitRoom(myRoom);
	myRoom->Initialize();
	
	InitSquare(Square);
	Square->Initialize();

	//////////////////////////////////////////////////////////////////////////
	// Create and compile our GLSL program from the shaders
	shader.LoadProgram();

	// Use our shader
	shader.UseProgram();

	Hero = std::unique_ptr<Player>(new Player(glm::vec3(0, 0, 0), glm::vec3(0)));

	//////////////////////////////////////////////////////////////////////////
	// Camera
	Hero->InitializeCamera(ApplicationManager::WindowSizeWidth, ApplicationManager::WindowSizeHeight);
	eyePosition = Hero->myCamera->GetEyePosition();
	//////////////////////////////////////////////////////////////////////////
	
	TreesCnt = 5;
	 TreeMinX=-200;
	 TreeMaxX= 200;
	 TreeMinZ = -700;
	 TreeMaxZ = 700;
	 int TreeRangeX = TreeMaxX*2 ;
	 int TreeRangeZ = TreeMaxZ * 2;
/*	for (int i = TreeMinX; i <= TreeMaxX; i += 10)
	{
		for (int j = TreeMinX; j <= TreeMaxX; j += 10)
		{
			Tree* Tree1;
			if (TreesCnt <= 10)
			 Tree1 = (new Tree(&shader, glm::vec3(i, -Env_Height, j), glm::vec3(0), vec3 (5,3,3)));
			else 
				 Tree1 = (new Tree(&shader, glm::vec3(i, -Env_Height, j), glm::vec3(0), vec3(4,6, 6)));

			Trees.push_back(Tree1);
			TreesCnt++;
		}
		if (TreesCnt >= 20)break;
	}

	*/

	 Model3D* MyTree = new Model3D();
	 MyTree->LoadFromFile("data/models/3DS/tree6/Tree N161113.3ds", true);
	 for (int i = 0; i<TreesCnt; i++)
	 {
		 srand(time(NULL));
		 int x = rand() % (TreeRangeX/2);
		 int z = rand() % (TreeRangeZ/2);
		 int s = rand() % 2;
		 int ss = rand() % 2;
		 if (s == 0) s = -1;
		 if (ss == 0) ss = -1;
		 int typ = rand() % 2;
		 Tree* Tree1;
		 if (typ==0)
			 Tree1 = (new Tree(MyTree, &shader, glm::vec3(s*x, -200, ss*z), glm::vec3(0), vec3(7, 10, 7)));
		 else
			 Tree1 = (new Tree(MyTree, &shader, glm::vec3(s*x, -200, ss*z), glm::vec3(0), vec3(5, 7, 5)));
		 
		 Trees.push_back(Tree1);
		 collisionManager.AddCollidableModel(Tree1);
		 bool tmam = 0;
	/*	 for (int j = 0; j < collisionManager.CollidableModels.size() - 1; j++)
		 {
			 if (Tree1->GetBoundingBox().IsIntersecting(collisionManager.CollidableModels[j]->GetBoundingBox()))
			 {
				 Trees.pop_back();
				 collisionManager.RemoveCollidableModel(Tree1);
				 delete Tree1;
				 i--;
				 printf("ms7ha!!\n");
				 break;
			 }
		 }*/
		 printf(" tree size  % d \n", Trees.size());
	 }

	bool mshTmam = 1;
	while (mshTmam)
	{
		int x = rand() % 200;
		int z = rand() % 200;
		int sx = rand() % 2;
		if (sx == 1)
			sx = -1;
		int sz = rand() % 2;
		if (sz == 1)
			sz = -1;
		Fruit* fruit = (new Fruit(&shader, glm::vec3(x*sx, -(Env_Height-2), z*sz), glm::vec3(0)));
		fruit->Scale(vec3(0.3, 0.3, 0.3));
		fruits.push_back(fruit);
		collisionManager.AddCollidableModel(fruit);
		bool tmam = 0;
		for (int j = 0; j < collisionManager.CollidableModels.size()-1; j++)
		{
			if (fruit->GetBoundingBox().IsIntersecting(collisionManager.CollidableModels[j]->GetBoundingBox()))
			{
				fruits.pop_back();
				collisionManager.RemoveCollidableModel(fruit);
				delete fruit;
				tmam = 1;
				break;
			}
		}
		if (tmam == 0) mshTmam = 0;
	}
	for (int i = 0; i < fruits.size(); i++)
	{
		collisionManager.AddCollidableModel(fruits[i]);
	}

	animatedModelShader.LoadProgram();
	int x = 0, z = 0;
	srand(time(NULL));
	EnemiesCount = 7;
	 ZombieMinX = TreeMinX+25;
	 ZombieMaxX = TreeMaxX-25;
	int s = 0;
	for (int i = 0; i < (EnemiesCount/2) +1; i++)
	{
		Enemy* enemy = new Enemy(1, &shader, glm::vec3(x, -(Env_Height-2.3), z), glm::vec3(0));
		Enemies.push_back(enemy);

		x = rand() % (int)150;
		z = rand() % (int)150;
		s = rand() % 2;
		if (s == 0)
		{
			x = ZombieMinX + x;
			z = ZombieMinX + z;
		}
		else
		{
			x = ZombieMaxX - x;
			z = ZombieMaxX - z;
		}

		collisionManager.AddCollidableModel(enemy);
		for (int j = 0; j < collisionManager.CollidableModels.size()-1; j++)
		{
			if (enemy->GetBoundingBox().IsIntersecting(collisionManager.CollidableModels[j]->GetBoundingBox()))
			{
				Enemies.pop_back();
				i--;
				collisionManager.RemoveCollidableModel(enemy);
				delete enemy;
				break;
			}
		}

	}
	for (int i = 0; i < EnemiesCount/2; i++)
	{
		Enemy* enemy = new Enemy(0, &shader, glm::vec3(x, -(Env_Height-2.3), z), glm::vec3(0));
		Enemies.push_back(enemy);
		
		x = rand() % (int)150;
		z = rand() % (int)150;
		s = rand() % 2;
		if (s == 0)
		{
			x = ZombieMinX + x;
			z = ZombieMinX + z;
		}
		else
		{
			x = ZombieMaxX - x;
			z = ZombieMaxX - z;
		}

		collisionManager.AddCollidableModel(enemy);
		for (int j = 0; j < collisionManager.CollidableModels.size()-1; j++)
		{
			if (enemy->GetBoundingBox().IsIntersecting(collisionManager.CollidableModels[j]->GetBoundingBox()))
			{
				Enemies.pop_back();
				i--;
				collisionManager.RemoveCollidableModel(enemy);
				break;
			}
		}
	}

	//Houses & fruits
	Model3D* Myhouse = new Model3D();
	Myhouse->LoadFromFile("data/models/3DS/House/house.obj", true);
	//Myhouse->LoadFromFile("data/models/obj/Bear/Bear.obj", true);
	//Myhouse->LoadFromFile("data/models/obj/Grass/grass.obj", true);
	
	//House* myHouse1 = (new House(&shader, glm::vec3(300, -Env_Height, -350), glm::vec3(0)));
	//House* myHouse2 = (new House(&shader, glm::vec3(-300, -Env_Height, 350), glm::vec3(0)));
	/*House * myHouse1 = (new House(&shader, glm::vec3(300, -Env_Height, -350), glm::vec3(0), Myhouse));
	Houses.push_back(myHouse1);
	House* myHouse2 = (new House(&shader, glm::vec3(-300, -Env_Height, 350), glm::vec3(0), Myhouse));
	myHouse2->Rotate(180.0f, glm::vec3(0, 1, 0));
	Houses.push_back(myHouse2);*/
	
	House* myHouse1;
	HouseCount = 50;
	for (int xCoord = 450; xCoord < 999; xCoord+=50)
	{
		if (HouseCount == 0)
			break;
		for (int zCoord = 600; zCoord < 999; zCoord += 100)
		{
			if (HouseCount == 0)
				break;
			int sx = rand() % 2;
			if (sx == 0)
				sx = -1;
			int sz = rand() % 2;
			if (sz == 0)
				sz = -1;
			int rot = rand() % 2;
			myHouse1 = (new House(&shader, glm::vec3(sx*(xCoord), -Env_Height, sz*(zCoord)), glm::vec3(0), Myhouse));
			if (rot==1)
				myHouse1->Rotate(180.0f, glm::vec3(0, 1, 0));

			Houses.push_back(myHouse1);
			HouseCount--;
			collisionManager.AddCollidableModel(myHouse1);
			for (int j = 0; j < collisionManager.CollidableModels.size() - 1; j++)
			{
				if (myHouse1->GetBoundingBox().IsIntersecting(collisionManager.CollidableModels[j]->GetBoundingBox()))
				{
					Houses.pop_back();
					HouseCount++;
					collisionManager.RemoveCollidableModel(myHouse1);
					break;
				}
			}
			printf(" house %d \n", Houses.size());

		}
	}
	/*for (int i = 0; i < Houses.size(); i++)
	{
		collisionManager.AddCollidableModel(Houses[i]);

	}*/


Hero->InitializeGunModel();
	collisionManager.AddCollidableModel(Hero->myGun);
	TexID = glGetUniformLocation(shader.programID,"ApplyTexOnlY");
	ApplyTexOnlY = 0;
}

bool Renderer::Draw()
{
	shader.UseProgram();
	glm::mat4 VP = Hero->GetCameraVP();
	glUniform1i(TexID, ApplyTexOnlY);
	eyePosition = Hero->myCamera->GetEyePosition();
	if (Hero->myGun->health <= 0)
	{
		GameOver = 1;
	}
	if (Enemies.empty())
		YouWon = 1;
	if (GameOver||YouWon)
	{
		ApplyTexOnlY = 1;
		glUniform1i(TexID, ApplyTexOnlY);
		Hero->myCamera->Reset(
		+0.0f,0.0f, -2.5f,// Camera Position
		+0.0f, 0.0f, +0.0f,// Look at Point
		+0.0f, +1.0f, +0.0f // Up Vector
		);
		Hero->UpdateCamera();
		mat4 id = mat4(1.0f);
		shader.BindVPMatrix(&VP[0][0]);
		shader.BindModelMatrix(&id[0][0]);
		if (GameOver)
			GameOverTexture->Bind();
		else
			YouWonTexture->Bind();

		Square->Draw();
		return GameOver||YouWon;
	}
	
	// light 
	ambientLight = vec3(0.3f, 0.3f, 0.3f);
	lightPosition = vec3(0, 0.5, 0);
	shader.BindAmbientLight(&ambientLight[0]);
	shader.BindLightPosition(&lightPosition[0]);
	shader.BindEyePosition(&Hero->myCamera->GetEyePosition()[0]);
	

	// room
	RoomMat = glm::scale(glm::vec3(Env_Size, Env_Height, Env_Size));

	shader.BindVPMatrix(&VP[0][0]);
	shader.BindModelMatrix(&RoomMat[0][0]);

	//room

	glBindVertexArray(myRoom->mVertexArrayObjectID);
	
	face1->Bind();
	glDrawArrays(GL_TRIANGLES, 0, 6);
	face2->Bind();
	glDrawArrays(GL_TRIANGLES, 6, 6);
	face3->Bind();
	glDrawArrays(GL_TRIANGLES, 12, 6);
	face4->Bind();
	glDrawArrays(GL_TRIANGLES, 18, 6);
	face5->Bind();
	glDrawArrays(GL_TRIANGLES, 24, 6);
	face6->Bind();
	glDrawArrays(GL_TRIANGLES, 30, 6);


	float angle1 = atan2(Hero->myCamera->GetLookDirection().z*-1, Hero->myCamera->GetLookDirection().x) * 180 / PI;

	CursorMat =
		glm::translate(Hero->myCamera->mPosition + Hero->myCamera->GetLookDirection())
		*glm::rotate(angle1, glm::vec3(0, 1, 0))
		*glm::scale(vec3(0.01, 0.01, 0.01));
	shader.BindVPMatrix(&VP[0][0]);
	shader.BindModelMatrix(&CursorMat[0][0]);
	CursorTexture->Bind();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	Cursor->Draw();
	glDisable(GL_BLEND);

	
	Hero->DrawGun(shader);
	
	for (int i = 0; i < Trees.size(); i++)
	{
		Trees[i]->Render(VP, ambientLight, lightPosition, eyePosition);
	}

	for (int i = 0; i < Houses.size(); i++)
	{
		Houses[i]->Render(VP, ambientLight, lightPosition, eyePosition);

	}
	if (fruits.size() == 0)
	{
		bool mshTmam = 1;
		while (mshTmam)
		{
			int x = rand() % 200;
			int z = rand() % 200;
			int sx = rand() % 2;
			if (sx == 1)
				sx = -1;
			int sz = rand() % 2;
			if (sz == 1)
				sz = -1;
			Fruit* fruit = (new Fruit(&shader, glm::vec3(x*sx, -(Env_Height - 2), z*sz), glm::vec3(0)));
			fruit->Scale(vec3(0.3, 0.3, 0.3));
			fruits.push_back(fruit);
			collisionManager.AddCollidableModel(fruit);
			bool tmam = 0;
			for (int j = 0; j < collisionManager.CollidableModels.size() - 1; j++)
			{
				if (fruit->GetBoundingBox().IsIntersecting(collisionManager.CollidableModels[j]->GetBoundingBox()))
				{
					fruits.pop_back();
					collisionManager.RemoveCollidableModel(fruit);
					delete fruit;
					tmam = 1;
					break;
				}
			}
			if (tmam == 0) mshTmam = 0;
		}
	}
	for (int i = 0; i < fruits.size(); i++)
	{
		fruits[i]->Render(VP, ambientLight, lightPosition, eyePosition);

	}
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->Render(VP, ambientLight, lightPosition, eyePosition);
	}
	for (int i = 0; i < Enemies.size(); i++)
	{
		Enemies[i]->Render(VP, ambientLight, lightPosition, eyePosition);
		if (Enemies[i]->Destroyed()) {
			Enemies[i]->counter--;
		}
		else MoveAnimatedModel(i);
	}

	
	return GameOver;
}

void Renderer::Tree_Coord(int i,int &x, int &z)
{
	srand(i);
	
}

void  Renderer::InitSquare(std::unique_ptr<Model>& nSquare)
{
	nSquare = std::unique_ptr<Model>(new Model());
	double x = 2;
	double y = 1.125;

	GLfloat verts[] =
	{
		-1*x, -1*y, 0,
		-1*x, 1*y, 0,
		1*x, -1*y, 0,

		-1*x, 1*y, 0,
		1*x, -1*y, 0,
		1*x, 1*y, 0
	};
	GLfloat Uv[]=
	{
		1,1,
		1,0,
		0,1,

		1,0,
		0,1,
		0,0
	};
	for (int i = 0; i < 18-2; i+=3)
	{
		nSquare->VertexData.push_back(vec3(verts[i], verts[i + 1], verts[i + 2]));
		nSquare->ColorData.push_back(vec3(1,1, 1));
	}
	for (int i = 0; i < 12 - 1; i+=2)
	{
		nSquare->UVData.push_back(vec2(Uv[i], Uv[i + 1]));
	}
}


void Renderer::InitRoom(std::unique_ptr<Model> & Room)
{
	Room = std::unique_ptr<Model>(new Model());
	GLfloat norm[] =
	{
		1,0,0,
		1,0,0,
		1,0,0,

		1,0,0,
		1,0,0,
		1,0,0,
		/////////
		-1,0,0,
		-1,0,0,
		-1,0,0,

		-1,0,0,
		-1,0,0,
		-1,0,0,
		///////////////
		0,1,0,
		0,1,0,
		0,1,0,

		0,1,0,
		0,1,0,
		0,1,0,
		//////////////////
		0,-1,0,
		0,-1,0,
		0,-1,0,

		0,-1,0,
		0,-1,0,
		0,-1,0,
		///////////////
		0,0,-1,
		0,0,-1,
		0,0,-1,

		0,0,-1,
		0,0,-1,
		0,0,-1,
		/////////
		0,0,1,
		0,0,1,
		0,0,1,

		0,0,1,
		0,0,1,
		0,0,1,


	};
	GLfloat color[] =
	{
		// right
		0.5, 0.0, 0.0,
		0.5, 0.0, 0.0,
		0.5, 0.0, 0.0,

		0.5, 0.0, 0.0,
		0.5, 0.0, 0.0,
		0.5, 0.0, 0.0,

		//left
		0.5, 0.0, 0.0,
		0.5, 0.0, 0.0,
		0.5, 0.0, 0.0,

		0.5, 0.0, 0.0,
		0.5, 0.0, 0.0,
		0.5, 0.0, 0.0,

		//up
		0.0, 0.0, 0.5,
		0.0, 0.0, 0.5,
		0.0, 0.0, 0.5,

		0.0, 0.0, 0.5,
		0.0, 0.0, 0.5,
		0.0, 0.0, 0.5,

		//down
		0.0, 0.0, 0.5,
		0.0, 0.0, 0.5,
		0.0, 0.0, 0.5,

		0.0, 0.0, 0.5,
		0.0, 0.0, 0.5,
		0.0, 0.0, 0.5,

		//front
		0.0, 0.5, 0.0,
		0.0, 0.5, 0.0,
		0.0, 0.5, 0.0,

		0.0, 0.5, 0.0,
		0.0, 0.5, 0.0,
		0.0, 0.5, 0.0,

		//back
		0.0, 0.5, 0.0,
		0.0, 0.5, 0.0,
		0.0, 0.5, 0.0,

		0.0, 0.5, 0.0,
		0.0, 0.5, 0.0,
		0.0, 0.5, 0.0

	};
	GLfloat cube[] = {

		//right face
		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,

		//right face
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,

		//left face 
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,

		//left face
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,

		//up face
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,

		//up face
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,

		//down face
		1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		//down face
		1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,

		//front face
		-1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,

		//front face
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,


		//back face
		1.0f, 1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,

		//back face
		1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f
	};

	GLfloat UV[] = {

		//right
		1, 0,
		0, 1,
		0, 0,

		0, 1,
		1, 0,
		1, 1,

		//left
		0, 1,
		1, 1,
		1, 0,


		0, 1,
		1, 0,
		0, 0,

		//up
		0, 1,
		0, 0,
		1, 0,


		0, 1,
		1, 0,
		0, 0,
		//down

		0, 1,
		1, 0,
		0, 0,


		0, 1,
		1, 1,
		1, 0,

		//front
		1, 0,
		1, 1,
		0, 1,


		0, 0,
		1, 0,
		0, 1,

		//back

		0, 0,
		1, 1,
		1, 0,


		0, 0,
		0, 1,
		1, 1


	};


	for (int i = 0; i < 108 - 2; i += 3)
	{
		Room->VertexData.push_back(glm::vec3(cube[i], cube[i + 1], cube[i + 2]));
	}
	for (int i = 0; i < 108 - 2; i += 3)
	{
		Room->ColorData.push_back(glm::vec3(color[i], color[i + 1], color[i + 2]));
	}

	for (int i = 0; i < 72 - 1; i += 2)
	{
		Room->UVData.push_back(glm::vec2(UV[i], UV[i + 1]));
	}

	int c = 0;
	for (int i = 0; i < Room->VertexData.size(); i += 3)
	{
		vec3 v1 = Room->VertexData[i], v2 = Room->VertexData[i + 1], v3 = Room->VertexData[i + 2];
		vec3 u = v2 - v1, v = v3 - v1;
		vec3 normal = cross(u, v);
		c++;
		if (c != 5 && c != 6)normal = -normal;
		Room->NormalsData.push_back(normalize(normal));
		Room->NormalsData.push_back(normalize(normal));
		Room->NormalsData.push_back(normalize(normal));
	}
	/*for (int i = 0; i < 108; i += 3)
	{
		Room->NormalsData.push_back(-vec3(norm[i],norm[i+1],norm[i+2]));

	}*/
}

void Renderer::InitCursor(std::unique_ptr<Model> & Cur)
{
	Cur = std::unique_ptr<Model>(new Model());

	GLfloat cube[] = {

		//right face
		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,

		//right face
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,

		//left face 
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,

		//left face
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,

		//up face
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,

		//up face
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, -1.0f,
		-1.0f, 1.0f, 1.0f,

		//down face
		1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		//down face
		1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,
		-1.0f, -1.0f, -1.0f,

		//front face
		-1.0f, 1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,

		//front face
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,


		//back face
		1.0f, 1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, 1.0f, -1.0f,

		//back face
		1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f
	};

	GLfloat UV[] = {

		//right
		1, 0,
		0, 1,
		0, 0,

		0, 1,
		1, 0,
		1, 1,

		//left
		0, 1,
		1, 1,
		1, 0,


		0, 1,
		1, 0,
		0, 0,

		//up
		0, 1,
		0, 0,
		1, 0,


		0, 1,
		1, 0,
		0, 0,
		//down

		0, 1,
		1, 0,
		0, 0,


		0, 1,
		1, 1,
		1, 0,

		//front
		1, 0,
		1, 1,
		0, 1,


		0, 0,
		1, 0,
		0, 1,

		//back

		0, 0,
		1, 1,
		1, 0,


		0, 0,
		0, 1,
		1, 1


	};

	GLfloat norm[] =
	{
		1,0,0,
		1,0,0,
		1,0,0,

		1,0,0,
		1,0,0,
		1,0,0,
		/////////
		-1,0,0,
		-1,0,0,
		-1,0,0,

		-1,0,0,
		-1,0,0,
		-1,0,0,
		///////////////
		0,1,0,
		0,1,0,
		0,1,0,

		0,1,0,
		0,1,0,
		0,1,0,
		//////////////////
		0,-1,0,
		0,-1,0,
		0,-1,0,

		0,-1,0,
		0,-1,0,
		0,-1,0,
		///////////////
		0,0,-1,
		0,0,-1,
		0,0,-1,

		0,0,-1,
		0,0,-1,
		0,0,-1,
		/////////
		0,0,1,
		0,0,1,
		0,0,1,

		0,0,1,
		0,0,1,
		0,0,1,


	};
	for (int i = 0; i < 108 - 2; i += 3)
	{
		Cur->VertexData.push_back(glm::vec3(cube[i], cube[i + 1], cube[i + 2]));
	}
	for (int i = 0; i < 108 - 2; i += 3)
	{
		Cur->ColorData.push_back(glm::vec3(1, 1, 1));
	}
	for (int i = 0; i < 72 - 1; i += 2)
	{
		Cur->UVData.push_back(glm::vec2(UV[i], UV[i + 1]));
	}
	/*for (int i = 0; i < Cur->VertexData.size(); i += 3)
	{
		vec3 v1 = Cur->VertexData[i], v2 = Cur->VertexData[i + 1], v3 = Cur->VertexData[i + 2];
		vec3 u = v2 - v1, v = v3 - v1;
		vec3 normal = cross(u, v);
		Cur->NormalsData.push_back(normalize(normal));
		Cur->NormalsData.push_back(normalize(normal));
		Cur->NormalsData.push_back(normalize(normal));
	}
	*/
	for (int i = 0; i < 108; i += 3)
	{
		Cur->NormalsData.push_back(-vec3(norm[i], norm[i + 1], norm[i + 2]));

	}
}

void Renderer::Cleanup()
{
	glDeleteProgram(programID);
}

void Renderer::Update(double deltaTime)
{
	if (jmpDownWait > 0)
		jmpDownWait--;
	if (jmpUp)
	{
		while (jmpCount < 50)
		{
			Hero->myCamera->Fly(jmpValue+0.2);

			Hero->UpdateGunModelMatrix();
			collisionManager.UpdateCollisions();

			jmpCount++;
			printf(" jmp up \n");
		}
		jmpDown = 1;
		// kol ma nzwd el models n2ll el var dah
		jmpDownWait = 0;
		jmpUp = 0;
	}
	else if (jmpDown&&jmpDownWait <= 0)
	{
		jmpDown = 0;
		jmpDownWait = 0;
		while (jmpCount > 0)
		{
			Hero->myCamera->Fly(-(jmpValue+0.2));
			Hero->UpdateGunModelMatrix();
			collisionManager.UpdateCollisions();

			jmpCount--;
			printf(" jmp down \n");
		}
	}


	for (int i = 0; i < Enemies.size(); i++) {
		Enemies[i]->UpdateAnimation(deltaTime);
		if (Enemies[i]->Destroyed() && Enemies[i]->counter <= 0) {
			collisionManager.RemoveCollidableModel(Enemies[i]);
			Enemies.erase(Enemies.begin() + i);
			i--;
		}
	}

	for (int i = 0; i < bullets.size(); i++) {
		bullets[i]->Update(deltaTime);
		if (bullets[i]->Destroyed()) {
			collisionManager.RemoveCollidableModel(bullets[i]);
			bullets.erase(bullets.begin() + i);
			i--;
		}
	}

	for (int i = 0; i < fruits.size(); i++) {
		if (fruits[i]->Destroyed()) {
			collisionManager.RemoveCollidableModel(fruits[i]);
			fruits.erase(fruits.begin() + i);
			i--;
		}
	}
	collisionManager.UpdateCollisions();

	Hero->UpdateCamera();
	//Hero->UpdateGunModelMatrix();
}

void Renderer::HandleKeyboardInput(int key, int action)
{
	
	float speed = 3;
	float move;
	char dir='s';
	switch (key)
	{
		//Moving forward
	case GLFW_KEY_UP:
	case GLFW_KEY_W:
	Hero->MoveForward(speed*1.0);
		coll = collisionManager.UpdateCollisions();
		if (coll|| Hero->myCamera->mPosition.z>995.7|| Hero->myCamera->mPosition.z<-995.7
			|| Hero->myCamera->mPosition.x>995.7 || Hero->myCamera->mPosition.x<-995.7)
			Hero->MoveForward(-speed*1.0);
		Hero->UpdateGunModelMatrix();
		
		move = 1;
		dir = 'f';
		break;

		//Moving backword
	case GLFW_KEY_DOWN:
	case GLFW_KEY_S:
		Hero->MoveForward(-speed*1.0);
		Hero->UpdateGunModelMatrix();
		coll = collisionManager.UpdateCollisions();
		if (coll || Hero->myCamera->mPosition.z>995.7 || Hero->myCamera->mPosition.z<-995.7
			|| Hero->myCamera->mPosition.x>995.7 || Hero->myCamera->mPosition.x<-995.7)
			Hero->MoveForward(speed*1.0);
		Hero->UpdateGunModelMatrix();
	
		move = -1;
		dir = 'f';
		break;

		// Moving right
	case GLFW_KEY_RIGHT:
	case GLFW_KEY_D:
	Hero->MoveRight(speed*0.4);
		Hero->UpdateGunModelMatrix();
		coll = collisionManager.UpdateCollisions();
		if (coll|| Hero->myCamera->mPosition.x>995.7 || Hero->myCamera->mPosition.x<-995.7
			|| Hero->myCamera->mPosition.z>995.7 || Hero->myCamera->mPosition.z<-995.7)
			Hero->MoveRight(-speed*0.4);
		Hero->UpdateGunModelMatrix();
		
		move = 0.4;
		dir = 'r';

		break;

		// Moving left
	case GLFW_KEY_LEFT:
	case GLFW_KEY_A:
		Hero->MoveRight(speed*-0.4);
		Hero->UpdateGunModelMatrix();
		coll = collisionManager.UpdateCollisions();
		if (coll || Hero->myCamera->mPosition.x>995.7 || Hero->myCamera->mPosition.x<-995.7
			|| Hero->myCamera->mPosition.z>995.7 || Hero->myCamera->mPosition.z<-995.7)
			Hero->MoveRight(speed*0.4);
		Hero->UpdateGunModelMatrix();
		move = -0.4;
		dir = 'r';

		break;
	case GLFW_KEY_SPACE:
	{
		jmpUp = 1; break;
	}
		
	default:
		break;
	}
	
	
}

void Renderer::HandleMouseClick(double MouseXPos, double MouseYPos)
{
	PlaySound(TEXT("Shoot.wav"), NULL, SND_ASYNC);
	Bullet* bullet;
		bullet = Hero->Shoot(&shader);
		bullets.push_back(bullet);
		collisionManager.AddCollidableModel(bullet);
}

void Renderer::HandleMouse(double deltaX, double deltaY)
{
	deltaY *= 3.0;  deltaX *= 3.0;
	if (Hero->RotateCamera(deltaY, deltaX) == 0) deltaY = 0;
	Hero->UpdateGunRotateMat(deltaY, deltaX);
	Hero->UpdateGunModelMatrix();
}

void Renderer::MoveAnimatedModel(int index)
{
	//if (index == 1) Enemies[index]->now = 2;
	//glm::mat4 modelMatrix = Enemies[index]->GetModelMatrix();

	Enemies[index]->Translate(glm::vec3(0, -1*Enemies[index]->rateX, 0));
	//printf("%f %f %f now=%d\n", Enemies[index]->GetBoundingBox().GetCenter().x, Enemies[index]->GetBoundingBox().GetCenter().y, Enemies[index]->GetBoundingBox().GetCenter().z,Enemies[index]->now);
	srand(time(NULL));
	Enemies[index]->posX = Enemies[index]->GetBoundingBox().GetCenter().x;
	Enemies[index]->posZ = Enemies[index]->GetBoundingBox().GetCenter().z;
	if ((Enemies[index]->posX >= ZombieMaxX || (rand() % 100000 + 1) % (rand() % 10 + 1) == 0 && abs(Enemies[index]->lastX - Enemies[index]->posX)>(rand() % 50 + 10)) && Enemies[index]->now == 1)
	{
		Enemies[index]->lastX = Enemies[index]->posX;
		Enemies[index]->noww = Enemies[index]->now;
		Enemies[index]->now = Randomize(index, Enemies[index]->now, Enemies[index]->posX, Enemies[index]->posZ);
		//Enemies[index]->now = 2;
		if (Enemies[index]->now == 2) Enemies[index]->Rotate(180.0f, glm::vec3(0, 0, 1));
		if (Enemies[index]->now == 3) Enemies[index]->Rotate(90.0f, glm::vec3(0, 0, 1));
		if (Enemies[index]->now == 4) Enemies[index]->Rotate(270.0f, glm::vec3(0, 0, 1));
	}
	else if (((Enemies[index]->posX <=ZombieMinX ) ||( (rand() % 100000 + 1) % (rand() % 10 + 1) == 0 && abs(Enemies[index]->lastX - Enemies[index]->posX)>(rand() % 50 + 10))) && Enemies[index]->now == 2)
	{
		Enemies[index]->lastX = Enemies[index]->posX;
		Enemies[index]->noww = Enemies[index]->now;
		Enemies[index]->now = Randomize(index, Enemies[index]->now, Enemies[index]->posX, Enemies[index]->posZ);
		//Enemies[index]->now = 1; 
		if (Enemies[index]->now == 1) Enemies[index]->Rotate(180.0f, glm::vec3(0, 0, 1));
		if (Enemies[index]->now == 3) Enemies[index]->Rotate(270.0f, glm::vec3(0, 0, 1));
		if (Enemies[index]->now == 4) Enemies[index]->Rotate(90.0f, glm::vec3(0, 0, 1));
	}
	else if ((Enemies[index]->posZ <= ZombieMinX || (rand() % 100000 + 1) % (rand() % 10 + 1) == 0 && abs(Enemies[index]->lastZ - Enemies[index]->posZ)>(rand() % 50 + 10)) && Enemies[index]->now == 3)
	{
		Enemies[index]->lastZ = Enemies[index]->posZ;
		Enemies[index]->noww = Enemies[index]->now;
		Enemies[index]->now = Randomize(index, Enemies[index]->now, Enemies[index]->posX, Enemies[index]->posZ);
		//now = 1;
		if (Enemies[index]->now == 4) Enemies[index]->Rotate(180.0f, glm::vec3(0, 0, 1));
		if (Enemies[index]->now == 2) Enemies[index]->Rotate(90.0f, glm::vec3(0, 0, 1));
		if (Enemies[index]->now == 1) Enemies[index]->Rotate(270.0f, glm::vec3(0, 0, 1));
	}
	else if ((Enemies[index]->posZ >=ZombieMaxX|| (rand() % 100000 + 1) % (rand() % 10 + 1) == 0 && abs(Enemies[index]->lastZ - Enemies[index]->posZ)>(rand() % 50 + 10)) && Enemies[index]->now == 4)
	{
		Enemies[index]->lastZ = Enemies[index]->posZ;
		Enemies[index]->noww = Enemies[index]->now;
		Enemies[index]->now = Randomize(index, Enemies[index]->now, Enemies[index]->posX, Enemies[index]->posZ);
		//now = 2;
		if (Enemies[index]->now == 3) Enemies[index]->Rotate(180.0f, glm::vec3(0, 0, 1));
		if (Enemies[index]->now == 1) Enemies[index]->Rotate(90.0f, glm::vec3(0, 0, 1));
		if (Enemies[index]->now == 2) Enemies[index]->Rotate(270.0f, glm::vec3(0, 0, 1));
	}
	if (Enemies[index]->posX >=ZombieMaxX || Enemies[index]->posX <= -(Env_Size + 0.7) || Enemies[index]->posZ >= (Env_Size + 0.7) || Enemies[index]->posZ <= -(Env_Size + 0.7))
	{
		Enemies[index]->Rotate(180.0f, glm::vec3(0, 0, 1));
		Enemies[index]->Translate(glm::vec3(5, 0, 0));
		Enemies[index]->noww = Enemies[index]->now;

		if (Enemies[index]->posX >= (ZombieMaxX + 5)) Enemies[index]->now = 2;
		else if (Enemies[index]->posX <= (ZombieMinX + 5)) Enemies[index]->now = 1;
		else if (Enemies[index]->posZ <= (ZombieMinX + 5)) Enemies[index]->now = 4;
		else if (Enemies[index]->posZ >= (ZombieMaxX + 5)) Enemies[index]->now = 3;
		printf("before=%d, now=%d posX=%f posZ=%f lastX=%f lastZ=%f\n", Enemies[index]->noww, Enemies[index]->now, Enemies[index]->posX, Enemies[index]->posZ, Enemies[index]->lastX, Enemies[index]->lastZ);
		//system("pause");
	}
}

int Renderer::Randomize(int index, int now, float posX, float posZ)
{
	srand(time(NULL));
	int random;
	while (1)
	{
		random = rand() % 100000 + 1;
		printf("%d ", random);
		random %= 4;
		random += index;
		random %= 4;
		random++;
		if (random != now)
		{
			if (random == 3 && posZ > ZombieMinX) return random;
			if (random == 4 && posZ < ZombieMaxX) return random;
			if (random == 1 && posX < ZombieMaxX) return random;
			if (random == 2 && posX > ZombieMinX) return random;
		}
	}
}
