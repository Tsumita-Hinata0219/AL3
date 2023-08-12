#include "Enemy.h"
#include <cassert>

#include "ImGuiManager.h"
#include "Player.h"
#include "GameScene.h"



Enemy::~Enemy() {}



/// <summary>
/// 初期化
/// </summary>
void Enemy::Initialize(Model* model, Vector3 pos) {

	// NULLポインタチェック
	assert(model);

	this->model_ = model;
	textureHandle_ = TextureManager::Load("/picture/Enemy.png");

	worldTransform_.Initialize();
	worldTransform_.translation_.x = pos.x;
	worldTransform_.translation_.y = pos.y;
	worldTransform_.translation_.z = pos.z;


	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
		
	//phease_ = Phease::Approach;
	state_ = new EnemyStateApproach();

}



/// <summary>
/// 更新処理
/// </summary>
void Enemy::Update() {


	// 移動(ベクトルを加算)
	velocity_ = {0, 0, kCharacterSpeed}; // 敵の移動速度

	state_->Update(this, velocity_);
	

	//switch ( phease_) 
	//{
	//case Phease::Approach:
	//default:
	//	
	//	Approach();

	//	// 発射タイマーカウントダウン
	//	fireTimer_--;

	//	// 指定時間に達した
	//	if (fireTimer_ <= 0) {

	//		// 弾を発射
	//		Fire();

	//		// 発射タイマーを初期化
	//		fireTimer_ = kFireInterval_;
	//	}

	//	break;


	//case Phease::Leave:
	//	
	//	Leave();

	//	break;

	//}

	
	// ワールドトラスフォームの更新
	worldTransform_.UpdateMatrix();


	// Enemyデバッグ
	ImGui::Begin("EnemyDebug1");

	// float3入力ボックス
	ImGui::InputFloat3("EnemyPosition", &worldTransform_.translation_.x);
	// float3スライダー
	ImGui::SliderFloat3("EnemySlider", &worldTransform_.translation_.x, 0.0f, 40.0f);

	ImGui::End();
}



/// <summary>
/// 攻撃
/// </summary>
void Enemy::Fire() {

	assert(player_);

	// 弾の速度
	const float kBulletSpeed = 1.0f;

	// 自キャラのワールド座標を取得する
	playerWorldPos_ = player_->GetPlayerWorldPosition(); 

	// 敵キャラのワールド座標を取得
	enemyWorldPos_ = GetWorldPosition();

	// 敵キャラ->自キャラの差分ベクトルを求める
	EnePlaVector_ = Subtract(enemyWorldPos_, playerWorldPos_);

	// ベクトルの正規化
	EnePlaVector_ = Normalize(EnePlaVector_);

	// ベクトルの長さを、速さに合わせる
	velocity_ = {
	    EnePlaVector_.x,
	    EnePlaVector_.y,
	    EnePlaVector_.z * kBulletSpeed,
	};

	// 速度ベクトルを自機の向きに合わせて回転させる
	velocity_ = TransformNormal(velocity_, worldTransform_.matWorld_);

	// 弾を生成し、初期化
	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity_);

	// 弾をGameSceneに登録する
	gameScene_->AddEnemyBullet(newBullet);
}



/// <summary>
/// 衝突時間数
/// </summary>
void Enemy::onCollision() {

	// デスフラグを立てる
	isDead_ = true;
}



void Enemy::ChangeState(EnemyStates* newState) {

	// 元のstate_を削除してnewStateを入れる
	delete state_;
	state_ = newState;
}


/// <summary>
/// ステートパターン内で使用する移動用関数(加算 減算) 
/// </summary>
void Enemy::AddTransform(const Vector3& velocity) {

	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity);
}
void Enemy::SubtructTransform(const Vector3& velocity) {

	worldTransform_.translation_ = Subtract(worldTransform_.translation_, velocity);
}



///// <summary>
///// 行動フェーズ : 接近
///// </summary>
//void Enemy::Approach() {
//
//	// 座標を移動させる(1フレーム分の移動量を足しこむ)
//	worldTransform_.translation_ = Subtract(worldTransform_.translation_, velocity_);
//
//
//	// 規定の位置に到達し
//	if (worldTransform_.translation_.z < -10.0f) {
//
//		// 行動フェーズを離脱へ
//		phease_ = Phease::Leave;
//	}
//}



///// <summary>
///// 行動フェーズ : 離脱
///// </summary>
//void Enemy::Leave() {
//
//	// 座標を移動させる(1フレーム分の移動量を足しこむ)
//	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);
//
//	// 規定の位置に到達したら離脱
//	if (worldTransform_.translation_.z > 50.0f) {
//		phease_ = Phease::Approach;
//	}
//}



/// <summary>
/// 描画処理
/// </summary>
void Enemy::Draw(ViewProjection viewProjection) {

	model_->Draw(worldTransform_, viewProjection, textureHandle_);

}


/// <summary>
/// ワールド座標を取得
/// </summary>
Vector3 Enemy::GetWorldPosition() {
	
	// ワールド座標を入れる変数
	Vector3 worldPos{};

	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.translation_.x;
	worldPos.y = worldTransform_.translation_.y;
	worldPos.z = worldTransform_.translation_.z;

	return worldPos;
}