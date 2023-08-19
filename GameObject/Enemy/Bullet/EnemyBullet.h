#pragma once

#include <Function.h>
#include <Model.h>
#include <Vector3.h>
#include <WorldTransform.h>
#include <cassert>
#include <ImGuiManager.h>




// 自機クラスの前方宣言
class Player;



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


	// プレイヤーの取得
	void SetPlayer(Player* player) { player_ = player; }
	


private:

	Player* player_ = nullptr;
	Vector3 toPlayer_{};

	WorldTransform worldTransform_; // ワールド変換データ

	Model* model_ = nullptr; // モデル

	uint32_t textureHandle_ = 0u; // テクスチャハンドル

	Vector3 velocity_; // 速度

	static const int32_t kLifeTimer = 50 * 5; // 寿命<frm>

	int32_t deathTimer_ = kLifeTimer; // デスタイマー

	bool isDead_ = false; // デスフラグ

	const float radius_ = 2.0f; // 半径

	float height_ = 0.0f;

	float velocityZ_ = 0.0f;
};

