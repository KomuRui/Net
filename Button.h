#pragma once
#include "Engine/GameObject.h"
#include "Engine/Fade.h"

//�����V�[�����Ǘ�����N���X
class Button : public GameObject
{
protected:

	//�摜�ԍ�
	int hPict_;

	//�t�@�C����
	std::string fileNamePas;

	//���I������Ă��邩
	bool controllerSelect;

	//�t�F�[�h����̂ɕK�v�Ȃ��
	Fade* pfadeButton;

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Button(GameObject* parent);
	Button(GameObject* parent, std::string name);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void StartUpdate() override;

	//�{�^���������ꂽ�牽���邩
	virtual void IsButtonPush() = 0;

	//�{�^�����I������Ă���Ƃ��������邩
	//�f�t�H���g�F�t�F�[�h�C���A�E�g���J��Ԃ�(�p�������Ƃ���override����Β��g�ς����)
	virtual void IsButtonSelect();

	//�I������Ă��邩���Z�b�g
	void SetSelect(const bool& flag) { controllerSelect = flag; }

	//�I������Ă��邩���m�F
	bool GetSelect() { return controllerSelect; }
};