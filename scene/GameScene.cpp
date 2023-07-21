#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"


GameScene::GameScene() {
}

GameScene::~GameScene() {

	delete model_; 

	// 自キャラの解放
	delete player_;
	
	// 敵キャラの解放
	delete enemy_;

	// デバッグカメラの解放
	delete debugCamera_;

	// 天球の解放
	delete modelSkydome_;
	delete skydome_;

	// レールカメラの解放
	delete railCamera_;

}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();



	// 3Dモデルの生成
	model_ = Model::Create();

	// ビュープロジェクションの初期化
	viewProjection_.Initialize();



	
	/* ----- キャラクターの生成・初期化 ----- */

	// Player
	player_ = new Player();
	player_->Initialize(model_);

	
	// Enemy
	enemy_ = new Enemy();
	enemy_->Initialize(model_, enemy_->Velocity());
	// 敵キャラに自キャラのアドレスを渡す
	enemy_->SetPlayer(player_);
	

	// Skydome
	modelSkydome_ = Model::CreateFromOBJ("Skydome", true);
	skydome_ = new Skydome();
	skydome_->Initialize(modelSkydome_);


	// RailCamera
	Vector3 rotation = {0.0f, 0.0f, 0.0f};
	railCamera_ = new RailCamera();
	railCamera_->Initialize(player_->GetWorldPosition(), rotation);



	// デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);

	// 軸方向表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

}

void GameScene::Update() {

	// 自キャラの更新
	player_->Update();

	// 敵キャラの更新
	enemy_->Update();

	// 天球の更新処理
	skydome_->Update();


	// 衝突判定処理
	CheckAllCollision();


	#ifdef _DEBUG

	if (input_->TriggerKey(DIK_RETURN)) 
	{
		isDebugCameraActive_ = true;
	}

#endif // DEBUG


	// カメラの処理
	if (isDebugCameraActive_) {

		 //デバッグカメラの更新
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;

		
	}
	else {
		railCamera_->Update();
		viewProjection_.matView = railCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = railCamera_->GetViewProjection().matProjection;

		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	}
}

void GameScene::CheckAllCollision() {

	// 判定対象AとBの座標
	Vector3 posA, posB;

	// 自弾リストの取得
	const std::list<PlayerBullet*>& playerBullets = player_->GetBullet();

	// 敵弾リストの取得
	const std::list<EnemyBullet*>& enemyBullets = enemy_->GetBullet();



	#pragma region 自キャラと敵弾の当たり判定

	// 自キャラの座標
	posA = player_->GetWorldPosition();

	// 自キャラと敵弾のすべての当たり判定
	for (EnemyBullet* bullet : enemyBullets) {
		// 敵弾の座標
		posB = bullet->GetWorldPosition();

		// 座標Aと座標Bの距離を求める
		float distAB = ClacDistance(posA, posB);

		float radiusAB = (player_->GetRadius() + bullet->GetRadius());

		// 球と球の交差判定
		if (distAB <= radiusAB) {

			// 自キャラの衝突時コールバックを呼び出す
			player_->onCollision();

			// 敵弾の衝突時コールバックを呼び出す
			bullet->onCollision();
		}
	}

	#pragma endregion


	#pragma region 自弾と敵キャラの当たり判定

	// 敵キャラの座標
	posA = enemy_->GetWorldPosition();

	// 敵キャラと自弾のすべての当たり判定
	for (PlayerBullet* bullet : playerBullets) {

		// 自弾の座標
		posB = bullet->GetWorldPosition();

		// 座標Aと座標Bの距離を求める
		float distAB = ClacDistance(posA, posB);

		float radiusAB = (player_->GetRadius() + bullet->GetRadius());

		// 球と球の交差判定
		if (distAB <= radiusAB) {

			// 自弾の衝突判定時コールバックを呼び出す
			bullet->onCollision();

			// 敵キャラの衝突時コールバックを呼び出す
			enemy_->onCollision();
		}
	}

	#pragma endregion


	#pragma region 自弾と敵弾の当たり判定

	// 自キャラと敵弾のすべての当たり判定
	for (PlayerBullet* plaBullet : playerBullets) {
		for (EnemyBullet* eneBullet : enemyBullets) {

			// 自弾の座標
			posA = plaBullet->GetWorldPosition();

			// 敵弾の座標
			posB = eneBullet->GetWorldPosition();

			// 座標Aと座標Bを求める
			float distAB = ClacDistance(posA, posB);

			float radiusAB = (plaBullet->GetRadius() + eneBullet->GetRadius());

			// 球と球の交差判定
			if (distAB <= radiusAB) {

				// 自弾の衝突時コールバックを呼び出す
				plaBullet->onCollision();

				// 敵弾の衝突時コールバックを呼び出す
				eneBullet->onCollision();
			}
		}
	}

	#pragma endregion
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>


	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 自キャラの描画
	player_->Draw(viewProjection_);

	// 敵キャラの描画
	enemy_->Draw(viewProjection_);

	// 天球の描画
	skydome_->Draw(viewProjection_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

