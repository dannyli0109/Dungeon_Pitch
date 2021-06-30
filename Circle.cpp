#include "Circle.h"
#include "Entity.h"
#include "Transform.h"

glm::vec2 Circle::GetCenter()
{
	return entity->transform->GetPosition() + offset;
}

void Circle::DrawShape(LineRenderer* lineRenderer)
{
	lineRenderer->AddCircle(glm::vec3(entity->transform->GetPosition() + offset, 0), radius, color, 64);
}

bool Circle::ContainPoint(glm::vec2 point)
{
	glm::vec2 center = entity->transform->GetPosition() + offset;
	return glm::length(point - center) < radius;
}
