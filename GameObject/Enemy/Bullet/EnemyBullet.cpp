#include "EnemyBullet.h"



/// <summary>
/// 初期化
/// </summary>
void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {

	// NULLポインタチェック
	assert(model);

	model_ = model;
	textureHandle_ = TextureManager::Load("/picture/eneBullet.png");

	// Z方向に伸びた形状
	worldTransform_.scale_.x = 0.5f;
	worldTransform_.scale_.y = 0.5f;
	worldTransform_.scale_.z = 3.0f;


	// 弾をプレイヤーのほうへ回転
	worldTransform_.rotation_.y = std::atan2(velocity.x, velocity.z);
	velocityZ_ = sqrt((velocity.x * velocity.x) + (velocity.z * velocity.z));
	height_ = -velocity.y;
	worldTransform_.rotation_.x = std::atan2(height_, velocityZ_);


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
/// 衝突時判定
/// </summary>
void EnemyBullet::onCollision() {

	// デスフラグを立てる
	isDead_ = true;
}



/// <summary>
/// 描画処理
/// </summary>
void EnemyBullet::Draw(const ViewProjection& viewProjection) {

	// モデルの描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}


Vector3 EnemyBullet::GetWorldPosition() {

	// ワールド座標を取得
	Vector3 worldPos{};

	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}