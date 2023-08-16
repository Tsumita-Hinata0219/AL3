#include "TimedCall.h"



// コンストラクタ
TimedCall::TimedCall(std::function<void()> function, uint32_t time) {

	function_ = function;
	time_ = time;
}


// 更新処理
void TimedCall::Update() {


	// 完了なら
	if (isFinished_) {
		return;
	}

	// タイマーを減らす
	time_--;

	if (time_ <= 0) {

		// フラグを立てる
		isFinished_ = true;

		// コールバッグ関数呼び出し
		function_();
	}
}