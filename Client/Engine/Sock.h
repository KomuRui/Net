#pragma once
#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string>
#include "Transform.h"
#include "GameObject.h"

#pragma comment( lib, "ws2_32.lib" )

//�ʒu
struct Position
{
	float x;
	bool minusx;
	float y;
	bool minusy;
	float z;
	bool minusz;
};

//������
struct SendInfo
{
	int iD;
	Position pos;
	float axisAngle;
	bool minus;
	float axisAngleX;
	bool minusX;
	bool isShot;
	bool isDead;
};

class Sock
{
	std::string ipAddress_;
	//�T�[�o�[�|�[�g
	const unsigned short SERVERPORT = 8080;

	//�\�P�b�g
	SOCKET sock;

	//����f�[�^���i�[����p�̕ϐ�
	SendInfo sendData;

	std::string ip;

	//�e
	GameObject* parent;

	//�K�v�ȕϐ�
	u_long arg = 0x01;
	int ret;
	int port;
	std::string message;
	char buff[1024];
	char ipAddr[256];
	char portstr[256];

	SOCKADDR_IN fromAddr;
	int fromlen = sizeof(fromAddr);
	SOCKADDR_IN toAddr;
	int tolen = sizeof(toAddr);

public:

	//�R���X�g���N�^
	Sock(GameObject* p);

	//������
	void Initialize(std::string ipAddress);

	//����Ăԏ���
	void Updata();

	//��M
	BOOL Receiving();

	//���M
	BOOL Sending(SendInfo data);

	//���r�[�̑��M
	BOOL LobySending();

};

