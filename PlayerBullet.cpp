#include <PlayerBullet.h>



void PlayerBullet::Initialize(Model* model, const Vector3& position) {

	// NULLポインタチェック
	assert(model);

	this->model_ = model;
	this->textureHandle_ = TextureManager::Load("/picture/BlackBall.png");

	worldTransform_.Initialize();

	// 引数で受け取った初期座標をリセット
	worldTransform_.translation_ = position;
}



void PlayerBullet::Update() {

	// ワールドトラスフォームの更新
	worldTransform_.UpdateMatrix();

}


void PlayerBullet::Draw(const ViewProjection& viewProjection) {

	// モデルの描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}