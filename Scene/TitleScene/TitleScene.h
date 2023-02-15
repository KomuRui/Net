#pragma once

#include "../../Engine/GameObject.h"
#include "../../Engine/Fade.h"
#include "../../Button.h"



//■■シーンを管理するクラス
class TitleScene : public GameObject
{
	enum TitleImages
	{
		TITLE = 0,
		START,
		MAX_SIZE_TITLEIMAGE
	};

	int hPict_[MAX_SIZE_TITLEIMAGE];    //画像番号

	Fade* pfade_;				        //フェード用
	char IP_[20];
	int count_;

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	TitleScene(GameObject* parent);

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void StartUpdate() override;
	void IPSetDraw(char* ip);
};

