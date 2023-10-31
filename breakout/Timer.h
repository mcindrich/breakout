#pragma once

#include <chrono>

class Timer
{
public:
    Timer();

    float restart();
    float getElapsedTime();

    void pause();
    void resume();

    inline bool isPaused()
    {
        return m_pause;
    }

private:
    std::chrono::time_point<std::chrono::system_clock> m_start;
    std::chrono::time_point<std::chrono::system_clock> m_pauseStart;
    float m_pauseTime;
    bool m_pause;
};
