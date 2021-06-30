#pragma once
#include "Component.h"
#include "Player.h"
#include <functional>
#include "Entity.h"
#include "Transform.h"
#include "RigidBody.h"
#include "BoxRotated.h"
#include "SpriteAnimation.h"
#include "Agent.h"
#include "Ammo.h"
#include "AmmoFactory.h"
class Enemy :
    public Agent
{
public:
    Enemy(Player* player, float speed, float health, std::vector<AmmoStats> ammos);
public:
    virtual void Update(float deltaTime) override;
    virtual void Draw(SpriteRenderer* spriteRenderer) override {
        SpriteContainer* spriteContainer = entity->GetComponent<SpriteContainer>();
        if (damaging)
        {
            spriteContainer->sprite.tint = { 1, 0, 0, 1 };
        }
    };
    virtual void Attack();
    virtual void TakeDamage(float amount) override
    {
        Agent::TakeDamage(amount);
        if (health <= 0 && !entity->removing)
        {
            player->gold += 1;
            entity->removing = true;
        }
    }

    int index;
    std::vector <std::function<void()>> spellQueue;
    std::vector<float> spellTime;
protected:
    Player* player;
    float speed;
    std::vector<AmmoStats> ammos;
    float fireRate;
    float timeSinceLastShoot;
};

