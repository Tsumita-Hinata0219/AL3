#pragma once

#include <Model.h>
#include <WorldTransform.h>
#include <Input.h>
#include <ImGuiManager.h>
#include <Function.h>


/// <summary>
/// 敵キャラ
/// </summary>
class Enemy {

public:

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
	/// 行動フェーズ : 接近
	/// </summary>
	void Approach();

	/// <summary>
	/// 行動フェーズ : 離脱
	/// </summary>
	void Leave();


	// インライン関数
	Vector3 Velocity() const { return velocity_; };


private:
	
	// 行動フェーズ
	enum class Phease {
		Approach, // 接近する
		Leave,    // 離脱する
	};
	Phease phease_ = Phease(); // フェーズ

	// フェーズのstaticメンバ変数
	static void (Enemy::*pPheaseTable[])();


	WorldTransform worldTransform_; // ワールド変換データ

	Model* model_ = nullptr; // モデル

	uint32_t textureHandle_ = 0u; // テクスチャハンドル

	const float kCharacterSpeed = 0.3f; // 移動速度

	Vector3 velocity_; // 弾の速度を設定

};
