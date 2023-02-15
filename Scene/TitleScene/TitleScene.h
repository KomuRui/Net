#pragma once

#include "../../Engine/GameObject.h"
#include "../../Engine/Fade.h"
#include "../../Button.h"



//�����V�[�����Ǘ�����N���X
class TitleScene : public GameObject
{
	enum TitleImages
	{
		TITLE = 0,
		START,
		MAX_SIZE_TITLEIMAGE
	};

	int hPict_[MAX_SIZE_TITLEIMAGE];    //�摜�ԍ�

	Fade* pfade_;				        //�t�F�[�h�p
	char IP_[20];
	int count_;

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	TitleScene(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void StartUpdate() override;
	void IPSetDraw(char* ip);
};

