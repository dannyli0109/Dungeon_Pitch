#pragma once
#include "Shape.h"
#include "Transform.h"
class Box :
	public Shape
{
public:
	Box(float xMin, float xMax, float yMin, float yMax, int layer, int mask, glm::vec4 color);

	std::vector<glm::vec2> GetPoints();
	glm::vec2 GetCenter();

#pragma region Overrdie
	virtual void Update(float deltaTime) override {};
	virtual void Draw(SpriteRenderer* spriteRenderer) override {};
	virtual void DrawShape(LineRenderer* lineRenderer) override;
	virtual bool ContainPoint(glm::vec2 point) override;
#pragma endregion
public:
	float xMin, xMax, yMin, yMax;
};

