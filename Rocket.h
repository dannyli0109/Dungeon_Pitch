#pragma once
#include "Ammo.h"
#include "RigidBody.h"
#include "BoxRotated.h"
#include "AmmoFactory.h"
class Rocket :
    public Ammo
{
public:
    Rocket(AmmoStats stat);
public:
    virtual void Update(float deltaTime) override;
    virtual void Draw(SpriteRenderer* spriteRenderer) override {};
    virtual void OnImpact(Agent* agent) override;
public:
    float explodeDamage;
    float explodeRadius;
    float rad;
    float explodeMask;
    float explodeLayer;
};

