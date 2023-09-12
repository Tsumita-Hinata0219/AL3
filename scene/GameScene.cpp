#include "GameScene.h"
#include "AxisIndicator.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {

}

GameScene::~GameScene() {

	delete model_;

	// 自キャラの解放
	delete player_;
	// 自弾リストの解放
	for (PlayerBullet* playerBullet : playerBullets_) {
		delete playerBullet;
	}

	// 敵キャラの解放
	for (Enemy* enemy : enemys_) {
		delete enemy;
	}
	// 敵弾リストの解放
	for (EnemyNormalBullet* enemyBullet : enemyNormalBullets_) {
		delete enemyBullet;
	}
	for (EnemyChaseBullet* enemyBullet : enemyChaseBullets_) {
		delete enemyBullet;
	}

	// 天球の解放
	delete modelSkydome_;
	delete skydome_;

	// 地面の解放
	delete modelGround_;
	delete ground_;

	// レールカメラの解放
	delete railCamera_;
	// デバッグカメラの解放
	delete debugCamera_;

	// コライダー
	delete collisionnManager_;
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



	// サウンド
	sound_.game = audio_->LoadWave("/sound/game.wav");
	sound_.clear = audio_->LoadWave("/sound/clear.wav");
	sound_.over = audio_->LoadWave("/sound/over.wav");
	sound_.boss = audio_->LoadWave("/sound/boss.wav");
	sound_.decision = audio_->LoadWave("/sound/decision.wav");
	sound_.eneDie = audio_->LoadWave("/sound/enemydead.wav");
	sound_.plaDamage = audio_->LoadWave("/sound/playerdamage.wav");
	sound_.plaDie = audio_->LoadWave("/sound/playerdead.wav");
	sound_.shoot1 = audio_->LoadWave("/sound/shoot2.wav");

	gameBGMHandle_ = audio_->PlayWave(sound_.game, true);


	scene_ = TITLE;

	// Sprite
	titleTextureHandle_ = TextureManager::Load("/picture/title.png");
	clearTextureHandle_ = TextureManager::Load("/picture/Clear.png");
	overTextureHandle_ = TextureManager::Load("/picture/GameOver.png");
	pushATextureHandle_ = TextureManager::Load("/picture/pushA.png");
	pushBTextureHandle_ = TextureManager::Load("/picture/pushB.png");
	titleSprite_ = Sprite::Create(titleTextureHandle_, {0.0f, 0.0f});
	clearSprite_ = Sprite::Create(clearTextureHandle_, {0.0f, 0.0f});
	overSprite_ = Sprite::Create(overTextureHandle_, {0.0f, 0.0f});
	pushASprite_ = Sprite::Create(pushATextureHandle_, {448.0f, 473.0f});
	pushBSprite_ = Sprite::Create(pushBTextureHandle_, {448.0f, 473.0f});


	/* ----- キャラクターの生成・初期化 ----- */

	/* ----- Player 自キャラ ----- */

	player_ = new Player();
	Vector3 playerPosition(0.0f, -5.0f, 20.0f);
	player_->Initialize(model_, playerPosition, sound_);
	// 自キャラにゲームシーンを渡す
	player_->SetGameScene(this);


	/* ----- Enemy 敵キャラ ----- */

	enemy_ = new Enemy();
	Vector3 enemyPosition(20.0f, 2.0f, 50.0f);
	enemy_->Initialize(model_, enemyPosition, sound_);
	// 敵キャラにゲームシーンを渡す
	enemy_->SetGameScene(this);
	// 敵キャラに自キャラのアドレスを渡す
	enemy_->SetPlayer(player_);
	// 敵を登録する
	enemys_.push_back(enemy_);
	// 敵発生スクリプトの読み込み
	LoadEnemyPopDate();


	/* ----- Skydome 天球 ----- */

	modelSkydome_ = Model::CreateFromOBJ("Skydome", true);
	skydome_ = new Skydome();
	skydome_->Initialize(modelSkydome_);


	/* ----- Ground 地面 ----- */

	modelGround_ = Model::CreateFromOBJ("Ground", true);
	ground_ = new Ground();
	ground_->Initialize(modelGround_);


	/* ----- RailCamera レールカメラ ----- */

	Vector3 rotation = {0.0f, 0.0f, 0.0f};
	railCamera_ = new RailCamera();
	railCamera_->Initialize(player_->GetWorldPosition(), rotation);

	// 親子関係を結ぶ
	// 自キャラとレールカメラの親子関係を結ぶ
	player_->SetParent(&railCamera_->GetWorldTransform());


	/* ----- Collider コライダー ----- */
	collisionnManager_ = new CollisionManager;


	// デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);

	// 軸方向表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	// 軸方向表示が参照するビュープロジェクションを指定する(アドレス渡し)
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
}

void GameScene::Update() {

	// サウンドのループBGM

	switch (scene_) {

		case TITLE:

			if (!Input::GetInstance()->GetJoystickState(0, joyState_)) {
				return;
			}
		    if (joyState_.Gamepad.wButtons & XINPUT_GAMEPAD_A) {

				audio_->PauseWave(sound_.decision);
			    scene_ = GAME;
			}

			break;


		case GAME:

	/* ----- Player 自キャラ ----- */

		    // 自キャラの更新処理
		    player_->Update(viewProjection_);

		    // 自弾の更新処理
		    for (PlayerBullet* playerBullet : playerBullets_) {
			    playerBullet->Update();
		    }

		    // デスフラグの立った弾を削除
		    playerBullets_.remove_if([](PlayerBullet* bullet) {
			    if (bullet->IsDead()) {
				    delete bullet;
				    return true;
			    }
			    return false;
		    });

		    /* ----- Enemy 敵キャラ ----- */

		    // 敵キャラの更新処理
		    for (Enemy* enemy : enemys_) {
			    enemy->Update();
		    }
		    // 敵発生スクリプトの実行
		    UpdateEnemyPopCommands();

		    // 敵弾の更新処理
		    for (EnemyNormalBullet* enemyBullet : enemyNormalBullets_) {
			    enemyBullet->Update();
		    }
		    for (EnemyChaseBullet* enemyBullet : enemyChaseBullets_) {
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
		    enemyNormalBullets_.remove_if([](EnemyNormalBullet* bullet) {
			    if (bullet->IsDead()) {
				    delete bullet;
				    return true;
			    }
			    return false;
		    });
		    enemyChaseBullets_.remove_if([](EnemyChaseBullet* bullet) {
			    if (bullet->IsDead()) {
				    delete bullet;
				    return true;
			    }
			    return false;
		    });

		    /* ----- Skydome 天球 ----- */

		    // 天球の更新処理
		    skydome_->Update();

			// 地面の更新処理
		    ground_->Update();

		    // 衝突判定処理
		    CheckAllCollision();


			if (!Input::GetInstance()->GetJoystickState(0, joyState_)) {
			    return;
		    }
		    if (joyState_.Gamepad.wButtons & XINPUT_GAMEPAD_Y) {

			    audio_->PauseWave(sound_.decision);
			    scene_ = CLEARRESULT;
		    }
		    if (joyState_.Gamepad.wButtons & XINPUT_GAMEPAD_X) {

			    audio_->PauseWave(sound_.decision);
			    scene_ = OVERRESULT;
		    }

			break;


		case CLEARRESULT:

			if (!Input::GetInstance()->GetJoystickState(0, joyState_)) {
			    return;
		    }
		    if (joyState_.Gamepad.wButtons & XINPUT_GAMEPAD_B) {

			    audio_->PauseWave(sound_.decision);
			    audio_->StopWave(gameBGMHandle_);
			    Initialize();
			    scene_ = TITLE;
		    }

			break;


		case OVERRESULT:

			if (!Input::GetInstance()->GetJoystickState(0, joyState_)) {
			    return;
		    }
		    if (joyState_.Gamepad.wButtons & XINPUT_GAMEPAD_B) {

			    audio_->PauseWave(sound_.decision);
			    audio_->StopWave(gameBGMHandle_);
			    Initialize();
			    scene_ = TITLE;
		    }

			break;
	}


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

	collisionnManager_->ColliderClear();

	// コライダー
	std::list<Collider*> colliders_;

	// コライダーをリストに登録
	// 自キャラ
	collisionnManager_->ColliderPushBack(player_);

	// 自弾
	for (PlayerBullet* bullet : playerBullets_) {
		collisionnManager_->ColliderPushBack(bullet);
	}

	// 敵キャラ
	for (Enemy* enemy : enemys_) {
		collisionnManager_->ColliderPushBack(enemy);
	}

	// 敵弾
	for (EnemyNormalBullet* bullet : enemyNormalBullets_) {
		collisionnManager_->ColliderPushBack(bullet);
	}
	for (EnemyChaseBullet* bullet : enemyChaseBullets_) {
		collisionnManager_->ColliderPushBack(bullet);
	}

	collisionnManager_->CheckAllCollision();
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

	switch (scene_) {

	case TITLE:
		drawScene_.Title(titleSprite_);
		pushASprite_->Draw();
		break;

	case CLEARRESULT:
		drawScene_.CLEAR(clearSprite_);
		pushBSprite_->Draw();
		break;

	case OVERRESULT:
		drawScene_.Over(overSprite_);
		pushBSprite_->Draw();
		break;
	}




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

	switch (scene_) {

		case TITLE:

			break;


		case GAME:

			/* ----- Player 自キャラ ----- */

		    // 自キャラの描画
		    player_->Draw3D(viewProjection_);

		    // 自弾リストの描画処理
		    for (PlayerBullet* playerBullet : playerBullets_) {
			playerBullet->Draw(viewProjection_);
		    }

		    /* ----- Enemy 敵キャラ ----- */

		    // 敵キャラの描画処理
		    for (Enemy* enemy : enemys_) {
			enemy->Draw(viewProjection_);
		    }
		    // 敵弾リストの描画処理処理
		    for (EnemyNormalBullet* enemyBullet : enemyNormalBullets_) {
			enemyBullet->Draw(viewProjection_);
		    }
		    for (EnemyChaseBullet* enemyBullet : enemyChaseBullets_) {
			enemyBullet->Draw(viewProjection_);
		    }

		    /* ----- Skydome 天球 ----- */

		    // 天球の描画処理
		    skydome_->Draw(viewProjection_);


		    /* ----- Ground 地面 ----- */

			// 地面の描画処理
		    ground_->Draw(viewProjection_);

			break;
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	switch (scene_) {
	case GAME:

		/* ----- Player 自キャラ ----- */

		player_->DrawUI();

		break;
	}

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

// ゲームシーンに弾を登録する
void GameScene::AddPlayerBullet(PlayerBullet* playerBullet) {

	// リストに登録する
	playerBullets_.push_back(playerBullet);
}

void GameScene::AddEnemyNormalBullet(EnemyNormalBullet* enemyBullet) {

	// リストに登録する
	enemyNormalBullets_.push_back(enemyBullet);
}

void GameScene::AddEnemyChaseBullet(EnemyChaseBullet* enemyBullet) {

	// リストに登録する
	enemyChaseBullets_.push_back(enemyBullet);
}

void GameScene::LoadEnemyPopDate() {

	// ファイルを開く
	std::ifstream file;
	file.open("Resources/parameter/enemyPop.csv");
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
	enemy_->Initialize(model_, pos, sound_);
	// 敵キャラにゲームシーンを渡す
	enemy_->SetGameScene(this);
	// 敵キャラに自キャラのアドレスを渡す
	enemy_->SetPlayer(player_);
	// 敵を登録する
	enemys_.push_back(enemy_);
}


