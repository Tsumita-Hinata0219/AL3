#pragma once

#include <Model.h>
#include <WorldTransform.h>
#include <Input.h>
#include <ImGuiManager.h>
#include <Function.h>



class EnemyState;
class EnemyApproach;
class EnemyLeave;


/// <summary>
/// 敵キャラ
/// </summary>
class Enemy {

public:

	Enemy();
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
	/// 挙動処理
	/// </summary>
	void Approach();
	void Leave();

	/// <summary>
	/// 行動フェーズを変更する
	/// </summary>
	void ChanegeState(EnemyState* newState);


	// インライン関数
	Vector3 Velocity() const { return velocity_; };


	// アクセッサ
	WorldTransform GetWorldTransform() { return worldTransform_; };
	Vector3 GetVelocity() { return velocity_; };
	EnemyState* GetState() { return state_; };

	void SetWorldTranslation(Vector3 translation);



private:

	// 行動フェーズ
	EnemyState* state_ = nullptr;

	WorldTransform worldTransform_; // ワールド変換データ

	Model* model_ = nullptr; // モデル

	uint32_t textureHandle_ = 0u; // テクスチャハンドル

	const float kCharacterSpeed = 0.3f; // 移動速度

	Vector3 velocity_; // 弾の速度を設定

};





/// <summary>
/// EnemyStateクラス
/// </summary>
class EnemyState {

public:
	// 純粋仮想関数　※派生クラスに実装を強制する
	virtual void Update(Enemy* pEnemy) = 0;
};


/// <summary>
/// EnemyApproachクラス : 接近
/// </summary>
class EnemyApproach : public EnemyState {

public:
	void Update(Enemy* pEnemy) override;
};


/// <summary>
/// EnemyLeaveクラス : 離脱
/// </summary>
class EnemyLeave : public EnemyState {

public:
	void Update(Enemy* pEnemy) override;
};