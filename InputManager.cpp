#include "InputManager.h"

InputManager* InputManager::GetInstance()
{
	return instance;
}

InputManager* InputManager::CreateInstance()
{
    if (!instance)
    {
        instance = new InputManager();
    }
    return instance;
}

void InputManager::Update(GLFWwindow* window)
{
    previousState = state;
    state = {};
    glfwGetCursorPos(window, &state.mouseX, &state.mouseY);
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) state.mouseDown = true;
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) state.mouseUp = true;
    if (glfwGetKey(window, GLFW_KEY_W)) state.wKeyDown = true;
    if (glfwGetKey(window, GLFW_KEY_A)) state.aKeyDown = true;
    if (glfwGetKey(window, GLFW_KEY_S)) state.sKeyDown = true;
    if (glfwGetKey(window, GLFW_KEY_D)) state.dKeyDown = true;
}

void InputManager::Destroy()
{
    delete instance;
    instance = nullptr;
}

InputManager* InputManager::instance = nullptr;