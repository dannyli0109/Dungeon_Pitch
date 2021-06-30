#include "Augment.h"

void AugmentStats::Draw(GLFWwindow* window, SpriteRenderer* spriteRenderer, Font* font, glm::vec2 position, glm::vec2 size, float fontSize)
{
    double cursorX, cursorY;
    glfwGetCursorPos(window, &cursorX, &cursorY);
    float xMin = position.x;
    float xMax = position.x + size.x;
    float yMin = position.y;
    float yMax = position.y + size.y;

    bool hover = false;
    float opacity = 0.5f;
    if (cursorX > xMin && cursorX < xMax && cursorY > yMin && cursorY < yMax)
    {
        hover = true;
        opacity = 1.0f;
        
        if (InputManager::GetInstance()->previousState.mouseDown&& InputManager::GetInstance()->state.mouseUp)
        {
            onClick(cost[rarity]);
        }
    }

    int width, height;
    //GLFWwindow* window = instance->window;
    //Font* font = font;
    glfwGetWindowSize(window, &width, &height);
    glm::mat4 projection = glm::ortho(0.0f, float(width), 0.0f, float(height));
    spriteRenderer->Begin(projection);
    glm::mat4 buttonTransform = glm::mat4(1.0f);
    buttonTransform = glm::translate(buttonTransform, { position.x + size.x / 2.0f, position.y + size.y / 2.0f, 0 });
    buttonTransform = glm::scale(buttonTransform, glm::vec3(size, 1));
    spriteRenderer->AddSprite(buttonTransform, glm::vec4(bgColors[rarity], opacity));
    spriteRenderer->End();

    font->GetShader()->SetUniform("u_ProjectionMatrix", projection);

    float padding = 10;
    float yoffset = size.y - fontSize - padding;

    {
        std::string text = name;
        float textWidth = font->MeasureWidth(text, fontSize);
        float xoffset = (size.x - textWidth) / 2.0f;
        font->Draw(text, position.x + xoffset, position.y + yoffset, fontSize, { 0, 0, 0 });
    }

    yoffset -= 30.0f;
    {
        std::string text = "$: " + std::to_string(cost[rarity]);
        float textWidth = font->MeasureWidth(text, fontSize);
        float xoffset = (size.x - textWidth) / 2.0f;
        font->Draw(text, position.x + xoffset, position.y + yoffset, fontSize, { 0, 0, 0 });
    }

    yoffset -= 30.0f;
    {
        for (int i = 0; i < descriptions[0].size(); i++)
        {
            std::string text = descriptions[0][i];
            float textWidth = font->MeasureWidth(text, fontSize);
            float xoffset = (size.x - textWidth) / 2.0f;
            yoffset -= fontSize + padding;
            font->Draw(text, position.x + xoffset, position.y + yoffset, fontSize, { 0, 0, 0 });
        }
    }

    yoffset = 200;
    {
        for (int i = 0; i < synergies.size(); i++)
        {
            std::string text = synergyText[synergies[i]];
            float textWidth = font->MeasureWidth(text, fontSize);
            float xoffset = (size.x - textWidth) / 2.0f;
            yoffset -= fontSize + padding;
            font->Draw(text, position.x + xoffset, position.y + yoffset, fontSize, synergyColor[synergies[i]]);
        }
    }
}
