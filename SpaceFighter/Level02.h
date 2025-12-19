#pragma once
#include "Level.h"

/** @brief The second level of the game. */
class Level02 : public Level
{
public:
    Level02(AircraftType type);

    virtual void LoadContent(ResourceManager& resourceManager) override;
    virtual void Update(const GameTime& gameTime) override;
    virtual bool IsComplete() const override;

protected:
    bool m_bossAlive = true;
    bool m_hasHadActiveEnemy = false;

private:
    void CheckEnemies(); // helper to check for active enemies & boss
};
