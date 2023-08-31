#include "EnemyStateApproach.h"
#include "Enemy.h"


void EnemyStateApproach::Update(Enemy* pEnemy) {

	// 座標を移動させる(1フレーム分の移動量を足しこむ)
	pEnemy->SubtructTransform(pEnemy->GetVelocity());

	// 攻撃
	pEnemy->Attack();


	// 規定の位置に到達したらstate_変更
	if (pEnemy->GetWorldPosition().z < 30) {

		// Approach -> Leave
		pEnemy->ChangeState(new EnemyStateLeave());
	}
}

