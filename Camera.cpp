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

//look up

void Camera::startLookUp()
{
	m_isLookUp = true;
}

void Camera::stopLookUp()
{
	m_isLookUp = false;
}

bool Camera::needLookUp() const
{
	return m_isLookUp;
}

//look down

void Camera::startLookDown()
{
	m_isLookDown = true;
}

void Camera::stopLookDown()
{
	m_isLookDown = false;
}

bool Camera::needLookDown() const
{
	return m_isLookDown;
}

//Turn left

void Camera::startTurnLeft()
{
	m_isTurnLeft = true;
}

void Camera::stopTurnLeft()
{
	m_isTurnLeft = false;
}

bool Camera::needTurnLeft() const
{
	return m_isTurnLeft;
}

//Turn right

void Camera::startTurnRight()
{
	m_isTurnRight = true;
}

void Camera::stopTurnRight()
{
	m_isTurnRight = false;
}

bool Camera::needTurnRight() const
{
	return m_isTurnRight;
}
