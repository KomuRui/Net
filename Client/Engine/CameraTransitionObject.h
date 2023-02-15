#pragma once
#include "GameObject.h"
#include "ImGuiSet.h"

//�e�X�e�[�W�ŏꏊ���ƂɃJ�����J�ڂ��邽�߂ɕK�v�ȃI�u�W�F�N�g
class CameraTransitionObject : public GameObject
{
private:

	StageCameraTransition info;

public:

	//�R���X�g���N�^
	CameraTransitionObject(GameObject* parent, const StageCameraTransition& camInfo);

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

	//�����蔻��
	void OnCollision(GameObject* pTarget) override;
};

