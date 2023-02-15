#pragma once
#include"Engine/GameObject.h"
class Bullet : public GameObject
{
private:

	//���f��
	int hModel_;

	//�L�����̌��ƂȂ�O�x�N�g��
	XMVECTOR front_;

	//���x
	float bulletSpeed_;

	//����
	int life_;

public:
	//�R���X�g���N�^
	Bullet(GameObject* parent);
	~Bullet();
	/////////////////////�I�[�o�[���C�h����֐�//////////////////////

	//������
	void Initialize() override;

	//�X�V�̑O�Ɉ��Ă΂��֐�
	void StartUpdate() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//�J��
	void Release() override;

	void OnCollision(GameObject* target) override;

	//////////////�Q�b�g�Z�b�g�֐�///////////////

	//���g�̔C�ӎ���]�s����Z�b�g
	void SetmMatrix(XMMATRIX m) { transform_.mmRotate_ = m; }
};

