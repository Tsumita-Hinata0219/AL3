#include "Enemy.h"
#include <cassert>

#include "ImGuiManager.h"



/// <summary>
/// コンストラクタ
/// </summary>
Enemy::Enemy() {

}



/// <summary>
/// デストラクタ
/// </summary>
Enemy::~Enemy() {}



/// <summary>
/// 初期化
/// </summary>
void Enemy::Initialize(Model* model) {

	// NULLポインタチェック
	assert(model);

	this->model_ = model;
	this->textureHandle_ = TextureManager::Load("/picture/Enemy.png");

	worldTransform_.Initialize();
	
}



/// <summary>
/// 更新処理
/// </summary>
void Enemy::Update() {

	
}



/// <summary>
/// 描画処理
/// </summary>
void Enemy::Draw(ViewProjection viewProjection) {

	
}


