////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2014 Laurent Gomila (laurent.gom@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/System/Clock.hpp>

#if defined(SFML_SYSTEM_WINDOWS)
    #include <SFML/System/Win32/ClockImpl.hpp>
#else
    #include <SFML/System/Unix/ClockImpl.hpp>
#endif


namespace sf
{
////////////////////////////////////////////////////////////
Clock::Clock() :
m_startTime(priv::ClockImpl::getCurrentTime()),
m_pauseTime(),
m_timePaused(),
m_running(true)
{
}


////////////////////////////////////////////////////////////
Time Clock::getElapsedTime() const
{
    if (m_running)
        return priv::ClockImpl::getCurrentTime() - m_startTime - m_timePaused;
    else
        return m_pauseTime - m_startTime - m_timePaused;
}


////////////////////////////////////////////////////////////
Time Clock::restart()
{
    Time now = priv::ClockImpl::getCurrentTime();
    Time elapsed = getElapsedTime();
    m_startTime = now;
    m_pauseTime = now;
    m_timePaused = sf::Time();

    return elapsed;
}

void Clock::start()
{
    if (!m_running)
    {
        Time now = priv::ClockImpl::getCurrentTime();
        Time elapsedPause = now - m_pauseTime;
        m_timePaused += elapsedPause;
        m_running = true;
    }
}

void Clock::stop()
{
    if (m_running)
    {
        Time now = priv::ClockImpl::getCurrentTime();
        m_pauseTime = now;
        m_running = false;
    }
}

} // namespace sf
