#include "Rocket.h"

Rocket::Rocket(AmmoStats stat) : Ammo(AmmoType::Rocket, stat)
{
	this->explodeDamage = stat.rocket.explodeDamage;
	this->explodeRadius = stat.rocket.explodeRadius;
	this->rad = stat.rocket.rad;
	this->explodeMask = stat.rocket.explodeMask;
	this->explodeLayer = stat.rocket.explodeLayer;
}

void Rocket::Update(float deltaTime)
{
}

void Rocket::OnImpact(Agent* agent)
{
	if (agent)
	{
		agent->TakeDamage(damage);
	}
	glm::vec2 position = entity->transform->GetPosition();
	

	AmmoStats stats = {};
	stats.speed = 0;
	stats.type = AmmoType::Bullet;
	stats.damage = explodeDamage;
	stats.size = explodeRadius;
	stats.critChance = 0.0f;
	stats.travelTime = 0.0f;
	stats.count = 1;
	stats.baseSize = { 1.0f, 1.0f };

	Entity* explode = AmmoFactory::GetInstance()->InitBullet(
		entity->transform->GetPosition(), rad,
		explodeLayer, explodeMask,
		stats
	);

	Entity::entities.push_back(explode);
}
