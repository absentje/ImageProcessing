#pragma once
#include <chrono>

class Timer
{
public:
    Timer();
	
	void		Start();
	void		Stop();
	float		GetElapsedSeconds() const;
	bool		IsRunning() const;

private:
	bool		isRunning;
	std::chrono::high_resolution_clock::time_point	mStart;
	std::chrono::high_resolution_clock::time_point	mStop;
};