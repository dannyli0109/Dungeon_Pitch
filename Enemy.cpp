#include "Enemy.h"

Enemy::Enemy(Player* player, float speed, float health, std::vector<AmmoStats> ammos) : Agent(health)
{
	this->player = player;
	this->speed = speed;
	this->ammos = ammos;
	//this->attack = attack;
	//this->bulletSize = bulletSize;

	this->index = 0;
	spellQueue.push_back(
		[this]()
		{
			glm::vec2 position = entity->transform->GetPosition();
			glm::vec2 targetPosition = this->player->GetEntity()->transform->GetPosition();
			float distance = glm::length(glm::vec3(targetPosition - position, 0.0f));
			

			float rad = atan2((targetPosition.y - position.y), targetPosition.x - position.x) - M_PI_2;
			glm::vec2 dir = { targetPosition.x - position.x, targetPosition.y - position.y };

			float l = glm::length(dir);
			if (l > 0)
			{
				dir /= l;
			}
			int bulletType = 0;

			Entity* bullet = AmmoFactory::GetInstance()->InitBullet(entity->transform->GetPosition(), rad, ENEMY_BULLET_LAYER, WALL_LAYER | PLAYER_LAYER, this->ammos[bulletType]);

			Entity::entities.push_back(bullet);
		}
	);
	spellTime.push_back(1.0f);
	fireRate = spellTime[0];
	timeSinceLastShoot = 0;
}

void Enemy::Update(float deltaTime)
{
	Agent::Update(deltaTime);
	glm::vec2 position = entity->transform->GetPosition();
	glm::vec2 targetPosition = this->player->GetEntity()->transform->GetPosition();
	SpriteAnimation* spriteAnimation = entity->GetComponent<SpriteAnimation>();
	SpriteContainer* spriteContainer = entity->GetComponent<SpriteContainer>();

	float angle = GetAngle({ targetPosition.x - position.x, -(targetPosition.y - position.y) });
	std::string dirString = "s";
	std::string stateString = "idle";

	if (angle >= -22.5f && angle < 22.5f) dirString = "e";
	if (angle >= 22.5f && angle < 67.5f) dirString = "se";
	if (angle >= 67.5f && angle < 112.5f) dirString = "s";
	if (angle >= 112.5f && angle < 157.5f) dirString = "sw";
	if (angle >= 157.5f || angle < -157.5f) dirString = "w";
	if (angle >= -157.5f && angle < -112.5f) dirString = "nw";
	if (angle >= -112.5f && angle < -67.5f) dirString = "n";
	if (angle >= -67.5f && angle < -22.5f) dirString = "ne";

	spriteAnimation->SetState(stateString + "_" + dirString);

	//if (damaging)
	//{
	//	spriteContainer->sprite.tint = { 1, 0, 0, 1 };
	//}


	timeSinceLastShoot += deltaTime;
	if (timeSinceLastShoot >= fireRate)
	{
		Attack();
		timeSinceLastShoot = 0;
	}
}

void Enemy::Attack()
{
	spellQueue[index % spellQueue.size()]();
	index++;
	fireRate = spellTime[index % spellTime.size()];
}
