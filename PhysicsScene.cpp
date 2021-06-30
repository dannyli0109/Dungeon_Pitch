#include "PhysicsScene.h"

PhysicsScene* PhysicsScene::CreateInstance()
{
	if (!instance)
	{
		instance = new PhysicsScene();
	}
	return instance;
}

PhysicsScene* PhysicsScene::GetInstance()
{
    return instance;
}

void PhysicsScene::Update(float deltaTime)
{
	static float accumulatedTime = 0.0f;
	accumulatedTime += deltaTime;
	ClearCollision();

	while (accumulatedTime >= timeStep)
	{
		for (PhysicalObject* physicalObject : physicalObjects)
		{
			physicalObject->FixedUpdate(gravity, timeStep);
		}
		accumulatedTime -= timeStep;
	}
}

void PhysicsScene::Draw(LineRenderer* lineRenderer)
{
	for (PhysicalObject* physicalObject : physicalObjects)
	{
		physicalObject->DrawShape(lineRenderer);
	}
}

void PhysicsScene::CheckForCollisions()
{
	for (int i = 0; i < int(physicalObjects.size()) - 1; i++)
	{
		for (int j = i + 1; j < physicalObjects.size(); j++)
		{
			Shape* shapeI = physicalObjects[i]->GetEntity()->GetComponent<Shape>();
			Shape* shapeJ = physicalObjects[j]->GetEntity()->GetComponent<Shape>();

			if ((shapeI->mask & shapeJ->layer) == 0 || (shapeJ->mask & shapeI->layer) == 0) continue;
			CollisionData hitData = CheckCollisionBetweenShapes(shapeI, shapeJ);

			if (hitData.depth >= 0)
			{
				// PLAYER_BULLET_LAYER
				{
					Shape* currentShape = nullptr;
					Shape* otherShape = nullptr;
					if (shapeI->layer == PLAYER_BULLET_LAYER) {
						currentShape = shapeI;
						otherShape = shapeJ;
					}
					if (shapeJ->layer == PLAYER_BULLET_LAYER) {
						currentShape = shapeJ;
						otherShape = shapeI;
					}

					if (currentShape && currentShape->layer == PLAYER_BULLET_LAYER)
					{
						currentShape->GetEntity()->removing = true;
						Agent* enemy = otherShape->GetEntity()->GetComponent<Agent>();
						Ammo* bullet = currentShape->GetEntity()->GetComponent<Ammo>();
						bullet->OnImpact(enemy);
					}
				}

				{
					Shape* currentShape = nullptr;
					Shape* otherShape = nullptr;
					if (shapeI->layer == PLAYER_DETECT_WALL_H_LAYER) {
						currentShape = shapeI;
						otherShape = shapeJ;
					}
					if (shapeJ->layer == PLAYER_DETECT_WALL_H_LAYER) {
						currentShape = shapeJ;
						otherShape = shapeI;
						//hitData.normal = -hitData.normal;
					}

					if (currentShape && currentShape->layer == PLAYER_DETECT_WALL_H_LAYER)
					{
						if (otherShape && otherShape->layer == WALL_LAYER)
						{
							/*currentShape->GetEntity()->removing = true;
							currentShape->GetEntity()->transform->Translate(glm::vec3(hitData.normal, 0));*/
							//ResolveCollision(hitData);
							RigidBody* rb = currentShape->GetEntity()->GetParent()->GetComponent<RigidBody>();
							rb->SetVelocity({ 0, rb->velocity.y });
						}
					}
				}

				{
					Shape* currentShape = nullptr;
					Shape* otherShape = nullptr;
					if (shapeI->layer == PLAYER_DETECT_WALL_V_LAYER) {
						currentShape = shapeI;
						otherShape = shapeJ;
					}
					if (shapeJ->layer == PLAYER_DETECT_WALL_V_LAYER) {
						currentShape = shapeJ;
						otherShape = shapeI;
						//hitData.normal = -hitData.normal;
					}

					if (currentShape && currentShape->layer == PLAYER_DETECT_WALL_V_LAYER)
					{
						if (otherShape && otherShape->layer == WALL_LAYER)
						{
							/*currentShape->GetEntity()->removing = true;
							currentShape->GetEntity()->transform->Translate(glm::vec3(hitData.normal, 0));*/
							//ResolveCollision(hitData);
							RigidBody* rb = currentShape->GetEntity()->GetParent()->GetComponent<RigidBody>();
							rb->SetVelocity({ rb->velocity.x, 0 });
						}
					}
				}

				// ENEMY_BULLET_LAYER
				{
					Shape* currentShape = nullptr;
					Shape* otherShape = nullptr;
					if (shapeI->layer == ENEMY_BULLET_LAYER) {
						currentShape = shapeI;
						otherShape = shapeJ;
					}
					if (shapeJ->layer == ENEMY_BULLET_LAYER) {
						currentShape = shapeJ;
						otherShape = shapeI;
					}

					if (currentShape && currentShape->layer == ENEMY_BULLET_LAYER)
					{
						currentShape->GetEntity()->removing = true;
						Agent* player = otherShape->GetEntity()->GetComponent<Agent>();
						Ammo* bullet = currentShape->GetEntity()->GetComponent<Ammo>();

						bullet->OnImpact(player);
					}
				}

			}
		}
	}
}

void PhysicsScene::Add(PhysicalObject* physicalObject)
{
	physicalObjects.push_back(physicalObject);
}

void PhysicsScene::ResolveCollision(CollisionData collisionData)
{
	RigidBody* rbA = collisionData.a->GetComponent<RigidBody>();
	RigidBody* rbB = collisionData.b->GetComponent<RigidBody>();

	// friended this method for rigidbody class so that this function have access to private varibales for rigid body

	glm::vec2 vA = rbA->velocity;
	glm::vec2 vB = rbB->velocity;
	glm::vec2 vRel = vA - vB;
	glm::vec2 n = collisionData.normal;

	// avoid two objects getting stuck
	if (glm::dot(vRel, n) > 0)
	{
		float e = 1;
		float mA = rbA->mass;
		float mB = rbB->mass;

		float jNumerator = glm::dot(-(1 + e) * vRel, n);
		float jDenumerator = glm::dot(n, n) * (1 / mA + 1 / mB);

		float impulseMagnitude = jNumerator / jDenumerator;

		glm::vec2 impulse = n * impulseMagnitude;

		rbA->ApplyForceToRigidBody(rbB, -impulse / timeStep);
	}
}

PhysicsScene* PhysicsScene::instance = nullptr;
