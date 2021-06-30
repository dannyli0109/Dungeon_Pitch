#pragma once
#include "PhysicalObject.h"
#include "SpriteRenderer.h"
#include "Transform.h"
#include "Shape.h"

class RigidBody :
    public PhysicalObject
{
public:
	RigidBody(glm::vec2 velocity, glm::vec2 acceleration, float mass, bool isStatic = false);
	RigidBody() = default;

	virtual void FixedUpdate(glm::vec2 gravity, float timeStep) override;
	virtual void DrawShape(LineRenderer* lineRenderer) override;
	virtual void Update(float deltaTime) override {};
	virtual void Draw(SpriteRenderer* spriteRenderer) override {}

	void ApplyForce(glm::vec2 force);
	void ApplyForceToRigidBody(RigidBody* other, glm::vec2 force);
	void SetVelocity(glm::vec2 velocity) { this->velocity = velocity; }
	glm::vec2 velocity = { 0, 0 };
	float mass = 1.0f;

protected:
	glm::vec2 acceleration = { 0, 0 };
	bool isStatic;
};

