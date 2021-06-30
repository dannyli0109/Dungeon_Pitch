#pragma once
#include "Entity.h"
#include "Bullet.h"
#include "AmmoStats.h"
#include "Transform.h"
#include "RigidBody.h"
#include "BoxRotated.h"
#include "Rocket.h"

class AmmoFactory
{
public:
	static AmmoFactory* GetInstance();
	static AmmoFactory* CreateInstance();
	Entity* InitBullet(glm::vec2 position, float rotation, int layer, int mask, AmmoStats stats);
private:
	AmmoFactory() {};
	~AmmoFactory() {};
	static AmmoFactory* instance;
};

