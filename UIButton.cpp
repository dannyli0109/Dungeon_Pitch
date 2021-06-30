#include "UIButton.h"


UIButton* UIButton::GetInstance()
{
	return instance;
}

UIButton* UIButton::CreateInstance(GLFWwindow* window, Font* font)
{
	if (!instance)
	{
		instance = new UIButton();
		instance->font = font;
        instance->window = window;
	}

	return instance;
}

void UIButton::Draw(SpriteRenderer* spriteRenderer, glm::vec2 position, glm::vec2 size, glm::vec3 backgroundColor, std::string text, float fontSize, glm::vec3 textColor)
{
    int width, height;
    GLFWwindow* window = instance->window;
    Font* font = instance->font;
    glfwGetWindowSize(window, &width, &height);
    glm::mat4 projection = glm::ortho(0.0f, float(width), 0.0f, float(height));
    spriteRenderer->Begin(projection);
    glm::mat4 buttonTransform = glm::mat4(1.0f);
    buttonTransform = glm::translate(buttonTransform, { position.x + size.x / 2.0f, position.y + size.y / 2.0f, 0 });
    buttonTransform = glm::scale(buttonTransform, glm::vec3(size, 1));
    spriteRenderer->AddSprite(buttonTransform, glm::vec4(backgroundColor, 1));
    spriteRenderer->End();

    font->GetShader()->SetUniform("u_ProjectionMatrix", projection);
    float textWidth = font->MeasureWidth(text, fontSize);
    float xoffset = (size.x - textWidth) / 2.0f;
    font->Draw(text, position.x + xoffset, position.y + size.y / 2.0f - fontSize / 2.0f, fontSize, textColor);
}

UIButton* UIButton::instance = nullptr;