#include "Sock.h"
#include "GameManager.h"
#include "../Enemy.h"

namespace
{
    static const std::string ip = "192.168.42.61";
}
//コンストラクタ
Sock::Sock(GameObject* p)
{
    parent = p;
}

//初期化
void Sock::Initialize(std::string ipAddress)
{
    ip = ipAddress;

    // WinSock初期化
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // ソケット作成
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock > 0)
    {
        //  message.append("socket ok\r\n");
    }

    // ノンブロッキングソケットに設定
    ioctlsocket(sock, FIONBIO, &arg);
}

//更新
void Sock::Updata()
{
    ////////////////////////すべての変数初期化//////////////////////////

    ipAddr[256] = {};
    portstr[256] = {};

    port = 0;
    ret = 0;
    arg = 0x01;
}

//受信
BOOL Sock::Receiving()
{
        if (GameManager::GetId() == 0)
        {
            //受信データがあればここでその時の処理を書く
            inet_ntop(AF_INET, &fromAddr.sin_addr, ipAddr, sizeof(ipAddr));
            sprintf_s(portstr, "%d", ntohs(fromAddr.sin_port));

            //受信したのを格納するための変数
            int data;

            // 受信
            ret = recvfrom(sock, (char*)&data, sizeof(data), 0, (SOCKADDR*)&fromAddr, &fromlen);

            if (ret < 0)
            {
                if (WSAGetLastError() != WSAEWOULDBLOCK)
                {
                    // エラー

                }
                return TRUE;
            }
            else
            {
                //変換
                int id = ntohl(data);

                //格納
                GameManager::SetId(id);
            }
        }
        else
        {
            //受信データがあればここでその時の処理を書く
            inet_ntop(AF_INET, &fromAddr.sin_addr, ipAddr, sizeof(ipAddr));
            sprintf_s(portstr, "%d", ntohs(fromAddr.sin_port));

            //受信したのを格納するための変数
            SendInfo data;

            // 受信
            ret = recvfrom(sock, (char*)&data, sizeof(data), 0, (SOCKADDR*)&fromAddr, &fromlen);

            if (ret < 0)
            {
                if (WSAGetLastError() != WSAEWOULDBLOCK)
                {
                    // エラー

                }
                return TRUE;
            }
            else
            {

                //実際に使うためにバイトオーダーを変換
                sendData.iD = ntohl(data.iD);
                sendData.pos.x = ntohl(data.pos.x);
                sendData.pos.y = ntohl(data.pos.y);
                sendData.pos.z = ntohl(data.pos.z);

                if (ntohl(data.pos.minusx))
                    sendData.pos.x *= -1;
                if (ntohl(data.pos.minusy))
                    sendData.pos.y *= -1;
                if (ntohl(data.pos.minusz))
                    sendData.pos.z *= -1;

                sendData.axisAngle = ntohl(data.axisAngle);
                sendData.axisAngleX = ntohl(data.axisAngleX);
                if (ntohl(sendData.minus))
                    sendData.axisAngle *= -1;
                if (ntohl(sendData.minusX))
                    sendData.axisAngleX *= -1;

                sendData.isDead = ntohl(data.isDead);
                sendData.isShot = ntohl(data.isShot);
        
                //参加プレイヤーの情報を持ってくる
                std::vector<std::pair<int, Enemy*>> a = GameManager::GetEnemyVec();

                //登録されていない
                bool isNot = true;

                //登録されてた時そのEnemyの情報いれておく用
                Enemy* enemy = nullptr;

                //送信してきたクライアントのIDがあるかどうか調べる
                for (auto i = a.begin(); i != a.end(); i++)
                {
                    //IDが登録されているなら
                    if ((*i).first == sendData.iD)
                    {
                        isNot = false;
                        enemy = (*i).second;
                    }
                    
                }

                //もし登録されていないのなら
                if (isNot)
                {
                    Enemy* p = Instantiate<Enemy>(parent);
                    GameManager::SetEnemy(std::make_pair(sendData.iD, p));
                }
                //もし登録されているのなら
                else
                {
                    //各設定
                    enemy->PosMove(XMFLOAT3(sendData.pos.x, sendData.pos.y, sendData.pos.z));
                    enemy->SetAngle(sendData.axisAngle * 3.141565 / 180.0);
                    enemy->SetAngleX(sendData.axisAngleX * 3.141565 / 180.0);
                    enemy->SetShot(sendData.isShot);

                   // if (sendData.isDead)
                       // enemy->KillMe();
                }

            }
        }

    return TRUE;
}

//送信
BOOL Sock::Sending(SendInfo data)
{
    //このままだと送信できないのでバイトオーダーを変換
    sendData.iD = htonl(GameManager::GetId());
    sendData.pos.x = htonl(abs(data.pos.x));
    sendData.pos.minusx = htonl((data.pos.x < 0));
    sendData.pos.y = htonl(abs(data.pos.y));
    sendData.pos.minusy = htonl((data.pos.y < 0));
    sendData.pos.z = htonl(abs(data.pos.z));
    sendData.pos.minusz = htonl((data.pos.z < 0));
    sendData.axisAngle = htonl(abs(data.axisAngle * 180.0 / 3.141565));
    sendData.minus = htonl((data.axisAngle * 180.0 / 3.141565) < 0);
    sendData.axisAngleX = htonl(abs(data.axisAngleX * 180.0 / 3.141565));
    sendData.minusX = htonl((data.axisAngleX * 180.0 / 3.141565) < 0);
    sendData.isDead = htonl(data.isDead);
    sendData.isShot = htonl(data.isShot);

    //アドレスとかポート設定
    // サーバのアドレス情報セット
    const char* SERVERIPADDRESS = ip.c_str();	// 自分自身がサーバの場合
    SOCKADDR_IN serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));							// 0クリアで初期化
    serverAddr.sin_family = AF_INET;									// IPv4アドレス使用
    serverAddr.sin_port = htons(SERVERPORT);						    // ポート番号指定
    inet_pton(AF_INET, SERVERIPADDRESS, &serverAddr.sin_addr.s_addr);

    //送信
    sendto(sock, (char*)&sendData, sizeof(sendData), 0, (SOCKADDR*)&serverAddr, sizeof(serverAddr));

    return TRUE;
}

//ロビーの送信
BOOL Sock::LobySending()
{
    //アドレスとかポート設定
    // サーバのアドレス情報セット
    const char* SERVERIPADDRESS = ip.c_str();	// 自分自身がサーバの場合
    SOCKADDR_IN serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));							// 0クリアで初期化
    serverAddr.sin_family = AF_INET;									// IPv4アドレス使用
    serverAddr.sin_port = htons(SERVERPORT);						    // ポート番号指定
    inet_pton(AF_INET, SERVERIPADDRESS, &serverAddr.sin_addr.s_addr);

    //送信
    sendto(sock, (char*)&sendData, sizeof(sendData), 0, (SOCKADDR*)&serverAddr, sizeof(serverAddr));

    return TRUE;
}