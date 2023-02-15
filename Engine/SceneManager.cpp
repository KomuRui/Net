#include "sceneManager.h"
#include "Model.h"
#include "Image.h"
#include "Audio.h"
#include "Light.h"
#include "../Scene/TitleScene/TitleScene.h"
#include "../Scene/PlayScene/PlayScene.h"
#include "GameManager.h"

//�R���X�g���N�^
SceneManager::SceneManager(GameObject * parent)
	: GameObject(parent, "SceneManager")
{
}

//������
void SceneManager::Initialize()
{
	//�ŏ��̃V�[��������
	currentSceneID_ = SCENE_ID_TITLE;
	nextSceneID_ = currentSceneID_;
	Instantiate<TitleScene>(this);
}

//�X�V
void SceneManager::Update()
{
	//���̃V�[�������݂̃V�[���ƈႤ�@���@�V�[����؂�ւ��Ȃ���΂Ȃ�Ȃ�
	if (currentSceneID_ != nextSceneID_)
	{
		//���̃V�[���̃I�u�W�F�N�g��S�폜
		KillAllChildren();

		//���[�h�����f�[�^��S�폜
		Audio::AllRelease();
		Model::AllRelease();
		Image::AllRelease();

		//���C�g����������Ԃɂ��Ă���
		Light::Initialize();
		GameManager::SceneChangeInitialize();

		//���̃V�[�����쐬
		switch (nextSceneID_)
		{
		case SCENE_ID_TITLE: Instantiate<TitleScene>(this); break;
		case SCENE_ID_PLAY:	 Instantiate<PlayScene>(this); break;
		}
		currentSceneID_ = nextSceneID_;
	}

}

//�`��
void SceneManager::Draw()
{
}

//�J��
void SceneManager::Release()
{
}

void SceneManager::StartUpdate()
{
}

//�V�[���؂�ւ��i���ۂɐ؂�ւ��̂͂��̎��̃t���[���j
void SceneManager::ChangeScene(SCENE_ID next)
{
	nextSceneID_ = next;

}