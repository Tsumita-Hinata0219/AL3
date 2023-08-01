#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

#include "Player.h"
#include "DebugCamera.h"
#include "Enemy.h"
#include "Skydome.h"
#include "RailCamera.h"


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
	/// 敵弾を追加する
	/// </summary>
	/// <param name="enemyBullet">敵弾</param>
	void AddEnemyBullet(EnemyBullet* enemyBullet);


	// 弾リストを取得
	const std::list<EnemyBullet*>& GetEnemyBullet() { return enemyBullets_; };


private: // メンバ変数

	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;


	// テクスチャハンドル
	uint32_t textureHandle_ = 0;


	// 3Dモデル
	Model* model_ = nullptr;

	// ビュープロジェクション
	ViewProjection viewProjection_;

	// 自キャラ
	Player* player_ = nullptr;

	// 敵キャラ
	Enemy* enemy_ = nullptr;
	EnemyBullet* enemyBullet_ = nullptr;
	// 敵弾リストをEnemyからGameSceneに引っ越す
	std::list<EnemyBullet*> enemyBullets_;
	

	// 天球
	Skydome* skydome_ = nullptr;
	Model* modelSkydome_ = nullptr;

	// レールカメラ
	RailCamera* railCamera_ = nullptr;


	// デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;

	// デバッグカメラ有効
	bool isDebugCameraActive_ = false;


	/// <summary>
	/// ゲームシーン用
	/// </summary>
};


