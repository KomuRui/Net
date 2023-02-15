#include "Stage.h"
#include"Engine/Model.h"
#include "Engine/ImGuiSet.h"

//�R���X�g���N�^
Stage::Stage(GameObject* parent)
	:GameObject(parent,"Stage"),
	hModel_(-1)
{
}
//�R���X�g���N�^
Stage::~Stage()
{

}

/////////////////////�I�[�o�[���C�h����֐�//////////////////////

//������
void Stage::Initialize()
{
	//�X�e�[�W�쐬
	ImGuiSet* a = Instantiate<ImGuiSet>(this);

	hModel_ = Model::Load("Field.fbx");
	assert(hModel_ >= 0);
	transform_.scale_ = { 2.6f,2.6f,2.6f };
}

//�X�V�̑O�Ɉ��Ă΂��֐�
void Stage::StartUpdate()
{

}

//�X�V
void Stage::Update()
{

}

//�`��
void Stage::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void Stage::Release()
{

}
