#ifndef __TIMER_H__
#define __TIMER_H__

// a timer class
class Timer {
public:
    Timer();
    // start the timer
    void Start();
    // stop the timer
    void Stop();
    // pause the timer
    void Pause();
    // unpause the timer
    void Unpause();

	// restart the timer and return the elapsed ticks
    int Restart();

	// get the elapsed ticks
    int Ticks() const;
    // check if Timer is started
    bool Started() const;
    // check if Timer is paused
    bool Paused() const;

private:
    int m_startTicks, m_pausedTicks;
    bool m_started, m_paused;
};

#endif	// __TIMER_H__