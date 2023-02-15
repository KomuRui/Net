#pragma once
#include "Engine/GameObject.h"
#include <vector>

//各ステージクラスのもととなるクラス
class Stage : public GameObject
{
private:
	int hModel_;
public:

	//コンストラクタ
	Stage(GameObject* parent);
	~Stage();
	/////////////////////オーバーライドする関数//////////////////////

	//初期化
	void Initialize() override;

	//更新の前に一回呼ばれる関数
	void StartUpdate() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//モデル番号取得
	int GetModelHandle() { return hModel_; }

	//開放
	void Release() override;

};

