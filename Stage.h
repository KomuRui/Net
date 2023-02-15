#pragma once
#include "Engine/GameObject.h"
#include <vector>

//�e�X�e�[�W�N���X�̂��ƂƂȂ�N���X
class Stage : public GameObject
{
private:
	int hModel_;
public:

	//�R���X�g���N�^
	Stage(GameObject* parent);
	~Stage();
	/////////////////////�I�[�o�[���C�h����֐�//////////////////////

	//������
	void Initialize() override;

	//�X�V�̑O�Ɉ��Ă΂��֐�
	void StartUpdate() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//���f���ԍ��擾
	int GetModelHandle() { return hModel_; }

	//�J��
	void Release() override;

};

