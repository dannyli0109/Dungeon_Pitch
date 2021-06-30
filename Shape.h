#pragma once
#include "Component.h"
#include "LineRenderer.h"
#include "GUI.h"
#include "Entity.h"
#include "Transform.h"
enum class ShapeType
{
	Circle = 0,
	Box,
	BoxRotated,
	Plane,
	Count
};
class Shape : public Component
{
public:
	Shape(ShapeType type, int layer, int mask) : type(type), layer(layer), mask(mask) {};
	virtual void DrawShape(LineRenderer* lineRenderer) = 0;
	ShapeType GetType() {
		return type;
	};
	virtual bool ContainPoint(glm::vec2 point) = 0;
	int layer, mask;
	virtual void DrawGUI() override{

	}
protected:
	ShapeType type;
	glm::vec4 color = { 1, 1, 1, 1 };
};

const int PLAYER_LAYER = 1 << 0;
const int PLAYER_BULLET_LAYER = 1 << 1;
const int ENEMY_LAYER = 1 << 2;
const int ENEMY_BULLET_LAYER = 1 << 3;
const int WALL_LAYER = 1 << 4;
const int PLAYER_DETECT_WALL_H_LAYER = 1 << 5;
const int PLAYER_DETECT_WALL_V_LAYER = 1 << 6;
const int PLAYER_EXPLOSIVE_LAYER = 1 << 7;
const int ENEMY_EXPLOSIVE_LAYER = 1 << 8;