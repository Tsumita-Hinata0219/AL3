#pragma once
#include "Function.h"



/// <summary>
/// 衝突判定オブジェクト
/// </summary>
class Collider {

public:

	/// <summary>
	/// 仮想関数
	/// 衝突時に呼ばれる関数　
	/// </summary>
	virtual void onCollision() = 0;


	/// <summary>
	/// 純粋仮想関数
	/// ワールド座標を取得
	/// </summary>
	virtual Vector3 GetWorldPosition() = 0;


	/// <summary>
	/// 半径を取得・設定
	/// </summary>
	float GetRadius() { return radisu_; }
	void SetRadius(float radius) { radisu_ = radius; }


	/// <summary>
	/// 衝突属性(自分)の取得・設定
	/// </summary>
	uint32_t GetCollisionAttribute() { return collisionAttribute_; }
	void SetCollisionAttribute(uint32_t collisionAttribute) { collisionAttribute_ = collisionAttribute; }


	/// <summary>
	/// 衝突属性(相手)の取得・設定
	/// </summary>
	uint32_t GetCollisionMask() { return collisionMask_; }
	void SetCollisionMask(uint32_t CollisionMask) { collisionMask_ = CollisionMask; }



private:

	// 衝突半径 デフォルト値
	float radisu_ = 1.0f; 

	// 衝突属性(自分)
	uint32_t collisionAttribute_ = 0xffffffff;

	// 衝突属性(相手)
	uint32_t collisionMask_ = 0xffffffff;

};

