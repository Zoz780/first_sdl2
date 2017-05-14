#pragma once
#include "Vec3.h"
#include "Utils.h"

class Cam
{
public:
	Vec3 position;
	Vec3 pose;
};

class Camera
{
public:
	Camera();

	void SetPosX(float xpos);
	float GetPosX();

	void SetPosY(float ypos);
	float GetPosY();

	void SetPosZ(float zpos);
	float GetPosZ();

	void SetPoseX(float xpose);
	float GetPoseX();

	void SetPoseY(float ypose);
	float GetPoseY();

	/**
	* Initialize the camera position and direction.
	*/
	void init_camera();

	/**
	* Transform the models into the view point of the camera.
	*/
	void set_view_point();

	/**
	* Rotate the camera horizontally and vertically.
	*/
	void rotate_camera(float delta_rotate_x, float delta_rotate_y, float mouse_speed);

	/**
	* Move the camera forward.
	*/
	void move_camera_forward(double distance);

	/**
	* Move the camera backward.
	*/
	void move_camera_backward(double distance);

	/**
	* Step the camera left.
	*/
	void step_camera_left(double distance);

	/**
	* Step the camera right.
	*/
	void step_camera_right(double distance);

	/**
	* Move the camera up.
	*/
	void move_camera_up(double distance);

	/**
	* Move the camera down.
	*/
	void move_camera_down(double distance);

private:

	Cam cam;
	Utils utils_cam;

};

