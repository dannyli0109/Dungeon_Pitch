#include "Agent.h"

void Agent::TakeDamage(float amount)
{
	if (armor >= amount) armor -= amount;
	else
	{
		amount -= armor;
		health -= amount;
		armor = 0;
	}
	damaging = true;

}

void Agent::DrawOverlay(SpriteRenderer* spriteRenderer, Font* font)
{
	if (!damaging) return;
	float percent = health / maxHealth;
	float width = 0.3f;
	float height = 0.05f;
	float y = 7.0f;
	if (percent >= 0)
	{
		Transform* transform = entity->GetComponent<Transform>();
		glm::vec2 position = transform->GetPosition();
		glm::mat4 transformMat(1);
		transformMat = glm::translate(transformMat, glm::vec3(position, 1));
		transformMat = glm::scale(transformMat, { width, height, 1 });
		transformMat = glm::translate(transformMat, { 0, y, 0 });

		ResourceManager* resourceManager = ResourceManager::GetInstance();
		spriteRenderer->AddSprite(transformMat, { 0, 0, 0, 1 });

		transformMat = glm::mat4(1);
		transformMat = glm::translate(transformMat, { 
				position.x - width * ((1.0f - percent) / 2.0f), position.y, 1 
			}
		);
		transformMat = glm::scale(transformMat, { width * percent, height, 1 });
		transformMat = glm::translate(transformMat, { 0, y, 0 });
		spriteRenderer->AddSprite(transformMat, { 0, 1, 0, 1 });
	}
}

void Agent::Update(float deltaTime)
{
	if (damaging)
	{
		damageTime += deltaTime;
	}

	if (damageTime >= damageDuration)
	{
		damaging = false;
		damageTime = 0;
	}
}
