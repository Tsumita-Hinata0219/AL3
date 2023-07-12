#include "Enemy.h"
#include <cassert>

#include "ImGuiManager.h"



/// <summary>
/// コンストラクタ
/// </summary>
Enemy::Enemy() { 
	state_ = new EnemyApproach(); 
}



/// <summary>
/// デストラクタ
/// </summary>
Enemy::~Enemy() { 
	delete state_; 
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
		
	this->velocity_ = velocity;

	state_ = new EnemyApproach();
}



/// <summary>
/// 更新処理
/// </summary>
void Enemy::Update() {

	state_->Update(this);

	// ワールドトラスフォームの更新
	worldTransform_.UpdateMatrix();

	// 移動(ベクトルを加算)
	velocity_ = {0, 0, kCharacterSpeed}; // 敵の移動速度
}



/// <summary>
/// 描画処理
/// </summary>
void Enemy::Draw(ViewProjection viewProjection) {

	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}



/// <summary>
/// 挙動処理
/// </summary>
// 接近
void Enemy::Approach() {
	// 座標を移動させる(1フレーム分の移動量を引く)
	worldTransform_.translation_ = Subtract(worldTransform_.translation_, velocity_);
}

// 離脱
void Enemy::Leave() {
	// 座標を移動させる(1フレーム分の移動量を足す)
	worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);

}



/// <summary>
/// 行動フェーズを変更する
/// </summary>
void Enemy::ChanegeState(EnemyState* newState) { 
	delete state_;
	this->state_ = newState;
}



/// <summary>
/// アクセッサ
/// </summary>
void Enemy::SetWorldTranslation(Vector3 translation) { worldTransform_.translation_ = translation; }




// ----- EnemyState ----- //

/// <summary>
/// EnemyApproach : 接近
/// </summary>
void EnemyApproach::Update(Enemy* pEnemy) {

	// 座標を移動させる(1フレーム分の移動量を足す)
	/*pEnemy->SetWorldTranslation(
	    Subtract(pEnemy->GetWorldTransform().translation_, pEnemy->GetVelocity()));*/
	pEnemy->Approach();

	// 規定の位置に到達したら離脱フェーズへ
	if (pEnemy->GetWorldTransform().translation_.z <= -30.0f) {
		pEnemy->ChanegeState(new EnemyLeave());
	}
}


/// <summary>
/// EnemyLeave : 離脱
/// </summary>
void EnemyLeave::Update(Enemy* pEnemy) {

	// 座標を移動させる(1フレーム分の移動量を引く)
	/*pEnemy->SetWorldTranslation(
	    Add(pEnemy->GetWorldTransform().translation_, pEnemy->GetVelocity()));*/
	pEnemy->Leave();

	// 規定の位置に到達したら接近フェーズへ
	if (pEnemy->GetWorldTransform().translation_.z >= 30.0f) {
		pEnemy->ChanegeState(new EnemyApproach());
	}
}

