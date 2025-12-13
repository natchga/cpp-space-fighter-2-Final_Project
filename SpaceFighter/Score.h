#include <iostream>
#pragma once

using namespace std;

class ScoreSystem
{
private: static int s_enemiesDestroyed;

public:
	static void Reset();
	static void AddEnemyDestroyed();
	static int GetEnemyDestroyed();
};
