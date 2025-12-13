#pragma once
#include <iostream>
#include "Score.h"

using namespace std;

int ScoreSystem::s_enemiesDestroyed = 0;

void ScoreSystem::Reset()
{
	s_enemiesDestroyed = 0;
}

void ScoreSystem::AddEnemyDestroyed()
{
	s_enemiesDestroyed++;
	system("cls"); // Windows only
	cout << "Enemies Destroyed: " << s_enemiesDestroyed << '\n';

}

int ScoreSystem::GetEnemyDestroyed()
{
	return s_enemiesDestroyed;
}