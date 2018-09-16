/*
 * Timer.h
 *
 *  Created on: Sep 12, 2018
 *      Author: julia
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <ctime>
#include <chrono>

class Timer{
public:
    Timer() :
            m_beg(clock_::now()) {
    }
    void reset() {
        m_beg = clock_::now();
    }

    double getMillis() const {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
                clock_::now() - m_beg).count();
    }
    double getSeconds() const {
    	return std::chrono::duration_cast<std::chrono::seconds>(
    	                clock_::now() - m_beg).count();
    }

private:
    typedef std::chrono::steady_clock clock_;
    typedef std::chrono::duration<double, std::ratio<1> > second_;
    std::chrono::time_point<clock_> m_beg;
};

#endif /* TIMER_H_ */


