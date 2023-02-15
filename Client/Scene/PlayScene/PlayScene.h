#pragma once
#define WIN32_LEAN_AND_MEAN
#include"../../Engine/GameObject.h"
#include "../../Engine/Fade.h"
#include "../../Button.h"

class Sock;

class PlayScene : public GameObject
{
private:
	//TitleSceneに表示する画像


	Sock* pSock_;//ソケット



public:
	PlayScene(GameObject* parent);
	~PlayScene();

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Release() override;

	void StartUpdate() override;
};
