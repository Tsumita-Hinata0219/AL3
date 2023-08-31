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
	delete hitDamageSprite_;

}



void Player::Initialize(Model* model, Vector3 position, Sound sound) {

	audio_ = Audio::GetInstance();

	// NULLポインタチェック
	assert(model);

	this->model_ = model;
	this->sound_ = sound;
	playerTextureHandle_ = TextureManager::Load("/picture/Player.png");
	ReticleTextureHandle_ = TextureManager::Load("/picture/reticle.png");
	hitDamageTexture_ = TextureManager::Load("/picture/hitDamage.png");

	// プレイヤー
	worldTransform_.translation_ = position;
	worldTransform_.Initialize();

	// スプライト生成
	sprite2DReticle_ =
	    Sprite::Create(ReticleTextureHandle_, {640.0f, 500.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
	worldTransform3DReticle_.Initialize();

	hitDamageSprite_ = Sprite::Create(hitDamageTexture_, {0.0f, 0.0f});
	hitDamageDrawTimer_ = hittimer;

	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();

	fireTimer_ = IniFireTimer;

	killCount_ = 0;


	// 衝突属性を設定
	SetCollisionAttribute(kCollisionAttributePlayer);

	// 省都対象を自分以外に設定
	SetCollisionMask(kCollisionAttributeEnemy);
}



void Player::Update(ViewProjection viewProjection) {

	// 自キャラの移動処理
	PlayerMove();

	// レティクルの移動処理
	ReticleMove();


	// 3Dレティクルの更新処理
	ReticleUpdate(viewProjection);



	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();


	// アフィン変換行列
	worldTransform_.matWorld_ = MakeAffineMatrix(
	    worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);



	worldTransform_.UpdateMatrix();

	
	// 自機の旋回処理
	Rotate();


	// 攻撃処理
	// ゲームパッドを未接続なら何もせず抜ける
	if (!Input::GetInstance()->GetJoystickState(0, joyState_)) {
		return;
	}

	if (input_->PushKey(DIK_SPACE) || joyState_.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) {
		fireTimer_--;
	} 
	if (fireTimer_ <= 0) {
		
		// 攻撃
		Attack();
		audio_->PlayWave(sound_.shoot1);

		// タイマーをリセット
		fireTimer_ = kFireInterval_;
	}



	if (hitDamage_) {
		hitDamageDrawTimer_--;

		if (hitDamageDrawTimer_ <= 0) {
			hitDamage_ = false;
			hitDamageDrawTimer_ = hittimer;
		}
	}


	//// プレイヤーデバッグ
	//ImGui::Begin("PlayerDebug1");

	//ImGui::Text(
	//    "Player:(%+.2f, %+.2f, %+.2f)", worldTransform_.translation_.x,
	//    worldTransform_.translation_.y, worldTransform_.translation_.z);

	//ImGui::Text("3DReticle:(%+.2f, %+.2f, %+.2f)", worldTransform3DReticle_.translation_.x, 
	//	worldTransform3DReticle_.translation_.y, worldTransform3DReticle_.translation_.z);
	//ImGui::Text("2DReticle:(%f, %f)", position2DReticle_.x, position2DReticle_.y);
	//ImGui::Text("Near:(%+.2f, %+.2f, %+.2f)", posNear_.x, posNear_.y, posNear_.z);
	//ImGui::Text("Far:(%+.2f, %+.2f, %+.2f)", posFar_.x, posFar_.y, posFar_.z);

	//ImGui::End();
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
	velocity_ = Subtract(GetReticleWorldPosition(), GetWorldPosition());
	velocity_ = Normalize(velocity_);

	velocity_ = { 
		Normalize(velocity_).x * kBulletSpeed_,
	    Normalize(velocity_).y * kBulletSpeed_,
	    Normalize(velocity_).z * kBulletSpeed_,	   
	};
		

	// 速度ベクトルを自機の向きに合わせて回転させる
	velocity_ = TransformNormal(velocity_, worldTransform_.matWorld_);
	
	// 弾を生成し、初期化
	PlayerBullet* newBullet = new PlayerBullet();
	newBullet->Initialize(model_, GetWorldPosition(), velocity_);
	newBullet->SetPlayer(this);

	// 弾をGameSceneに登録する
	gameScene_->AddPlayerBullet(newBullet);
}



void Player::onCollision() { 

	audio_->PlayWave(sound_.plaDamage);
	hitDamage_ = true;
}



void Player::PlayerMove() {

	Vector3 move = {0.0f, 0.0f, 0.0f}; // 移動ベクトル

	const float kCharacterSpeed = 0.3f; // 移動速度

	// 押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_LEFT)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHT)) {
		move.x += kCharacterSpeed;
	}
	if (input_->PushKey(DIK_UP)) {
		move.y += kCharacterSpeed;
	} else if (input_->PushKey(DIK_DOWN)) {
		move.y -= kCharacterSpeed;
	}

	if (input_->PushKey(DIK_R)) {
		worldTransform_.rotation_.y = 0.0f;
	}

	// ゲームパッド状態取得
	if (Input::GetInstance()->GetJoystickState(0, joyState_)) {
		move.x += (float)joyState_.Gamepad.sThumbLX / SHRT_MAX * kCharacterSpeed;
		move.y += (float)joyState_.Gamepad.sThumbLY / SHRT_MAX * kCharacterSpeed;
	}

	// 移動限界座標
	const float kMoveLimitX = 13.0f;
	const float kMoveLimitY = 7.0f;

	// 範囲を超えない処理
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	// 移動行列に移動ベクトルを加算
	worldTransform_.translation_ = Add(worldTransform_.translation_, move);
}



void Player::ReticleMove() { 

	// スプライトの現在の座標を取得
	spritePosition_ = sprite2DReticle_->GetPosition();

	// ジョイスティック状態取得
	if (Input::GetInstance()->GetJoystickState(0, joyState_)) {
		spritePosition_.x += (float)joyState_.Gamepad.sThumbRX / SHRT_MAX * 12.0f;
		spritePosition_.y -= (float)joyState_.Gamepad.sThumbRY / SHRT_MAX * 12.0f;

		// スプライトの座標変更を反映
		sprite2DReticle_->SetPosition(spritePosition_);
	}
}



void Player::ReticleUpdate(ViewProjection viewProjection) {
	
	// 自機のワールド行列の回転を反映
	offset = TransformNormal(offset, worldTransform_.matWorld_);
	// ベクトルの長さを整える
	offset = {
	    Normalize(offset).x * kDistancePlayerTo3DReticle,
	    Normalize(offset).y * kDistancePlayerTo3DReticle,
	    Normalize(offset).z * kDistancePlayerTo3DReticle,
	};
	Vector3 newOffset = Add(offset, GetWorldPosition());
	// 3Dベクトルの座標を設定
	worldTransform3DReticle_.translation_ = newOffset;
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




	// マウス座標(スクリーン座標)を取得する
	GetCursorPos(&mousePosition_);

	// クライアントエリア座標に変換する
	hwnd = WinApp::GetInstance()->GetHwnd();
	ScreenToClient(hwnd, &mousePosition_);


	Vector2 reticlePosition = {
		float(position2DReticle_.x), 
		float(position2DReticle_.y),
	};
	// マウス座標をを2Dレティクルのスプライトに代入する
	sprite2DReticle_->SetPosition(Vector2(float(spritePosition_.x), float(spritePosition_.y)));


	// ビュープロジェクションビューポート合成行列
	matVPV_ = Multiply(
	    viewProjection.matView,
	    Multiply(
	        viewProjection.matProjection,
	        MakeViewportMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1)));

	// 合成行列の逆行列を計算する
	matInverseVPV_ = Inverse(matVPV_);


	// スクリーン座標
	posNear_ = Vector3(float(spritePosition_.x), float(spritePosition_.y), 0);
	posFar_ = Vector3(float(spritePosition_.x), float(spritePosition_.y), 1);

	// スクリーン座標系からワールド座標系へ
	posNear_ = Transform(posNear_, matInverseVPV_);
	posFar_ = Transform(posFar_, matInverseVPV_);



	// 3Dレティクルの座標計算
	// マウスレイの方向
	mouseDirection_ = Subtract(posNear_, posFar_);
	mouseDirection_ = Add(posNear_, posFar_);
	mouseDirection_ = Normalize(mouseDirection_);

	// カメラから照準オブジェクトの距離
	worldTransform3DReticle_.translation_ = { 
		posNear_.x + mouseDirection_.x * kDistanceTestObject, 
		posNear_.y + mouseDirection_.y * kDistanceTestObject,
		posNear_.z + mouseDirection_.z * kDistanceTestObject,
	};


	// worldTransform3DReticleのワールド行列の更新と転送
	worldTransform3DReticle_.UpdateMatrix();
	worldTransform3DReticle_.TransferMatrix();
}



void Player::Draw3D(ViewProjection viewProjection) { 
	
	model_->Draw(worldTransform_, viewProjection, playerTextureHandle_);

	//model_->Draw(worldTransform3DReticle_, viewProjection, ReticleTextureHandle_);

}



void Player::DrawUI() { 

	// 2Dレティクル描画
	sprite2DReticle_->Draw(); 
	if (hitDamage_) {
		hitDamageSprite_->Draw();
	}
}



Vector3 Player::GetWorldPosition() {

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

