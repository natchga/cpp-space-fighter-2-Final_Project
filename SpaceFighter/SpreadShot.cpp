#include "SpreadShot.h"
#include "Level.h"
#include <cmath>

// initializes the weapon key, number of projectiles per shot, and spread angle
SpreadShot::SpreadShot(const std::string& key, int projectilesPerShot, float spreadAngle)
    : Weapon(key), m_projectilesPerShot(projectilesPerShot), m_spreadAngle(spreadAngle)
{
}

// Update method called every frame to reduce cooldown timer
void SpreadShot::Update(const GameTime& gameTime)
{
    if (m_cooldown > 0)
        m_cooldown -= gameTime.GetElapsedTime(); // decrement cooldown by elapsed time
}

// Check if weapon can fire (cooldown is finished)
bool SpreadShot::CanFire() const
{
    return m_cooldown <= 0;
}

// Reset cooldown after firing
void SpreadShot::ResetCooldown()
{
    m_cooldown = m_cooldownSeconds;
}

// Fire method called when trigger is pressed
void SpreadShot::Fire(TriggerType triggerType)
{
    // Only fire if correct trigger, weapon is active, and cooldown finished
    if (triggerType != GetTriggerType() || !CanFire() || !IsActive())
        return;

    Vector2 shipPos = GetPosition(); // Get current weapon position (usually the ship)

    // Calculate offsets dynamically based on m_spreadWidth
    std::vector<Vector2> offsets;
    if (m_projectilesPerShot > 1)
    {
        float spacing = m_spreadWidth / (m_projectilesPerShot - 1); // horizontal spacing between bullets
        float startX = -m_spreadWidth / 2.0f; // start offset from left
        for (int i = 0; i < m_projectilesPerShot; i++)
        {
            offsets.push_back(Vector2(startX + i * spacing, -10.0f)); // -10 is slightly in front of ship center
        }
    }
    else
    {
        offsets.push_back(Vector2(0, -10)); // single bullet in center if only 1 projectile
    }

    // Fire each projectile in the spread
    for (int i = 0; i < m_projectilesPerShot; i++)
    {
        Projectile* p = GetProjectile(); // get an inactive projectile from pool
        if (!p) continue; // skip if no projectile available

        // Calculate angular spread for each bullet
        float angleDeg = -m_spreadAngle / 2.0f + i * (m_spreadAngle / std::max(1, m_projectilesPerShot - 1));
        float angleRad = angleDeg * 3.14159265f / 180.0f; // convert degrees to radians

        Vector2 velocity(std::sin(angleRad), -std::cos(angleRad)); // calculate directional velocity
        velocity *= 600.0f; // multiply by bullet speed

        p->Activate(shipPos + offsets[i], true, velocity); // activate projectile at position with velocity
    }

    ResetCooldown(); // reset weapon cooldown

    // Play fire sound if available
    if (GetFireSound())
        GetFireSound()->Play();
}
