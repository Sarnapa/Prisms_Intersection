/*
	Micha³ Piotrak
	numer albumu: 269336
	Przeciêcie graniastos³upów
*/

#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <chrono>

class Timer 
{
public:
	Timer() : beg_(clock_::now()) { }

	void reset() { beg_ = clock_::now(); }

	double elapsed() const 
	{
		return std::chrono::duration_cast<msecond_>
			(clock_::now() - beg_).count();
	}

private:
	typedef std::chrono::high_resolution_clock clock_;
	typedef std::chrono::duration<double, std::milli> msecond_;
	std::chrono::time_point<clock_> beg_;
};

#endif //TIMER_H