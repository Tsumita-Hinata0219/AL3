#pragma once
#include "Model.h"
#include "WorldTransform.h"



/// <summary>
/// �V��
/// </summary>
class Skydome {
public:

	/// <summary>
	/// ����������
	/// </summary>
	void Initialize();


	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();


	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw(ViewProjection viewProjection);


private:

	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;

	// ���f��
	Model* model_ = nullptr;

};