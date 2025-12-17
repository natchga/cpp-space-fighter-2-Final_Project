
#include "Level01.h"
#include "BioEnemyShip.h"
#include "EnemyShipMedium.h"



Level01::Level01(AircraftType type) : Level(type) {}

void Level01::LoadContent(ResourceManager& resourceManager)
{

	// Setup enemy ships
	Texture* pTexture = resourceManager.Load<Texture>("Textures\\BioEnemyShip.png");

	const int COUNT = 21;

	double xPositions[COUNT] =
	{
		0.25, 0.2, 0.3,
		0.75, 0.8, 0.7,
		0.3, 0.25, 0.35, 0.2, 0.4,
		0.7, 0.75, 0.65, 0.8, 0.6,
		0.5, 0.4, 0.6, 0.45, 0.55
	};

	double delays[COUNT] =
	{
		0.0, 0.25, 0.25,
		3.0, 0.25, 0.25,
		3.25, 0.25, 0.25, 0.25, 0.25,
		3.25, 0.25, 0.25, 0.25, 0.25,
		3.5, 0.3, 0.3, 0.3, 0.3
	};

	float delay = 3.0; // start delay
	Vector2 position;

	for (int i = 0; i < COUNT; i++)
	{
		delay += delays[i];
		position.Set(xPositions[i] * Game::GetScreenWidth(), -pTexture->GetCenter().Y);

		BioEnemyShip* pEnemy = new BioEnemyShip();
		pEnemy->SetTexture(pTexture);
		pEnemy->SetCurrentLevel(this);
		pEnemy->Initialize(position, (float)delay);
		AddGameObject(pEnemy);

	}

	// medium enemy new code
	Texture* pMediumTex =
		resourceManager.Load<Texture>("Textures\\EnemyShipMedium.png");

	for (int i = 0; i < 4; i++)
	{
		Vector2 pos(
			(0.3f + i * 0.1f) * Game::GetScreenWidth(),
			-pMediumTex->GetCenter().Y
		);

		EnemyShipMedium* pMedium = new EnemyShipMedium();
		pMedium->SetTexture(pMediumTex);
		pMedium->SetCurrentLevel(this);
		pMedium->Initialize(pos, 8.0f + i); // this spawns the medium enemys late in the level
		AddGameObject(pMedium);
	}

	// Setup background
	SetBackground(resourceManager.Load<Texture>("Textures\\SpaceBackground01.png"));

	Level::LoadContent(resourceManager);
}

