#pragma once

// A Rotation in space consisting of yaw, pitch, and roll
class Rotation {
public:
	Rotation(double Yaw, double Pitch, double Roll);

	double getYaw() const;
	double getPitch() const;
	double getRoll() const;

	void setYaw(double Yaw);
	void setPitch(double Pitch);
	void setRoll(double Roll);

	void setRotation(double Yaw, double Pitch, double Roll);
	void setRotation(Rotation angle);

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
