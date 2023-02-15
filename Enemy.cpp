#include "Enemy.h"
#include "Engine/Model.h"
#include "Bullet.h"

//コンストラクタ
Enemy::Enemy(GameObject* parent)
	:GameObject(parent, "Player"), hModel_(-1), angle_(0), isShot_(false), angleX(0)
{
}

//初期化
void Enemy::Initialize()
{
    ///////////////モデルデータのロード///////////////////

    hModel_ = Model::Load("Player.fbx");
    assert(hModel_ >= ZERO);

    ///////////////Playerは元々あるTransform.Rotateを使わないためFlagをTrueにする///////////////////

    transform_.mFlag_ = true;

    transform_.scale_ = { 2,2,2 };
}

//更新の前に一度だけ呼ばれる
void Enemy::StartUpdate()
{
}

//更新
void Enemy::Update()
{
    //Playerの向きの角度分軸ベクトルを回転させる
    transform_.mmRotate_ = XMMatrixRotationX(angleX) * XMMatrixRotationY(angle_);

    if (isShot_)
        IsShot();
}

//描画
void Enemy::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

//解放
void Enemy::Release()
{
}

//球を打つ
void Enemy::IsShot()
{
    //球1
    Bullet* bul = Instantiate<Bullet>(GetParent());
    bul->SetPosition(Model::GetBonePosition(hModel_, "Left"));
    bul->SetmMatrix(transform_.mmRotate_);

    //球2
    Bullet* bul2 = Instantiate<Bullet>(GetParent());
    bul2->SetPosition(Model::GetBonePosition(hModel_, "Right"));
    bul2->SetmMatrix(transform_.mmRotate_);
}

//ポジション移動
void Enemy::PosMove(XMFLOAT3 p)
{
    XMStoreFloat3(&transform_.position_, (XMVectorLerp(XMLoadFloat3(&transform_.position_), XMLoadFloat3(&p), 0.3f)));
}

