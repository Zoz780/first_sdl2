#pragma once
class Camera
{

public:
	Camera();

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

	//Jump
	void startJump();
	void stopJump();
	bool needToJump() const;

private:

	bool m_isGoForward;
	bool m_isGoBackward;
	bool m_isStrafeLeft;
	bool m_isStrafeRight;
	bool m_isJump;
};

