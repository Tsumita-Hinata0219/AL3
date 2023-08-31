#pragma once

#include <Model.h>
#include <cassert>
#include <WorldTransform.h>
#include <Vector3.h>
#include <Function.h>
#include "Collider.h"
#include "CollisionConfig.h"
#include <Sprite.h>


// 自機クラスの前方宣言
class Player;

class PlayerBullet : public Collider {

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


	/// <summary>
	/// UI描画
	/// </summary>
	void DrawUI();


	/// <summary>
	/// 衝突を検出したら呼び出されるコールバッグ関数
	/// </summary>
	void onCollision() override;


	// ワールド座標を取得
	Vector3 GetWorldPosition() override;

	
	// 半径を取得
	float GetRadius() { return radius_; };


	//void SetTextureHandle(uint32_t textureHandle) { textureHandle_ = textureHandle; }


	bool IsDead() const { return isDead_; }

	// プレイヤーの取得
	Player* GetPlayer() { return player_; }
	void SetPlayer(Player* player) { player_ = player; }


public:

	uint32_t textureHandle_ = 0u; // テクスチャハンドル

private:

	// 自キャラ
	Player* player_ = nullptr;
	
	WorldTransform worldTransform_; // ワールド変換データ

	Model* model_ = nullptr; // モデル


	Vector3 velocity_; // 速度

	static const int32_t kLifeTimer = 60 * 5; // 寿命<frm>

	int32_t deathTimer_ = kLifeTimer; // デスタイマー

	bool isDead_ = false; // デスフラグ

	const float radius_ = 4.0f; // 半径

	uint32_t killCount_;
};