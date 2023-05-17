#include <PlayerBullet.h>



/// <summary>
/// インストラクタ
/// </summary>
PlayerBullet::PlayerBullet() {}



/// <summary>
/// デストラクタ
/// </summary>
PlayerBullet::~PlayerBullet() {}



/// <summary>
/// 初期化
/// </summary>
void PlayerBullet::Initialize(Model* model, const Vector3& position) {

	// NULLポインタチェック
	assert(model);

	model_ = model;
	textureHandle_ = TextureManager::Load("/picture/BlackBall.png");

	worldTransform_.Initialize();

	// 引数で受け取った初期座標をリセット
	worldTransform_.translation_ = position;
}



/// <summary>
/// 更新処理
/// </summary>
void PlayerBullet::Update() {

	// ワールドトラスフォームの更新
	worldTransform_.UpdateMatrix();

}



/// <summary>
/// 描画処理
/// </summary>
void PlayerBullet::Draw(const ViewProjection& viewProjection) {

	// モデルの描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}