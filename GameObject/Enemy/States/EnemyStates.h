#pragma once
#include "Enemy.h"
#include "WorldTransform.h"
#include "Function.h"

// Enemyの前方宣言
class Enemy;


class EnemyStates {

public:
	// 純粋仮想関数　※派生クラスに実装を強制する
	virtual void Update(Enemy* pEnemy) = 0;

protected:

	Enemy* pEnemy;

};

