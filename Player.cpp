#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Engine/Camera.h"
#include <cmath>
#include "Engine/Light.h"
#include "Engine/BoxCollider.h"
#include "Engine/SphereCollider.h"
#include "Engine/GameManager.h"
#include"Stage.h"
#include"Bullet.h"
#include <algorithm>
#include <iostream>

//�萔
const XMVECTOR UP_VECTOR = { 0,1,0,0 };          //��x�N�g��
const float NORMAL_INTERPOLATION_FACTOR = 0.045; //�@�����Ԃ���Ƃ��̕�ԌW��
const float RUN_SPEED = 1.5f;                    //�����Ă���Ƃ��̃L�����̃X�s�[�h
const float ANIM_SPEED = 1.0f;                   //�A�j���[�V�����̍Đ����x
const float ANIM_RUN_SPEED = 2.0f;               //�A�j���[�V�����̍Đ����x(�����Ă�Ƃ�)
const int ANIM_START_FRAME = 1;                  //�A�j���[�V�����̊J�n�t���[��
const int ANIM_END_FRAME = 60;					 //�A�j���[�V�����̏I���t���[��
const int MAX_NORMAL_RADIANS = 50;				 //�@���Ƃ̍ő�p�x
const float CAMERA_INTERPOLATION_FACTOR = 0.8;  //�J�����̈ړ����Ԃ���Ƃ��̕�ԌW��
const float CAM_POS_2D_Z = 20;                   //2D�̎��̃J������Z�̈ʒu
const float LIGHT_POS_Z = 2;                     //���C�g��Z�̃|�W�V����
const XMFLOAT3 COLLIDER_POS = { 0,0,0 };         //�R���C�_�[�̈ʒu
const float    COLLIDER_SIZE = 1.0f;             //�R���C�_�[�̃T�C�Y
const int ATTENUATION_MAX = 45;


//�R���X�g���N�^
Player::Player(GameObject* parent)
    : GameObject(parent, "Player"), angleY_(0),angleX_(0),gravity_(-0.3f), attenuate_(0.9),vMove_(XMVectorSet(0,0,0,0)),
    hGroundModel_(-1),
    front_(XMVectorSet(0, 0, 1, 0)),
    isShot_(false)
{
}

/////////////////////�I�[�o�[���C�h����֐�//////////////////////

//������
void Player::Initialize()
{
    ///////////////���f���f�[�^�̃��[�h///////////////////

    hModel_ = Model::Load("Player.fbx");
    assert(hModel_ >= ZERO);
    ///////////////Player�͌��X����Transform.Rotate���g��Ȃ�����Flag��True�ɂ���///////////////////
    SphereCollider* pCollision = new SphereCollider(XMFLOAT3(0, 0, 0), 1);
    transform_.mFlag_ = true;

    transform_.scale_ = { 2,2,2 };
}

//�X�V�̑O�Ɉ��Ă΂��֐�
void Player::StartUpdate()
{
    hGroundModel_ = GameManager::GetpStage()->GetModelHandle();
}

//�X�V
void Player::Update()
{
    CameraBehavior();

    MovingOperation();

    StageRayCast();
} 

//�`��
void Player::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//�J��
void Player::Release()
{
}

void Player::OnCollision(GameObject* target)
{
    if (target->GetObjectName() == "Bullet")
    {

    }
}

/////////////////////�֐�//////////////////////

//�J�����̏���
void Player::CameraBehavior()
{
    static XMFLOAT3 camtar = transform_.position_;
    static XMFLOAT3 campos = transform_.position_;

    XMFLOAT3 camPos;                                              //�ŏI�I�ȃJ�����̈ʒu������ϐ�
    XMFLOAT3 camTar = { transform_.position_.x,transform_.position_.y + 2, transform_.position_.z };   //�ŏI�I�ȃJ�����̃^�[�Q�b�g�����ϐ�
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);          //transform_.position_��Vector�^
    XMVECTOR vCam = XMVectorSet(0.0f, 10, -16, 0.0f);

    vCam = XMVector3TransformCoord(vCam, XMMatrixRotationX(angleX_)*XMMatrixRotationY(angleY_)); //vCam����

    vPos += vCam;                    //Player��Pos��Player����J�����̃x�N�g��������
    XMStoreFloat3(&camPos, vPos);    //camPos��vPos��XMFLOAT3�ɕς��Ă����

    //�J�����̂��낢��ݒ�
    Camera::SetUpDirection(UP_VECTOR);
    Camera::SetPosition(camPos);
    Camera::SetTarget(camTar);

    //���C�g�ݒ�
    XMFLOAT3 lightPos;
    XMStoreFloat3(&lightPos, UP_VECTOR * 2 + XMLoadFloat3(&transform_.position_));

    Light::SetPlayerPosition(XMFLOAT4(lightPos.x, lightPos.y, lightPos.z, ZERO));
}

//�v���C���[����(3D�p)
void Player::MovingOperation()
{
    isShot_ = false;
    //////���ׂĂ̏�Ԃɋ��ʂ��鏈�������Ă���

    float PadLx = Input::GetPadStickL().x;
    float PadLy = Input::GetPadStickL().y;
    float LTrriger = Input::GetPadTrrigerL();
    float RTrriger = Input::GetPadTrrigerR();
    //���̊p�x�ݒ�
    angleY_ = camAngleY_;
    angleX_ = camAngleX_;
    
    XMVECTOR MoveDir = XMVectorSet(PadLx, 0, PadLy, 0);
    //float MoveLength = XMVectorGetX(XMVector3Length(MoveDir));

    if (RTrriger > ZERO)
    {
        MoveDir *= 1.3f;
        //attenuateTime_ = ATTENUATION_MAX;
    }

    if (LTrriger > ZERO)
    {
        upVelocity_ += 0.6;
        upVelocity_ = min(upVelocity_, 5.0f);
    }

    //���x�����̂��߂̕��
    vMove_ += MoveDir*0.1f;
    upVelocity_ += gravity_;
    if (XMVectorGetX(XMVector3Length(vMove_)) <= 0.03f)
    {
        vMove_ = XMVectorSet(0, 0, 0, 0);
    }
    else if (XMVectorGetX(XMVector3Length(vMove_)) > 1.3f)
    {
           vMove_ = XMVector3Normalize(vMove_) * 1.3f;
    }

    vMove_ *= attenuate_;// XMVector3Normalize(vMove_)* (-attenuate_);
    upVelocity_ = max(upVelocity_, -5.0f);
    MoveDir = UP_VECTOR * upVelocity_;
    transform_.position_ = Transform::Float3Add(transform_.position_, Transform::VectorToFloat3(XMVector3TransformCoord(vMove_+MoveDir / 10, XMMatrixRotationY(angleY_))));
    
    //�ʔ���
    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
    {
        isShot_ = true;

        //��1
        Bullet* bul = Instantiate<Bullet>(GetParent());
        bul->SetPosition(Model::GetBonePosition(hModel_, "Left"));
        bul->SetmMatrix(XMMatrixRotationX(angleX_) * XMMatrixRotationY(angleY_));

        //��2
        Bullet* bul2 = Instantiate<Bullet>(GetParent());
        bul2->SetPosition(Model::GetBonePosition(hModel_, "Right"));
        bul2->SetmMatrix(XMMatrixRotationX(angleX_) * XMMatrixRotationY(angleY_));
    }

    //�E�X�e�B�b�N�ŃJ�����̊p�x������
    if (Input::GetPadStickR().x || Input::GetPadStickR().y)
    {
        camAngleY_ += 0.03f * Input::GetPadStickR().x;
        camAngleX_ += -(0.03f * Input::GetPadStickR().y);
        //�p�x�����ȏ�ɂȂ�Ȃ��悤�ɂ���
        camAngleX_ = max(camAngleX_, 0.5f*-3.14);
        camAngleX_ = min(camAngleX_, 0.3f*3.14);
    }

    //Player�̌����̊p�x�����x�N�g������]������
    transform_.mmRotate_ = XMMatrixRotationX(angleX_) * XMMatrixRotationY(angleY_);//XMMatrixRotationAxis(UP_VECTOR, angleY_);
}

//���C(3D�p)
void Player::StageRayCast()
{
    //�͈͐���
   
    transform_.position_.x = max(transform_.position_.x, -200.0f);
    transform_.position_.x = min(transform_.position_.x, 200.0f);

        transform_.position_.y = max(transform_.position_.y, 0.0f);
        transform_.position_.y = min(transform_.position_.y, 100.0f);

        transform_.position_.z=max(transform_.position_.z, -200.0f);
        transform_.position_.z=min(transform_.position_.z, 200.0f);
}

//�|�W�V�����ړ�
void Player::PosMove(XMFLOAT3 p)
{
    XMStoreFloat3(&transform_.position_, (XMVectorLerp(XMLoadFloat3(&transform_.position_), XMLoadFloat3(&p), 0.3f)));
}