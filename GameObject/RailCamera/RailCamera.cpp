#include "RailCamera.h"



// 初期化処理
void RailCamera::Initialize(Vector3 translation, Vector3 rotation) {

	// ワールドトランスフォームの初期設定
	worldTransform_.rotation_ = rotation;
	worldTransform_.translation_ = translation ;
	worldTransform_.Initialize();

	// ビュープロジェクションの初期化
	viewProjection_.farZ = 1200.0f;
	viewProjection_.Initialize();

}



// 更新処理
void RailCamera::Update() {

	// ワールドトランスフォームの加算
	Vector3 move = {0.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);

	Vector3 rotate = {0.0f, 0.0f, 0.0f};
	worldTransform_.rotation_ = Add(worldTransform_.rotation_, rotate);


	// ワールドトランスフォームのワールド行列再計算
	worldTransform_.UpdateMatrix();

	
	// カメラオブジェクトのワールド行列からビュー行列を計算する
	viewProjection_.matView = Inverse(worldTransform_.matWorld_);

	
	// カメラの座標を画面表示する処理
	ImGui::Begin("RailCamera");

	// スライダーでtranslationとratationを表示
	ImGui::SliderFloat3("translation", &worldTransform_.translation_.x, -100.0f, 100.0f);
	ImGui::SliderFloat3("rotation", &worldTransform_.rotation_.x, -50.0f, 50.0f);

	ImGui::End();
}


