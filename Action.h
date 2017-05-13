#pragma once
class Action
{
public:
	Action();
	//go Forward
	void startGoForward();
	void stopForward();
	bool needGoForward() const;

	//go Backward
	void startGoBackward();
	void stopBackward();
	bool needGoBackward() const;

	//Strafe left
	void startStrafeLeft();
	void stopStrafeLeft();
	bool needStrafeLeft() const;

	//Strafe right
	void startStrafeRight();
	void stopStrafeRight();
	bool needStrafeRight() const;

	//Running
	void startRun();
	void stopRun();
	bool needToRun() const;

	//Crouching
	void startCrouch();
	void stopCrouch();
	bool needToCrouch() const;

	//Check the player moving or not
	void playerMoving();
	void playerNotMoving();
	bool needToMove() const;

private:

	bool m_isGoForward;
	bool m_isGoBackward;
	bool m_isStrafeLeft;
	bool m_isStrafeRight;
	bool m_isRunning;
	bool m_isCrouching;
	bool m_one_of_movement_keys_pressed;
};

