#include "ForestSimApp.h"
#include "ScreenDefines.h"
#include <Windows.h>

bool EnableVirtualTerminal()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hOut == INVALID_HANDLE_VALUE)
		return false;

	DWORD dwMode = 0;
	if (!GetConsoleMode(hOut, &dwMode))
		return false;

	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	if (!SetConsoleMode(hOut, dwMode))
		return false;

	return true;
}

int main()
{
	EnableVirtualTerminal();
	auto app = new ForestSimApp();
	app->run("Forest Simulator", SCR_WIDTH, SCR_HEIGHT, false);
	delete app;

	return 0;
}