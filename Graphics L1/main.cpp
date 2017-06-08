#include "Application Manager/ApplicationManager.h"

int main(void)
{
	bool again = false;
	std::unique_ptr<ApplicationManager> appManager (new ApplicationManager());
	do
	{
		again = false;
		if (appManager->InitalizeApplication(1920, 1080) == true)
		{
			 again = appManager->StartMainLoop();
				appManager->CloseApplication();
		}
	}while (again);
}


