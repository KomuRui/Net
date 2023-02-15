#include "Stage.h"
#include"Engine/Model.h"
#include "Engine/ImGuiSet.h"

//コンストラクタ
Stage::Stage(GameObject* parent)
	:GameObject(parent,"Stage"),
	hModel_(-1)
{
}
//コンストラクタ
Stage::~Stage()
{

}

/////////////////////オーバーライドする関数//////////////////////

//初期化
void Stage::Initialize()
{
	//ステージ作成
	ImGuiSet* a = Instantiate<ImGuiSet>(this);

	hModel_ = Model::Load("Field.fbx");
	assert(hModel_ >= 0);
	transform_.scale_ = { 2.6f,2.6f,2.6f };
}

//更新の前に一回呼ばれる関数
void Stage::StartUpdate()
{

}

//更新
void Stage::Update()
{

}

//描画
void Stage::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

//開放
void Stage::Release()
{

}
