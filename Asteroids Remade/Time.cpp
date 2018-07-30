#include "stdafx.h"

#include "Time.h"


std::chrono::duration<double> Time::m_deltaTime;
std::chrono::time_point<std::chrono::system_clock> Time::m_prevTime;
std::chrono::time_point<std::chrono::system_clock> Time::m_currTime;

// Starts the clock
void Time::StartTime()
{
	m_currTime = std::chrono::system_clock::now();
}

// Returns the time since the last frame
float Time::GetDeltaTime()
{
	return m_deltaTime.count();
}

// Updates the time since the last frame
void Time::Update()
{
	m_prevTime = m_currTime;
	m_currTime = std::chrono::system_clock::now();
	m_deltaTime = m_currTime - m_prevTime;
}