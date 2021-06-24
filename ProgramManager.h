#pragma once
#include "Graphics.h"
#include "GUI.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "Camera.h"
#include "Entity.h"
#include "Transform.h"
#include "SpriteContainer.h"
#include "SpriteAnimation.h"
#include "PlayerInputManager.h"
#include "Font.h";
#include "UIButton.h"

class ProgramManager
{
public:
	bool Init();
	void Run();
	void Destroy();
private:
	void RenderGUI();
	//bool InitWindow();
	//void InitResources();
	void InitEntities();
private:
	GLFWwindow* window;
	ResourceManager* resourceManager;
	SpriteRenderer* spriteRenderer;
	ShaderProgram* spriteShader;
	ShaderProgram* textShader;
	Camera* camera;
	Entity* player;
	float time;
	float currentTime;
	float deltaTime;
	Font* font;
	UIButton* button;
};

