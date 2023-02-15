#include "Button.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"

//�R���X�g���N�^
Button::Button(GameObject* parent)
	: GameObject(parent, "Button"), controllerSelect(false), hPict_(-1), pfadeButton(new Fade)
{
}


Button::Button(GameObject* parent,std::string name)
	: GameObject(parent, name), controllerSelect(false), hPict_(-1), pfadeButton(new Fade)
{
}

//������
void Button::Initialize()
{
	///////////////�摜�f�[�^�̃��[�h///////////////////
	hPict_ = Image::Load(fileNamePas);
	assert(hPict_ >= 0);
}

//�X�V
void Button::Update()
{
	//�{�^�����I�΂�Ă��鎞�ɉ������邩
	IsButtonSelect();

	//���M���I�΂�Ă��Ă��C�ӂ̃{�^���������ꂽ��
	if (controllerSelect && (Input::IsPadButtonDown(XINPUT_GAMEPAD_A) || Input::IsKeyDown(DIK_RETURN)))
	{
		//�{�^���������ꂽ���̏���
		IsButtonPush();
	}
}

//�`��
void Button::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
}

//�J��
void Button::Release()
{
}

void Button::StartUpdate()
{
}

//�{�^�����I�΂�Ă��鎞�ɂ��邱��(�f�t�H���g�t�F�[�h����)
void Button::IsButtonSelect()
{
	if (controllerSelect)
	{
		pfadeButton->FadeInOut(hPict_, 2.0f);
	}
	else if (!controllerSelect)
	{
		if (Image::GetAlpha(hPict_) != 255)
			Image::SetAlpha(hPict_, 255);
	}
}
