#include "BoxRotated.h"

BoxRotated::BoxRotated(std::vector<glm::vec2> points, int layer, int mask, glm::vec4 color) : Shape(ShapeType::BoxRotated, layer, mask)
{
	this->points = points;
	this->color = color;
}

std::vector<glm::vec2> BoxRotated::GetPoints()
{
	Transform* transform = entity->transform;
	glm::mat4 m = transform->GetTransformMatrix();
	std::vector<glm::vec2> pointsTransformed;
	for (int i = 0; i < points.size(); i++)
	{
		glm::vec2 pointTransformed = m * glm::vec4(points[i], 0, 1.0f);
		pointsTransformed.push_back(pointTransformed);
	}
	return pointsTransformed;
}

glm::vec2 BoxRotated::GetCenter()
{
	glm::vec2 sum = { 0, 0 };
	std::vector<glm::vec2> pointsTransformed = GetPoints();
	for (int i = 0; i < points.size(); i++)
	{
		sum += points[i];
	}

	glm::vec2 average = sum / (float)points.size();
	return average;
}

void BoxRotated::DrawShape(LineRenderer* lineRenderer)
{
	std::vector<glm::vec2> pointsTransformed = GetPoints();
	for (int i = 0; i < pointsTransformed.size(); i++)
	{
		glm::vec2 p1 = pointsTransformed[i];
		glm::vec2 p2 = pointsTransformed[(i + 1) % pointsTransformed.size()];
		lineRenderer->AddLine(glm::vec3(p1, 0), glm::vec3(p2, 0), color);
	}
}

bool BoxRotated::ContainPoint(glm::vec2 point)
{
	int pos = 0;
	int neg = 0;
	std::vector<glm::vec2> pointsTransformed = GetPoints();
	for (int i = 0; i < pointsTransformed.size(); i++)
	{
		glm::vec2 p1 = pointsTransformed[i];
		glm::vec2 p2 = pointsTransformed[(i + 1) % pointsTransformed.size()];
		//var d = (x - x1) * (y2 - y1) - (y - y1) * (x2 - x1);
		float d = (point.x - p1.x) * (p2.y - p1.y) - (point.y - p1.y) * (p2.x - p1.x);
		if (d > 0) pos++;
		if (d < 0) neg++;

		if (pos > 0 && neg > 0) return false;
	}
	return true;
}
