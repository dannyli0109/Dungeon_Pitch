#include "AmmoFactory.h"

AmmoFactory* AmmoFactory::GetInstance()
{
	return instance;
}

AmmoFactory* AmmoFactory::CreateInstance()
{
    if (!instance)
    {
        instance = new AmmoFactory();
    }
    return instance;
}

Entity* AmmoFactory::InitBullet(glm::vec2 position, float rotation, int layer, int mask, AmmoStats stats)
{
	Entity* bullet = new Entity(new Transform(glm::vec3(position, 0), rotation, glm::vec2(1, 1) * stats.size));
	bullet->AddComponent(new RigidBody(glm::vec2(0, 1.0f) * stats.speed, { 0, 0 }, 1));
	bullet->AddComponent(
		new BoxRotated(
			{
				{-0.5f * stats.baseSize.x, 0.5f * stats.baseSize.y}, 
				{0.5f * stats.baseSize.x, 0.5f * stats.baseSize.y }, 
				{0.5f * stats.baseSize.x, -0.5f * stats.baseSize.y }, 
				{-0.5f * stats.baseSize.x, -0.5f * stats.baseSize.y }
			},
			layer,
			mask,
			{ 1, 0, 0, 1 }
		)
	);
	if (stats.type == AmmoType::Bullet)
	{
		bullet->AddComponent(new Bullet(stats));
	}
	else if (stats.type == AmmoType::Rocket)
	{
		stats.rocket.rad = rotation;
		bullet->AddComponent(new Rocket(stats));
	}
	return bullet;
}

AmmoFactory* AmmoFactory::instance = nullptr;