
#pragma once

#include "Ship.h"

/** @brief Represents an enemy ship. */
class EnemyShip : public Ship
{

public:

	/** @brief Creates a new instance of EnemyShip. */
	EnemyShip();
	virtual ~EnemyShip() { }

	/** @brief Loads the content for the enemy ship.
		@param resourceManager A reference to the game's resource manager,
		used for loading and managing game assets (resources). */
	virtual void Update(const GameTime& gameTime);


	/** @brief Draws the enemy ship.
		@param spriteBatch A reference to the game's sprite batch, used for rendering. */
	virtual void Draw(SpriteBatch& spriteBatch) = 0;

	/** @brief Initializes the enemy ship.
		@param position The starting position of the enemy ship.
		@param delaySeconds The delay before the enemy ship activates. */
	virtual void Initialize(const Vector2 position, double delaySeconds);

	/** @brief Fires a weapon from the enemy ship. */
	virtual void Fire() { }

	/** @brief Applies damage to the ship.
		@param damage The amount of damage to apply. */
	virtual void Hit(float damage);

	/** @brief Gets the string representation of the enemy ship.
		@return Returns the string "Enemy Ship". */
	virtual std::string ToString() const { return "Enemy Ship"; }

	/** @brief Gets the collision type of the enemy ship.
		@return Returns the collision type of the enemy ship. */
	virtual CollisionType GetCollisionType() const { return CollisionType::Enemy | CollisionType::Ship; }

	void SetDelaySeconds(float delay) { m_delaySeconds = delay; }
	float GetDelaySeconds() const { return m_delaySeconds; }


protected: // moved everything to protected -- paul

	double m_delaySeconds = 0.0;
	double m_activationSeconds = 0.0;
	bool m_countedAsSpawned = false;
};
