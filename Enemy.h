#pragma once

#include <Model.h>
#include <WorldTransform.h>
#include <Input.h>
#include <ImGuiManager.h>
#include <Function.h>
#include <EnemyBullet.h>
#include <list>


// 行動フェーズ
enum class Phease {
	Approach, // 接近する
	Leave,  // 離脱する
};


/// <summary>
/// 敵キャラ
/// </summary>
class Enemy {

public:

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Enemy();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, const Vector3 velocity);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(ViewProjection viewProjection);

	/// <summary>
	/// 攻撃
	/// </summary>
	void Fire();

	/// <summary>
	/// 行動フェーズ : 接近
	/// </summary>
	void Approach();

	void ApproachIni();

	/// <summary>
	/// 行動フェーズ : 離脱
	/// </summary>
	void Leave();


	// インライン関数
	Vector3 Velocity() const { return velocity_; };


private:

	EnemyBullet* bullet_ = nullptr;

	Phease phease_; // フェーズ

	WorldTransform worldTransform_; // ワールド変換データ

	Model* model_ = nullptr; // モデル

	uint32_t textureHandle_ = 0u; // テクスチャハンドル

	const float kCharacterSpeed = 0.3f; // 移動速度

	Vector3 velocity_; // 弾の速度を設定

	std::list<EnemyBullet*> bullets_; // 弾

	static const int kFireInterval_ = 60; // 発射間隔の設定

	int32_t fireTimer_ = 0; // 発射タイマー

	Input* input_ = nullptr; // キーボード入力
};
