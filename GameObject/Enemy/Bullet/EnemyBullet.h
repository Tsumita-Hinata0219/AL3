#pragma once

#include <Function.h>
#include <Model.h>
#include <Vector3.h>
#include <WorldTransform.h>
#include <cassert>





class EnemyBullet {

public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);


	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();


	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(const ViewProjection& viewProjection);

	
	// ワールド座標を取得
	Vector3 GetWorldPosition();

	
	// 半径を取得
	float GetRadius() { return radius_; };


	/// <summary>
	/// 衝突を検出したら呼び出されるコールバッグ関数
	/// </summary>
	void onCollision();



	bool IsDead() const { return isDead_; }



	//void SetTextureHandle(uint32_t textureHandle) { textureHandle_ = textureHandle; }
	


private:
	WorldTransform worldTransform_; // ワールド変換データ

	Model* model_ = nullptr; // モデル

	uint32_t textureHandle_ = 0u; // テクスチャハンドル

	Vector3 velocity_; // 速度

	static const int32_t kLifeTimer = 60 * 5; // 寿命<frm>

	int32_t deathTimer_ = kLifeTimer; // デスタイマー

	bool isDead_ = false; // デスフラグ

	const float radius_ = 2.0f; // 半径

	float height_ = 0.0f;

	float velocityZ_ = 0.0f;
};

