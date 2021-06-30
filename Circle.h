#pragma once
#include "Shape.h"
class Circle :
	public Shape
{
public:
	Circle(int layer, int mask) : Shape(ShapeType::Circle, layer, mask) {};
	Circle(glm::vec2 offset, float radius, int layer, int mask, glm::vec4 color) : Shape(ShapeType::Circle, layer, mask) {
		this->offset = offset;
		this->radius = radius;
		this->color = color;
	};
	glm::vec2 GetCenter();
	float GetRadius() { return radius; };

#pragma region Override
	virtual void Update(float deltaTime) override {};
	virtual void Draw(SpriteRenderer* spriteRenderer) override {};
	virtual void DrawShape(LineRenderer* lineRenderer) override;
	virtual bool ContainPoint(glm::vec2 point) override;
#pragma endregion

	glm::vec2 offset = { 0, 0 };
	float radius = 1.0f;
protected:
};

