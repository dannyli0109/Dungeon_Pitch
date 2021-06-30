#include "CollisionFunctions.h"
#include <math.h>


std::vector<float> GetMinMaxProjection(const std::vector<glm::vec2>& points, const glm::vec2& vec)
{
	float min = FLT_MAX;
	float max = FLT_MIN;
	for (int i = 0; i < points.size(); i++)
	{
		float mag = glm::dot(points[i], vec);
		min = std::fmin(min, mag);
		max = std::fmax(max, mag);
	}
	return { min, max };
}

float LineOverlap(float min1, float max1, float min2, float max2)
{
	float min = std::fmin(max1, max2);
	float max = std::fmax(min1, min2);
	float diff = std::fmax(min - max, 0.0f);
	return diff;
}


// check the distance between two circle 
// if the distance > a.r + b.r
// they are not collide 
// otherwise they collide
CollisionData CollideCircleWithCircle(Shape* a, Shape* b)
{
	CollisionData result;
	Circle* circleA = (Circle*)a;
	Circle* circleB = (Circle*)b;

	float distance = glm::length(circleA->GetCenter() - circleB->GetCenter());

	float radiusA = circleA->GetRadius();
	float radiusB = circleB->GetRadius();

	if (distance < radiusA + radiusB)
	{
		result.a = circleA->GetEntity();
		result.b = circleB->GetEntity();

		result.depth = (radiusA + radiusB) - distance;

		// from b to a
		result.normal = glm::normalize(circleB->GetCenter() - circleA->GetCenter());

		result.position = circleA->GetCenter() + (result.normal * (circleA->GetRadius() - result.depth / 2));
	}
	return result;
}

// check the point closest to the box against the center of the circle
// if the distance between the point and the center of the circle is greater than the radius
// two shapes are not colliding
// otherwise they collides
// normals depends on which edge the circle clamps to
CollisionData CollideCircleWithBox(Shape* a, Shape* b)
{
	CollisionData result;
	Circle* circle = (Circle*)a;
	Box* box = (Box*)b;

	std::vector<glm::vec2> points = box->GetPoints();
	float xMin = points[0].x;
	float xMax = points[1].x;
	float yMin = points[1].y;
	float yMax = points[2].y;

	glm::vec2 clampPoint = circle->GetCenter();
	glm::vec2 normal = { 0, 0 };

	if (xMin > circle->GetCenter().x)
	{
		clampPoint.x = xMin;
		normal.x = -1;
	}
	else if (xMax < circle->GetCenter().x)
	{
		clampPoint.x = xMax;
		normal.x = 1;
	}

	if (yMin > circle->GetCenter().y)
	{
		clampPoint.y = yMin;
		normal.y = -1;
	}
	else if (yMax < circle->GetCenter().y)
	{
		clampPoint.y = yMax;
		normal.y = 1;
	}

	float distance = glm::length(clampPoint - circle->GetCenter());

	if (distance < circle->GetRadius())
	{
		result.a = a->GetEntity();
		result.b = b->GetEntity();
		result.normal = -glm::normalize(normal);
		result.depth = distance;
		result.position = clampPoint;
	}

	return result;
}

CollisionData CollideCircleWithBoxRotated(Shape* a, Shape* b)
{
	return CollisionData();
}

// project origin to center to the normal of the plane
// if the projection distance is greater than the radius to the circle
// the circle does collide to the plane
// other wise circle collides to the plane
// collision normal is the normal of the plane
CollisionData CollideCircleWithPlane(Shape* a, Shape* b)
{
	return CollisionData();
}

CollisionData CollideBoxWithCircle(Shape* a, Shape* b)
{
	return CollideCircleWithBox(b, a);
}

// the normal depends on the shortest distance to move out of the overlap;
CollisionData CollideBoxWithBox(Shape* a, Shape* b)
{
	CollisionData result;

	Box* boxA = (Box*)a;
	Box* boxB = (Box*)b;

	std::vector<glm::vec2> pointsA = boxA->GetPoints();
	std::vector<glm::vec2> pointsB = boxB->GetPoints();

	float minXA = pointsA[0].x;
	float maxXA = pointsA[1].x;
	float minYA = pointsA[1].y;
	float maxYA = pointsA[2].y;

	float minXB = pointsB[0].x;
	float maxXB = pointsB[1].x;
	float minYB = pointsB[1].y;
	float maxYB = pointsB[2].y;


	// (minX < other.maxX) && (maxX > other.minX) && (minY < other.maxY) && (maxY > other.minY);
	if ((minXA < maxXB) && (maxXA > minXB) && (minYA < maxYB) && (maxYA > minYB))
	{
		float minMaxX = maxXA > maxXB ? maxXB : maxXA;
		float maxMinX = minXA > minXB ? minXA : minXB;
		float diffX = minMaxX - maxMinX;

		float minMaxY = maxYA > maxYB ? maxYB : maxYA;
		float maxMinY = minYA > minYB ? minYA : minYB;
		float diffY = minMaxY - maxMinY;

		result.a = a->GetEntity();
		result.b = b->GetEntity();

		// the normal depends on the shortest distance to move out of the overlap;
		if (diffX < diffY)
		{
			if (boxA->GetCenter().x > boxB->GetCenter().x)
			{
				result.normal = { -1, 0 };
			}
			else {
				result.normal = { 1, 0 };
			}
			result.depth = diffX;
		}
		else {
			if (boxA->GetCenter().y > boxB->GetCenter().y)
			{
				result.normal = { 0, -1 };
			}
			else {
				result.normal = { 0, 1 };
			}
			result.depth = diffY;
		}

		result.position = boxA->GetCenter();
	}

	return result;
}

CollisionData CollideBoxWithBoxRotated(Shape* a, Shape* b)
{
	Box* sa = (Box*)a;
	BoxRotated* sb = (BoxRotated*)b;
	CollisionData result;

	std::vector<glm::vec2> shape1 = sa->GetPoints();
	std::vector<glm::vec2> shape2 = sb->GetPoints();

	float depth = FLT_MAX;
	bool overlapped = false;
	std::vector<std::vector<glm::vec2>> shapes = { shape1, shape2 };

	for (int i = 0; i < shapes.size(); i++)
	{
		for (int j = 0; j < shapes[i].size(); j++)
		{
			std::vector<glm::vec2> shape = shapes[i];
			glm::vec2 p1 = shape[j];
			glm::vec2 p2 = shape[(j + 1) % shape.size()];
			glm::vec2 v12 = p2 - p1;
			glm::vec2 normal = { -v12.y, v12.x };
			normal = glm::normalize(normal);
			std::vector<float> minmax1 = GetMinMaxProjection(shape1, normal);
			std::vector<float> minmax2 = GetMinMaxProjection(shape2, normal);
			float overlap = LineOverlap(minmax1[0], minmax1[1], minmax2[0], minmax2[1]);
			if (overlap == 0) return CollisionData();
			if (overlap < depth)
			{
				depth = std::fmin(depth, overlap);
				result.a = a->GetEntity();
				result.b = b->GetEntity();
				result.depth = depth;
				result.normal = glm::normalize(sb->GetCenter() - sa->GetCenter());
				result.position = sa->GetCenter();
			}
		}
	}
	return result;
}

// check all points of the box against the normal of the plane
// if a point is behind the plane box collides to the plane
// otherwise they are not
// the normal is the normal of the plane
CollisionData CollideBoxWithPlane(Shape* a, Shape* b)
{
	return CollisionData();
}

CollisionData CollideBoxRotatedWithCircle(Shape* a, Shape* b)
{
	return CollisionData();
}

CollisionData CollideBoxRotatedWithBox(Shape* a, Shape* b)
{
	return CollideBoxWithBoxRotated(b, a);
}


CollisionData CollideBoxRotatedWithBoxRotated(Shape* a, Shape* b)
{
	BoxRotated* sa = (BoxRotated*)a;
	BoxRotated* sb = (BoxRotated*)b;
	CollisionData result;

	std::vector<glm::vec2> shape1 = sa->GetPoints();
	std::vector<glm::vec2> shape2 = sb->GetPoints();

	float depth = FLT_MAX;
	bool overlapped = false;
	std::vector<std::vector<glm::vec2>> shapes = { shape1, shape2 };

	for (int i = 0; i < shapes.size(); i++)
	{
		for (int j = 0; j < shapes[i].size(); j++)
		{
			std::vector<glm::vec2> shape = shapes[i];
			glm::vec2 p1 = shape[j];
			glm::vec2 p2 = shape[(j + 1) % shape.size()];
			glm::vec2 v12 = p2 - p1;
			glm::vec2 normal = { -v12.y, v12.x };
			normal = glm::normalize(normal);
			std::vector<float> minmax1 = GetMinMaxProjection(shape1, normal);
			std::vector<float> minmax2 = GetMinMaxProjection(shape2, normal);
			float overlap = LineOverlap(minmax1[0], minmax1[1], minmax2[0], minmax2[1]);
			if (overlap == 0) return CollisionData();
			if (overlap < depth)
			{
				depth = std::fmin(depth, overlap);
				result.a = a->GetEntity();
				result.b = b->GetEntity();
				result.depth = depth;
				result.normal = glm::normalize(sb->GetCenter() - sa->GetCenter());
				result.position = sa->GetCenter();
			}
		}
	}
	return result;
}

CollisionData CollideBoxRotatedWithPlane(Shape* a, Shape* b)
{
	return CollisionData();
}

CollisionData CollidePlaneWithCircle(Shape* a, Shape* b)
{
	return CollideCircleWithPlane(b, a);
}

CollisionData CollidePlaneWithBox(Shape* a, Shape* b)
{
	return CollideBoxWithPlane(b, a);
}

CollisionData CollidePlaneWithBoxRotated(Shape* a, Shape* b)
{
	return CollisionData();
}

CollisionData CollidePlaneWithPlane(Shape* a, Shape* b)
{
	return CollisionData();
}

CollisionData CheckCollisionBetweenShapes(Shape* shapeA, Shape* shapeB)
{
	int typeA = (int)shapeA->GetType();
	int typeB = (int)shapeB->GetType();

	return COLLISION_FUNCTION_TABLE[typeA][typeB](shapeA, shapeB);
}
