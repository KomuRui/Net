#pragma once
#include "../Stage.h"
#include "../Player.h"
#include "../Enemy.h"

//�Q�[���̂��낢��ȊǗ�������
namespace GameManager
{

	//������
	void Initialize();

	//����[��
	void SceneChangeInitialize();

	//�`��
	void Draw();

	//�v���C���[�̃|�C���^�Z�b�g
	void SetpPlayer(Player* player);

	//�v���C���[�̃|�C���^�Q�b�g
	Player* GetpPlayer();

	//�X�e�[�W�̃|�C���^�Z�b�g
	void SetpStage(Stage* stage);

	//�X�e�[�W�̃|�C���^�Q�b�g
	Stage* GetpStage();

	//ID�Z�b�g
	void SetId(int num);

	//ID�Q�b�g
	int GetId();

	void SetIP(std::string ipadd);
	std::string GetIP();

	//�G�Z�b�g
	void SetEnemy(std::pair<int, Enemy*> a);

	//�Q���v���C���[�������Ă�vector�Q�b�g
	std::vector<std::pair<int, Enemy*>>  GetEnemyVec();
};

