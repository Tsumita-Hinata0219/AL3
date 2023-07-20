#pragma once

#include <Model.h>
#include <WorldTransform.h>
#include <Input.h>
#include <ImGuiManager.h>
#include <Function.h>
#include <PlayerBullet.h>
#include <list>


/// <summary>
/// 自キャラ
/// </summary>
class Player {

public:


	/// <summary>
	/// コンストラクタ
	/// </summary>
	Player();


	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();

	
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model);


	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();


	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name = "viewProjection">ビュープロジェクション (参照渡し) </pram>
	void Draw(ViewProjection viewProjection);


	/// <summary>
	/// 旋回(回転)
	/// </summary>
	void Rotate();
		

	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack();


	/// <summary>
	/// 衝突を検出したら呼び出されるコールバッグ関数
	/// </summary>
	void onCollision();


	// ワールド座標を取得
	Vector3 GetWorldPosition();

	// 半径を取得
	float GetRadius() { return radius_; };


	// 弾リストを取得
	const std::list<PlayerBullet*>& GetBullet() { return bullets_; };



private:

	WorldTransform worldTransform_; // ワールド変換データ

	Model* model_ = nullptr; // モデル

	uint32_t textureHandle_ = 0u; // テクスチャハンドル

	Input* input_ = nullptr; // キーボード入力

	std::list<PlayerBullet*> bullets_; // 弾

	int32_t fireTimer_ = 0; // 発射タイマー

	static const int IniFireTimer = 3;
	static const int kFireInterval_ = 7; // 発射間隔の設定

	const float radius_ = 2.0f; // 半径

};

