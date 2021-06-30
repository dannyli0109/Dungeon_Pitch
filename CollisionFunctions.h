#pragma once
#include "CollisionData.h"
#include <functional>
#include "Shape.h"
#include "Graphics.h"
#include "RigidBody.h"

#include "Circle.h"
#include "Box.h"
#include "BoxRotated.h"
#include "Transform.h"

typedef std::function<CollisionData(Shape*, Shape*)> CollisionFunction;

CollisionData CollideCircleWithCircle(Shape* a, Shape* b);
CollisionData CollideCircleWithBox(Shape* a, Shape* b);
CollisionData CollideCircleWithBoxRotated(Shape* a, Shape* b);
CollisionData CollideCircleWithPlane(Shape* a, Shape* b);

CollisionData CollideBoxWithCircle(Shape* a, Shape* b);
CollisionData CollideBoxWithBox(Shape* a, Shape* b);
CollisionData CollideBoxWithBoxRotated(Shape* a, Shape* b);
CollisionData CollideBoxWithPlane(Shape* a, Shape* b);

CollisionData CollideBoxRotatedWithCircle(Shape* a, Shape* b);
CollisionData CollideBoxRotatedWithBox(Shape* a, Shape* b);
CollisionData CollideBoxRotatedWithBoxRotated(Shape* a, Shape* b);
CollisionData CollideBoxRotatedWithPlane(Shape* a, Shape* b);

CollisionData CollidePlaneWithCircle(Shape* a, Shape* b);
CollisionData CollidePlaneWithBox(Shape* a, Shape* b);
CollisionData CollidePlaneWithBoxRotated(Shape* a, Shape* b);
CollisionData CollidePlaneWithPlane(Shape* a, Shape* b);

static const CollisionFunction COLLISION_FUNCTION_TABLE[(int)ShapeType::Count][(int)ShapeType::Count] = {
	{CollideCircleWithCircle, CollideCircleWithBox, CollideCircleWithBoxRotated, CollideCircleWithPlane},
	{CollideBoxWithCircle, CollideBoxWithBox, CollideBoxWithBoxRotated, CollideBoxWithPlane},
	{CollideBoxRotatedWithCircle, CollideBoxRotatedWithBox, CollideBoxRotatedWithBoxRotated, CollideBoxRotatedWithPlane},
	{CollidePlaneWithCircle, CollidePlaneWithBox, CollidePlaneWithBoxRotated, CollidePlaneWithPlane},
};

CollisionData CheckCollisionBetweenShapes(Shape* shapeA, Shape* shapeB);