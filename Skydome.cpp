#include "Skydome.h"



// ����������
void Skydome::Initialize() {

}

// �X�V����
void Skydome::Update() {

}


// �`�揈��
void Skydome::Draw(ViewProjection viewProjection) {

	// 3D���f���̕`��
	model_->Draw(worldTransform_, viewProjection);
}
