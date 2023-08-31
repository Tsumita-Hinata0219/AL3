#include "Enemy.h"
#include <cassert>

#include "ImGuiManager.h"
#include "Player.h"
#include "GameScene.h"



/// <summary>
/// デストラクタ
/// </summary>
Enemy::~Enemy() {}



/// <summary>
/// 初期化
/// </summary>
void Enemy::Initialize(Model* model, Vector3 pos, Sound sound) {

	audio_ = Audio::GetInstance();

	// NULLポインタチェック
	assert(model);

	this->model_ = model;
	this->sound_ = sound;
	textureHandle_ = TextureManager::Load("/picture/Enemy.png");
	enemyNormalBulletModel_ = Model::CreateFromOBJ("EnemyBullet1", true);
	enemyChaseBulletModel_ = Model::CreateFromOBJ("EnemyBullet2", true);

	worldTransform_.Initialize();
	worldTransform_.translation_.x = pos.x;
	worldTransform_.translation_.y = pos.y;
	worldTransform_.translation_.z = pos.z;


	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
		
	//phease_ = Phease::Approach;
	state_ = new EnemyStateApproach();


	// 衝突属性を設定
	SetCollisionAttribute(kCollisionAttributeEnemy);

	// 省都対象を自分以外に設定
	SetCollisionMask(kCollisionAttributePlayer);
}



/// <summary>
/// 更新処理
/// </summary>
void Enemy::Update() {


	// 移動(ベクトルを加算)
	velocity_ = {0, 0, kCharacterSpeed}; // 敵の移動速度

	state_->Update(this);


	// ワールドトラスフォームの更新
	worldTransform_.UpdateMatrix();


	// Enemyデバッグ
	ImGui::Begin("EnemyDebug1");

	// float3入力ボックス
	ImGui::InputFloat3("EnemyPosition", &worldTransform_.translation_.x);

	ImGui::End();
}



/// <summary>
/// 攻撃
/// </summary>
void Enemy::Attack() {

	rethicle_.translation_ = player_->GetReticleWorldPosition();

	// 発射タイマーカウントダウン
	NormalBulletFireTimer_--;
	ChaseBulletFireTimer_--;

	// 指定時間に達した
	if (NormalBulletFireTimer_ <= 0) {

		// プレイヤーより前にいたら攻撃
		if (player_->GetWorldPosition().z <= worldTransform_.translation_.z) {

			// 弾を発射
			FireNormalBullet();
		}

		// 発射タイマーを初期化
		NormalBulletFireTimer_ = kNormalBulletFireInterval_;
	}
	if (ChaseBulletFireTimer_ <= 0) {

		// プレイヤーより前にいたら攻撃
		if (player_->GetWorldPosition().z <= worldTransform_.translation_.z) {

			// 弾を発射
			FireChaseBullet();
		}

		// 発射タイマーを初期化
		ChaseBulletFireTimer_ = kChaseBulletFireInterval_;
	}
}



/// <summary>
/// 射撃準備処理
/// </summary>
void Enemy::FirePreparation() {

	assert(player_);

	// 自キャラのワールド座標を取得する
	playerWorldPos_ = player_->GetWorldPosition();

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
	    EnePlaVector_.z * kBulletSpeed_,
	};

	// 速度ベクトルを自機の向きに合わせて回転させる
	velocity_ = TransformNormal(velocity_, worldTransform_.matWorld_);
}



/// <summary>
/// 弾の射撃処理
/// </summary>
void Enemy::FireNormalBullet() {

	// 射撃準備
	FirePreparation();

	// 弾を生成し、初期化
	EnemyNormalBullet* newBullet = new EnemyNormalBullet();
	newBullet->Initialize(enemyNormalBulletModel_, worldTransform_.translation_, velocity_);
	newBullet->SetPlayer(player_);

	// 弾をGameSceneに登録する
	gameScene_->AddEnemyNormalBullet(newBullet);
}
void Enemy::FireChaseBullet() {

	// 射撃準備
	FirePreparation();

	// 弾を生成し、初期化
	EnemyChaseBullet* newBullet = new EnemyChaseBullet();
	newBullet->Initialize(enemyChaseBulletModel_, worldTransform_.translation_, velocity_);
	newBullet->SetPlayer(player_);

	// 弾をGameSceneに登録する
	gameScene_->AddEnemyChaseBullet(newBullet);
}


/// <summary>
/// 衝突時間数
/// </summary>
void Enemy::onCollision() {

	// デスフラグを立てる
	audio_->PlayWave(sound_.eneDie);
	isDead_ = true;
}



/// <summary>
/// フェーズを変更する
/// </summary>
void Enemy::ChangeState(EnemyStates* newState) {

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
	
	// ワールド座標を取得
	Vector3 worldPos{};

	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}