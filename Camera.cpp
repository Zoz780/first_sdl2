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
	position.x = xpos;
}
float Camera::GetPosX()
{
	return position.x;
}

void Camera::SetPosY(float ypos)
{
	position.y = ypos;
}
float Camera::GetPosY()
{
	return position.y;
}

void Camera::SetPosZ(float zpos)
{
	position.z = zpos;
}
float Camera::GetPosZ()
{
	return position.z;
}

void Camera::SetPoseX(float xpose)
{
	pose.x = xpose;
}
float Camera::GetPoseX()
{
	return pose.x;
}

void Camera::SetPoseY(float ypose)
{
	pose.y = ypose;
}
float Camera::GetPoseY()
{
	return pose.y;
}

void Camera::set_view_point()
{
	float verticalAngle = utils_cam.ToRad(pose.x);
	float horizontalAngle = utils_cam.ToRad(pose.y);

	direction.x = cos(verticalAngle) * cos(horizontalAngle);
	direction.y = cos(verticalAngle) * sin(horizontalAngle);
	direction.z = sin(verticalAngle);

	float cx = position.x + direction.x, cy = position.y + direction.y, cz = position.z + direction.z;
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

Vec3 Camera::get_camera_far_point()
{
	Vec3 Line_far_point;

	Line_far_point.x = position.x + (direction.x * 500);
	Line_far_point.y = position.y + (direction.y * 500);
	Line_far_point.z = position.z + (direction.z * 500);

	return Line_far_point;
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


