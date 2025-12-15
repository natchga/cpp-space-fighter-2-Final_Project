#pragma once
#include "Weapon.h"
#include "GameTime.h"
#include "Projectile.h"

class SingleShot : public Weapon
{
public:
    SingleShot(const std::string& key);
    virtual ~SingleShot() {}

    virtual void Update(const GameTime& gameTime) override;
    virtual void Fire(TriggerType triggerType) override;

private:
    bool CanFire() const;
    void ResetCooldown();

    float m_cooldown = 0;
    float m_cooldownSeconds = 0.5f;
};
