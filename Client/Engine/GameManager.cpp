#include "GameManager.h"
#include "Text.h"

namespace GameManager
{
	//���ݎg�p����Ă���v���C���[�̃|�C���^�i�[�p
	Player* pNowPlayer_;

	//���݂̎g�p����Ă���X�e�[�W�̃|�C���^�i�[�p
	Stage* pNowStage_;

	//�Q���v���C���[��ID�ƃN���X�������Ă�
	std::vector<std::pair<int, Enemy*>> enemy_;

	//ID
	int iD_;
	
	std::string ipadd_;
	//����
	Text* text_;

	//������
	void GameManager::Initialize()
	{
		iD_ = 0;
		text_ = new Text;
		ipadd_ = "";
		text_->Initialize();
	}

	//����[��
	void SceneChangeInitialize()
	{
		text_ = new Text;
		text_->Initialize();
	}

	//�`��
	void GameManager::Draw()
	{
		Direct3D::SetShader(Direct3D::SHADER_3D);
		Direct3D::SetBlendMode(Direct3D::BLEND_DEFAULT);

		if (iD_ != 0)
			text_->Draw(1600, 850, iD_, 2);
	}

	//�v���C���[�̃|�C���^�Z�b�g
	void GameManager::SetpPlayer(Player* player) { pNowPlayer_ = player; }

	//�v���C���[�̃|�C���^�Q�b�g
	Player* GameManager::GetpPlayer() { return pNowPlayer_; }

	//�X�e�[�W�̃|�C���^�Z�b�g
	void GameManager::SetpStage(Stage* stage) { pNowStage_ = stage; }

	//�X�e�[�W�̃|�C���^�Q�b�g
	Stage* GameManager::GetpStage() { return pNowStage_; }

	//ID�Z�b�g
	void GameManager::SetId(int num) { iD_ = num; };

	//ID�Q�b�g
	int GameManager::GetId() { return iD_; }

	void SetIP(std::string ipadd) {
		ipadd_ = ipadd;
	}
	std::string GetIP() { return ipadd_; }

	//�G�Z�b�g
	void GameManager::SetEnemy(std::pair<int, Enemy*> a) { enemy_.push_back(a); }

	//�Q���v���C���[�������Ă�vector�Q�b�g
	std::vector<std::pair<int, Enemy*>> GameManager::GetEnemyVec() { return enemy_; }
}