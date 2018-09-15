/*
 * Position.cpp
 *
 *  Created on: Aug 4, 2018
 *      Author: julia
 */

#include "Position.h"

Position::Position(){
	x = 0.0;
	y = 0.0;
	z = 0.0;
	roll = 0.0;
	pitch = 0.0;
	yaw = 0.0;
}

Position::Position(double x, double y, double z, double roll, double pitch, double yaw){
	this->x = x;
	this->y = y;
	this->z = z;
	this->roll = roll;
	this->pitch = pitch;
	this->yaw = yaw;
}

void Position::set(double x, double y, double z, double roll, double pitch, double yaw){
	this->x = x;
	this->y = y;
	this->z = z;
	this->roll = roll;
	this->pitch = pitch;
	this->yaw = yaw;
}

void Position::copy(Position a){
	this->x = a.x;
	this->y = a.y;
	this->z = a.z;
	this->roll = a.roll;
	this->pitch = a.pitch;
	this->yaw = a.yaw;
}

Position::~Position() {
	// TODO Auto-generated destructor stub
}

