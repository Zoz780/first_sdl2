#include "Camera.h"

#include <glut.h>
#include <math.h>

#include <iostream>
using namespace std;

Camera::Camera()
{
}

void Camera::SetPosX(float xpos)
{
	cam.position.SetX(xpos);
}
float Camera::GetPosX()
{
	return cam.position.GetX();
}

void Camera::SetPosY(float ypos)
{
	cam.position.SetY(ypos);
}
float Camera::GetPosY()
{
	return cam.position.GetY();
}

void Camera::SetPosZ(float zpos)
{
	cam.position.SetZ(zpos);
}
float Camera::GetPosZ()
{
	return cam.position.GetZ();
}

void Camera::SetPoseX(float xpose)
{
	cam.pose.SetX(xpose);
}
float Camera::GetPoseX()
{
	return cam.pose.GetX();
}

void Camera::SetPoseY(float ypose)
{
	cam.pose.SetY(ypose);
}
float Camera::GetPoseY()
{
	return cam.pose.GetY();
}

void Camera::init_camera()
{
	cam.position.x = 0;
	cam.position.y = 0;
	cam.position.z = 5;

	cam.pose.x = 0;
	cam.pose.y = 0;
	cam.pose.z = 0;
}

void Camera::set_view_point()
{
	float verticalAngle = utils_cam.ToRad(cam.pose.x);
	float horizontalAngle = utils_cam.ToRad(cam.pose.y);

	float dx = cos(verticalAngle) * cos(horizontalAngle);
	float dy = cos(verticalAngle) * sin(horizontalAngle);
	float dz = sin(verticalAngle);

	float cx = cam.position.x + dx, cy = cam.position.y + dy, cz = cam.position.z + dz;
	gluLookAt(cam.position.x, cam.position.y, cam.position.z, cx, cy, cz, 0, 0, 1);
}

void Camera::rotate_camera(float delta_rotate_x, float delta_rotate_y, float mouse_speed)
{

	cam.pose.x -= (float)(delta_rotate_y)* mouse_speed;
	cam.pose.y -= (float)(delta_rotate_x)* mouse_speed;

	if (cam.pose.x >= 87.0f)
	{
		cam.pose.x = 87.0f;
	}
	if (cam.pose.x <= -87.0f)
	{
		cam.pose.x = -87.0f;
	}
}

void Camera::move_camera_forward(double distance)
{
	double angle = utils_cam.ToRad(cam.pose.y);

	cam.position.x += cos(angle) * distance;
	cam.position.y += sin(angle) * distance;
}

void Camera::move_camera_backward(double distance)
{
	double angle = utils_cam.ToRad(cam.pose.y);

	cam.position.x -= cos(angle) * distance;
	cam.position.y -= sin(angle) * distance;
}

void Camera::step_camera_left(double distance)
{
	double angle = utils_cam.ToRad(cam.pose.y + 90.0);

	cam.position.x += cos(angle) * distance;
	cam.position.y += sin(angle) * distance;
}

void Camera::step_camera_right(double distance)
{
	double angle = utils_cam.ToRad(cam.pose.y - 90.0);

	cam.position.x += cos(angle) * distance;
	cam.position.y += sin(angle) * distance;
}

void Camera::move_camera_up(double distance)
{
	cam.position.z += distance;
}

void Camera::move_camera_down(double distance)
{
	cam.position.z -= distance;
}


