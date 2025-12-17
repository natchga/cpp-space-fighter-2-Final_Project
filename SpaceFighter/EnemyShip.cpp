
#include "EnemyShip.h"
#include "Score.h" 
#include "Level.h"

EnemyShip::EnemyShip()
{
	SetMaxHitPoints(1);
	SetCollisionRadius(20);
}


void EnemyShip::Update(const GameTime& gameTime) // updated code for enemy spawn
{
	if (m_delaySeconds > 0) // delayed timer for when enemies spawn
	{
		m_delaySeconds -= gameTime.GetElapsedTime();

		if (m_delaySeconds <= 0)
		{
			GameObject::Activate();

			// count this enemy as "spawned" one time  
			if (!m_countedAsSpawned)
			{
				m_countedAsSpawned = true;

				Level* pLevel = GetCurrentLevel(); // notify the level that the enemy has spawned.
				if (pLevel)
					pLevel->AddEnemySpawned();
			}
		}

	}

	if (IsActive()) // removes enemies that have "flown off" of the screen.
	{
		m_activationSeconds += gameTime.GetElapsedTime();
		if (m_activationSeconds > 2 && !IsOnScreen()) Deactivate(); // more than 2 secs off screen = deactivated.
	}

	Ship::Update(gameTime);
}


void EnemyShip::Initialize(const Vector2 position, const double delaySeconds)
{
	SetPosition(position);
	m_delaySeconds = delaySeconds;

	Ship::Initialize();
}


void EnemyShip::Hit(const float damage)
{
	const float hpBefore = GetHitPoints();
	Ship::Hit(damage);

	const float hpAfter = GetHitPoints();
	if (hpBefore > 0 && hpAfter <= 0)
	{
		ScoreSystem::AddEnemyDestroyed();
	}
}