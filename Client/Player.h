#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"
#include "Engine/Particle.h"
#include "Engine/Fbx.h"


class Player : public GameObject
{
	///////////////キャラの必要な情報///////////////////

	//変数

	float angleY_;                           //キャラの上の軸の角度
	float angleX_;							//キャラの上下回転の角度
	XMVECTOR front_;                        //キャラの前方向のベクトル
	int   hModel_;                          //モデル番号
	float gravity_;							//キャラにかかる重力
	float upVelocity_;						//上昇速度
	float attenuate_;						//速度減衰
	XMVECTOR vMove_;
	bool isShot_;

	///////////////カメラ///////////////////

	//変数

	float camAngleX_;                        //カメラの上下の角度
	float camAngleY_;                        //カメラのY軸周りの角度

	///////////////当たり判定///////////////////

	//変数

	Stage* pstage_;                           //ステージクラスのポインタ
	int    hGroundModel_;                   //ステージのモデル番号を入れる変数

	enum StageRayDecision                     //各方向への当たり判定するために列挙する
	{
		Straight = 0,                         //前
		Back,                                 //後
		Left,                                 //左
		Right,                                //右
		Under,                                //下
		Top,                                  //上
		MAX_RAY_SIZE
	};
	

public:

	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Player(GameObject* parent);

	/////////////////////オーバーライドする関数//////////////////////

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	void OnCollision(GameObject* target) override;

	//更新の前に一回呼ばれる関数
	void StartUpdate() override;

	/////////////////////関数//////////////////////

	//カメラの処理
	void CameraBehavior();

	//プレイヤー操作(3D用)
	void MovingOperation();

	//レイ
	void StageRayCast();

	//////////////ゲットセット関数///////////////

	//前ベクトルをゲット
	XMVECTOR GetFront() { return front_; }

	//キャラの上軸の角度を取得
	float GetAxisAngle() { return angleY_; }
	float GetAxisAngleX() { return angleX_; }

	bool IsShot() { return isShot_; }

	void PosMove(XMFLOAT3 p);
};

