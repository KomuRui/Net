#include "Enemy.h"
#include "Engine/Model.h"
#include "Bullet.h"

//�R���X�g���N�^
Enemy::Enemy(GameObject* parent)
	:GameObject(parent, "Player"), hModel_(-1), angle_(0), isShot_(false), angleX(0)
{
}

//������
void Enemy::Initialize()
{
    ///////////////���f���f�[�^�̃��[�h///////////////////

    hModel_ = Model::Load("Player.fbx");
    assert(hModel_ >= ZERO);

    ///////////////Player�͌��X����Transform.Rotate���g��Ȃ�����Flag��True�ɂ���///////////////////

    transform_.mFlag_ = true;

    transform_.scale_ = { 2,2,2 };
}

//�X�V�̑O�Ɉ�x�����Ă΂��
void Enemy::StartUpdate()
{
}

//�X�V
void Enemy::Update()
{
    //Player�̌����̊p�x�����x�N�g������]������
    transform_.mmRotate_ = XMMatrixRotationX(angleX) * XMMatrixRotationY(angle_);

    if (isShot_)
        IsShot();
}

//�`��
void Enemy::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//���
void Enemy::Release()
{
}

//����ł�
void Enemy::IsShot()
{
    //��1
    Bullet* bul = Instantiate<Bullet>(GetParent());
    bul->SetPosition(Model::GetBonePosition(hModel_, "Left"));
    bul->SetmMatrix(transform_.mmRotate_);

    //��2
    Bullet* bul2 = Instantiate<Bullet>(GetParent());
    bul2->SetPosition(Model::GetBonePosition(hModel_, "Right"));
    bul2->SetmMatrix(transform_.mmRotate_);
}

//�|�W�V�����ړ�
void Enemy::PosMove(XMFLOAT3 p)
{
    XMStoreFloat3(&transform_.position_, (XMVectorLerp(XMLoadFloat3(&transform_.position_), XMLoadFloat3(&p), 0.3f)));
}

