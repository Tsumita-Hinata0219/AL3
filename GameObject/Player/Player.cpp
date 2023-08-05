#include "Player.h"
#include <cassert>

#include "ImGuiManager.h"
#include "GameScene.h"


/// <summary>
/// コンストラクタ
/// </summary>
Player::Player() {

}



/// <summary>
/// デストラクタ
/// </summary>
Player::~Player() {

	// スプライトの解放
	delete sprite2DReticle_;

}



void Player::Initialize(Model* model, Vector3 position) {

	// NULLポインタチェック
	assert(model);

	this->model_ = model;
	playerTextureHandle_ = TextureManager::Load("/picture/Player.png");
	ReticleTextureHandle_ = TextureManager::Load("/picture/reticle.png");


	// プレイヤー
	worldTransform_.translation_ = position;
	worldTransform_.Initialize();

	// スプライト生成
	sprite2DReticle_ =
	    Sprite::Create(ReticleTextureHandle_, {640.0f, 500.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
	worldTransform3DReticle_.Initialize();

	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();

	fireTimer_ = IniFireTimer;
}



void Player::Update(ViewProjection viewProjection) {
	
	// 3Dレティクルの更新処理
	ReticleUpdate(viewProjection);



	// 自機の旋回処理
	Rotate();


	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();


	Vector3 move = {0.0f, 0.0f, 0.0f}; // 移動ベクトル

	const float kCharacterSpeed = 0.3f; // 移動速度

	// 押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_LEFT))	{
		move.x -= kCharacterSpeed;
	} 
	else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}
	if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	} 
	else if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	}

	if (input_->PushKey(DIK_R)) {
		worldTransform_.rotation_.y = 0.0f;
	}

	// 移動限界座標
	const float kMoveLimitX = 27.0f;
	const float kMoveLimitY = 14.0f;


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

	worldTransform_.UpdateMatrix();



	if (input_->PushKey(DIK_SPACE)) {
		fireTimer_--;
	} 
	if (fireTimer_ <= 0) {
		
		// 攻撃
		Attack();

		// タイマーをリセット
		fireTimer_ = kFireInterval_;
	}


	// プレイヤーデバッグ
	ImGui::Begin("PlayerDebug1");

	// float3入力ボックス
	ImGui::InputFloat3("PlayerPosition", &worldTransform_.translation_.x);
	// float3スライダー
	ImGui::SliderFloat3("PlayerSlider", &worldTransform_.translation_.x, 0.0f, 40.0f);
	ImGui::SliderFloat3("Playerrotation", &worldTransform_.rotation_.x, 0.0f, 40.0f);

	ImGui::Text("isDebugCameraActive_->Enter");
	ImGui::Text("R -> rotation.y Reset");

	ImGui::End();

	// レティクルデバッグ
	ImGui::Begin("ReticleDebug1");

	// float3入力ボックス
	ImGui::InputFloat3("ReticlePosition", &worldTransform3DReticle_.translation_.x);
	// float3スライダー
	ImGui::SliderFloat3("ReticleSlider", &worldTransform3DReticle_.translation_.x, 0.0f, 50.0f);

	ImGui::End();
}



void Player::Rotate() {

	// 回転速さ[ラジアン / frame]
	const float kRotSpeed = 0.05f;

	// 押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y -= kRotSpeed;
	} else if (input_->PushKey(DIK_D)) {
		worldTransform_.rotation_.y += kRotSpeed;
	}

}



void Player::Attack() {

	// 自機から照準オブジェクトのベクトル
	velocity_ = Subtract(GetReticleWorldPosition(), GetPlayerWorldPosition());
	velocity_ = Normalize(velocity_);

	velocity_ = { 
		Normalize(velocity_).x * kBulletSpeed_,
	    Normalize(velocity_).y * kBulletSpeed_,
	    Normalize(velocity_).z * kBulletSpeed_,	   
	};

	velocity_ = {
	    velocity_.x,
	    velocity_.y,
	    velocity_.z * kBulletSpeed_,
	};
		

	// 速度ベクトルを自機の向きに合わせて回転させる
	velocity_ = TransformNormal(velocity_, worldTransform_.matWorld_);
	
	// 弾を生成し、初期化
	PlayerBullet* newBullet = new PlayerBullet();
	newBullet->Initialize(model_, GetPlayerWorldPosition(), velocity_);

	// 弾をGameSceneに登録する
	gameScene_->AddPlayerBullet(newBullet);
}



void Player::onCollision() {

}



void Player::ReticleUpdate(ViewProjection viewProjection) {

	Vector3 pos{};

	pos.x = worldTransform_.matWorld_.m[3][0];
	pos.y = worldTransform_.matWorld_.m[3][1];
	pos.z = worldTransform_.matWorld_.m[3][2];

	// 自機のワールド行列の回転を反映
	offset = TransformNormal(offset, worldTransform_.matWorld_);

	// ベクトルの長さを整える
	//offset = {
	//    Normalize(offset).x * kDistancePlayerTo3DReticle,
	//	Normalize(offset).y * kDistancePlayerTo3DReticle,
	//	Normalize(offset).z * kDistancePlayerTo3DReticle,
	//};

	offset = Normalize(offset);
	offset.x *= kDistancePlayerTo3DReticle;
	offset.y *= kDistancePlayerTo3DReticle;
	offset.z *= kDistancePlayerTo3DReticle;
	

	//Vector3 newOffset = Add(offset, GetPlayerWorldPosition());

	worldTransform3DReticle_.translation_.x = offset.x + pos.x;
	worldTransform3DReticle_.translation_.y = offset.y + pos.y;
	worldTransform3DReticle_.translation_.z = offset.z + pos.z;

	// 3Dベクトルの座標を設定
	//worldTransform3DReticle_.translation_ = newOffset;



	worldTransform3DReticle_.UpdateMatrix();
	worldTransform3DReticle_.TransferMatrix();




	// 3Dレティクルのワールド座標から、ワールド座標を取得
	position2DReticle_ = GetReticleWorldPosition();
	
	// ビューポート行列
	matViewport_ = 
		MakeViewportMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);

	// ビュー行悦人プロジェクション行列、ビューポート行列を合成する
	matViewProjectionViewport_ =
	    Multiply(viewProjection.matView, Multiply(viewProjection.matProjection, matViewport_));

	// ワールド->スクリーン座標変換(ここで3Dから2Dになる)
	position2DReticle_ = Transform(position2DReticle_, matViewProjectionViewport_);

	// スプライトにレティクルに座標指定
	sprite2DReticle_->SetPosition(Vector2(position2DReticle_.x, position2DReticle_.y));

}



void Player::Draw3D(ViewProjection viewProjection) { 
	
	model_->Draw(worldTransform_, viewProjection, playerTextureHandle_);

	model_->Draw(worldTransform3DReticle_, viewProjection, ReticleTextureHandle_);

}



void Player::DrawUI() { 

	// 2Dレティクル描画
	sprite2DReticle_->Draw(); 
}



Vector3 Player::GetPlayerWorldPosition() {

	// ワールド座標を取得
	Vector3 worldPos{};

	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}


Vector3 Player::GetReticleWorldPosition() {

	// ワールド座標を取得
	Vector3 worldPos{};

	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform3DReticle_.matWorld_.m[3][0];
	worldPos.y = worldTransform3DReticle_.matWorld_.m[3][1];
	worldPos.z = worldTransform3DReticle_.matWorld_.m[3][2];

	return worldPos;
}



void Player::SetParent(const WorldTransform* parent) { 
	
	// 親子関係を結ぶ
	worldTransform_.parent_ = parent;
}

