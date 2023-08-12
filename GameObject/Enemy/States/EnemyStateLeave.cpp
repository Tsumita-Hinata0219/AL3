#include "EnemystateLeave.h"
#include "Enemy.h"


void EnemyStateLeave::Update(Enemy* pEnemy, const Vector3& velocity) {

	// 座標を移動させる(1フレーム分の移動量を足しこむ)
	pEnemy->SubtructTransform(velocity);


	// 規定の位置に到達したらstate_変更
	if (pEnemy->GetWorldPosition().z > 30.0f) {

		// Leave -> Approach
		pEnemy->ChangeState(new EnemyStateApproach());
	}
}

