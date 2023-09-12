#include "CollisionManager.h"



/// <summary>
/// 衝突判定と応答
/// </summary>
void CollisionManager::CheckAllCollision() {

	// リスト内のペアを総当たり
	std::list<Collider*>::iterator itrA = colliders_.begin();
	for (; itrA != colliders_.end(); ++itrA) {

		// イテレータAからコライダーAを取得する
		Collider* colliderA = *itrA;

		// イテレータBはイテレータAの次の要素から回す(重複判定を回避)
		std::list<Collider*>::iterator itrB = itrA;
		itrB++;

		for (; itrB != colliders_.end(); ++itrB) {

			// イテレータBからコライダーBを取得する
			Collider* colliderB = *itrB;

			// ペアの当たり判定
			CheckCollisionPair(colliderA, colliderB);
		}
	}
}



/// <summary>
/// コライダー2つの衝突判定と応答
/// </summary>
void CollisionManager::CheckCollisionPair(Collider* colliderA, Collider* colliderB) {

	// 2つのオブジェクトの座標を取得
	Vector3 posA = colliderA->GetWorldPosition();
	Vector3 posB = colliderB->GetWorldPosition();

	// 2つのオブジェクト間の距離を求める
	float distAtoB = CalcDistance(posA, posB);

	float radiusAandB = (colliderA->GetRadius() + colliderB->GetRadius());

	// 衝突フィルタリング
	if ((colliderA->GetCollisionAttribute() & colliderB->GetCollisionMask()) == 0 ||
	    (colliderB->GetCollisionAttribute() & colliderA->GetCollisionMask()) == 0) {

		// 像区政判定の時点で当たらないペアの場合は早期リターン
		return;
	}

	// 球と球の交差判定
	if (distAtoB <= (radiusAandB * radiusAandB)) {

		// コライダーAの衝突時コールバックを呼び出す
		colliderA->onCollision();
		// コライダーBの衝突時コールバックを呼び出す
		colliderB->onCollision();
	}
}



/// <summary>
/// コライダーを受け取り、リストに登録する
/// </summary>
void CollisionManager::ColliderPushBack(Collider* collider) {

	colliders_.push_back(collider);

}



/// <summary>
/// コライダーリストをクリアにする関数
/// </summary>
void CollisionManager::ColliderClear() { 

	colliders_.clear(); 
}


