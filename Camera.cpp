#include "Camera.h"


Camera::Camera()
{
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

//Jump

void Camera::startJump()
{
	m_isJump = true;
}

void Camera::stopJump()
{
	m_isJump = false;
}

bool Camera::needToJump() const
{
	return m_isJump;
}