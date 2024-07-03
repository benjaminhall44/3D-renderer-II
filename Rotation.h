#pragma once

class Rotation {
public:
	Rotation(double Yaw, double Pitch, double Roll);

	double getYaw() const;
	double getPitch() const;
	double getRoll() const;

	void turn(double Yaw, double Pitch, double Roll);
	void turn(Rotation angle);

	Rotation operator-() const;

private:
	static double normalizeAngle(double angle);

	double yaw;
	double pitch;
	double roll;
};

const Rotation FORWARD(0.0, 0.0, 0.0);
