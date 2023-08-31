#include "Ground.h"



void Ground::Initialize(Model* model) {
	// NULLポインタチェック
	assert(model);

	this->model_ = model;

	worldTransform_.translation_.y = -50.0f;

	worldTransform_.scale_.x = 500.0f;
	worldTransform_.scale_.y = 500.0f;
	worldTransform_.scale_.z = 500.0f;
	worldTransform_.Initialize();
}


void Ground::Update() {
	// アフィン変換行列
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();
}


void Ground::Draw(ViewProjection viewProjection) {
	// 3Dモデルの描画
	model_->Draw(worldTransform_, viewProjection);
}

