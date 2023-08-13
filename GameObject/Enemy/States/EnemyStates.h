#pragma once

// Enemyの前方宣言
class Enemy;


class EnemyStates {

public:



	// 純粋仮想関数　※派生クラスに実装を強制する
	virtual void Update(Enemy* pEnemy) = 0;
};
