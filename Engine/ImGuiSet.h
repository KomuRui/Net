#pragma once
#include <vector>
#include "GameObject.h"
#include "../Player.h"

//�ő��Imgui�ŏo����I�u�W�F�N�g�T�C�Y
const int MAX_OBJECT_SIZE = 50;

//�e�X�e�[�W�ŃJ�����J�ڂ���Ƃ��̕K�v�ȏ��
struct StageCameraTransition
{
	XMFLOAT3 CameraPosition;  //�J�����̃|�W�V����
	XMFLOAT3 CameraTarget;    //�J�����̃^�[�Q�b�g
	XMFLOAT3 CollisionSize;   //�R���C�_�[�̃T�C�Y
};

//�����V�[�����Ǘ�����N���X
class ImGuiSet : public GameObject
{
	//�\���������I�u�W�F�N�g���i�[����ꏊ
	//first->���f���ԍ�
	//second->���f���ԍ����Ƃ̃g�����X�t�H�[��
	std::vector<std::pair<int,Transform>>obj;

	//3D�����{�^���������Ă�����true
	bool Create3Dflag;

	//�Ŕ����{�^������������
	bool CreateSigeboardflag;

	//�J�����J�ڂ����{�^������������
	bool CreateCameraTransitionflag;

	//3D�����������
	int ObjectCount;

	//�Ŕ��������
	int SigeboardCount;

	//�J�����J�ڂ����������
	int CameraTransitionCount;

	//�g�����X�t�H�[���ۑ����邽�߂Ɏ����Ă���
	Player* pPlayer_;

	//�e�X�e�[�W�̃J�����J�ڂ���Ƃ��̊e����ۑ�
	std::vector<StageCameraTransition> CameraTransition;

public:
	//�R���X�g���N�^
	//�����Fparent  �e�I�u�W�F�N�g�iSceneManager�j
	ImGuiSet(GameObject* parent);

	//������
	void Initialize() override;

	//�X�V
	void Update() override;

	//�`��
	void Draw() override;

	//3D�I�u�W�F�N�g�쐬
	void Create3D();

	//�Ŕ쐬
	void CreateSigeboard();

	//�J�����̑J�ڍ쐬(�R���C�_�[�ɓ���������J�����̃|�W�V�����ς���@�\)
	void CreateCameraTransition();

	//�J��
	void Release() override;

	void StartUpdate() override;

	void CreateStage(std::string filename);

	void InstantiateString(std::string ModelPathName, std::string inName, Transform t,XMFLOAT3 camPos);
};