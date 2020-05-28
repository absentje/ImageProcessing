#include "Timer.h"
#include <ctime>
#include <ratio>

using namespace std::chrono;

Timer::Timer()
	: isRunning(false)
{

}

void	Timer::Start()
{
	mStart = high_resolution_clock::now();
	isRunning = true;
}

void	Timer::Stop()
{
	mStop = high_resolution_clock::now();
	isRunning = false;
}

float	Timer::GetElapsedSeconds() const
{
	auto end = isRunning ? high_resolution_clock::now() : mStop;
	return duration_cast<duration<float>>(end - mStart).count();
}

bool	Timer::IsRunning() const
{
	return isRunning;
}
