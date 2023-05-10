#include "Player.h"
#include <cassert>


void Player::Initialize(Model* model, uint32_t textureHandle) {

	// NULLポインタチェック
	assert(model);

	this->model_ = model;
	this->textureHandle_ = textureHandle;

	worldTransform_.Initialize();
}



void Player::Update() {

	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();

}



void Player::Draw(ViewProjection viewProjection) { 
	
	model_->Draw(this->worldTransform_, viewProjection, this->textureHandle_);

}