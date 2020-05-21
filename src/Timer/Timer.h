#ifndef TIMER_H
#define TIMER_H

#include <GL/glfw3.h>

class Timer
{
public:
	Timer() : m_previousTime(0.0f), m_currentTime(0.0f) {}
	Timer(const Timer& timer) = delete;
	Timer& operator=(const Timer& timer) = delete;

	void StartTimer() { m_timerStarted = true; }
	
	GLfloat m_previousTime;
	GLfloat m_currentTime;

private:
	bool m_timerStarted = false;	
};

#endif
