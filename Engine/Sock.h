#pragma once
#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <string>
#include "Transform.h"
#include "GameObject.h"

#pragma comment( lib, "ws2_32.lib" )

//位置
struct Position
{
	float x;
	bool minusx;
	float y;
	bool minusy;
	float z;
	bool minusz;
};

//送る情報
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
	//サーバーポート
	const unsigned short SERVERPORT = 8080;

	//ソケット
	SOCKET sock;

	//送るデータを格納する用の変数
	SendInfo sendData;

	std::string ip;

	//親
	GameObject* parent;

	//必要な変数
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

	//コンストラクタ
	Sock(GameObject* p);

	//初期化
	void Initialize(std::string ipAddress);

	//毎回呼ぶ処理
	void Updata();

	//受信
	BOOL Receiving();

	//送信
	BOOL Sending(SendInfo data);

	//ロビーの送信
	BOOL LobySending();

};

