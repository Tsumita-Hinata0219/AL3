#include "Enemy.h"
#include <cassert>

#include "ImGuiManager.h"


// フェーズの関数テーブルの実体
void (Enemy::*Enemy::pPheaseTable[])() = {
	&Enemy::Approach, 
	&Enemy::Leave
};


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

	// メンバ関数を呼び出す
	(this->*pPheaseTable[static_cast<size_t>(phease_)])();

	// ワールドトラスフォームの更新
	worldTransform_.UpdateMatrix();

	// 移動(ベクトルを加算)
	velocity_ = {0, 0, kCharacterSpeed}; // 敵の移動速度
	}



/// <summary>
/// 行動フェーズ : 接近
/// </summary>
void Enemy::Approach() {

	// 座標を移動させる(1フレーム分の移動量を足しこむ)
	worldTransform_.translation_ = Subtract(worldTransform_.translation_, velocity_);

	// 規定の位置に到達したら離脱フェーズへ
	if (worldTransform_.translation_.z <= -30.0f) {
		phease_ = Phease::Leave;
	}
}



/// <summary>
/// 行動フェーズ : 離脱
/// </summary>
void Enemy::Leave() {

	// 座標を移動させる(1フレーム分の移動量を足しこむ)
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);

	// 規定の位置に到達したら接近フェーズへ
	if (worldTransform_.translation_.z >= 30.0f) {
		phease_ = Phease::Approach;
	}
}



/// <summary>
/// 描画処理
/// </summary>
void Enemy::Draw(ViewProjection viewProjection) {

	model_->Draw(worldTransform_, viewProjection, textureHandle_);

}


