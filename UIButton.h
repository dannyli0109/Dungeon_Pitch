#pragma once
#include "Font.h"
#include "SpriteRenderer.h"

class UIButton
{
public:
	static UIButton* GetInstance();
	static UIButton* CreateInstance(GLFWwindow* window, Font* font);
	static void Draw(SpriteRenderer* spriteRenderer, glm::vec2 position, glm::vec2 size, glm::vec3 backgroundColor, std::string text, float fontSize, glm::vec3 textColor);
private:
	UIButton() {};
	~UIButton() {};
	static UIButton* instance;
	Font* font;
	GLFWwindow* window;
};

