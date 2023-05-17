#pragma once

#include <Model.h>
#include <cassert>
#include <WorldTransform.h>
#include <Vector3.h>





class PlayerBullet {

public:

	/// <summary>
	/// インストラクタ
	/// </summary>
	PlayerBullet();


	/// <summary>
	/// デストラクタ
	/// </summary>
	~PlayerBullet();
	

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, const Vector3& position);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name = "viewProjection">ビュープロジェクション (参照渡し) </pram>
	void Draw(const ViewProjection& viewProjection);

	
	


private:

	
	WorldTransform worldTransform_; // ワールド変換データ

	Model* model_ = nullptr; // モデル

	uint32_t textureHandle_ = 0u; // テクスチャハンドル

};