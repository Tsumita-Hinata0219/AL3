#include "Player.h"
#include <cassert>


void Player::Initialize(Model* model, uint32_t textureHandle) {

	// NULLポインタチェック
	assert(model);

	this->model_ = model;
	this->textureHandle_ = textureHandle;

	worldTransform_.Initialize();

	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
}



void Player::Update() {


	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();

	Vector3 move = {0.0f, 0.0f, 0.0f}; // 移動ベクトル

	const float kCharacterSpeed = 0.3f; // 移動速度


	// 押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_LEFT)) // 左移動
	{
		move.x -= kCharacterSpeed;
	}
	else if (input_->PushKey(DIK_RIGHT)) // 右移動
	{
		move.x += kCharacterSpeed;
	}
	if (input_->PushKey(DIK_UP)) // 上移動
	{
		move.y += kCharacterSpeed;
	}
	else if (input_->PushKey(DIK_DOWN)) // 下移動
	{
		move.y -= kCharacterSpeed;
	}


	// 移動行列に移動ベクトルを加算
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);

	// アフィン変換行列
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	}



void Player::Draw(ViewProjection viewProjection) { 
	
	model_->Draw(this->worldTransform_, viewProjection, this->textureHandle_);

}