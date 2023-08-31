#include <PlayerBullet.h>
#include "Player.h"



/// <summary>
/// 初期化
/// </summary>
void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {

	// NULLポインタチェック
	assert(model);

	model_ = model;
	textureHandle_ = TextureManager::Load("/picture/Bullet.png");


	worldTransform_.Initialize();

	// 引数で受け取った初期座標をリセット
	worldTransform_.translation_ = position;

	// 引数で受け取った速度をメンバ変数に代入
	velocity_ = velocity;

	// 衝突属性を設定
	SetCollisionAttribute(kCollisionAttributePlayer);

	// 省都対象を自分以外に設定
	SetCollisionMask(kCollisionAttributeEnemy);

}



/// <summary>
/// 更新処理
/// </summary>
void PlayerBullet::Update() {

	// 座標を移動させる(1フレーム分の移動量を足しこむ)
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);

	// ワールドトラスフォームの更新
	worldTransform_.UpdateMatrix();


	// 時間経過でデス
	if (--deathTimer_ <= 0) {

		isDead_ = true;
	}

}



void PlayerBullet::onCollision() {

	// デスフラグを立てる
	isDead_ = true;
	
	player_->SetKillCount(player_->GetKillCount() + 1);
	
}



/// <summary>
/// 描画処理
/// </summary>
void PlayerBullet::Draw(const ViewProjection& viewProjection) {

	// モデルの描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}



Vector3 PlayerBullet::GetWorldPosition() {

	// ワールド座標を取得
	Vector3 worldPos{};

	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}