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

//定数
const XMVECTOR UP_VECTOR = { 0,1,0,0 };          //上ベクトル
const float NORMAL_INTERPOLATION_FACTOR = 0.045; //法線を補間するときの補間係数
const float RUN_SPEED = 1.5f;                    //走っているときのキャラのスピード
const float ANIM_SPEED = 1.0f;                   //アニメーションの再生速度
const float ANIM_RUN_SPEED = 2.0f;               //アニメーションの再生速度(走ってるとき)
const int ANIM_START_FRAME = 1;                  //アニメーションの開始フレーム
const int ANIM_END_FRAME = 60;					 //アニメーションの終了フレーム
const int MAX_NORMAL_RADIANS = 50;				 //法線との最大角度
const float CAMERA_INTERPOLATION_FACTOR = 0.8;  //カメラの移動を補間するときの補間係数
const float CAM_POS_2D_Z = 20;                   //2Dの時のカメラのZの位置
const float LIGHT_POS_Z = 2;                     //ライトのZのポジション
const XMFLOAT3 COLLIDER_POS = { 0,0,0 };         //コライダーの位置
const float    COLLIDER_SIZE = 1.0f;             //コライダーのサイズ
const int ATTENUATION_MAX = 45;


//コンストラクタ
Player::Player(GameObject* parent)
    : GameObject(parent, "Player"), angleY_(0),angleX_(0),gravity_(-0.3f), attenuate_(0.9),vMove_(XMVectorSet(0,0,0,0)),
    hGroundModel_(-1),
    front_(XMVectorSet(0, 0, 1, 0)),
    isShot_(false)
{
}

/////////////////////オーバーライドする関数//////////////////////

//初期化
void Player::Initialize()
{
    ///////////////モデルデータのロード///////////////////

    hModel_ = Model::Load("Player.fbx");
    assert(hModel_ >= ZERO);
    ///////////////Playerは元々あるTransform.Rotateを使わないためFlagをTrueにする///////////////////
    SphereCollider* pCollision = new SphereCollider(XMFLOAT3(0, 0, 0), 1);
    transform_.mFlag_ = true;

    transform_.scale_ = { 2,2,2 };
}

//更新の前に一回呼ばれる関数
void Player::StartUpdate()
{
    hGroundModel_ = GameManager::GetpStage()->GetModelHandle();
}

//更新
void Player::Update()
{
    CameraBehavior();

    MovingOperation();

    StageRayCast();
} 

//描画
void Player::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//開放
void Player::Release()
{
}

void Player::OnCollision(GameObject* target)
{
    if (target->GetObjectName() == "Bullet")
    {

    }
}

/////////////////////関数//////////////////////

//カメラの処理
void Player::CameraBehavior()
{
    static XMFLOAT3 camtar = transform_.position_;
    static XMFLOAT3 campos = transform_.position_;

    XMFLOAT3 camPos;                                              //最終的なカメラの位置を入れる変数
    XMFLOAT3 camTar = { transform_.position_.x,transform_.position_.y + 2, transform_.position_.z };   //最終的なカメラのターゲット入れる変数
    XMVECTOR vPos = XMLoadFloat3(&transform_.position_);          //transform_.position_のVector型
    XMVECTOR vCam = XMVectorSet(0.0f, 10, -16, 0.0f);

    vCam = XMVector3TransformCoord(vCam, XMMatrixRotationX(angleX_)*XMMatrixRotationY(angleY_)); //vCamを回す

    vPos += vCam;                    //PlayerのPosにPlayerからカメラのベクトルをたす
    XMStoreFloat3(&camPos, vPos);    //camPosにvPosをXMFLOAT3に変えていれる

    //カメラのいろいろ設定
    Camera::SetUpDirection(UP_VECTOR);
    Camera::SetPosition(camPos);
    Camera::SetTarget(camTar);

    //ライト設定
    XMFLOAT3 lightPos;
    XMStoreFloat3(&lightPos, UP_VECTOR * 2 + XMLoadFloat3(&transform_.position_));

    Light::SetPlayerPosition(XMFLOAT4(lightPos.x, lightPos.y, lightPos.z, ZERO));
}

//プレイヤー操作(3D用)
void Player::MovingOperation()
{
    isShot_ = false;
    //////すべての状態に共通する処理をしておく

    float PadLx = Input::GetPadStickL().x;
    float PadLy = Input::GetPadStickL().y;
    float LTrriger = Input::GetPadTrrigerL();
    float RTrriger = Input::GetPadTrrigerR();
    //軸の角度設定
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

    //速度減衰のための補間
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
    
    //玉発射
    if (Input::IsPadButtonDown(XINPUT_GAMEPAD_A))
    {
        isShot_ = true;

        //球1
        Bullet* bul = Instantiate<Bullet>(GetParent());
        bul->SetPosition(Model::GetBonePosition(hModel_, "Left"));
        bul->SetmMatrix(XMMatrixRotationX(angleX_) * XMMatrixRotationY(angleY_));

        //球2
        Bullet* bul2 = Instantiate<Bullet>(GetParent());
        bul2->SetPosition(Model::GetBonePosition(hModel_, "Right"));
        bul2->SetmMatrix(XMMatrixRotationX(angleX_) * XMMatrixRotationY(angleY_));
    }

    //右スティックでカメラの角度かえる
    if (Input::GetPadStickR().x || Input::GetPadStickR().y)
    {
        camAngleY_ += 0.03f * Input::GetPadStickR().x;
        camAngleX_ += -(0.03f * Input::GetPadStickR().y);
        //角度が一定以上にならないようにする
        camAngleX_ = max(camAngleX_, 0.5f*-3.14);
        camAngleX_ = min(camAngleX_, 0.3f*3.14);
    }

    //Playerの向きの角度分軸ベクトルを回転させる
    transform_.mmRotate_ = XMMatrixRotationX(angleX_) * XMMatrixRotationY(angleY_);//XMMatrixRotationAxis(UP_VECTOR, angleY_);
}

//レイ(3D用)
void Player::StageRayCast()
{
    //範囲制限
   
    transform_.position_.x = max(transform_.position_.x, -200.0f);
    transform_.position_.x = min(transform_.position_.x, 200.0f);

        transform_.position_.y = max(transform_.position_.y, 0.0f);
        transform_.position_.y = min(transform_.position_.y, 100.0f);

        transform_.position_.z=max(transform_.position_.z, -200.0f);
        transform_.position_.z=min(transform_.position_.z, 200.0f);
}

//ポジション移動
void Player::PosMove(XMFLOAT3 p)
{
    XMStoreFloat3(&transform_.position_, (XMVectorLerp(XMLoadFloat3(&transform_.position_), XMLoadFloat3(&p), 0.3f)));
}