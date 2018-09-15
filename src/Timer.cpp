/*
 * Timer.cpp
 *
 *  Created on: Sep 12, 2018
 *      Author: julia
 */

#include "Timer.h"

Timer::Timer(bool start_immediately): start(0), stop(0), running(false){
    if (start_immediately){
        Start(true);
    }
}
void Timer::Start(bool reset){
    if (!running){
        if (reset){
            start = std::clock();
        }
        running = true;
    }
}
void Timer::reset(){
	start = std::clock();
}
void Timer::Stop(){
    if (running){
        stop = std::clock();
        running = false;
    }
}
unsigned long Timer::get() const{
	clock_t ticks = (running ? std::clock() : stop) - start;
	double seconds = (double)ticks / CLOCKS_PER_SEC;
	unsigned long milliseconds = seconds * 1000;
	return milliseconds;
}


Timer::~Timer() {
	// TODO Auto-generated destructor stub
}
