#ifndef TIME_H
#define TIME_H

#include "stdafx.h"

#include <chrono>


/// Static class used for getting the delta time between frames
class Time
{
	public:
		static void StartTime();
		static float GetDeltaTime();
		static void Update();

	private:
		static std::chrono::duration<double> m_deltaTime;
		static std::chrono::time_point<std::chrono::system_clock> m_prevTime;
		static std::chrono::time_point<std::chrono::system_clock> m_currTime;
};

#endif