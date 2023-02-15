#include "Bullet.h"
#include"Engine/Model.h"
#include "Engine/GameManager.h"
#include"Engine/SphereCollider.h"

//�R���X�g���N�^
Bullet::Bullet(GameObject* parent)
	:GameObject(parent,"Bullet"),
	hModel_(-1),
	bulletSpeed_(1.5f),
	life_(300),
	front_(XMVectorSet(0,0,1,0))
{

}
Bullet::~Bullet()
{

}
/////////////////////�I�[�o�[���C�h����֐�//////////////////////

//������
void Bullet::Initialize()
{
	///////////////���f���f�[�^�̃��[�h///////////////////

	hModel_ = Model::Load("Bullet.fbx");
	assert(hModel_ >= 0);

	///////////////////////////�����蔻��////////////////////
	SphereCollider* pCollision = new SphereCollider(XMFLOAT3(0, 0, 0), 0.5f);
	///////////////���X����Transform.Rotate���g��Ȃ�����Flag��True�ɂ���///////////////////

	transform_.mFlag_ = true;

}

//�X�V�̑O�Ɉ��Ă΂��֐�
void Bullet::StartUpdate()
{
	//���g�̑O�x�N�g������]
	front_ = XMVector3TransformCoord(front_,transform_.mmRotate_);
}

//�X�V
void Bullet::Update()
{
	//�ړ�����
	{
		transform_.position_ = Transform::Float3Add(transform_.position_ , Transform::VectorToFloat3(front_ * bulletSpeed_)); //���f
	}

	//��������
	{
		//�������s�����Ȃ�
		if (life_ <= ZERO)
			KillMe();  //�폜
		else
			life_--;   //�������炷
	}
}

//�`��
void Bullet::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//�J��
void Bullet::Release()
{

}

void Bullet::OnCollision(GameObject* target)
{
	if (target->GetObjectName() == "Player")
	{
		KillMe();
	}
}
