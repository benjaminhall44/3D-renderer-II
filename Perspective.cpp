#include "Perspective.h"
#define _USE_MATH_DEFINES
#include "math.h"


Rotation Perspective::getRotation() const {
	SpaceVector K = SpaceVector(cos(-pitch) * sin(-yaw), sin(-pitch), cos(-pitch) * cos(-yaw)); // Forward
	SpaceVector J = SpaceVector(sin(-pitch) * sin(-yaw), cos(-pitch), sin(-pitch) * cos(-yaw)); // Up
	SpaceVector I = K / J; // Rightward

	return Rotation(I, J, K);
}

SpaceVector Perspective::getPosition() const {
	return position;
}


void Perspective::moveAbs(SpaceVector displacement) {
	position += displacement;
}
void Perspective::moveRel(SpaceVector displacement) {
	SpaceVector K = SpaceVector(cos(pitch) * sin(yaw), sin(pitch), cos(pitch) * cos(yaw)); // Forward
	SpaceVector J = SpaceVector(sin(pitch) * sin(yaw), cos(pitch), sin(pitch) * cos(yaw)); // Up
	SpaceVector I = K / J; // Rightward

	position += I * displacement.getX() + J * displacement.getY() + K * displacement.getZ();

}

void Perspective::turnAbs(double Yaw, double Pitch, double Roll) {
	yaw = normalizeAngle(yaw + Yaw);
	pitch = normalizeAngle(pitch + Pitch);
	roll = normalizeAngle(roll + Roll);
}
void Perspective::turnRel(double Yaw, double Pitch, double Roll) {

}

double Perspective::normalizeAngle(double angle) {
	if (angle > M_PI) {
		angle += M_PI;
		angle = angle - int((angle) / M_2_PI) * M_2_PI;
		angle -= M_PI;
	}
	else if (angle < -M_PI) {
		angle -= M_PI;
		angle = angle - int((angle) / M_2_PI) * M_2_PI;
		angle += M_PI;
	}
	return angle;
}