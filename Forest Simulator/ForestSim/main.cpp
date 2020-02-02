#include "ForestSimApp.h"
#include "ScreenDefines.h"

int main()
{
	auto app = new ForestSimApp();
	app->run("Forest Simulator", SCR_WIDTH, SCR_HEIGHT, false);
	delete app;

	return 0;
}