#pragma once
#include <WorldTransform.h>
#include <ViewProjection.h>
#include <ImGuiManager.h>

#include "Function.h"




/// <summary>
/// レールカメラ
/// </summary>
class RailCamera {
public:

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();


	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();


	/// <summary>
	/// ビュープロジェクションの取得関数
	/// </summary>
	ViewProjection& GetViewProjection() { return viewProjection_; }


private:

	// ワールド変換データ
	WorldTransform worldTransform_;

	// ビュープロジェクション
	ViewProjection viewProjection_;


};