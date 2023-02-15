#pragma once
#include "GameObject.h"

//�萔
const int LIGHT_TOTAL_NUM = 8; //���C�g�̑���        

//-----------------------------------------------------------
//�_�������C�g
//-----------------------------------------------------------
namespace Light
{
	//�������i���C�g��Pos�ƌ����j
	void Initialize();

	//���C�g�̈ʒu��ݒ�
	void SetPlayerPosition(XMFLOAT4 position);

	//�ʒu��ݒ�
	void SetPositionAndIntensity(XMFLOAT4 position, float intensity);

	//�����ɂ���Ăǂ̂悤�ɖ��邳��ω������邩(�����p�����[�^)��ݒ�
	void SetAttenuation(XMFLOAT4 attenuation);

	//���C�g�̌�����ݒ�
	void SetDirection(XMFLOAT4 direction);

	//���C�g�̋�����ݒ�
	void SetIntensity(float intensity);

	//�ʒu���擾
	XMFLOAT4 GetPosition(int num);

	//�����p�����[�^���擾
	XMFLOAT4 GetAttenuation();

	//���C�g�̌���
	XMFLOAT4 GetDirection();

	//���C�g�̋���
	float  GetIntensity(int num);
};

