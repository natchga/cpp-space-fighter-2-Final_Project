#include "SingleShot.h"
#include "Level.h"
#include "Projectile.h"


SingleShot::SingleShot(const std::string& key)
    : Weapon(key)
{
}

void SingleShot::Update(const GameTime& gameTime)
{
    if (m_cooldown > 0)
        m_cooldown -= gameTime.GetElapsedTime();
}

void SingleShot::Fire(TriggerType triggerType)
{
    if (triggerType != GetTriggerType() || !CanFire() || !IsActive())
        return;

    Projectile* p = GetProjectile(); //  Weapon pool
    if (!p)
        return;

    Vector2 velocity(0, -1);
    velocity *= 600.0f;

    p->Activate(GetPosition(), true, velocity);


    ResetCooldown();

    if (GetFireSound())
        GetFireSound()->Play();
}

bool SingleShot::CanFire() const
{
    return m_cooldown <= 0;
}

void SingleShot::ResetCooldown()
{
    m_cooldown = m_cooldownSeconds;
}
