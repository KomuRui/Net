#include "CameraTransitionObject.h"
#include "BoxCollider.h"
#include "Camera.h"
#include "GameManager.h"

//�R���X�g���N�^
CameraTransitionObject::CameraTransitionObject(GameObject* parent, const StageCameraTransition& camInfo)
	:GameObject(parent,"CameraTransition")
{
	//�e�ϐ�������
	ARGUMENT_INITIALIZE(info, camInfo);
}

//������
void CameraTransitionObject::Initialize()
{
	//���`�̓����蔻��쐬
	BoxCollider* collision = new BoxCollider(XMFLOAT3(0,0,0), info.CollisionSize);
	AddCollider(collision);
}

//�X�V�̑O�Ɉ��Ă΂��֐�
void CameraTransitionObject::StartUpdate()
{
}

//�X�V
void CameraTransitionObject::Update()
{
}

//�`��
void CameraTransitionObject::Draw()
{
}

//���
void CameraTransitionObject::Release()
{
}

//�����蔻��
void CameraTransitionObject::OnCollision(GameObject* pTarget)
{
	//�����������肪Player�ȊO�Ȃ�
	if (pTarget->GetObjectName() != "Player") return;

	//�J�����̃|�W�V�����ƃ^�[�Q�b�g�Z�b�g
	Camera::SetPosition(info.CameraPosition);
	Camera::SetTarget(info.CameraTarget);
}