#pragma once

#include "KatanaEngine.h"
#include "TriggerType.h"
#include <vector>
#include <string>
#include "Projectile.h"
using namespace KatanaEngine;

/* =========================
   Forward Declarations
   ========================= */
class Projectile;
class GameObject;

/** @brief Base class for all weapons that can be fired by a game object. */
class Weapon : public IAttachment
{
public:

	/** @brief Instantiate a weapon object.
		@param key A string to help lookup attached items.
		@param isAttachedToPlayer Flag to specify that the attachement belongs to the player.
		@param isActive A flag to determine if the weapon is active.
		@param triggerType Used to map buttons/keys for firing the weapon. */
	//Weapon(const std::string& key, bool isAttachedToPlayer = true, bool isActive = true,
	//	TriggerType triggerType = TriggerType::Primary);

	Weapon(const std::string& key, bool isAttachedToPlayer = true, bool isActive = true,
		TriggerType triggerType = TriggerType::Primary)
		: m_key(key), m_isAttachedToPlayer(isAttachedToPlayer), m_isActive(isActive),
		m_triggerType(triggerType) {
	}

	virtual ~Weapon() {}


	//Added by @Emilien

	void SetProjectileTexture(Texture* texture) { m_pProjectileTexture = texture; }
	Texture* GetProjectileTexture() const { return m_pProjectileTexture; }

	//End

	/** @brief Update the weapon.
		@param pGameTime Timing values including time since last update. */
	virtual void Update(const GameTime& gameTime) {};

	/** @brief Render the weapon.
		@param spriteBatch A reference to the game's sprite batch, used for rendering. */
	virtual void Draw(SpriteBatch& spriteBatch) {};

	/** @brief Attempt to fire the weapon. */
	virtual void Fire(TriggerType triggerType) = 0;

	/** @brief Set the type of trigger that can fire the weapon. */
	virtual void SetTriggerType(TriggerType triggerType);

	/** @brief Set the pool of projectiles that the weapon can fire. */
	virtual void SetProjectilePool(std::vector<Projectile*>* pProjectiles);

	/** @brief Activate the weapon. */
	virtual void Activate() { m_isActive = true; }

	/** @brief Deactivate the weapon. */
	virtual void Dectivate() { m_isActive = false; }

	/** @brief Determine if the weapon is active. */
	virtual bool IsActive() const;

	/** @brief Set the sound that will be played when the weapon is fired. */
	virtual void SetFireSound(AudioSample* pSound) { m_pFireSound = pSound; }

	/** @brief Get the sound that will be played when the weapon is fired. */
	virtual AudioSample* GetFireSound() { return m_pFireSound; }

	/** @brief Determine if the weapon is attached to the player. */
	virtual bool IsAttachedToPlayer() const { return m_isAttachedToPlayer; }

	/** @brief Attach the weapon to a game object. */
	virtual void AttachTo(IAttachable* pAttachable, Vector2& position);

	/** @brief Gets the key to retreive attachment. */
	virtual const std::string& GetKey() const override { return m_key; }

	/** @brief Gets the type of attachment. */
	virtual std::string GetAttachmentType() const override { return "Weapon"; }

protected:

	/** @brief Get the trigger type. */
	virtual TriggerType GetTriggerType() const { return m_triggerType; }

	/** @brief Get the screen position of the weapon. */
	virtual Vector2 GetPosition() const;

	/** @brief Get a projectile from the pool. */
	virtual Projectile* GetProjectile();

private:

	bool m_isActive = true;
	bool m_isAttachedToPlayer = true;

	std::string m_key;

	GameObject* m_pGameObject = nullptr;
	Vector2 m_offset;

	TriggerType m_triggerType = TriggerType::Primary;

	std::vector<Projectile*>* m_pProjectiles = nullptr;

	AudioSample* m_pFireSound = nullptr;
	Texture* m_pProjectileTexture = nullptr;
};
