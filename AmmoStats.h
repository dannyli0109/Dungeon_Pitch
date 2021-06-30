#pragma once


enum class AmmoType
{
    Bullet,
    Rocket,
    Laser,
    Explosive
};

struct AmmoStats
{
    glm::vec2 baseSize;
    AmmoType type;
    float damage;
    float speed;
    float size;
    float critChance;
    float travelTime;
    float count;
    union
    {
        struct
        {
            float explodeDamage;
            float explodeRadius;
            float rad;
            int explodeMask;
            int explodeLayer;
        } rocket;
    };
};

