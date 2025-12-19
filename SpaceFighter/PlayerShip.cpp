#include "PlayerShip.h"
#include "SingleShot.h"
#include "SpreadShot.h"

Texture* Projectile::s_pTexture = nullptr;

// User Stored selection
PlayerShip::PlayerShip(AircraftType type, std::vector<Projectile*>* pProjectilePool)
	: m_type(type)
	, m_pProjectilePool(pProjectilePool)
{
	// Assign default weapon based on type
	switch (m_type)
	{
	case AircraftType::DefaultFighter:
	case AircraftType::LightFighter:
	{
		Weapon* pWeapon = new SingleShot("Main Blaster");
		pWeapon->SetProjectilePool(m_pProjectilePool);
		AttachItem(pWeapon, Vector2(0, -20));
		break;
	}
	case AircraftType::HeavyBomber:
	{
		Weapon* pWeapon = new SpreadShot("Spread Shot", 5, 45.0f);
		pWeapon->SetProjectilePool(m_pProjectilePool);
		AttachItem(pWeapon, Vector2(0, -25));
		break;
	}
	}
}



void PlayerShip::LoadContent(ResourceManager& resourceManager)
{
	ConfineToScreen();
	SetResponsiveness(0.1f);

	m_pStealthFont = resourceManager.Load<Font>("Fonts\\Arialbd.ttf", false);  // Load a font for stealth countdown

	// Load ship texture
	switch (m_type)
	{
	case AircraftType::LightFighter:
		m_pTexture = resourceManager.Load<Texture>("Textures\\LightFighterShip.png");
		m_maxStealthDuration = 15.0f; // Short duration
		SetSpeed(300);
		break;

	case AircraftType::HeavyBomber:
		m_pTexture = resourceManager.Load<Texture>("Textures\\HeavyBomberShip.png");
		m_maxStealthDuration = 20.0f; // Longer duration
		SetSpeed(100);
		break;

	case AircraftType::DefaultFighter:
	default:
		m_pTexture = resourceManager.Load<Texture>("Textures\\PlayerShip.png");
		m_maxStealthDuration = 10.0f; // Longer duration
		SetSpeed(250);
		break;
	}

	// Assign bullet textures and sounds to all weapons
	for (auto& pair : m_attachments)
	{
		IAttachment* attachment = pair.second;
		if (attachment->GetAttachmentType() != "Weapon") continue;

		Weapon* weapon = static_cast<Weapon*>(attachment);
		Texture* bulletTexture = nullptr;

		// Keep your original paths
		if (weapon->GetKey() == "Main Blaster")
			bulletTexture = resourceManager.Load<Texture>("Textures\\Weapons\\SingleShot.png");
		else if (weapon->GetKey() == "Spread Shot")
			bulletTexture = resourceManager.Load<Texture>("Textures\\Weapons\\SpreadShot.png");
		else bulletTexture = resourceManager.Load<Texture>("Textures\\Bullet.png");

		// Assign texture to all projectiles in the pool
		for (Projectile* pProj : *m_pProjectilePool)
			pProj->SetTexture(bulletTexture);

		weapon->SetProjectileTexture(bulletTexture);

		// Assign fire sound
		AudioSample* pAudio = resourceManager.Load<AudioSample>("Audio\\Effects\\Laser.wav");
		pAudio->SetVolume(0.5f);
		weapon->SetFireSound(pAudio);
	}

	m_pStealthSound = resourceManager.Load<AudioSample>(
		"Audio\\Effects\\stealthMode.MP3"
	);
	m_pStealthSound->SetVolume(0.6f);


	// Set starting position
	SetPosition(Game::GetScreenCenter() + Vector2::UNIT_Y * 300);
}




void PlayerShip::Initialize(Level* pLevel, Vector2& startPosition)
{
	SetPosition(startPosition);
}

void PlayerShip::HandleInput(const InputState& input)
{

	if (IsActive())
	{
		Vector2 direction;
		if (input.IsKeyDown(Key::DOWN)) direction.Y++;
		if (input.IsKeyDown(Key::UP)) direction.Y--;
		if (input.IsKeyDown(Key::Right)) direction.X++;
		if (input.IsKeyDown(Key::Left)) direction.X--;

		// Normalize the direction
		if (direction.X != 0 && direction.Y != 0)
		{
			direction *= Math::NORMALIZE_PI_OVER4;
		}

		TriggerType type = TriggerType::None;
		if (input.IsKeyDown(Key::SPACE)) type |= TriggerType::Primary;
		//if (input.IsKeyDown(Key::D)) type |= TriggerType::Secondary;
		//if (input.IsKeyDown(Key::S)) type |= TriggerType::Special;

		//// Handle Xbox Controller
		//GamePadState* pState = input.GetGamePadState(0);
		//if (pState->IsConnected)
		//{
		//	// gamepad overrides keyboard input
		//	Vector2 thumbstick = pState->Thumbsticks.Left;
		//	if (thumbstick.LengthSquared() < 0.08f) thumbstick = Vector2::ZERO;
		//	direction = thumbstick;

		//	type = TriggerType::None;
		//	if (pState->Triggers.Right > 0.5f) type |= TriggerType::Primary;
		//	if (pState->Triggers.Left > 0.5f) type |= TriggerType::Secondary;
		//	if (pState->IsButtonDown(Button::Y)) type |= TriggerType::Special;
		//}


		SetDesiredDirection(direction);
		if (type != TriggerType::None) FireWeapons(type);
	}

	//Check Input for Stealth Activation @By Emilien
	// --- Stealth input only ---
	if (input.IsKeyDown(Key::S) && !m_isStealthActive && m_killsSinceLastStealth >= m_killsToActivateStealth)
	{
		ActivateStealth();
		m_killsSinceLastStealth = 0;
	}
	else
	{
		std::cout << "Not enough killed ("
			<< m_killsSinceLastStealth << "/"
			<< m_killsToActivateStealth << ")\n";
	}


}



void PlayerShip::Update(const GameTime& gameTime)
{

	float deltaTime = gameTime.GetElapsedTime(); //------@Emilien


	// Get the velocity for the direction that the player is trying to go.
	Vector2 targetVelocity = m_desiredDirection * GetSpeed() * gameTime.GetElapsedTime();
	// We can't go from 0-100 mph instantly! This line interpolates the velocity for us.
	m_velocity = Vector2::Lerp(m_velocity, targetVelocity, GetResponsiveness());
	// Move that direction
	TranslatePosition(m_velocity);

	if (m_isConfinedToScreen)
	{
		const int PADDING = 4; // keep the ship 4 pixels from the edge of the screen
		const int TOP = PADDING;
		const int Left = PADDING;
		const int Right = Game::GetScreenWidth() - PADDING;
		const int BOTTOM = Game::GetScreenHeight() - PADDING;

		Vector2* pPosition = &GetPosition(); // current position (middle of the ship)
		if (pPosition->X - GetHalfDimensions().X < Left) // are we past the left edge?
		{
			// move the ship to the left edge of the screen (keep Y the same)
			SetPosition(Left + GetHalfDimensions().X, pPosition->Y);
			m_velocity.X = 0; // remove any velocity that could potentially
			// keep the ship pinned against the edge
		}
		if (pPosition->X + GetHalfDimensions().X > Right) // right edge?
		{
			SetPosition(Right - GetHalfDimensions().X, pPosition->Y);
			m_velocity.X = 0;
		}
		if (pPosition->Y - GetHalfDimensions().Y < TOP) // top edge?
		{
			SetPosition(pPosition->X, TOP + GetHalfDimensions().Y);
			m_velocity.Y = 0;
		}
		if (pPosition->Y + GetHalfDimensions().Y > BOTTOM) // bottom edge?
		{
			SetPosition(pPosition->X, BOTTOM - GetHalfDimensions().Y);
			m_velocity.Y = 0;
		}
	}

	Ship::Update(gameTime);

	UpdateStealth(deltaTime);//------@Emilien:  Update stealth 

}

//==================Added by @Emilien========================

void PlayerShip::Draw(SpriteBatch& spriteBatch)
{
	if (!IsActive())
		return;

	float alpha = m_isStealthActive ? 0.5f : 1.0f;

	if (m_pTexture)
	{
		spriteBatch.Draw(
			m_pTexture,
			GetPosition(),
			Color::WHITE * alpha,
			m_pTexture->GetCenter()
		);
	}
	if (m_isStealthActive && m_pStealthFont)
	{
		int secondsLeft = static_cast<int>(std::ceil(m_stealthDuration));
		m_stealthCountdownText = "Stealth Mode: " + std::to_string(secondsLeft) + "s"; //Countdown display

		spriteBatch.DrawString(
			m_pStealthFont,
			&m_stealthCountdownText,  // persistent string pointer
			GetPosition() - Vector2(0, m_pTexture ? m_pTexture->GetHeight() / 2 + 20 : 20),
			Color::YELLOW
		);
	}

}



Vector2 PlayerShip::GetHalfDimensions() const
{
	return m_pTexture->GetCenter();
}

void PlayerShip::SetResponsiveness(const float responsiveness)
{
	m_responsiveness = Math::Clamp(0, 1, responsiveness);
}


/*Activate  and Activate the Stealth*/
void PlayerShip::ActivateStealth()
{
	if (m_isStealthActive) return;

	m_isStealthActive = true;
	m_stealthDuration = m_maxStealthDuration;

	if (m_pStealthSound)
		m_pStealthSound->Play();
}

/*Activate  and Deactivate the Stealth*/
void PlayerShip::DeactivateStealth()
{
	m_isStealthActive = false;

}

//countdown of the stealth mode
void PlayerShip::UpdateStealth(float deltaTime)
{
	if (m_isStealthActive)
	{
		m_stealthDuration -= deltaTime;
		if (m_stealthDuration <= 0.0f)
			DeactivateStealth();

	}
}


void PlayerShip::IncrementKillCount()
{
	// Only increment count of enemies killed if stealth is NOT active
    if (!m_isStealthActive)  
    {
        m_killsSinceLastStealth++;

        std::cout << "Kills for stealth: "
                  << m_killsSinceLastStealth << "/"
                  << m_killsToActivateStealth << std::endl;
	}
}

// This return the ratio of how close the player is to being able to activate stealth
float PlayerShip::GetStealthUnlockRatio() const
{
	if (m_killsToActivateStealth == 0) return 0.0f; // Avoid division by zero
	// Return the ratio of kills
	return static_cast<float>(m_killsSinceLastStealth) / m_killsToActivateStealth;
}



void PlayerShip::CheckEnemyCollisions()
{
	// skip collisions if stealth is active
	if (m_isStealthActive)
		return;
}







