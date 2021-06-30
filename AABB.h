#pragma once
class AABB
{
public:
	AABB() = default;
	AABB(float minX, float minY, float maxX, float maxY);
	bool IsOverlapping(AABB other);

	float minX, minY, maxX, maxY;
};

