#include "BulletManager.h"

BulletManager::BulletManager(Camera* camera)
{
	this->camera = camera;
}

void BulletManager::Update(float deltaTime)
{
	Circle* circle = entity->GetComponent<Circle>();

	if (circle)
	{
		glm::vec2 windowSize = camera->GetSize();
		float zoom = camera->GetZoom();
		float xMin = -windowSize.x / zoom / 2.0f;
		float xMax = windowSize.x / zoom / 2.0f;
		float yMin = -windowSize.y / zoom / 2.0f;
		float yMax = windowSize.y / zoom / 2.0f;

		Transform* transform = entity->transform;
		glm::vec2 pos = transform->GetPosition();
		if (pos.x < xMin) entity->removing = true;
		if (pos.x > xMax) entity->removing = true;
		if (pos.y < yMin) entity->removing = true;
		if (pos.y > yMax) entity->removing = true;

		//if (playerPos.x - boxOffsetX < xMin) entity->transform->localTransform[3][0] = xMin + boxOffsetX;
		//if (playerPos.x + boxOffsetX > xMax) entity->transform->localTransform[3][0] = xMax - boxOffsetX;
		//if (playerPos.y - boxOffsetY < yMin) entity->transform->localTransform[3][1] = yMin + boxOffsetY;
		//if (playerPos.y + boxOffsetY > yMax) entity->transform->localTransform[3][1] = yMax - boxOffsetY;
	}
}

void BulletManager::Draw(SpriteRenderer* spriteRenderer)
{
}
