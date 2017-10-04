#include "Camera.h"

#include <glut.h>
#include <math.h>

#include <iostream>
using namespace std;

Camera::Camera()
{
	position.x = 0;
	position.y = 0;
	position.z = 0;

	pose.x = 0;
	pose.y = 0;
	pose.z = 0;
}

void Camera::SetPosX(float xpos)
{
	position.SetX(xpos);
}
float Camera::GetPosX()
{
	return position.GetX();
}

void Camera::SetPosY(float ypos)
{
	position.SetY(ypos);
}
float Camera::GetPosY()
{
	return position.GetY();
}

void Camera::SetPosZ(float zpos)
{
	position.SetZ(zpos);
}
float Camera::GetPosZ()
{
	return position.GetZ();
}

void Camera::SetPoseX(float xpose)
{
	pose.SetX(xpose);
}
float Camera::GetPoseX()
{
	return pose.GetX();
}

void Camera::SetPoseY(float ypose)
{
	pose.SetY(ypose);
}
float Camera::GetPoseY()
{
	return pose.GetY();
}

void Camera::set_view_point()
{
	float verticalAngle = utils_cam.ToRad(pose.x);
	float horizontalAngle = utils_cam.ToRad(pose.y);

	float dx = cos(verticalAngle) * cos(horizontalAngle);
	float dy = cos(verticalAngle) * sin(horizontalAngle);
	float dz = sin(verticalAngle);

	float cx = position.x + dx, cy = position.y + dy, cz = position.z + dz;
	gluLookAt(position.x, position.y, position.z, cx, cy, cz, 0, 0, 1);
}

void Camera::rotate_camera(float delta_rotate_x, float delta_rotate_y, float mouse_speed)
{

	pose.x -= (float)(delta_rotate_y)* mouse_speed;
	pose.y -= (float)(delta_rotate_x)* mouse_speed;

	if (pose.x >= 87.0f)
	{
		pose.x = 87.0f;
	}
	if (pose.x <= -87.0f)
	{
		pose.x = -87.0f;
	}
}

void Camera::move_camera_forward(double distance)
{
	double angle = utils_cam.ToRad(pose.y);

	position.x += cos(angle) * distance;
	position.y += sin(angle) * distance;
}

void Camera::move_camera_backward(double distance)
{
	double angle = utils_cam.ToRad(pose.y);

	position.x -= cos(angle) * distance;
	position.y -= sin(angle) * distance;
}

void Camera::step_camera_left(double distance)
{
	double angle = utils_cam.ToRad(pose.y + 90.0);

	position.x += cos(angle) * distance;
	position.y += sin(angle) * distance;
}

void Camera::step_camera_right(double distance)
{
	double angle = utils_cam.ToRad(pose.y - 90.0);

	position.x += cos(angle) * distance;
	position.y += sin(angle) * distance;
}

void Camera::move_camera_up(double distance)
{
	position.z += distance;
}

void Camera::move_camera_down(double distance)
{
	position.z -= distance;
}

void Camera::set_game_area()
{
	if (position.x <= 3)
	{
		position.x = 3;
	}
	if (position.x >= 497)
	{
		position.x = 497;
	}
	if (position.y <= 3)
	{
		position.y = 3;
	}
	if (position.y >= 497)
	{
		position.y = 497;
	}
}


