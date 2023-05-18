#include "Enemy.h"
#include <cassert>

#include "ImGuiManager.h"



/// <summary>
/// コンストラクタ
/// </summary>
Enemy::Enemy() {

}



/// <summary>
/// デストラクタ
/// </summary>
Enemy::~Enemy() {}



/// <summary>
/// 初期化
/// </summary>
void Enemy::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {

	// NULLポインタチェック
	assert(model);

	this->model_ = model;
	this->textureHandle_ = TextureManager::Load("/picture/Enemy.png");

	worldTransform_.Initialize();
		
	// 引数で受け取った初期座標をリセット
	worldTransform_.translation_ = position;

	// 引数で受け取った速度をメンバ変数に代入
	velocity_ = velocity;
	
}



/// <summary>
/// 更新処理
/// </summary>
void Enemy::Update() {

	
	// 弾の速度を設定
	const float kBulletSpeed = -1.0f;
	Vector3 velocity(0, 0, kBulletSpeed);

	// 座標を移動させる(1フレーム分の移動量を足しこむ)
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);

	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();
		
	// アフィン変換行列
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);


}



/// <summary>
/// 描画処理
/// </summary>
void Enemy::Draw(ViewProjection viewProjection) {

	model_->Draw(worldTransform_, viewProjection, textureHandle_);

}


