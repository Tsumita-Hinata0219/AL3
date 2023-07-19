#include "Skydome.h"



// ‰Šú‰»ˆ—
void Skydome::Initialize() {

}

// XVˆ—
void Skydome::Update() {

}


// •`‰æˆ—
void Skydome::Draw(ViewProjection viewProjection) {

	// 3Dƒ‚ƒfƒ‹‚Ì•`‰æ
	model_->Draw(worldTransform_, viewProjection);
}
