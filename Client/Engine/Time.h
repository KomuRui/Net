#pragma once
#include "Text.h"

class Time
{
private:

	//�^�C�����i�[���邽�߂̕ϐ�
	float time_;

	//������\�����邽�߂̕ϐ�
	Text* text_;

	//�^�C��flag;
	bool Timeflag_;
	
public:

	//�R���X�g���N�^
	Time() {}

	//�f�X�g���N�^
	~Time() { delete text_; }

	//������
	void Initialize() { text_ = new Text; text_->Initialize(); time_ = 0; Timeflag_ = false; }

	//�^�C���̕`��
	//��1����:�\���ʒuX
	//��2����:�\���ʒuY
	//��3����:�����_�扽�܂ŕ\��
	void TimeDraw(int x, int y);

	//�Z�b�^�[
	void SetTimeflag(bool flag) { Timeflag_ = flag; }
};

