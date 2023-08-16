#pragma once

#include <Model.h>
#include <WorldTransform.h>
#include <Input.h>
#include <ImGuiManager.h>
#include <list>
#include "Function.h"
#include "EnemyBullet.h"
#include "EnemyStates.h"
#include "EnemyStateApproach.h"
#include "EnemystateLeave.h"
#include "TimedCall.h"



// 自機クラスの前方宣言
class Player;

// gameSceneの前方宣言
class GameScene;


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
	/// 弾を発射し、タイマーをリセットするコールバッグ関数
	/// </summary>
	void Attack();



	/// <summary>
	/// 弾の射撃処理
	/// </summary>
	void Fire();



	/// <summary>
	/// 衝突を検出したら呼び出されるコールバッグ関数
	/// </summary>
	void onCollision();


	/// <summary>
	/// フェーズを変更する
	/// </summary>
	void ChangeState(EnemyStates* newState);
	


	/// <summary>
	/// ステートパターン内で使用する移動用関数(加算 減算) 
	/// </summary>
	void AddTransform(const Vector3& velocity);
	void SubtructTransform(const Vector3& velocity);


	// インライン関数
	Vector3 GetVelocity() { return velocity_; };

	// ワールド座標を取得
	Vector3 GetWorldPosition();

	// 弾リストを取得
	const std::list<EnemyBullet*>& GetBullet() { return bullets_; };

	// 半径を取得
	float GetRadius() { return radius_; };
	
	// プレイヤーの取得
	Player* GetPlayer() { return player_; }
	void SetPlayer(Player* player) { player_ = player; }

	// ゲームシーンを取得
	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

	// 死亡判定
	bool IsDead() const { return isDead_; }
	



private:

	// 敵キャラ
	WorldTransform worldTransform_; // ワールド変換データ

	Vector3 enemyWorldPos_; // ワールド座標

	Model* model_ = nullptr; // モデル

	uint32_t textureHandle_ = 0u; // テクスチャハンドル

	const float kCharacterSpeed = 0.1f; // 移動速度

	Vector3 velocity_; // 敵キャラの移動量

	Input* input_ = nullptr; // キーボード入力

	const float radius_ = 2.0f; // 半径

	bool isDead_ = false; // デスフラグ

	Vector3 EnePlaVector_; // 敵キャラと自キャラの差分ベクトル


	// 自キャラ
	Player* player_ = nullptr;

	Vector3 playerWorldPos_; // ワールド座標


	// ゲームシーン
	GameScene* gameScene_ = nullptr;


	// タイムコール
	std::list<TimedCall*> timedCalls_;


	// 弾
	EnemyBullet* bullet_ = nullptr; // 弾

	std::list<EnemyBullet*> bullets_; // 弾リスト

	static const int kFireInterval_ = 60; // 発射間隔の設定

	int32_t fireTimer_ = 0; // 発射タイマー

	const float kBulletSpeed_ = 1.0f; // 弾の速度


	// ステートパターン
	EnemyStates* state_;

	
};
