#include "ForestSimApp.h"

int main()
{
	auto app = new ForestSimApp();
	app->run("AIE", 1280, 720, false);
	delete app;

	return 0;
}