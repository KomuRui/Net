#include "GameManager.h"
#include "Text.h"

namespace GameManager
{
	//現在使用されているプレイヤーのポインタ格納用
	Player* pNowPlayer_;

	//現在の使用されているステージのポインタ格納用
	Stage* pNowStage_;

	//参加プライヤーのIDとクラスが入ってる
	std::vector<std::pair<int, Enemy*>> enemy_;

	//ID
	int iD_;
	
	std::string ipadd_;
	//文字
	Text* text_;

	//初期化
	void GameManager::Initialize()
	{
		iD_ = 0;
		text_ = new Text;
		ipadd_ = "";
		text_->Initialize();
	}

	//しんーか
	void SceneChangeInitialize()
	{
		text_ = new Text;
		text_->Initialize();
	}

	//描画
	void GameManager::Draw()
	{
		Direct3D::SetShader(Direct3D::SHADER_3D);
		Direct3D::SetBlendMode(Direct3D::BLEND_DEFAULT);

		if (iD_ != 0)
			text_->Draw(1600, 850, iD_, 2);
	}

	//プレイヤーのポインタセット
	void GameManager::SetpPlayer(Player* player) { pNowPlayer_ = player; }

	//プレイヤーのポインタゲット
	Player* GameManager::GetpPlayer() { return pNowPlayer_; }

	//ステージのポインタセット
	void GameManager::SetpStage(Stage* stage) { pNowStage_ = stage; }

	//ステージのポインタゲット
	Stage* GameManager::GetpStage() { return pNowStage_; }

	//IDセット
	void GameManager::SetId(int num) { iD_ = num; };

	//IDゲット
	int GameManager::GetId() { return iD_; }

	void SetIP(std::string ipadd) {
		ipadd_ = ipadd;
	}
	std::string GetIP() { return ipadd_; }

	//敵セット
	void GameManager::SetEnemy(std::pair<int, Enemy*> a) { enemy_.push_back(a); }

	//参加プレイヤーが入ってるvectorゲット
	std::vector<std::pair<int, Enemy*>> GameManager::GetEnemyVec() { return enemy_; }
}