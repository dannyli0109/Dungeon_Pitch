#pragma once
#include "Ammo.h"
#include "SpriteRenderer.h"
class Bullet :
    public Ammo
{
public:
    Bullet(AmmoStats stat);
public:
    virtual void Update(float deltaTime) override;
    virtual void Draw(SpriteRenderer* spriteRenderer) override {};
    virtual void OnImpact(Agent* agent) override;
};

