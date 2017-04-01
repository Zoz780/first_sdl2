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

	//look up
	void startLookUp();
	void stopLookUp();
	bool needLookUp() const;

	//look down
	void startLookDown();
	void stopLookDown();
	bool needLookDown() const;

	//turn left
	void startTurnLeft();
	void stopTurnLeft();
	bool needTurnLeft() const;

	//turn right
	void startTurnRight();
	void stopTurnRight();
	bool needTurnRight() const;

private:

	bool m_isGoForward;
	bool m_isGoBackward;
	bool m_isLookUp;
	bool m_isLookDown;
	bool m_isTurnLeft;
	bool m_isTurnRight;
	bool m_isStrafeLeft;
	bool m_isStrafeRight;
};

