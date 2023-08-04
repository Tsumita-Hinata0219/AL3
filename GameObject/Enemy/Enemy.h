#pragma once

#include <Model.h>
#include <WorldTransform.h>
#include <Input.h>
#include <ImGuiManager.h>
#include <Function.h>
#include <EnemyBullet.h>
#include <list>



// 自機クラスの前方宣言
class Player;

// gameSceneの前方宣言
class GameScene;


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
	void Initialize(Model* model, Vector3 pos);


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


	/// <summary>
	/// 行動フェーズ : 離脱
	/// </summary>
	void Leave();


	/// <summary>
	/// 衝突を検出したら呼び出されるコールバッグ関数
	/// </summary>
	void onCollision();


	// インライン関数
	Vector3 Velocity() const { return velocity_; };

	// ワールド座標を取得
	Vector3 GetWorldPosition();

	// 弾リストを取得
	const std::list<EnemyBullet*>& GetBullet() { return bullets_; };

	// 半径を取得
	float GetRadius() { return radius_; };
	
	void SetPlayer(Player* player) { player_ = player; }

	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

	bool IsDead() const { return isDead_; }
	

private:

	// 自キャラ
	Player* player_ = nullptr;

	// ゲームシーン
	GameScene* gameScene_ = nullptr;

	EnemyBullet* bullet_ = nullptr;

	std::list<EnemyBullet*> bullets_; // 弾

	Phease phease_; // フェーズ

	WorldTransform worldTransform_; // ワールド変換データ

	Model* model_ = nullptr; // モデル

	uint32_t textureHandle_ = 0u; // テクスチャハンドル

	const float kCharacterSpeed = 0.1f; // 移動速度

	Vector3 velocity_; // 敵の速度を設定

	static const int kFireInterval_ = 60; // 発射間隔の設定

	int32_t fireTimer_ = 0; // 発射タイマー

	Input* input_ = nullptr; // キーボード入力

	const float radius_ = 2.0f; // 半径

	bool isDead_ = false; // デスフラグ
};
