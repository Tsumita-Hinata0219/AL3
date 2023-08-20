#pragma once

#include <Model.h>
#include <WorldTransform.h>
#include <Input.h>
#include <ImGuiManager.h>
#include <Function.h>
#include <PlayerBullet.h>
#include <list>
#include <Sprite.h>
#include "Collider.h"



// gameSceneの前方宣言
class GameScene;



/// <summary>
/// 自キャラ
/// </summary>
class Player : public Collider {

public:


	/// <summary>
	/// コンストラクタ
	/// </summary>
	Player();


	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();

	
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, Vector3 position);


	/// <summary>
	/// 更新処理
	/// </summary>
	void Update(ViewProjection viewProjection);


	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name = "viewProjection">ビュープロジェクション (参照渡し) </pram>
	void Draw3D(ViewProjection viewProjection);

	/// <summary>
	/// UI描画
	/// </summary>
	void DrawUI();

	/// <summary>
	/// 旋回(回転)
	/// </summary>
	void Rotate();
		

	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack();


	/// <summary>
	/// 3Dレティクルの更新処理
	/// </summary>
	void ReticleUpdate(ViewProjection viewProjection);

	/// <summary>
	/// 自キャラの移動処理
	/// </summary>
	void PlayerMove();

	/// <summary>
	/// レティクルの移動処理
	/// </summary>
	void ReticleMove();

	
	/// <summary>
	/// 衝突を検出したら呼び出されるコールバッグ関数
	/// </summary>
	void onCollision() override;


	/// <summary>
	/// ワールド座標を取得
	/// </summary>
	Vector3 GetWorldPosition() override;



	Vector3 GetReticleWorldPosition();

	WorldTransform GetWorldTransform() { return worldTransform_; }

	// 半径を取得
	float GetRadius() { return radius_; };

	// 弾リストを取得
	const std::list<PlayerBullet*>& GetBullet() { return bullets_; };


	/// <summary>
	/// 親となるワールドトランスフォームをセット
	/// </summary>
	/// <param name="parent"></param>
	void SetParent(const WorldTransform* parent);


	PlayerBullet* GetPlayerBullet() { return playerBullet_; };

	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }


	/*void SetTextureHandle(uint32_t playerTexture, uint32_t reticleTextuer) {
		playerTextureHandle_ = playerTexture;
		ReticleTextureHandle_ = reticleTextuer;
	}*/


private:

	// ゲームシーン
	GameScene* gameScene_ = nullptr;

	WorldTransform worldTransform_; // ワールド変換データ

	Model* model_ = nullptr; // モデル

	uint32_t playerTextureHandle_ = 0u; // テクスチャハンドル

	Input* input_ = nullptr; // キーボード入力

	PlayerBullet* playerBullet_ = nullptr;

	std::list<PlayerBullet*> bullets_; // 弾

	// 弾の速度
	const float kBulletSpeed_ = 5.0f;
	Vector3 velocity_ = {0.0f, 0.0f, 0.0f};

	int32_t fireTimer_ = 0; // 発射タイマー

	static const int IniFireTimer = 3;
	static const int kFireInterval_ = 7; // 発射間隔の設定

	const float radius_ = 2.0f; // 半径



	/* ----- 3DReticle 3Dレティクル ----- */

	// テクスチャハンドル
	uint32_t ReticleTextureHandle_ = 0u;


	// 3Dレティクル用ワールドトランスフォーム
	WorldTransform worldTransform3DReticle_;

	// 自機から3Dレティクルへの距離
	const float kDistancePlayerTo3DReticle = 70.0f;

	// 自機から3Dレティクルへのオフセット(Z+向き)
	Vector3 offset = {0.0f, 0.0f, 1.0f};

	// マウス例の方向
	Vector3 mouseDirection_;

	// カメラから照準オブジェクトの距離
	const float kDistanceTestObject = 100.0f;



	/* ----- 2DReticle 2Dレティクル ----- */

	// スプライト生成
	Sprite* sprite2DReticle_ = nullptr;

	// レティクルの2D座標
	Vector3 position2DReticle_;

	// ビューポート行列
	Matrix4x4 matViewport_;

	// ビュー行列とプロジェクション行列
	Matrix4x4 matViewProjectionViewport_;

	// ビュープロジェクションビューポート合成行列
	Matrix4x4 matVPV_;

	// 合成行列の逆行列
	Matrix4x4 matInverseVPV_;

	// スクリーン座標
	Vector3 posNear_;
	Vector3 posFar_;

	// スプライトの座標取得用
	Vector2 spritePosition_;


	/* ----- Mouse マウス ----- */

	// マウス座標
	POINT mousePosition_;

	HWND hwnd = nullptr;


	/* ----- GamePad ゲームパッド ----- */

	// ゲームパッドの状態を得る変数(XINPUT)
	XINPUT_STATE joyState_;


};

