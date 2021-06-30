#include "PhysicalObject.h"
#include "PhysicsScene.h"

PhysicalObject::PhysicalObject()
{
	PhysicsScene::GetInstance()->Add(this);
}
