#pragma once
#include "Weapon.h"
#include "Projectile.h"
#include <vector>
#include <string>

/** @brief Weapon that fires multiple projectiles in a spread pattern. */
class SpreadShot : public Weapon
{
public:
    //@param key Unique identifier for the weapon.
   //@param projectilesPerShot Number of projectiles per Shot.
   //@param spreadAngle Total angular spread in degrees.
    SpreadShot(const std::string& key, int projectilesPerShot = 5, float spreadAngle = 15.0f);

    virtual void Update(const GameTime& gameTime) override;
    virtual void Fire(TriggerType triggerType) override;

    //Optional: Set horizontal width of the firing points across the aircraft.
    void SetSpreadWidth(float width) { m_spreadWidth = width; }

private:
    bool CanFire() const;
    void ResetCooldown();
    int m_projectilesPerShot = 5;
    float m_spreadAngle = 45.0f;
    float m_cooldown = 0;
    float m_cooldownSeconds = 0.2f; // default cooldown between shots
    float m_spreadWidth = 80.0f;    // horizontal width for bullet offsets
};
