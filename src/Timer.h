/*
 * Timer.h
 *
 *  Created on: Sep 12, 2018
 *      Author: julia
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <ctime>

class Timer {
public:
	explicit Timer(bool start_immediately = false);
	void Start(bool reset = false);
	void Stop();
	void reset();
	unsigned long get() const;
	virtual ~Timer();
private:
	std::clock_t start, stop;
	bool running;
};

#endif /* TIMER_H_ */


