#include "AABB.h"

AABB::AABB(float minX, float minY, float maxX, float maxY)
{
	this->minX = minX;
	this->minY = minY;
	this->maxX = maxX;
	this->maxY = maxY;
}

bool AABB::IsOverlapping(AABB other)
{
	return (minX < other.maxX) && (maxX > other.minX) && (minY < other.maxY) && (maxY > other.minY);
}
