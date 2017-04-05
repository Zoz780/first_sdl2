#include "Camera.h"

#include <iostream>
using namespace std;

Camera::Camera()
{
	m_isGoForward = false;
	m_isGoBackward = false;
	m_isStrafeLeft = false;
	m_isStrafeRight = false;
	m_isRunning = false;
	m_isCrouching = false;
	m_one_of_movement_keys_pressed = false;
}


//Go forward

void Camera::startGoForward()
{
	m_isGoForward = true;
}

void Camera::stopForward()
{
	m_isGoForward = false;
}

bool Camera::needGoForward() const
{
	return m_isGoForward;
}

//Go backward

void Camera::startGoBackward()
{
	m_isGoBackward = true;
}

void Camera::stopBackward()
{
	m_isGoBackward = false;
}

bool Camera::needGoBackward() const
{
	return m_isGoBackward;
}

//Strafe left

void Camera::startStrafeLeft()
{
	m_isStrafeLeft = true;
}

void Camera::stopStrafeLeft()
{
	m_isStrafeLeft = false;
}

bool Camera::needStrafeLeft() const
{
	return m_isStrafeLeft;
}

//Strafe right

void Camera::startStrafeRight()
{
	m_isStrafeRight = true;
}

void Camera::stopStrafeRight()
{
	m_isStrafeRight = false;
}

bool Camera::needStrafeRight() const
{
	return m_isStrafeRight;
}

//Running

void Camera::startRun()
{
	m_isRunning = true;
}

void Camera::stopRun()
{
	m_isRunning = false;
}

bool Camera::needToRun() const
{
	return m_isRunning;
}


//Crouching
void Camera::startCrouch()
{
	m_isCrouching = true;
}

void Camera::stopCrouch()
{
	m_isCrouching = false;
}

bool Camera::needToCrouch() const
{
	return m_isCrouching;
}

//Check the player moving or not
void Camera::playerMoving() 
{
	m_one_of_movement_keys_pressed = true;
}
void Camera::playerNotMoving()
{
	m_one_of_movement_keys_pressed = false;
}
bool Camera::needToMove() const
{
	return m_one_of_movement_keys_pressed;
}
