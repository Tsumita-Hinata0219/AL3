#include "RailCamera.h"



// 初期化処理
void RailCamera::Initialize() {

	// ワールドトランスフォームの初期設定
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransform_.rotation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {0.0f, 0.0f, -50.0f};
	worldTransform_.Initialize();

	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

}



// 更新処理
void RailCamera::Update() {


	// ワールドトランスフォームの加算
	Vector3 move = {0.0f, 0.0f, 0.0f};
	//const float kRailCameraSpeed = -0.3f;
	//move.z -= kRailCameraSpeed;
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);

	Vector3 rotate = {0.0f, 0.0f, 0.0f};
	worldTransform_.rotation_ = Add(worldTransform_.rotation_, rotate);


	// ワールドトランスフォームのワールド行列再計算
	worldTransform_.UpdateMatrix();

	
	//// アフィン変換行列
	//worldTransform_.matWorld_ = MakeAffineMatrix(
	//    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);


	// カメラオブジェクトのワールド行列からビュー行列を計算する
	viewProjection_.matView = Inverse(worldTransform_.matWorld_);

	
	// カメラの座標を画面表示する処理
	ImGui::Begin("RailCamera");

	// スライダーでtranslationとratationを表示
	ImGui::SliderFloat3("translation", &worldTransform_.translation_.x, -50.0f, 50.0f);
	ImGui::SliderFloat3("rotation", &worldTransform_.rotation_.x, -50.0f, 50.0f);

	ImGui::End();
}

