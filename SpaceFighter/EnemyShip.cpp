#include "EnemyShip.h"
#include "Score.h"
#include "Level.h"

EnemyShip::EnemyShip()
{
    SetMaxHitPoints(1);
    SetCollisionRadius(20);
}

void EnemyShip::Update(const GameTime& gameTime)
{
    if (m_delaySeconds > 0)
    {
        m_delaySeconds -= gameTime.GetElapsedTime();
        if (m_delaySeconds <= 0)
        {
            GameObject::Activate();
            if (!m_countedAsSpawned)
            {
                m_countedAsSpawned = true;
                if (Level* pLevel = GetCurrentLevel())
                    pLevel->AddEnemySpawned();
            }
        }
        return; 
    }

    if (IsActive())
    {
        m_activationSeconds += gameTime.GetElapsedTime();
        if (m_activationSeconds > 2 && !IsOnScreen())
            Deactivate();
    }

    Ship::Update(gameTime);
}

void EnemyShip::Initialize(const Vector2 position, double delaySeconds)
{
    m_delaySeconds = delaySeconds;

    Ship::Initialize();

    SetPosition(position);
}

void EnemyShip::Hit(float damage)
{
    const float hpBefore = GetHitPoints();
    Ship::Hit(damage);
    const float hpAfter = GetHitPoints();

    if (hpBefore > 0 && hpAfter <= 0)
    {
        ScoreSystem::AddEnemyDestroyed();
    }
}
