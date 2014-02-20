#if defined(_MSC_VER)
#include <SDL.h>
#elif defined(__clang__)
#include <SDL2/SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include "Application.h"

int main(int argc, char** argv)
{
	const bool DEBUG = true;
	FILE *stream;
	// this redirects all standard output to file, logFile.txt
	if(!DEBUG && (stream = freopen("logFile.txt", "w", stdout)) == NULL)
		exit(-1);

	Application application;
	application.Init(WINDOW_TITLE, 0, 30, 640, 480, false);
	application.Run();
	application.Shutdown();

	if(!DEBUG)
		fclose(stream);

	return 0;
}