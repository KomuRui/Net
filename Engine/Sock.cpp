#include "Sock.h"
#include "GameManager.h"
#include "../Enemy.h"

namespace
{
    static const std::string ip = "192.168.42.61";
}
//�R���X�g���N�^
Sock::Sock(GameObject* p)
{
    parent = p;
}

//������
void Sock::Initialize(std::string ipAddress)
{
    ip = ipAddress;

    // WinSock������
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // �\�P�b�g�쐬
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock > 0)
    {
        //  message.append("socket ok\r\n");
    }

    // �m���u���b�L���O�\�P�b�g�ɐݒ�
    ioctlsocket(sock, FIONBIO, &arg);
}

//�X�V
void Sock::Updata()
{
    ////////////////////////���ׂĂ̕ϐ�������//////////////////////////

    ipAddr[256] = {};
    portstr[256] = {};

    port = 0;
    ret = 0;
    arg = 0x01;
}

//��M
BOOL Sock::Receiving()
{
        if (GameManager::GetId() == 0)
        {
            //��M�f�[�^������΂����ł��̎��̏���������
            inet_ntop(AF_INET, &fromAddr.sin_addr, ipAddr, sizeof(ipAddr));
            sprintf_s(portstr, "%d", ntohs(fromAddr.sin_port));

            //��M�����̂��i�[���邽�߂̕ϐ�
            int data;

            // ��M
            ret = recvfrom(sock, (char*)&data, sizeof(data), 0, (SOCKADDR*)&fromAddr, &fromlen);

            if (ret < 0)
            {
                if (WSAGetLastError() != WSAEWOULDBLOCK)
                {
                    // �G���[

                }
                return TRUE;
            }
            else
            {
                //�ϊ�
                int id = ntohl(data);

                //�i�[
                GameManager::SetId(id);
            }
        }
        else
        {
            //��M�f�[�^������΂����ł��̎��̏���������
            inet_ntop(AF_INET, &fromAddr.sin_addr, ipAddr, sizeof(ipAddr));
            sprintf_s(portstr, "%d", ntohs(fromAddr.sin_port));

            //��M�����̂��i�[���邽�߂̕ϐ�
            SendInfo data;

            // ��M
            ret = recvfrom(sock, (char*)&data, sizeof(data), 0, (SOCKADDR*)&fromAddr, &fromlen);

            if (ret < 0)
            {
                if (WSAGetLastError() != WSAEWOULDBLOCK)
                {
                    // �G���[

                }
                return TRUE;
            }
            else
            {

                //���ۂɎg�����߂Ƀo�C�g�I�[�_�[��ϊ�
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
        
                //�Q���v���C���[�̏��������Ă���
                std::vector<std::pair<int, Enemy*>> a = GameManager::GetEnemyVec();

                //�o�^����Ă��Ȃ�
                bool isNot = true;

                //�o�^����Ă�������Enemy�̏�񂢂�Ă����p
                Enemy* enemy = nullptr;

                //���M���Ă����N���C�A���g��ID�����邩�ǂ������ׂ�
                for (auto i = a.begin(); i != a.end(); i++)
                {
                    //ID���o�^����Ă���Ȃ�
                    if ((*i).first == sendData.iD)
                    {
                        isNot = false;
                        enemy = (*i).second;
                    }
                    
                }

                //�����o�^����Ă��Ȃ��̂Ȃ�
                if (isNot)
                {
                    Enemy* p = Instantiate<Enemy>(parent);
                    GameManager::SetEnemy(std::make_pair(sendData.iD, p));
                }
                //�����o�^����Ă���̂Ȃ�
                else
                {
                    //�e�ݒ�
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

//���M
BOOL Sock::Sending(SendInfo data)
{
    //���̂܂܂��Ƒ��M�ł��Ȃ��̂Ńo�C�g�I�[�_�[��ϊ�
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

    //�A�h���X�Ƃ��|�[�g�ݒ�
    // �T�[�o�̃A�h���X���Z�b�g
    const char* SERVERIPADDRESS = ip.c_str();	// �������g���T�[�o�̏ꍇ
    SOCKADDR_IN serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));							// 0�N���A�ŏ�����
    serverAddr.sin_family = AF_INET;									// IPv4�A�h���X�g�p
    serverAddr.sin_port = htons(SERVERPORT);						    // �|�[�g�ԍ��w��
    inet_pton(AF_INET, SERVERIPADDRESS, &serverAddr.sin_addr.s_addr);

    //���M
    sendto(sock, (char*)&sendData, sizeof(sendData), 0, (SOCKADDR*)&serverAddr, sizeof(serverAddr));

    return TRUE;
}

//���r�[�̑��M
BOOL Sock::LobySending()
{
    //�A�h���X�Ƃ��|�[�g�ݒ�
    // �T�[�o�̃A�h���X���Z�b�g
    const char* SERVERIPADDRESS = ip.c_str();	// �������g���T�[�o�̏ꍇ
    SOCKADDR_IN serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));							// 0�N���A�ŏ�����
    serverAddr.sin_family = AF_INET;									// IPv4�A�h���X�g�p
    serverAddr.sin_port = htons(SERVERPORT);						    // �|�[�g�ԍ��w��
    inet_pton(AF_INET, SERVERIPADDRESS, &serverAddr.sin_addr.s_addr);

    //���M
    sendto(sock, (char*)&sendData, sizeof(sendData), 0, (SOCKADDR*)&serverAddr, sizeof(serverAddr));

    return TRUE;
}