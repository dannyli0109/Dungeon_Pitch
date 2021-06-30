#pragma once
#include "SpriteRenderer.h"
#include "Font.h"
class Entity;
class Component
{
public:
	Component() = default;
	virtual ~Component() {}
	Entity* GetEntity() { return entity; }
	void SetEntity(Entity* entity) { this->entity = entity; }
	virtual void Update(float deltaTime) = 0;
	virtual void Draw(SpriteRenderer* spriteRenderer) = 0;
	virtual void DrawGUI() {};
	virtual void DrawOverlay(SpriteRenderer* spriteRenderer, Font* font) {}
protected:
	Entity* entity;
};

