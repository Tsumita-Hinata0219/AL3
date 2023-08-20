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
	/// 半径を取得
	/// </summary>
	float GetRadius() { return radisu_; }
	

	/// <summary>
	/// 半径を取得
	/// </summary>
	void SetRadius(float radius) { radisu_ = radius; }


private:

	// 衝突半径 デフォルト値
	float radisu_ = 1.0f; 
};