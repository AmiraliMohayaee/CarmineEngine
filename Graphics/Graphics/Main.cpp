#include "App.h"


int main(int argc, char* args[])
{
	App application;

	application.InitScreenAndShaders();
	application.BindElements();
	application.InitObjects();
	application.Update();
	application.Shutdown();


	return 0;
}