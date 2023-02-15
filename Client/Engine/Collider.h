#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;

//�N���X�̑O���錾
class GameObject;
class BoxCollider;
class SphereCollider;


//�����蔻��̃^�C�v
enum ColliderType
{
	COLLIDER_BOX,		//���^
	COLLIDER_CIRCLE		//����
};

//-----------------------------------------------------------
//�����蔻����Ǘ�����N���X
//-----------------------------------------------------------
class Collider
{
	//���ꂼ��̃N���X��private�����o�ɃA�N�Z�X�ł���悤�ɂ���
	friend class BoxCollider;
	friend class SphereCollider;

protected:
	GameObject*		pGameObject_;	//���̔���������Q�[���I�u�W�F�N�g
	ColliderType	type_;			//���
	XMFLOAT3		center_;		//���S�ʒu�i�Q�[���I�u�W�F�N�g�̌��_���猩���ʒu�j
	XMFLOAT3		size_;			//����T�C�Y�i���A�����A���s���j
	int				hDebugModel_;	//�f�o�b�O�\���p�̃��f����ID
	bool            rotateflag_;

public:
	//�R���X�g���N�^
	Collider();

	//�f�X�g���N�^
	virtual ~Collider();

	//�ڐG����i�p�����SphereCollider��BoxCollider�ŃI�[�o�[���C�h�j
	//�����Ftarget	����̓����蔻��
	//�ߒl�F�ڐG���Ă��true
	virtual bool IsHit(Collider* target) = 0;

	//���^���m�̏Փ˔���
	//�����FboxA	�P�ڂ̔��^����
	//�����FboxB	�Q�ڂ̔��^����
	//�ߒl�F�ڐG���Ă����true
	bool IsHitBoxVsBox(BoxCollider* boxA, BoxCollider* boxB);

	//���^�Ƌ��̂̏Փ˔���
	//�����Fbox	���^����
	//�����Fsphere	�Q�ڂ̔��^����
	//�ߒl�F�ڐG���Ă����true
	bool IsHitBoxVsCircle(BoxCollider* box, SphereCollider* sphere);

	//���̓��m�̏Փ˔���
	//�����FcircleA	�P�ڂ̋��̔���
	//�����FcircleB	�Q�ڂ̋��̔���
	//�ߒl�F�ڐG���Ă����true
	bool IsHitCircleVsCircle(SphereCollider* circleA, SphereCollider* circleB);

	//�e�X�g�\���p�̘g��`��
	//�����Fposition	�I�u�W�F�N�g�̈ʒu
	void Draw(XMFLOAT3 position, XMFLOAT3 rotate);

	//�Z�b�^�[
	void SetGameObject(GameObject* gameObject) { pGameObject_ = gameObject; }

	//�Z�b�^�[
	void SetPos(XMFLOAT3 pos) { center_ = pos; }

	//�Z�b�^�[
	void SetSize(XMFLOAT3 scale) { size_ = scale; }

	//�Z�b�^�[
	void SetSizePos(XMFLOAT3 scale, XMFLOAT3 pos) { size_ = scale; center_ = pos; }

	//Get
	XMFLOAT3 Getcenter() { return center_; }

	//���a�Q�b�g
	float GetRadius() { return size_.x; }
};
