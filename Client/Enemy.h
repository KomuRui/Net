#pragma once
#include "Engine/GameObject.h"

class Enemy : public GameObject
{
	//���f���ԍ�
	int hModel_;

	//��̎��̊p�x
	float angle_;

	float angleX;

	//�ł�����
	bool isShot_;

public:

	//�R���X�g���N�^
	Enemy(GameObject* parent);

	/////////////////////�I�[�o�[���C�h����֐�//////////////////////

	//������
	void Initialize() override;

	//�X�V�̑O�Ɉ��Ă΂��֐�
	void StartUpdate() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	///////////////////////////�֐�//////////////////////////////
	
	//���ł�
	void IsShot();

	//�ł����ǂ����Z�b�g
	void SetShot(bool flag) { isShot_ = flag; }

	//��̎��̊p�x�Z�b�g
	void SetAngle(float angle) { angle_ = angle; }
	void SetAngleX(float angle) { angleX = angle; }

	void PosMove(XMFLOAT3 p);
};

