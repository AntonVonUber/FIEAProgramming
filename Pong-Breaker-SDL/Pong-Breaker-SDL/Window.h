/**
*  Window.h	- This class was created in close connection to
*	a tutorial located online for SDL game programming.  Much
*	of it is copied directly, and therefore is not exemplary
*	of my coding styling.		- Anthony Bolton
*/

#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <string>
#include <stdexcept>
#include <memory>

#if defined(_MSC_VER)
#include <SDL.h>
#elif defined(__clang__)
#include <SDL2/SDL.h>
#else
#include <SDL2/SDL.h>
#endif

#include "Defines.h"

/**
*  Window management class, provides a simple wrapper around
*  the SDL_Window and SDL_Renderer functionalities
*/
class Window {
public:
	Window() { };
	~Window() { Quit(); };
	/**
	*  Initialize SDL, setup the window and renderer
	*  @param title The window title
	*  @param x		The starting x value of window's on-screen location
	*  @param y		The starting y value of window's on-screen location
	*/
	static void Init(std::string title = WINDOW_TITLE, int x = 50, int y = 50,
		int width=WINDOW_WIDTH, int height=WINDOW_HEIGHT, Uint32 flags=SDL_WINDOW_SHOWN);
	static void Resize();
	///Quit SDL and destroy the window and renderer
	static void Quit();
	/**
	*  Draw a SDL_Texture to the screen at dstRect with various other options
	*  @param tex The SDL_Texture to draw
	*  @param dstRect The destination position and width/height to draw the texture with
	*  @param clip The clip to apply to the image, if desired
	*  @param angle The rotation angle to apply to the texture, default is 0
	*  @param xPivot The x coordinate of the pivot, relative to (0, 0) being center of dstRect
	*  @param yPivot The y coordinate of the pivot, relative to (0, 0) being center of dstRect
	*  @param flip The flip to apply to the image, default is none
	*/
	static void Draw(SDL_Texture *tex, SDL_Rect &dstRect, SDL_Rect *clip = NULL,
		float angle = 0.0, int xPivot = 0, int yPivot = 0,
		SDL_RendererFlip flip = SDL_FLIP_NONE);

	static void DrawRectangle(int r, int g, int b, int a, SDL_Rect &rec);
	/**
	*  Loads an image directly to texture using SDL_image's
	*  built in function IMG_LoadTexture
	*  @param file The image file to load
	*  @return SDL_Texture* to the loaded texture
	*/
	static SDL_Texture* LoadImage(const std::string &file);
	/**
	*  Loads a bitmap directly to texture with potential
	*  transparent values for red, green, and blue
	*  @param file The image file to load
	*  @param invR The transparent red value
	*  @param invG The transparent green value
	*  @param invB The transparent blue value
	*  @return SDL_Texture* to the loaded texture
	*/
	SDL_Texture* LoadTransparentBMP(const std::string &file,
		int invR, int invG, int invB);
	/**
	*  Generate a texture containing the message we want to display
	*  @param message The message we want to display
	*  @param fontFile The font we want to use to render the text
	*  @param color The color we want the text to be
	*  @param fontSize The size we want the font to be
	*  @return An SDL_Texture* to the rendered message
	*/
	static SDL_Texture* RenderText(const std::string &message, const std::string &fontFile, SDL_Color color, int fontSize);
	///Clear the renderer
	static void Clear();
	///Present the renderer, ie. update screen
	static void Present();
	///Get the window's box
	static SDL_Rect Box();

private:
    Window(Window const&);	// Don't Implement.
    void operator=(Window const&);	// Don't implement.

	static SDL_Window*	m_screen;
	static SDL_Renderer* m_renderer;
	static SDL_Rect m_box;
};

#endif	// __WINDOW_H__