#include "Application.h"

int main(int argc, char** argv)
{
	Application application;
	
	// initialize application
	application.initialize(argc, argv);

	// run application's main loop
	application.run();

	return 0;
}