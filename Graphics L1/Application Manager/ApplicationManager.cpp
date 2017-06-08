#include "ApplicationManager.h"

//static members initalization.
int ApplicationManager::MouseClicked = 0;
int ApplicationManager::KeyPressed = -1;
int ApplicationManager::KeyAction = -1;
double ApplicationManager::MouseXPos = -1.0;
double ApplicationManager::MouseYPos = -1.0;
int ApplicationManager::WindowSizeWidth = 0;
int ApplicationManager::WindowSizeHeight = 0;

ApplicationManager::ApplicationManager()
{
}

ApplicationManager::~ApplicationManager(void)
{
	this->CloseApplication();
}

bool ApplicationManager::InitalizeApplication(int pWindowSizeWidth, int pWindowSizeHeight)
{
	//ilInit();
	glfwInit();
	mWindow = glfwCreateWindow( pWindowSizeWidth, pWindowSizeWidth, "Graphics 2016/2017", NULL, NULL);
	glfwMakeContextCurrent(mWindow);
	
	//set the initial time after initalization.
	mTime = glfwGetTime();
	glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	// ******************** Initialize GLEW ******************** //
	glewExperimental = true; // Needed for core profile
	glewInit();

	glfwSetInputMode(mWindow, GLFW_STICKY_KEYS, GL_TRUE); 
	
	// Keyboard pressing event handler binding
	glfwSetKeyCallback(mWindow, &this->SpecialKeyPressed);
	
	// Mouse movement event handler binding
	glfwSetMouseButtonCallback(mWindow, &this->MouseButtonClicked);

	// Mouse click event handler binding
	glfwGetWindowSize(mWindow,&WindowSizeWidth,&WindowSizeHeight);

	//initialize a value for the mouse position.
	MouseXPos = WindowSizeWidth/2;
	MouseYPos = WindowSizeHeight/2;
	glfwSetCursorPos(mWindow,MouseXPos,MouseYPos); //force the mouse position to be in the middle of the window at start up
	glfwSetCursorPosCallback(mWindow, &this->MouseMoved); //prepare mouse handler
	
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it is closer to the camera than the former one
	glDepthFunc(GL_LESS); 

	this->InitializeComponents(); // To be able to draw
	PlayAgain = 0;
	return true;
}

void ApplicationManager::InitializeComponents()
{
	mRenderer = std::unique_ptr<Renderer>(new Renderer());

	// Initialize primitives/models data (send data to OpenGL buffers)
	mRenderer->Initialize();
}

bool ApplicationManager::StartMainLoop()
{
	bool exitLoop = false;
	do 
	{
		glClearColor(1, 1, 1,1);
		//clear the color buffer, and the depth buffer each frame.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		bool GameOver=mRenderer->Draw();
		if (!GameOver)
		{
			//call the handle keyboard only when a button is pressed.
			if (ApplicationManager::KeyPressed != -1)
			{
				mRenderer->HandleKeyboardInput(KeyPressed, KeyAction);
				KeyPressed = -1;
			}

			if (ApplicationManager::MouseClicked == 1)
			{
				mRenderer->HandleMouseClick(MouseXPos, MouseYPos);
				ApplicationManager::MouseClicked = 0;
				printf("mouse= %d", MouseClicked);
			}
			// check if a mouse moved
			if (ApplicationManager::MouseXPos != ApplicationManager::WindowSizeWidth / 2
				|| ApplicationManager::MouseYPos != ApplicationManager::WindowSizeHeight / 2)
			{
				double mouseSpeed = 0.005; //it is just there to speed up or slow down the movements.
				double movedDistanceX;
				double movedDistanceY;

				//  the distance (old position - new position)
				// in other words:  how far is the mouse from the center of the window ? The bigger this value, the more we want to turn.
				// note that the old position (x_old, y_old) is fixed in this application (x_old = WindoSizeWidth/2, y_old = WindowSizeHeight/2)
				movedDistanceX = double(WindowSizeWidth / 2 - MouseXPos)*mouseSpeed;
				movedDistanceY = double(WindowSizeHeight / 2 - MouseYPos)*mouseSpeed;
				mRenderer->HandleMouse(movedDistanceX, movedDistanceY);

				// Pass the two distances to the Renderer (our drawings)

				//Force the new position of the mouse to be in the middle of the window
				MouseXPos = WindowSizeWidth / 2;
				MouseYPos = WindowSizeHeight / 2;
				glfwSetCursorPos(mWindow, MouseXPos, MouseYPos);
			}

			//Update everything every frame (time related).
			this->Update();
		}
		// Swap buffers
		glfwSwapBuffers(mWindow); //Displaying our finished scene
		glfwPollEvents();

		// Check if the window is closed to terminate
		if (glfwGetKey(mWindow, GLFW_KEY_ENTER) == GLFW_PRESS)
			PlayAgain = true;
		if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(mWindow) == true)
			PlayAgain = false;
		if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS || (glfwGetKey(mWindow, GLFW_KEY_ENTER) == GLFW_PRESS&GameOver)||
			glfwWindowShouldClose(mWindow) == true )
		{
			exitLoop = true;
		}
	} while (exitLoop == false);
	return PlayAgain;
}

// Terminate the window 
void ApplicationManager::CloseApplication()
{

	glfwTerminate();
	glfwDestroyWindow(mWindow);
}

// Keyboard pressing event
void ApplicationManager::SpecialKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	ApplicationManager::KeyPressed = key;
	ApplicationManager::KeyAction = action;
}


// Mouse movement event
void ApplicationManager::MouseMoved(GLFWwindow* window, double xpos, double ypos)
{
	//set the new mouse position to the MousXPos and MousYPos
	 ApplicationManager::MouseXPos = xpos;
	 ApplicationManager::MouseYPos = ypos;
}

// Mouse click event
void ApplicationManager::MouseButtonClicked(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_MOUSE_BUTTON_LEFT)
	{
		ApplicationManager::MouseClicked = 1;
	}
		
}

void ApplicationManager::Update()
{
	double currentTime = glfwGetTime(); //get currentTime
	double deltaTime = currentTime - mTime; //subtract the previous recorded time (mTime value)
	mTime = currentTime; //set the mTime with current (for calculating the next frame)
	mRenderer->Update(deltaTime);
}