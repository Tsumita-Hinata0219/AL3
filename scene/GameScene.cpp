#include "GameScene.h"
#include "AxisIndicator.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {

	delete model_;

	// 自キャラの解放
	delete player_;

	// 敵キャラの解放
	for (Enemy* enemy : enemys_) {
		delete enemy;
	}
	// 敵弾リストの解放
	for (EnemyBullet* enemyBullet : enemyBullets_) {
		delete enemyBullet;
	}

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
	viewProjection_.farZ = 1000.0f;
	viewProjection_.Initialize();



	/* ----- キャラクターの生成・初期化 ----- */

	// Player
	player_ = new Player();
	Vector3 playerPosition(0.0f, -5.0f, 20.0f);
	player_->Initialize(model_, playerPosition);

	
	// Enemy
	enemy_ = new Enemy();
	Vector3 enemyPosition(20.0f, 2.0f, 50.0f);
	enemy_->Initialize(model_, enemyPosition);
	// 敵キャラにゲームシーンを渡す
	enemy_->SetGameScene(this);
	// 敵キャラに自キャラのアドレスを渡す
	enemy_->SetPlayer(player_);
	// 敵を登録する
	enemys_.push_back(enemy_);
	// 敵発生スクリプトの読み込み
	LoadEnemyPopDate();

	// Skydome
	modelSkydome_ = Model::CreateFromOBJ("Skydome", true);
	skydome_ = new Skydome();
	skydome_->Initialize(modelSkydome_);


	// RailCamera
	Vector3 rotation = {0.0f, 0.0f, 0.0f};
	railCamera_ = new RailCamera();
	railCamera_->Initialize(player_->GetWorldPosition(), rotation);

	// 親子関係を結ぶ
	// 自キャラとレールカメラの親子関係を結ぶ
	player_->SetParent(&railCamera_->GetWorldTransform());

	// デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);

	// 軸方向表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
}

void GameScene::Update() {

	/* ----- Player 自キャラ ----- */

	// 自キャラの更新
	player_->Update();



	/* ----- Enemy 敵キャラ ----- */

	// 敵キャラの更新処理
	for (Enemy* enemy : enemys_) {
		enemy->Update();
	}
	// 敵発生スクリプトの実行
	UpdateEnemyPopCommands();

	// 敵弾の更新処理
	for (EnemyBullet* enemyBullet : enemyBullets_) {
		enemyBullet->Update();
	}

	// デスフラグの立った敵を削除
	enemys_.remove_if([](Enemy* enemy) {
		if (enemy->IsDead()) {
			delete enemy;
			return true;
		}
		return false;
	});
	
	// デスフラグの立った弾を削除
	enemyBullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});




	/* ----- SkyDome 天球 ----- */

	// 天球の更新処理
	skydome_->Update();



	// 衝突判定処理
	CheckAllCollision();



	/* ----- Camera カメラ ----- */

#ifdef _DEBUG

	if (input_->TriggerKey(DIK_RETURN)) {
		if (isDebugCameraActive_ == false) {
			isDebugCameraActive_ = true;
		} else {
			isDebugCameraActive_ = false;
		}
	}

#endif // DEBUG

	// カメラの処理
	if (isDebugCameraActive_) {

		// デバッグカメラの更新
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;

		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	} else {
		railCamera_->Update();
		viewProjection_.matView = railCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = railCamera_->GetViewProjection().matProjection;

		// ビュープロジェクション行列の
		viewProjection_.TransferMatrix();
	}
}

void GameScene::CheckAllCollision() {

	// 判定対象AとBの座標
	Vector3 posA, posB;

	// 自弾リストの取得
	const std::list<PlayerBullet*>& playerBullets = player_->GetBullet();


#pragma region 自キャラと敵弾の当たり判定

	// 自キャラの座標
	posA = player_->GetWorldPosition();

	// 自キャラと敵弾のすべての当たり判定
	for (EnemyBullet* enemyBullet : enemyBullets_) {
		// 敵弾の座標
		posB = enemyBullet->GetWorldPosition();

		// 座標Aと座標Bの距離を求める
		float distAB = ClacDistance(posA, posB);

		float radiusAB = (player_->GetRadius() + enemyBullet->GetRadius());

		// 球と球の交差判定
		if (distAB <= radiusAB) {

			// 自キャラの衝突時コールバックを呼び出す
			player_->onCollision();

			// 敵弾の衝突時コールバックを呼び出す
			enemyBullet->onCollision();
		}
	}

#pragma endregion

#pragma region 自弾と敵キャラの当たり判定

	// 敵キャラと自弾のすべての当たり判定
	for (PlayerBullet* bullet : playerBullets) {
		for (Enemy* enemy : enemys_) {

			// 自弾の座標
			posA = bullet->GetWorldPosition();
			// 敵キャラの座標
			posB = enemy->GetWorldPosition();

			// 座標Aと座標Bの距離を求める
			float distAB = ClacDistance(posA, posB);

			float radiusAB = (enemy->GetRadius() + bullet->GetRadius());

			// 球と球の交差判定
			if (distAB <= radiusAB) {

				// 自弾の衝突判定時コールバックを呼び出す
				bullet->onCollision();

				// 敵キャラの衝突時コールバックを呼び出す
				enemy->onCollision();
			}
		}
	}

#pragma endregion

#pragma region 自弾と敵弾の当たり判定

	// 自キャラと敵弾のすべての当たり判定
	for (PlayerBullet* plaBullet : playerBullets) {
		for (EnemyBullet* enemyBullet : enemyBullets_) {

			// 自弾の座標
			posA = plaBullet->GetWorldPosition();

			// 敵弾の座標
			posB = enemyBullet->GetWorldPosition();

			// 座標Aと座標Bを求める
			float distAB = ClacDistance(posA, posB);

			float radiusAB = (plaBullet->GetRadius() + enemyBullet->GetRadius());

			// 球と球の交差判定
			if (distAB <= radiusAB) {

				// 自弾の衝突時コールバックを呼び出す
				plaBullet->onCollision();

				// 敵弾の衝突時コールバックを呼び出す
				enemyBullet->onCollision();
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
	for (Enemy* enemy : enemys_) {
		enemy->Draw(viewProjection_);
	}
	// 敵弾リストの更新処理
	for (EnemyBullet* enemyBullet : enemyBullets_) {
		enemyBullet->Draw(viewProjection_);
	}

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


// ゲームシーンに弾を登録する
void GameScene::AddEnemyBullet(EnemyBullet* enemyBullet) {

	// リストに登録する
	enemyBullets_.push_back(enemyBullet);
}



void GameScene::LoadEnemyPopDate() {

	// ファイルを開く
	std::ifstream file;
	file.open("Resources/script/enemyPop.csv");
	assert(file.is_open());

	// ファイルの内容を文字列ストリームにコピー
	enemyPopCommands << file.rdbuf();

	// ファイルを閉じる
	file.close();
}

void GameScene::UpdateEnemyPopCommands() {

	// 待機処理
	if (isEnemyStay) {

		// 待機タイマーを減らす
		enemyStayTimer--;

		// 待機タイマーが0以下になったら待機終了
		if (enemyStayTimer <= 0) {

			// 待機終了
			isEnemyStay = false;
		}

		return;
	}

	// 1行分の文字列を入れる関数
	std::string line;

	// コマンド実行ループ
	while (std::getline(enemyPopCommands, line)) {

		// 1行分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);

		std::string word;
		// , 区切りで行の先頭文字列を取得
		std::getline(line_stream, word, ',');

		// "//"から始まる行はコメント
		if (word.find("//") == 0) {
			// コメント行を飛ばす
			continue;
		}

		// POPコマンド
		if (word.find("POP") == 0) {

			// X座標
			std::getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());

			// Y座標
			std::getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());

			// Z座標
			std::getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());

			// 敵を生成し、初期化
			generatedEnemy(Vector3(x, y, z));
		}

		// WAITコマンド
		else if (word.find("WAIT") == 0) {
			std::getline(line_stream, word, ',');

			// 待ち時間
			int32_t waitTime = std::atoi(word.c_str());

			// 待機開始
			isEnemyStay = true;
			enemyStayTimer = waitTime;

			break;
		}
	}
}



void GameScene::generatedEnemy(Vector3 pos) {

	enemy_ = new Enemy();
	enemy_->Initialize(model_, pos);
	// 敵キャラにゲームシーンを渡す
	enemy_->SetGameScene(this);
	// 敵キャラに自キャラのアドレスを渡す
	enemy_->SetPlayer(player_);
	// 敵を登録する
	enemys_.push_back(enemy_);
}
