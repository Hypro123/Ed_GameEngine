#include<iostream>
#include"ProjectFile.h"

int main()
{
	ProjectFile* app = new ProjectFile();
	app->Initialise();
	app->run();
	delete app;
	return 0;
}