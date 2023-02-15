#pragma once
#include <DirectXMath.h>
#include "windowsnumerics.h"

using namespace DirectX;


//-----------------------------------------------------------
//�ʒu�A�����A�g�嗦�Ȃǂ��Ǘ�����N���X
//-----------------------------------------------------------
class Transform
{
public:
	XMMATRIX matTranslate_;	//�ړ��s��
	XMMATRIX matRotate_;	//��]�s��	
	XMMATRIX matScale_;		//�g��s��
	XMFLOAT3 position_;		//�ʒu
	XMFLOAT3 rotate_;		//����
	XMFLOAT3 scale_;		//�g�嗦
	XMMATRIX mmRotate_;	    //��]�s��	
	bool     mFlag_;        //�t���O
	Transform* pParent_;	//�e�I�u�W�F�N�g�̏��

	//�R���X�g���N�^
	Transform();

	//�f�X�g���N�^
	~Transform();

	//�e�s��̌v�Z
	//�����F�Ȃ�
	//�ߒl�F�Ȃ�
	void Calclation();

	//���[���h�s����擾
	//�����F�Ȃ�
	//�ߒl�F���̎��_�ł̃��[���h�s��
	XMMATRIX GetWorldMatrix();


	static XMFLOAT3 Float3Add(XMFLOAT3 a, XMFLOAT3 b)
	{
		return XMFLOAT3(a.x + b.x, a.y + b.y, a.z + b.z);
	}

	static float RangeCalculation(XMFLOAT3 a, XMFLOAT3 b)
	{
		    return (sqrt(pow(a.x - b.x, 2) +
			             pow(a.y - b.y, 2) +
			             pow(a.z - b.z, 2)));
	}

	static XMFLOAT3 VectorToFloat3(XMVECTOR v)
	{
		XMFLOAT3 a;
		XMStoreFloat3(&a, v);

		return a;
	}

};

