#pragma once
#include <DirectXMath.h>
#include <assert.h>
#include <vector>
#include <string>
#include "Fbx.h"
#include "Transform.h"

//-----------------------------------------------------------
//3D���f���iFBX�t�@�C���j���Ǘ�����
//-----------------------------------------------------------
namespace Model
{
	//���f�����
	struct ModelData
	{
		//�t�@�C����
		std::string fileName;

		//���[�h�������f���f�[�^�̃A�h���X
		Fbx*		pFbx;

		//�s��
		Transform 	transform;

		//�A���t�@
		float		alpha;

		//�A���r�G���g
		int         ambient;

		//�X�y�L�����[
		XMFLOAT4    speculer;

		//���C�g�̌���
		XMFLOAT4    lightDirection;

		//���邳
		float brightness;

		//���C�̓����蔻���t���邩
		bool rayFlag;

		//�A�j���[�V�����Đ����邩
		bool animFlag;

		//�A�j���[�V�����̃t���[��
		float nowFrame, animSpeed;
		int startFrame, endFrame;


		//������
		ModelData() : pFbx(nullptr), rayFlag(false), nowFrame(0), startFrame(0), endFrame(0), animSpeed(0),
			alpha(1), ambient(1), animFlag(false), speculer(0,0,0,0), brightness(0)
		{
		}

		//�A�j���[�V�����̃t���[�������Z�b�g
		//�����FstartFrame	�J�n�t���[��
		//�����FendFrame	�I���t���[��
		//�����FanimSpeed	�A�j���[�V�������x
		void SetAnimFrame(int start, int end, float speed)
		{
			nowFrame = (float)start;
			startFrame = start;
			endFrame = end;
			animSpeed = speed;
		}
	};


	//������
	void Initialize();

	//���f�������[�h
	//�����FfileName�@�t�@�C����
	//�ߒl�F���̃��f���f�[�^�Ɋ��蓖�Ă�ꂽ�ԍ�
	int Load(std::string fileName);

	//�`��
	//�����Fhandle	�`�悵�������f���̔ԍ�
	//�����Fmatrix	���[���h�s��
	void Draw(int handle);

	//�C�ӂ̃��f�����J��
	//�����Fhandle	�J�����������f���̔ԍ�
	void Release(int handle);

	//�S�Ẵ��f�������
	//�i�V�[�����؂�ւ��Ƃ��͕K�����s�j
	void AllRelease();

	//���[���h�s���ݒ�
	//�����Fhandle	�ݒ肵�������f���̔ԍ�
	//�����Fmatrix	���[���h�s��
	void SetAlpha(int handle, float Alpha);

	//���[���h�s���ݒ�
	//�����Fhandle	�ݒ肵�������f���̔ԍ�
	//�����Fmatrix	���[���h�s��
	void SetAmbient(int handle, float ambt = 1);

	//���[���h�s���ݒ�
	//�����Fhandle	�ݒ肵�������f���̔ԍ�
	//�����Fmatrix	���[���h�s��
	void SetSpeculer(int handle, XMFLOAT4 Speculer = { 0,0,0,0 });

	//���[���h�s���ݒ�
	//�����Fhandle	�ݒ肵�������f���̔ԍ�
	//�����Fmatrix	���[���h�s��
	void SetBrightness(int handle, float Brightness = 0);

	//���[���h�s���ݒ�
	//�����Fhandle	�ݒ肵�������f���̔ԍ�
	//�����Fmatrix	���[���h�s��
	void SetRayFlag(int handle, bool flag);

	//�A�j���[�V�����̃t���[�������Z�b�g
	//�����Fhandle		�ݒ肵�������f���̔ԍ�
	//�����FstartFrame	�J�n�t���[��
	//�����FendFrame	�I���t���[��
	//�����FanimSpeed	�A�j���[�V�������x
	void SetAnimFrame(int handle, int startFrame, int endFrame, float animSpeed);

	//�A�j���[�V�������邩���Ȃ���
	void SetAnimFlag(int handle, bool flag);

	//�A�j���[�V�����̃X�s�[�h���Z�b�g����֐�
	void SetAnimSpeed(int handle, int speed);

	//���݂̃A�j���[�V�����̃t���[�����擾
	int GetAnimFrame(int handle);

	//�C�ӂ̃{�[���̈ʒu���擾
	//�����Fhandle		���ׂ������f���̔ԍ�
	//�����FboneName	���ׂ����{�[���̖��O
	//�ߒl�F�{�[���̈ʒu�i���[���h���W�j
	XMFLOAT3 GetBonePosition(int handle, std::string boneName);

	//���[���h�s���ݒ�
	//�����Fhandle	�ݒ肵�������f���̔ԍ�
	//�����Fmatrix	���[���h�s��
	void SetTransform(int handle, Transform& transform);

	//���[���h�s��̎擾
	//�����Fhandle	�m�肽�����f���̔ԍ�
	//�ߒl�F���[���h�s��
	XMMATRIX GetMatrix(int handle);


	//���C�L���X�g�i���C���΂��ē����蔻��j
	//�����Fhandle	���肵�������f���̔ԍ�
	//�����Fdata	�K�v�Ȃ��̂��܂Ƃ߂��f�[�^
	void RayCast(int handle, RayCastData *data);

	//��ԋ߂��|���S���̖@���ƃ|�W�V������RayCastData�Ɋi�[
	//�����Fhandle	���肵�������f���̔ԍ�
	//�����Fdata	�K�v�Ȃ��̂��܂Ƃ߂��f�[�^
	void NearPolyNormal(int handle, NearPolyData* data);

	//���C�L���X�g(�u���b�N�ƃX�e�[�W�Ƃ̓����蔻��)
	//�����Fdata	�K�v�Ȃ��̂��܂Ƃ߂��f�[�^
	void BlockRayCast(int handle, RayCastData* data);

};