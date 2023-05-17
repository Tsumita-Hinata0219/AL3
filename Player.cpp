#include "Player.h"
#include <cassert>

#include "ImGuiManager.h"




/// <summary>
/// コンストラクタ
/// </summary>
Player::Player() {

	// bullet_の解放
	for (PlayerBullet* bullet : bullets_) {
		delete bullet;
	}
}



/// <summary>
/// デストラクタ
/// </summary>
Player::~Player() {}



void Player::Initialize(Model* model) {

	// NULLポインタチェック
	assert(model);

	this->model_ = model;
	textureHandle_ = TextureManager::Load("/picture/Player.png");

	worldTransform_.Initialize();

	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
}



void Player::Update() {

	// デスフラグの立った弾を削除
	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	// 自機の旋回処理
	Rotate();

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

	// 攻撃
	Attack();

	// 弾更新
	for (PlayerBullet* bullet : bullets_) {
		bullet->Update();
	}


	// プレイヤーデバッグ
	ImGui::Begin("PlayerDebug1");

	// float3入力ボックス
	ImGui::InputFloat3("PlayerPosition", &worldTransform_.translation_.x);
	// float3スライダー
	ImGui::SliderFloat3("PlayerSlider", &worldTransform_.translation_.x, 0.0f, 40.0f);

	ImGui::Text("isDebugCameraActive_->Enter");

	ImGui::End();
}



void Player::Rotate() {
	// 回転速さ[ラジアン / frame]
	const float kRotSpeed = 0.02f;

	// 押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y -= kRotSpeed;
	} else if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y += kRotSpeed;
	}
}



void Player::Attack() {

	if (input_->TriggerKey(DIK_SPACE)) {

		// 弾の速度
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);

		// 速度ベクトルを自機の向きに合わせて回転させる
		velocity = TransformNormal(velocity, worldTransform_.matWorld_);
		
		// 弾を生成し、初期化
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, worldTransform_.translation_, velocity);

		// 弾を登録する
		bullets_.push_back(newBullet);
	}
}



void Player::Draw(ViewProjection viewProjection) { 
	
	model_->Draw(worldTransform_, viewProjection, textureHandle_);


	// 弾描画
	for (PlayerBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}

