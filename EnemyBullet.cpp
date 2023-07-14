#include "EnemyBullet.h"



/// <summary>
/// 初期化
/// </summary>
void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {

	// NULLポインタチェック
	assert(model);

	model_ = model;
	textureHandle_ = TextureManager::Load("/picture/Bullet.png");

	worldTransform_.Initialize();

	// 引数で受け取った初期座標をリセット
	worldTransform_.translation_ = position;

	// 引数で受け取った速度をメンバ変数に代入
	velocity_ = velocity;
}



/// <summary>
/// 更新処理
/// </summary>
void EnemyBullet::Update() {

	// ワールドトラスフォームの更新
	worldTransform_.UpdateMatrix();

	
	// 座標を移動させる(1フレーム分の移動量を足しこむ)
	worldTransform_.translation_ = Subtract(worldTransform_.translation_, velocity_);


	// 時間経過でデス
	if (--deathTimer_ <= 0) {

		isDead_ = true;
	}
}



/// <summary>
/// 描画処理
/// </summary>
void EnemyBullet::Draw(const ViewProjection& viewProjection) {

	// モデルの描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

