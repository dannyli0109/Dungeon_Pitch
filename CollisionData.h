#pragma once
#include "Matrices.h"
class Entity;

struct CollisionData
{
	glm::vec2 normal = { 0, 0 };
	float depth = -1;

	glm::vec2 position = { 0, 0 };

	Entity* a = nullptr;
	Entity* b = nullptr;

};