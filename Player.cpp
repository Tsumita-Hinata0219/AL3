#include "Player.h"
#include <cassert>

#include "ImGuiManager.h"


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


	// 移動限界座標
	const float kMoveLimitX = 33.0f;
	const float kMoveLimitY = 18.0f;

	// 範囲を超えない処理
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);


	// 移動行列に移動ベクトルを加算
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);

	// アフィン変換行列
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);


	ImGui::Begin("PlayerDebug1");

	// float3入力ボックス
	ImGui::InputFloat3("PlayerPosition", &worldTransform_.translation_.x);
	// float3スライダー
	ImGui::SliderFloat3("PlayerSlider", &worldTransform_.translation_.x, 0.0f, 40.0f);

	ImGui::Text("isDebugCameraActive_->Enter");

	ImGui::End();

	}



void Player::Draw(ViewProjection viewProjection) { 
	
	model_->Draw(this->worldTransform_, viewProjection, this->textureHandle_);

}