#pragma once
#include <functional>
#include <imgui.h>


class TimedCall {

public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	TimedCall(std::function<void()> function, uint32_t time);


	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();


	/// <summary>
	/// 完了ならtrueを返す
	/// </summary>
	bool IsFinished() { return isFinished_ = true; }

private:

	// コールバッグ
	std::function<void()> function_;

	// 残り時間
	uint32_t time_;

	// 完了フラグ
	bool isFinished_ = false;

};
