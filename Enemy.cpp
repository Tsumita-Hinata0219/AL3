#include "Enemy.h"
#include <cassert>

#include "ImGuiManager.h"



Enemy::~Enemy() {
	for (EnemyBullet* bullet : bullets_) {
		delete bullet;
	}
}



/// <summary>
/// 初期化
/// </summary>
void Enemy::Initialize(Model* model, const Vector3 velocity) {

	// NULLポインタチェック
	assert(model);

	this->model_ = model;
	this->textureHandle_ = TextureManager::Load("/picture/Enemy.png");

	worldTransform_.Initialize();
	worldTransform_.translation_.y = 2.0f;
	worldTransform_.translation_.z = 30.0f;


	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
		
	this->velocity_ = velocity;

	phease_ = Phease::Approach;
}



/// <summary>
/// 更新処理
/// </summary>
void Enemy::Update() {


	// ワールドトラスフォームの更新
	worldTransform_.UpdateMatrix();

	// 移動(ベクトルを加算)
	velocity_ = {0, 0, kCharacterSpeed}; // 敵の移動速度


	// デスフラグの立った弾を削除
	bullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});


	for (EnemyBullet* bullet : bullets_) {
		bullet->Update();
	}

	switch ( phease_) 
	{
	case Phease::Approach:
	default:
		
		Approach();

		break;


	case Phease::Leave:
		
		Leave();

		break;

	}
}



/// <summary>
/// 攻撃
/// </summary>
void Enemy::Fire() {

	// 弾の速度
	const float kBulletSpeed = 1.5f;
	Vector3 velocity(0, 0, kBulletSpeed);

	// 速度ベクトルを自機の向きに合わせて回転させる
	velocity = TransformNormal(velocity, worldTransform_.matWorld_);

	// 弾を生成し、初期化
	EnemyBullet* newBullet = new EnemyBullet();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity_);

	bullets_.push_back(newBullet);
}



/// <summary>
/// 行動フェーズ : 接近
/// </summary>
void Enemy::Approach() {

	// 座標を移動させる(1フレーム分の移動量を足しこむ)
	worldTransform_.translation_ = Subtract(worldTransform_.translation_, velocity_);

	
	// 発射タイマーカウントダウン
	fireTimer_--;

	// 指定時間に達した
	if (fireTimer_ <= 0) {

		// 弾を発射
		Fire();

		// 発射タイマーを初期化
		fireTimer_ = kFireInterval_;
	}
	

	// 規定の位置に到達し
	if (worldTransform_.translation_.z < -30.0f) {

		// 行動フェーズを離脱へ
		phease_ = Phease::Leave;
	}
}



/// <summary>
/// 接近フェーズ初期化
/// </summary>
void Enemy::ApproachIni() {

	
}



/// <summary>
/// 行動フェーズ : 離脱
/// </summary>
void Enemy::Leave() {

	// 座標を移動させる(1フレーム分の移動量を足しこむ)
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);

	// 規定の位置に到達したら離脱
	if (worldTransform_.translation_.z > 30.0f) {
		phease_ = Phease::Approach;
	}
}



/// <summary>
/// 描画処理
/// </summary>
void Enemy::Draw(ViewProjection viewProjection) {

	model_->Draw(worldTransform_, viewProjection, textureHandle_);


	for (EnemyBullet* bullet : bullets_) {
	bullet->Draw(viewProjection);	
	}

}


