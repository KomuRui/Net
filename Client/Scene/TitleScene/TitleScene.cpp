#define WIN32_LEAN_AND_MEAN
#include "TitleScene.h"
#include "../../Engine/Image.h"
#include "../../Engine/Input.h"
#include "../../Engine/SceneManager.h"
#include "../../Engine/Camera.h"
#include "../../Player.h"
#include"../../Stage.h"
#include "../../Engine/GameManager.h"
#include "../../Engine/Sock.h"
#include"../../Engine/Input.h"
#include"../../Engine/ImGuiSet.h"
#include "../../imgui/imgui_impl_dx11.h"
#include "../../imgui/imgui_impl_win32.h"
#include "../../imgui/imgui.h"


//コンストラクタ
TitleScene::TitleScene(GameObject* parent)
	: GameObject(parent, "TitleScene"),
	IP_("")
{

}

//初期化
void TitleScene::Initialize()
{
	

	hPict_[TITLE]=Image::Load("TitleImage.jpg");
	
}

//更新
void TitleScene::Update()
{
	if ((Input::IsPadButtonDown(XINPUT_GAMEPAD_A)||Input::IsKeyDown(DIK_SPACE))&&GameManager::GetIP()!="")
	{
		SceneManager* pScene = (SceneManager*)FindObject("SceneManager");
		pScene->ChangeScene(SCENE_ID_PLAY);
	}
}

//描画
void TitleScene::Draw()
{
	//Image::SetTransform(hPict_[TITLE], transform_);
	Image::Draw(hPict_[TITLE]);
	IPSetDraw(IP_);
}

//開放
void TitleScene::Release()
{
}

void TitleScene::StartUpdate()
{
}

void TitleScene::IPSetDraw(char* ipadd)
{
	//Imguiスタート
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	//window作る
	ImGui::Begin("IP");

	ImGui::InputText("IPaddress", ipadd, 20);
	GameManager::SetIP(IP_);

	ImGui::End();

	ImGui::Render();
	//描画
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
