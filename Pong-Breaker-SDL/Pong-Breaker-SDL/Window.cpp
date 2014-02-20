#include <string>
#include <stdexcept>
#include <memory>

#if defined(_MSC_VER)
#include <SDL.h>
#include <SDL_image.h>	// necessary for loading non-bmps
#include <SDL_ttf.h>
#elif defined(__clang__)
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif

#include "Window.h"
#include "Defines.h"

SDL_Window*	Window::m_screen;
SDL_Renderer* Window::m_renderer;
SDL_Rect Window::m_box;

void Window::Init(std::string title, int x, int y,
	int width, int height, Uint32 flags)
{
	m_screen = nullptr;
	m_renderer = nullptr;

    // initialize all SDL subsystems
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		throw std::runtime_error("SDL Init Failed");

    if (TTF_Init() == -1)
		throw std::runtime_error("TTF Init Failed");

    // setup our window
    m_box.x = 0;
    m_box.y = 0;
    m_box.w = width;
    m_box.h = height;
    //Create our window
	m_screen = SDL_CreateWindow(title.c_str(), x, y, 
		m_box.w, m_box.h, flags);

    // make sure it created ok
    if (m_screen == nullptr)
        throw std::runtime_error("Failed to create window");

    // create the renderer
	m_renderer = SDL_CreateRenderer(m_screen, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	// make sure it created ok
    if (m_renderer == nullptr)
        throw std::runtime_error("Failed to create renderer");
}

// this is used to exit fullscreen and make sure
// it's not stuck in fullscreen after the program
// is already shut down
void Window::Resize()
{
	SDL_CreateWindowAndRenderer(640, 480, SDL_WINDOW_SHOWN, &m_screen, &m_renderer);
}

void Window::Draw(SDL_Texture *tex, SDL_Rect &dstRect, SDL_Rect *clip, float angle, 
                  int xPivot, int yPivot, SDL_RendererFlip flip)
{
    // convert pivot pos from relative to object's center to screen space
    xPivot += dstRect.w / 2;
    yPivot += dstRect.h / 2;
    // SDL expects an SDL_Point as the pivot location
    SDL_Point pivot = { xPivot, yPivot };
    // draw the texture
	SDL_RenderCopyEx(m_renderer, tex, clip, &dstRect, angle, &pivot, flip);
}

// currently unused, but could be for filling a rectangle
// with a particular color and alpha value
void Window::DrawRectangle(int r, int g, int b, int a, SDL_Rect &rec)
{
	SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
	rec.x = 0;
	rec.y = 0;
	rec.w = 50;
	rec.h = 50;
	SDL_RenderFillRect(m_renderer, &rec);
}

SDL_Texture* Window::LoadImage(const std::string &file)
{
    SDL_Texture* tex = nullptr;
	tex = IMG_LoadTexture(m_renderer, file.c_str());
	if (tex == nullptr)
		throw std::runtime_error("Failed to load image: " + file + IMG_GetError());
	return tex;
}

SDL_Texture* Window::LoadTransparentBMP(const std::string &file,
	int invR, int invG, int invB)
{
	SDL_Texture* tex = nullptr;
	SDL_Surface *surf = SDL_LoadBMP(file.c_str());
	SDL_SetColorKey(surf, SDL_TRUE, SDL_MapRGB(surf->format, invR, invG, invB));
	tex = SDL_CreateTextureFromSurface(m_renderer, surf);

	//Clean up unneeded stuff
	SDL_FreeSurface(surf);
	return tex;
}

SDL_Texture* Window::RenderText(const std::string &message, const std::string &fontFile, SDL_Color color, int fontSize)
{
    //Open the font
	TTF_Font *font = nullptr;
	font = TTF_OpenFont(fontFile.c_str(), fontSize);
	if (font == nullptr)
		throw std::runtime_error("Failed to load font: " + fontFile + TTF_GetError());

	//Render the message to an SDL_Surface, as that's what TTF_RenderText_X returns
	SDL_Surface *surf = TTF_RenderText_Blended(font, message.c_str(), color);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(m_renderer, surf);
	//Clean up unneeded stuff
	SDL_FreeSurface(surf);
	TTF_CloseFont(font);

	return texture;
}

void Window::Clear()
{
	SDL_RenderClear(m_renderer);
}

void Window::Present()
{
	SDL_RenderPresent(m_renderer);
}

SDL_Rect Window::Box()
{
    return m_box;
}

void Window::Quit()
{
	Resize();
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_screen);

    TTF_Quit();
    SDL_Quit();
}