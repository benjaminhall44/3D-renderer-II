#include "Rotation.h"
#define _USE_MATH_DEFINES
#include "math.h"

Rotation::Rotation(double Yaw, double Pitch, double Roll) : yaw(Yaw), pitch(Pitch), roll(Roll) {};

double Rotation::getYaw() const { return yaw; }
double Rotation::getPitch() const { return pitch; }
double Rotation::getRoll() const { return roll; }

void Rotation::setYaw(double Yaw) {
	yaw = Yaw;
}
void Rotation::setPitch(double Pitch) {
	pitch = Pitch;
}
void Rotation::setRoll(double Roll) {
	roll = Roll;
}


void Rotation::setRotation(double Yaw, double Pitch, double Roll) {
	Rotation(Yaw, Pitch, Roll);
}
void Rotation::setRotation(Rotation angle) {
	Rotation(angle.yaw, angle.pitch, angle.roll);
}

void Rotation::turn(double Yaw, double Pitch, double Roll) {
	yaw = normalizeAngle(yaw + Yaw);
	pitch = normalizeAngle(pitch + Pitch);
	roll = normalizeAngle(roll + Roll);
}
void Rotation::turn(Rotation angle) {
	turn(angle.yaw, angle.pitch, angle.roll);
}

Rotation Rotation::operator-() const{
	return Rotation(-yaw, -pitch, -roll);
}

double Rotation::normalizeAngle(double angle) {
	if (angle > M_PI) {
		angle += M_PI;
		angle = angle - int((angle) / (2 * M_PI)) * 2 * M_PI;
		angle -= M_PI;
	}
	else if (angle < -M_PI) {
		angle -= M_PI;
		angle = angle + int((-angle) / (2 * M_PI)) * 2 * M_PI;
		angle += M_PI;
	}
	return angle;
}