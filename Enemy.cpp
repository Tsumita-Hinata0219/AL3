#include "Enemy.h"
#include <cassert>

#include "ImGuiManager.h"



/// <summary>
/// 初期化
/// </summary>
void Enemy::Initialize(Model* model, const Vector3 velocity) {

	// NULLポインタチェック
	assert(model);

	this->model_ = model;
	this->textureHandle_ = TextureManager::Load("/picture/Enemy.png");

	worldTransform_.Initialize();
	worldTransform_.translation_.y = 2.0f;
	worldTransform_.translation_.z = 30.0f;
		
	this->velocity_ = velocity;
}



/// <summary>
/// 更新処理
/// </summary>
void Enemy::Update() {

	// 敵の移動速度
	velocity_ = {0, 0, kCharacterSpeed};

	// 座標を移動させる(1フレーム分の移動量を足しこむ)
	worldTransform_.translation_ = Subtract(worldTransform_.translation_, velocity_);
	

	// ワールドトラスフォームの更新
	worldTransform_.UpdateMatrix();

}



/// <summary>
/// 描画処理
/// </summary>
void Enemy::Draw(ViewProjection viewProjection) {

	model_->Draw(worldTransform_, viewProjection, textureHandle_);

}


