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
	/// インストラクタ
	/// </summary>
	Player();


	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();

	
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, uint32_t textureHandle);


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



private:

	WorldTransform worldTransform_; // ワールド変換データ

	Model* model_ = nullptr; // モデル

	uint32_t textureHandle_ = 0u; // テクスチャハンドル

	Input* input_ = nullptr; // キーボード入力

	std::list<PlayerBullet*> bullets_; // 弾

};
