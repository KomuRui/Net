#pragma once
#include"Engine/GameObject.h"
class Bullet : public GameObject
{
private:

	//モデル
	int hModel_;

	//キャラの元となる前ベクトル
	XMVECTOR front_;

	//速度
	float bulletSpeed_;

	//寿命
	int life_;

public:
	//コンストラクタ
	Bullet(GameObject* parent);
	~Bullet();
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

	void OnCollision(GameObject* target) override;

	//////////////ゲットセット関数///////////////

	//自身の任意軸回転行列をセット
	void SetmMatrix(XMMATRIX m) { transform_.mmRotate_ = m; }
};

