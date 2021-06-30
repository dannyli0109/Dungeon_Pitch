#include "Bullet.h"

Bullet::Bullet(AmmoStats stat) : Ammo(AmmoType::Bullet, stat)
{

}

void Bullet::Update(float deltaTime)
{
}

void Bullet::OnImpact(Agent* agent)
{
	if (agent)
	{
		agent->TakeDamage(damage);
		//agent->GetEntity()->GetComponent<E
	}
}
