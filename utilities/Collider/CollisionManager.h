#pragma once
#include <list>
#include "Function.h"
#include "Collider.h"



class CollisionManager {

public:

	/// <summary>
	/// 衝突判定と応答
	/// </summary>
	void CheckAllCollision();


	/// <summary>
	/// コライダーを受け取り、リストに登録する
	/// </summary>
	void ColliderPushBack(Collider* collider);


	/// <summary>
	/// コライダーリストをクリアにする関数
	/// </summary>
	void ColliderClear();


private:

	/// <summary>
	/// コライダー2つの衝突判定と応答
	/// </summary>
	void CheckCollisionPair(Collider* colliderA, Collider* colliderB);


private:

	// コライダーリスト
	std::list<Collider*> colliders_;

};

