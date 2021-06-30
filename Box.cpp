#include "Box.h"

Box::Box(float xMin, float xMax, float yMin, float yMax, int layer, int mask, glm::vec4 color) : Shape(ShapeType::Box, layer, mask)
{
	this->xMin = xMin;
	this->xMax = xMax;
	this->yMin = yMin;
	this->yMax = yMax;
	this->color = color;

}

std::vector<glm::vec2> Box::GetPoints()
{
	Transform* transform = entity->transform;
	glm::vec2 position = transform->GetPosition();
	return {
		{position.x + xMin, position.y + yMin},
		{position.x + xMax, position.y + yMin},
		{position.x + xMax, position.y + yMax},
		{position.x + xMin, position.y + yMax}
	};
}

glm::vec2 Box::GetCenter()
{
	Transform* transform = entity->transform;
	glm::vec2 position = transform->GetPosition();
	float xMid = (xMax + xMin) / 2.0f;
	float yMid = (yMax + yMin) / 2.0f;
	return glm::vec2(position.x + xMid, position.y + yMid);
}

void Box::DrawShape(LineRenderer* lineRenderer)
{
	std::vector<glm::vec2> points = GetPoints();
	lineRenderer->AddLine(glm::vec3(points[0], 0), glm::vec3(points[1], 0), color);
	lineRenderer->AddLine(glm::vec3(points[1], 0), glm::vec3(points[2], 0), color);
	lineRenderer->AddLine(glm::vec3(points[2], 0), glm::vec3(points[3], 0), color);
	lineRenderer->AddLine(glm::vec3(points[3], 0), glm::vec3(points[0], 0), color);
}

bool Box::ContainPoint(glm::vec2 point)
{
	Transform* transform = entity->transform;
	glm::vec2 position = transform->GetPosition();
	return point.x > xMin + position.x && point.x < xMax + position.x && point.y > yMin + position.y && point.y < yMax + position.y;
}
