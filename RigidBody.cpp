#include "RigidBody.h"

RigidBody::RigidBody(glm::vec2 velocity, glm::vec2 acceleration, float mass, bool isStatic)
{
	this->velocity = velocity;
	this->acceleration = acceleration;
	this->mass = mass;
	this->isStatic = isStatic;
}

void RigidBody::FixedUpdate(glm::vec2 gravity, float timeStep)
{
	if (isStatic) return;
	ApplyForce(gravity * mass);
	velocity += acceleration * timeStep;
	entity->transform->Translate(glm::vec3(velocity, 0.0f) * timeStep);
	acceleration = { 0, 0 };
	init = true;
}

void RigidBody::DrawShape(LineRenderer* lineRenderer)
{
	Shape* shape = entity->GetComponent<Shape>();
	if (shape && init)
	{
		shape->DrawShape(lineRenderer);
	}
}

void RigidBody::ApplyForce(glm::vec2 force)
{
	acceleration += force / mass;
}

void RigidBody::ApplyForceToRigidBody(RigidBody* other, glm::vec2 force)
{
	other->ApplyForce(force);
	ApplyForce(-force);
}
