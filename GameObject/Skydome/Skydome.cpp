#include "Skydome.h"



// 初期化処理
void Skydome::Initialize(Model* model) {

	// NULLポインタチェック
	assert(model);

	this->model_ = model;

	worldTransform_.scale_.x = 100.0f;
	worldTransform_.scale_.y = 100.0f;
	worldTransform_.scale_.z = 100.0f;
	worldTransform_.Initialize();
}

// 更新処理
void Skydome::Update() {

	
	// アフィン変換行列
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);



	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();
}


// 描画処理
void Skydome::Draw(ViewProjection viewProjection) {

	// 3Dモデルの描画
	model_->Draw(worldTransform_, viewProjection);
}

