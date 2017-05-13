#include "Action.h"

#include <iostream>
using namespace std;


Action::Action()
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

void Action::startGoForward()
{
	m_isGoForward = true;
}

void Action::stopForward()
{
	m_isGoForward = false;
}

bool Action::needGoForward() const
{
	return m_isGoForward;
}

//Go backward

void Action::startGoBackward()
{
	m_isGoBackward = true;
}

void Action::stopBackward()
{
	m_isGoBackward = false;
}

bool Action::needGoBackward() const
{
	return m_isGoBackward;
}

//Strafe left

void Action::startStrafeLeft()
{
	m_isStrafeLeft = true;
}

void Action::stopStrafeLeft()
{
	m_isStrafeLeft = false;
}

bool Action::needStrafeLeft() const
{
	return m_isStrafeLeft;
}

//Strafe right

void Action::startStrafeRight()
{
	m_isStrafeRight = true;
}

void Action::stopStrafeRight()
{
	m_isStrafeRight = false;
}

bool Action::needStrafeRight() const
{
	return m_isStrafeRight;
}

//Running

void Action::startRun()
{
	m_isRunning = true;
}

void Action::stopRun()
{
	m_isRunning = false;
}

bool Action::needToRun() const
{
	return m_isRunning;
}


//Crouching
void Action::startCrouch()
{
	m_isCrouching = true;
}

void Action::stopCrouch()
{
	m_isCrouching = false;
}

bool Action::needToCrouch() const
{
	return m_isCrouching;
}

//Check the player moving or not
void Action::playerMoving()
{
	m_one_of_movement_keys_pressed = true;
}
void Action::playerNotMoving()
{
	m_one_of_movement_keys_pressed = false;
}
bool Action::needToMove() const
{
	return m_one_of_movement_keys_pressed;
}


