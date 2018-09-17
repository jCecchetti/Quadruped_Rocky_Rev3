/*
 * Joystick.h
 *
 *  Created on: Sep 16, 2018
 *      Author: julia
 */

#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include <vector>
#include <sys/ioctl.h>
#include <linux/joystick.h>

#define JOY_DEV "/dev/input/js0"

class Joystick {
public:
	Joystick();
	virtual ~Joystick();
	void update();

	int joy_fd(-1), num_of_axis(0), num_of_buttons(0);
	char name_of_joystick[80];
	vector<char> joy_button;
	vector<int> joy_axis;
};

#endif /* JOYSTICK_H_ */
