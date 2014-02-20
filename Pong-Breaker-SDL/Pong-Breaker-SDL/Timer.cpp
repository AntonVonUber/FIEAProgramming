#include "Timer.h"

#if defined(_MSC_VER)
#include <SDL.h>
#elif defined(__clang__)
#include <SDL2/SDL.h>
#else
#include <SDL2/SDL.h>
#endif

Timer::Timer()
    : m_startTicks(0), m_pausedTicks(0), m_started(false), m_paused(false)
{
}

void Timer::Start()
{
    m_started = true;
    m_paused  = false;
    m_startTicks = SDL_GetTicks();
}

void Timer::Stop()
{
    m_started = false;
    m_paused  = false;
}

void Timer::Pause()
{
    if (m_started && !m_paused){
        m_paused = true;
        m_pausedTicks = SDL_GetTicks() - m_startTicks;
    }
}

void Timer::Unpause()
{
    if (m_paused){
        m_paused = false;
        m_startTicks = SDL_GetTicks() - m_pausedTicks;
        m_pausedTicks = 0;
    }
}

int Timer::Restart()
{
    int elapsedTicks = Ticks();
    Start();
    return elapsedTicks;
}

int Timer::Ticks() const
{
    if (m_started){
        if (m_paused)
            return m_pausedTicks;
        else
            return SDL_GetTicks() - m_startTicks;
    }
    return 0;
}

bool Timer::Started() const
{
    return m_started;
}

bool Timer::Paused() const
{
    return m_paused;
}