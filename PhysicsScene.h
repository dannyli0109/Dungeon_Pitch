#pragma once
#include "Matrices.h"
#include <vector>
#include "PhysicalObject.h"
#include "LineRenderer.h"
#include "Shape.h"
#include "Entity.h"
#include "CollisionFunctions.h"
#include "Shape.h"
#include <functional>
#include "Enemy.h"

class PhysicalObject;
class PhysicsScene
{
	friend PhysicalObject;
public:
	static PhysicsScene* CreateInstance();
	static PhysicsScene* GetInstance();
	void Update(float deltaTime);
	void Draw(LineRenderer* lineRenderer);
	void CheckForCollisions();
	void ClearCollision() { collisions.clear(); };
	void ResolveCollision(CollisionData collisionData);
	void Add(PhysicalObject* physicalObject);
	std::vector<CollisionData> GetCollisions() { return collisions; }
	std::vector<PhysicalObject*> physicalObjects;
private:
	PhysicsScene() {
		timeStep = 0.01f;
		gravity = { 0, 0 };
	};
	~PhysicsScene() {};
private:
	std::vector<CollisionData> collisions;
	static PhysicsScene* instance;
	float timeStep;
	glm::vec2 gravity;
};

