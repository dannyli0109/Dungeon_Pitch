#pragma once
#include "Component.h"
#include <vector>
#include "Entity.h"
#include "Transform.h"
#include "BoxRotated.h"
#include "RigidBody.h"


class Map :
    public Entity
{
public:
    Map(Transform* transform, std::vector<std::string> layout);
    virtual void DrawGUI() override;
public:
    std::vector<Entity*> walls;

};

