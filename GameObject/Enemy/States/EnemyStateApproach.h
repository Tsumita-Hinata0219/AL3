#pragma once
#include "EnemyStates.h"


/// <summary>
/// EnemyStateApproach : 接近フェーズ
/// </summary>
class EnemyStateApproach : public EnemyStates {

public:
	void Update(Enemy* pEnemy) override;
};

