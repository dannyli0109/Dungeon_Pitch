#pragma once
#include "Component.h"
#include "SpriteRenderer.h"
#include "SpriteAnimation.h"
#include "Utilities.h"
#include "InputManager.h"
#include "RigidBody.h"
#include "Camera.h"
#include "Circle.h"
#include "Box.h"
#include "BulletManager.h"
#include "BoxRotated.h"
#include "Matrices.h"
#include "Agent.h"
#include "Ammo.h"
#include "AmmoFactory.h"
class Player :
    public Agent
{
public:
    Player(GLFWwindow* window, Camera* camera, float speed, Entity* boxCastH, Entity* boxCastV, float health, std::vector<AmmoStats> stats);
    virtual void Update(float deltaTime) override;
    virtual void Draw(SpriteRenderer* spriteRenderer) override {
        SpriteContainer* spriteContainer = entity->GetComponent<SpriteContainer>();
        if (damaging)
        {
            //spriteContainer->sprite.tint = { 1, 0, 0, 1 };
        }
    }

    virtual void TakeDamage(float amount) override
    {
        Agent::TakeDamage(amount);
    }

    int gold = 0;
private:
    GLFWwindow* window;
    float speed;
    Camera* camera;
    Entity* boxCastH;
    Entity* boxCastV;
    std::vector<AmmoStats> ammos;
};

