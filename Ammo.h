#pragma once
#include "Component.h"
#include "AmmoStats.h"
#include "Agent.h"
#include "Entity.h"

class Ammo :
    public Component
{
public:
    Ammo(AmmoType type, AmmoStats stat) : type(type) {
        this->damage = stat.damage;
        this->speed = stat.speed;
        this->size = stat.size;
        this->critChance = stat.critChance;
        this->travelTime = stat.travelTime;
        this->count = stat.count;
        this->baseSize = baseSize;
    };
    virtual void OnImpact(Agent* agent) = 0;
public:
    AmmoType type;
    float damage;
    float speed;
    float size;
    float critChance;
    float travelTime;
    int count;
    glm::vec2 baseSize;
};

