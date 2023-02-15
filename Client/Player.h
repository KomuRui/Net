#pragma once
#include "Engine/GameObject.h"
#include "Stage.h"
#include "Engine/Particle.h"
#include "Engine/Fbx.h"


class Player : public GameObject
{
	///////////////�L�����̕K�v�ȏ��///////////////////

	//�ϐ�

	float angleY_;                           //�L�����̏�̎��̊p�x
	float angleX_;							//�L�����̏㉺��]�̊p�x
	XMVECTOR front_;                        //�L�����̑O�����̃x�N�g��
	int   hModel_;                          //���f���ԍ�
	float gravity_;							//�L�����ɂ�����d��
	float upVelocity_;						//�㏸���x
	float attenuate_;						//���x����
	XMVECTOR vMove_;
	bool isShot_;

	///////////////�J����///////////////////

	//�ϐ�

	float camAngleX_;                        //�J�����̏㉺�̊p�x
	float camAngleY_;                        //�J������Y������̊p�x

	///////////////�����蔻��///////////////////

	//�ϐ�

	Stage* pstage_;                           //�X�e�[�W�N���X�̃|�C���^
	int    hGroundModel_;                   //�X�e�[�W�̃��f���ԍ�������ϐ�

	enum StageRayDecision                     //�e�����ւ̓����蔻�肷�邽�߂ɗ񋓂���
	{
		Straight = 0,                         //�O
		Back,                                 //��
		Left,                                 //��
		Right,                                //�E
		Under,                                //��
		Top,                                  //��
		MAX_RAY_SIZE
	};
	

public:

	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	Player(GameObject* parent);

	/////////////////////�I�[�o�[���C�h����֐�//////////////////////

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void OnCollision(GameObject* target) override;

	//�X�V�̑O�Ɉ��Ă΂��֐�
	void StartUpdate() override;

	/////////////////////�֐�//////////////////////

	//�J�����̏���
	void CameraBehavior();

	//�v���C���[����(3D�p)
	void MovingOperation();

	//���C
	void StageRayCast();

	//////////////�Q�b�g�Z�b�g�֐�///////////////

	//�O�x�N�g�����Q�b�g
	XMVECTOR GetFront() { return front_; }

	//�L�����̏㎲�̊p�x���擾
	float GetAxisAngle() { return angleY_; }
	float GetAxisAngleX() { return angleX_; }

	bool IsShot() { return isShot_; }

	void PosMove(XMFLOAT3 p);
};

