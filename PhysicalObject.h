#pragma once
#include "Component.h"
#include "LineRenderer.h"


class PhysicalObject :
    public Component
{

protected:
	PhysicalObject();
public:
	virtual void FixedUpdate(glm::vec2 gravity, float timeStep) = 0;
	virtual void DrawShape(LineRenderer* lineRenderer) = 0;
	bool init = false;
};

