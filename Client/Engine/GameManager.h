#pragma once
#include "../Stage.h"
#include "../Player.h"
#include "../Enemy.h"

//ゲームのいろいろな管理をする
namespace GameManager
{

	//初期化
	void Initialize();

	//しんーか
	void SceneChangeInitialize();

	//描画
	void Draw();

	//プレイヤーのポインタセット
	void SetpPlayer(Player* player);

	//プレイヤーのポインタゲット
	Player* GetpPlayer();

	//ステージのポインタセット
	void SetpStage(Stage* stage);

	//ステージのポインタゲット
	Stage* GetpStage();

	//IDセット
	void SetId(int num);

	//IDゲット
	int GetId();

	void SetIP(std::string ipadd);
	std::string GetIP();

	//敵セット
	void SetEnemy(std::pair<int, Enemy*> a);

	//参加プレイヤーが入ってるvectorゲット
	std::vector<std::pair<int, Enemy*>>  GetEnemyVec();
};

