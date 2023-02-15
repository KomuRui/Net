#pragma once
#include "Engine/GameObject.h"

class Enemy : public GameObject
{
	//モデル番号
	int hModel_;

	//上の軸の角度
	float angle_;

	float angleX;

	//打ったか
	bool isShot_;

public:

	//コンストラクタ
	Enemy(GameObject* parent);

	/////////////////////オーバーライドする関数//////////////////////

	//初期化
	void Initialize() override;

	//更新の前に一回呼ばれる関数
	void StartUpdate() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	///////////////////////////関数//////////////////////////////
	
	//球打つ
	void IsShot();

	//打ったどうかセット
	void SetShot(bool flag) { isShot_ = flag; }

	//上の軸の角度セット
	void SetAngle(float angle) { angle_ = angle; }
	void SetAngleX(float angle) { angleX = angle; }

	void PosMove(XMFLOAT3 p);
};

