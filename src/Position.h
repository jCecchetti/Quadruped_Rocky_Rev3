/*
 * Position.h
 *
 *  Created on: Aug 4, 2018
 *      Author: julia
 */

#ifndef POSITION_H_
#define POSITION_H_

class Position {
public:
	Position();
	Position(double x, double y, double z, double roll, double pitch, double yaw);
	void set(double x, double y, double z, double roll, double pitch, double yaw);
	void copy(Position a);
	virtual ~Position();

	double x, y, z, roll, pitch, yaw;

};

#endif /* POSITION_H_ */
