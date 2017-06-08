#ifndef ApplicationManager_h__
#define ApplicationManager_h__
#include <Windows.h>
#include "../../middleware/includes/gl/glew.h"
#include "../../middleware/includes/gl/glfw3.h"
#include <memory>
#include "../Renderer.h"
class ApplicationManager
{
	int mOpenGLMajorVersion;
	int mOpenGLMinorVersion;
	double mTime;
	GLFWwindow* mWindow; //Why didn't we use smart pointers here? google it! ;)
	std::unique_ptr<Renderer> mRenderer;
	
	void InitializeComponents();
	void HandleKeyboardInput();
	void HandleMouseLocation();
	void Update();
	static void SpecialKeyPressed(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void MouseMoved(GLFWwindow* window, double xpos, double ypos);
	static void MouseButtonClicked(GLFWwindow* window, int button, int action, int mods);
	static int KeyPressed;   //Keep the code of the pressed key
	static int KeyAction;    //Keep the code of the action
	static int MouseClicked;    //Keep the code of the action
	static double MouseXPos; //Keep the x-value of the mouse position
	static double MouseYPos; //Keep the y-value of the mouse position
	bool PlayAgain;
public:
	static int WindowSizeWidth;
	static int WindowSizeHeight;

	ApplicationManager();

	bool InitalizeApplication(int pWindowSizeWidth, int pWindowSizeHeight);
	bool StartMainLoop();
	void CloseApplication();

	~ApplicationManager(void);
};
#endif // ApplicationManager_h__

