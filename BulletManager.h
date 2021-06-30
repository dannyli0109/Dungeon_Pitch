#pragma once
#include "Component.h"
#include "SpriteRenderer.h"
#include "Circle.h"
#include "Entity.h"
#include "Transform.h"

class BulletManager :
    public Component
{
public:
    BulletManager(Camera* camera);
    void Update(float deltaTime) override;
    void Draw(SpriteRenderer* spriteRenderer) override;
private:
    Camera* camera;
};

