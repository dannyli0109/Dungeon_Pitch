#pragma once
#include "Component.h"
#include "Entity.h"
#include "Transform.h"
class Agent :
	public Component
{
public:
	Agent(float health) : health(health), armor(0), maxHealth(health), damageTime(0), damageDuration(1.0f) {}
	virtual void TakeDamage(float amount);
	virtual void DrawOverlay(SpriteRenderer* spriteRenderer, Font* font) override;
	virtual void Update(float deltaTime) override;
protected:
	float health;
	float maxHealth;
	float armor;
	bool damaging;
	float damageTime;
	float damageDuration;
};

