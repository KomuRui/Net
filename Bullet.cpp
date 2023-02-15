#include "Bullet.h"
#include"Engine/Model.h"
#include "Engine/GameManager.h"
#include"Engine/SphereCollider.h"

//コンストラクタ
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
/////////////////////オーバーライドする関数//////////////////////

//初期化
void Bullet::Initialize()
{
	///////////////モデルデータのロード///////////////////

	hModel_ = Model::Load("Bullet.fbx");
	assert(hModel_ >= 0);

	///////////////////////////当たり判定////////////////////
	SphereCollider* pCollision = new SphereCollider(XMFLOAT3(0, 0, 0), 0.5f);
	///////////////元々あるTransform.Rotateを使わないためFlagをTrueにする///////////////////

	transform_.mFlag_ = true;

}

//更新の前に一回呼ばれる関数
void Bullet::StartUpdate()
{
	//自身の前ベクトルを回転
	front_ = XMVector3TransformCoord(front_,transform_.mmRotate_);
}

//更新
void Bullet::Update()
{
	//移動処理
	{
		transform_.position_ = Transform::Float3Add(transform_.position_ , Transform::VectorToFloat3(front_ * bulletSpeed_)); //反映
	}

	//寿命処理
	{
		//寿命が尽きたなら
		if (life_ <= ZERO)
			KillMe();  //削除
		else
			life_--;   //寿命減らす
	}
}

//描画
void Bullet::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
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
