#include "PlayerInputManager.h"

PlayerInputManager::PlayerInputManager(GLFWwindow* window)
{
	this->window = window;
}

void PlayerInputManager::Update(float deltaTime)
{
	SpriteAnimation* spriteAnimation = entity->GetComponent<SpriteAnimation>();
	bool moved = false;

	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	int width, height;
	glfwGetWindowSize(window, &width, &height);

	float angle = GetAngle({ xpos - width / 2.0f, ypos - height / 2.0f });
	std::string dirString = "s";
	std::string stateString = "idle";

	if (angle >= -22.5f && angle < 22.5f) dirString = "e";
	if (angle >= 22.5f && angle < 67.5f) dirString = "se";
	if (angle >= 67.5f && angle < 112.5f) dirString = "s";
	if (angle >= 112.5f && angle < 157.5f) dirString = "sw";
	if (angle >= 157.5f || angle < -157.5f) dirString = "w";
	if (angle >= -157.5f && angle < -112.5f) dirString = "nw";
	if (angle >= -112.5f && angle < -67.5f) dirString = "n";
	if (angle >= -67.5f && angle < -22.5f) dirString = "ne";

	
	if (glfwGetKey(window, GLFW_KEY_W))
	{
		moved = true;
	}

	if (glfwGetKey(window, GLFW_KEY_A))
	{
		moved = true;
	}

	if (glfwGetKey(window, GLFW_KEY_S))
	{
		moved = true;
	}

	if (glfwGetKey(window, GLFW_KEY_D))
	{
		moved = true;
	}

	if (moved)
	{
		stateString = "running";
	}

	spriteAnimation->SetState(stateString + "_" + dirString);

	//if (!moved)
	//{
	//	std::string state = spriteAnimation->GetState();
	//	if (state == "running_s") spriteAnimation->SetState("idle_s");
	//	if (state == "running_n") spriteAnimation->SetState("idle_n");
	//	if (state == "running_e") spriteAnimation->SetState("idle_e");
	//	if (state == "running_w") spriteAnimation->SetState("idle_w");
	//}
}
