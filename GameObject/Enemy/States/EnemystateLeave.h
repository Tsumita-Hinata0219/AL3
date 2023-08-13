#pragma once
#include "EnemyStates.h"


/// <summary>
/// EnemyStateLeave : 離脱フェーズ
/// </summary>
class EnemyStateLeave : public EnemyStates {

public:
	void Update(Enemy* pEnemy) override;

};

