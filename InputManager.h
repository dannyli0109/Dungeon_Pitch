#pragma once
#include "Graphics.h"
struct InputStates
{
	double mouseX;
	double mouseY;
	bool mouseDown = false;
	bool mouseUp = false;
	bool wKeyDown = false;
	bool aKeyDown = false;
	bool sKeyDown = false;
	bool dKeyDown = false;
	bool rKeyDown = false;
	bool rKeyUp = false;
};

class InputManager
{
public:
	static InputManager* GetInstance();
	static InputManager* CreateInstance();
	void Update(GLFWwindow* window);
	void Destroy();
	InputStates state;
	InputStates previousState;
private:
	InputManager() {};
	~InputManager() {};
	static InputManager* instance;
};

