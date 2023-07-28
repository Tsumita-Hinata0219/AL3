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
	void Initialize(Vector3 transkation, Vector3 rotation);


	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();


	/// <summary>
	/// ビュープロジェクションの取得関数
	/// </summary>
	ViewProjection& GetViewProjection() { return viewProjection_; }


	/// <summary>
	/// ワールド変換データを取得
	/// </summary>
	WorldTransform& GetWorldTransform()  { return worldTransform_; };



private:

	// ワールド変換データ
	WorldTransform worldTransform_;

	// ビュープロジェクション
	ViewProjection viewProjection_;


};