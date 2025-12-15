#include "Weapon.h"
#include "Projectile.h"
#include "GameObject.h"

//Weapon::Weapon(const std::string& key, bool isAttachedToPlayer, bool isActive, TriggerType triggerType)
//	: m_key(key),
//	m_isAttachedToPlayer(isAttachedToPlayer),
//	m_isActive(isActive),
//	m_triggerType(triggerType)
//{
//}

void Weapon::SetProjectilePool(std::vector<Projectile*>* pProjectiles)
{
	m_pProjectiles = pProjectiles;
}

void Weapon::SetTriggerType(TriggerType triggerType)
{
	m_triggerType = triggerType;
}

bool Weapon::IsActive() const
{
	return m_isActive && m_pGameObject && m_pGameObject->IsActive();
}

void Weapon::AttachTo(IAttachable* pAttachable, Vector2& position)
{
	m_pGameObject = dynamic_cast<GameObject*>(pAttachable);
	m_offset = position;
}

Vector2 Weapon::GetPosition() const
{
	return m_pGameObject->GetPosition() + m_offset;
}

Projectile* Weapon::GetProjectile()
{
	if (!m_pProjectiles) return nullptr;

	for (Projectile* p : *m_pProjectiles)
	{
		if (!p->IsActive())
			return p;
	}
	return nullptr;
}
