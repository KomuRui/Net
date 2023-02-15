#define WIN32_LEAN_AND_MEAN
#include "PlayScene.h"
#include "../../Engine/Image.h"
#include "../../Engine/Input.h"
#include "../../Engine/SceneManager.h"
#include "../../Engine/Camera.h"
#include "../../Player.h"
#include"../../Stage.h"
#include "../../Engine/GameManager.h"
#include "../../Engine/Sock.h"


PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent,"PlayScene")
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{
	GameManager::SetpPlayer(Instantiate<Player>(this));
	GameManager::SetpStage(Instantiate<Stage>(this));

	///////////////画像データのロード///////////////////


	///////////////transform///////////////////


	///////////////カメラ///////////////////

	Camera::SetPosition(XMFLOAT3(0, 60, -50));
	Camera::SetTarget(XMFLOAT3(0, 10, 0));
	std::string ipadd = GameManager::GetIP();

	pSock_ = new Sock(this);
	pSock_->Updata();
	pSock_->Initialize(ipadd);
	pSock_->LobySending();

}

void PlayScene::Update()
{
	pSock_->Receiving();

	SendInfo a;
	a.pos.x = GameManager::GetpPlayer()->GetPosition().x;
	a.pos.y = GameManager::GetpPlayer()->GetPosition().y;
	a.pos.z = GameManager::GetpPlayer()->GetPosition().z;

	a.iD = GameManager::GetId();
	a.isShot = GameManager::GetpPlayer()->IsShot();
	a.axisAngle = GameManager::GetpPlayer()->GetAxisAngle();
	a.axisAngleX = GameManager::GetpPlayer()->GetAxisAngleX();

	pSock_->Sending(a);
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}

void PlayScene::StartUpdate()
{
}

