
#include "Projectile.h"
#include "Level.h"

//Texture *Projectile::s_pTexture = nullptr;

Projectile::Projectile()
{
	SetDirection(-Vector2::UNIT_Y);
	SetCollisionRadius(9);
}

void Projectile::Update(const GameTime& gameTime)
{
	if (IsActive() && s_pTexture)
	{
		Vector2 translation = m_direction * m_speed * gameTime.GetElapsedTime();
		TranslatePosition(translation);

		Vector2 position = GetPosition();
		Vector2 size = s_pTexture->GetSize();

		if (position.Y < -size.Y) Deactivate();
		else if (position.X < -size.X) Deactivate();
		else if (position.Y > Game::GetScreenHeight() + size.Y) Deactivate();
		else if (position.X > Game::GetScreenWidth() + size.X) Deactivate();
	}

	GameObject::Update(gameTime);
}


void Projectile::Draw(SpriteBatch& spriteBatch)
{
	if (IsActive() && s_pTexture)
	{
		const float alpha = GetCurrentLevel()->GetAlpha();
		spriteBatch.Draw(s_pTexture, GetPosition(), Color::WHITE * alpha, s_pTexture->GetCenter());
	}
}


void Projectile::Activate(const Vector2 &position, bool wasShotByPlayer)
{
	m_wasShotByPlayer = wasShotByPlayer;
	SetPosition(position);

	GameObject::Activate();
}

//===============Added by @Emilien ===============

void Projectile::Activate(const Vector2& position, bool isFriendly, const Vector2& velocity)
{
	SetPosition(position);
	m_velocity = velocity;
	m_isFriendly = isFriendly;
	GameObject::Activate();
}
//===============End==============================


std::string Projectile::ToString() const
{
	return std::string((WasShotByPlayer()) ? "Player" : "Enemy").append(" Projectile");
}

CollisionType Projectile::GetCollisionType() const
{
	CollisionType shipType = WasShotByPlayer() ? CollisionType::Player : CollisionType::Enemy;
	return (shipType | GetProjectileType());
}