#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include <sstream>
#include <fstream>
#include <string>

#include "Player.h"
#include "PlayerBullet.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "DebugCamera.h"
#include "Skydome.h"
#include "RailCamera.h"
#include "Collider.h"


/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 衝突判定と応答
	/// </summary>
	void CheckAllCollision();

	/// <summary>
	/// 自弾を追加する
	/// </summary>
	/// <param name="playerBullet">自弾</param>
	void AddPlayerBullet(PlayerBullet* playerBullet);

	/// <summary>
	/// 敵弾を追加する
	/// </summary>
	/// <param name="enemyBullet">敵弾</param>
	void AddEnemyBullet(EnemyBullet* enemyBullet);

	/// <summary>
	/// 敵発生データの読み込み
	/// </summary>
	void LoadEnemyPopDate();

	/// <summary>
	/// スクリプト実行
	/// </summary>
	void UpdateEnemyPopCommands();

	void generatedEnemy(Vector3 pos);



private:

	/// <summary>
	/// コライダー2つの衝突判定と応答
	/// </summary>
	void CheckCollisionPair(Collider* colliderA, Collider* colliderB);


private: // メンバ変数

	/* ----- テクスチャハンドル ----- */

	uint32_t playerTextureHandle_ = 0;
	uint32_t playerBulletTextureHandle_ = 0;
	uint32_t playerReticleTextureHandle_ = 0;

	uint32_t enemyTextureHandle_ = 0;
	uint32_t enemyBulletTextureHandle_ = 0;



	/* ----- Player 自キャラ ----- */

	// 自キャラ
	Player* player_ = nullptr;

	// 自弾
	PlayerBullet* playerBullet_ = nullptr;
	std::list<PlayerBullet*> playerBullets_;



	/* ----- Enemy 敵キャラ ----- */

	// 敵キャラ
	Enemy* enemy_ = nullptr;
	// 敵リスト
	std::list<Enemy*> enemys_;
	// 敵発生コマンド
	std::stringstream enemyPopCommands;
	// 待機フラグ
	bool isEnemyStay = false;
	// 待機タイマー
	uint32_t enemyStayTimer = 0;

	// 敵弾
	EnemyBullet* enemyBullet_ = nullptr;
	// 敵弾リスト
	std::list<EnemyBullet*> enemyBullets_;



	/* ----- SkyDome 天球 ----- */

	// 天球
	Skydome* skydome_ = nullptr;
	Model* modelSkydome_ = nullptr;



	/* ----- Camera カメラ ----- */

	// レールカメラ
	RailCamera* railCamera_ = nullptr;

	// デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;
	// デバッグカメラ有効
	bool isDebugCameraActive_ = false;

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;



	// 3Dモデル
	Model* model_ = nullptr;

	// ビュープロジェクション
	ViewProjection viewProjection_;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};


