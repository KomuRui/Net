#include "Image.h"
#include "SceneManager.h"
#include "Input.h"
#include "ImGuiSet.h"
#include "Model.h"
#include "SphereCollider.h"
#include "..\imgui\\imgui.h"
#include "..\imgui\\imgui_impl_win32.h"
#include "..\imgui\\imgui_impl_dx11.h"
#include <fstream>
#include "Light.h"
#include"../Engine/GameManager.h"
#include "CameraTransitionObject.h"

//�R���X�g���N�^
ImGuiSet::ImGuiSet(GameObject* parent)
	: GameObject(parent, "ImGuiSet"), Create3Dflag(false), ObjectCount(0), CreateSigeboardflag(false),SigeboardCount(0), CreateCameraTransitionflag(false),CameraTransitionCount(0)
{
}

//������
void ImGuiSet::Initialize()
{
}

//�X�V
void ImGuiSet::Update()
{
}

//�`��
void ImGuiSet::Draw()
{
    //Imgui�X�^�[�g
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
    //window���
    ImGui::Begin("StagePosition");

    //Player* pPlayer = (Player*)FindObject("Player");
    //XMFLOAT3 pos = { pPlayer->GetPosition().x,pPlayer->GetPosition().y,pPlayer->GetPosition().z };
    
    //ImGui::Text("x");
    //ImGui::InputFloat("x", &pos.x, -2000000.0f, 2000000.0f);
    //ImGui::Text("y");
    //ImGui::InputFloat("y", &pos.y, -2000000.0f, 2000000.0f);
    //ImGui::Text("z");
    //ImGui::InputFloat("z", &pos.z, -2000000.0f, 2000000.0f);

    ////3D�����{�^��
    //if (ImGui::Button("Create3D"))
    //{
    //    Create3Dflag = true;
    //    ObjectCount++;
    //}

    ////�Ŕ����{�^��
    //if (ImGui::Button("CreateSigeboard"))
    //{
    //    CreateSigeboardflag = true;
    //    SigeboardCount++;
    //}

    ////�J�����{�^��
    //if (ImGui::Button("CreateCameraTransition"))
    //{
    //    CreateCameraTransitionflag = true;
    //    CameraTransitionCount++;
    //}


    ////flag��true�Ȃ�֐����Ăяo��
    //if (Create3Dflag)
    //{
    //    Create3D();
    //}

    ////flag��true�Ȃ�֐����Ăяo��
    //if (CreateSigeboardflag)
    //{
    //    CreateSigeboard();
    //}

    ////flag��true�Ȃ�֐����Ăяo��
    //if (CreateCameraTransitionflag)
    //{
    //    CreateCameraTransition();
    //}

    ImGui::End();

    ImGui::Render();
    //�`��
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

//void ImGuiSet::Create3D()
//{
//    //�e�I�u�W�F�N�g�̏��
//    static int status[MAX_OBJECT_SIZE] = {};
//    static Mob* pNewObject[MAX_OBJECT_SIZE];
//    static XMFLOAT3 pos[MAX_OBJECT_SIZE];
//    static XMFLOAT3 rotate[MAX_OBJECT_SIZE];
//    static XMFLOAT3 scale[MAX_OBJECT_SIZE];
//    static XMFLOAT3 BasicPos = pPlayer_->GetPosition();
//    static XMFLOAT3 BasicRotate = pPlayer_->GetRotate();
//    static XMFLOAT3 BasicScale = pPlayer_->GetScale();
//      
//    //Create3D�����������E�B���h�E�����@
//    for (int i = 0; i < ObjectCount; i++)
//    {
//        if (status[i] == 1 || status[i] == 0)
//        {
//            //i��FBX�̌��ɂ���
//            char name[16];
//            sprintf_s(name, "FBX %d", i);
//
//            //window���
//            ImGui::Begin(name);
//
//            //�t�@�C���l�[�����͗�
//            static char text1[MAX_OBJECT_SIZE][50] = {};
//
//            //���͂��ꂽ������text1�Ɋi�[
//            ImGui::InputText("FBX filename", text1[i], sizeof(text1[i]));
//
//            //���[�h�{�^��
//            if (ImGui::Button("Load"))
//            {
//                //�����܂��������[�h���ĂȂ�������
//                if (status[i] == 0)
//                {
//
//                    //���[�h�����I�u�W�F�N�g�ɕK�v�ȃg�����X�t�H�[����p��
//                    Transform t;
//
//                    pos[i] = BasicPos;
//                    rotate[i] = BasicRotate;
//                    scale[i] = BasicScale;
//
//                    //�v�b�V�����邽�߂�pair�^�����
//                    //first->���[�h�������f���ԍ�
//                    //second->���[�h�������f����transform
//                    std::pair<int, Transform> a(Model::Load(text1[i]), t);
//                    assert(a.first > 0);
//
//                    //vector�Ɋi�[����
//                    obj.push_back(a);
//
//                    pNewObject[i] = new Mob(this, text1[i],"");
//                    if (GetParent() != nullptr)
//                    {
//                        this->PushBackChild(pNewObject[i]);
//                    }
//                    pNewObject[i]->Initialize();
//
//                    //status�v���X
//                    status[i]++;
//
//                }
//            }
//
//            //��񃍁[�h���Ă�����
//            if (status[i] == 1)
//            {
//
//                //Position�̖�
//                if (ImGui::TreeNode("position")) {
//
//                    //Position�Z�b�g
//                    ImGui::SliderFloat("x", &pos[i].x, -200.0f, 200.0f);
//                    ImGui::SliderFloat("y", &pos[i].y, -200.0f, 200.0f);
//                    ImGui::SliderFloat("z", &pos[i].z, -200.0f, 200.0f);
//
//                    if (ImGui::TreeNode("InputPosition")) {
//
//                        ImGui::Text("x");
//                        ImGui::InputFloat("x", &pos[i].x, -20.0f, 20.0f);
//                        ImGui::Text("y");
//                        ImGui::InputFloat("y", &pos[i].y, -20.0f, 20.0f);
//                        ImGui::Text("z");
//                        ImGui::InputFloat("z", &pos[i].z, -20.0f, 20.0f);
//
//                        ImGui::TreePop();
//                    }
//
//                    ImGui::TreePop();
//                }
//
//                //Scale�̖�
//                if (ImGui::TreeNode("scale")) {
//
//                    //Scale�Z�b�g
//                    ImGui::SliderFloat("x", &scale[i].x, -20.0f, 20.0f);
//                    ImGui::SliderFloat("y", &scale[i].y, -20.0f, 20.0f);
//                    ImGui::SliderFloat("z", &scale[i].z, -20.0f, 20.0f);
//
//                    if (ImGui::TreeNode("InputScale")) {
//
//                        ImGui::Text("x");
//                        ImGui::InputFloat("x", &scale[i].x, -20.0f, 20.0f);
//                        ImGui::Text("y");
//                        ImGui::InputFloat("y", &scale[i].y, -20.0f, 20.0f);
//                        ImGui::Text("z");
//                        ImGui::InputFloat("z", &scale[i].z, -20.0f, 20.0f);
//
//                        ImGui::TreePop();
//                    }
//
//                    ImGui::TreePop();
//                }
//
//                //rotate�̖�
//                if (ImGui::TreeNode("rotate")) {
//
//                    //Rotate�Z�b�g
//                    ImGui::SliderFloat("x", &rotate[i].x, 0.0f, 360.0f);
//                    ImGui::SliderFloat("y", &rotate[i].y, 0.0f, 360.0f);
//                    ImGui::SliderFloat("z", &rotate[i].z, 0.0f, 360.0f);
//
//                    if (ImGui::TreeNode("rotate")) {
//
//                        ImGui::Text("x");
//                        ImGui::InputFloat("x", &rotate[i].x, -20.0f, 20.0f);
//                        ImGui::Text("y");
//                        ImGui::InputFloat("y", &rotate[i].y, -20.0f, 20.0f);
//                        ImGui::Text("z");
//                        ImGui::InputFloat("z", &rotate[i].z, -20.0f, 20.0f);
//
//                        ImGui::TreePop();
//                    }
//
//                    ImGui::TreePop();
//                }
//
//                if (ImGui::TreeNode("StageSave")) {
//
//                    //�t�@�C���l�[�����͗�
//                    static char text2[MAX_OBJECT_SIZE][50] = {};
//
//                    //���͂��ꂽ������text1�Ɋi�[
//                    ImGui::InputText("ObjName", text2[i], sizeof(text2[i]));
//
//                    if (ImGui::Button("Save"))
//                    {
//                        BasicPos = { pos[i] };
//                        BasicRotate = { rotate[i] };
//                        BasicScale = { scale[i] };
//
//                        const char* fileName = "Stage/World/World1/StageInformation/WorldStage1.txt";
//                        std::ofstream ofs;
//                        ofs.open(fileName, std::ios::app);
//
//                        ofs << std::endl;
//
//                        ofs << text1[i] << "," <<text2[i] << "," << pos[i].x << "," << pos[i].y << "," << pos[i].z << ","
//                            << rotate[i].x << "," << rotate[i].y << "," << rotate[i].z << ","
//                            << scale[i].x << "," << scale[i].y << "," << scale[i].z;
//
//                        ofs.close();
//                    }
//                    ImGui::TreePop();
//                }
//
//                //�E�B���h�E�폜
//                if (ImGui::Button("close"))
//                {
//                    status[i]++;
//                }
//            }
//
//            ImGui::End();
//        }
//
//        //�`�悳���
//        if (status[i] >= 1)
//        {
//            pNewObject[i]->SetPosition(pos[i]);
//            pNewObject[i]->SetRotate(rotate[i]);
//            pNewObject[i]->SetScale(scale[i]);
//        }
//    }
//}
//
//void ImGuiSet::CreateSigeboard()
//{
//    //�e�I�u�W�F�N�g�̏��
//    static int Sstatus[MAX_OBJECT_SIZE] = {};
//    static Signboard* SpNewObject[MAX_OBJECT_SIZE];
//    static XMFLOAT3 Spos[MAX_OBJECT_SIZE];
//    static XMFLOAT3 Srotate[MAX_OBJECT_SIZE];
//    static XMFLOAT3 Sscale[MAX_OBJECT_SIZE];
//    static XMFLOAT3 SBasicPos = pPlayer_->GetPosition();
//    static XMFLOAT3 SBasicRotate = pPlayer_->GetRotate();
//    static XMFLOAT3 SBasicScale = pPlayer_->GetScale();
//
//    //Create3D�����������E�B���h�E�����@
//    for (int i = 0; i < SigeboardCount; i++)
//    {
//        if (Sstatus[i] == 1 || Sstatus[i] == 0)
//        {
//            //i��FBX�̌��ɂ���
//            char name[16];
//            sprintf_s(name, "FBX %d", i);
//
//            //window���
//            ImGui::Begin(name);
//
//            //�t�@�C���l�[�����͗�
//            static char Stext1[MAX_OBJECT_SIZE][50] = {};
//
//            //���͂��ꂽ������text1�Ɋi�[
//            ImGui::InputText("FBX filename", Stext1[i], sizeof(Stext1[i]));
//
//            //���[�h�{�^��
//            if (ImGui::Button("Load"))
//            {
//                //�����܂��������[�h���ĂȂ�������
//                if (Sstatus[i] == 0)
//                {
//
//                    //���[�h�����I�u�W�F�N�g�ɕK�v�ȃg�����X�t�H�[����p��
//                    Transform t;
//
//                    Spos[i] = SBasicPos;
//                    Srotate[i] = SBasicRotate;
//                    Sscale[i] = SBasicScale;
//
//                    ////�v�b�V�����邽�߂�pair�^�����
//                    ////first->���[�h�������f���ԍ�
//                    ////second->���[�h�������f����transform
//                    //std::pair<int, Transform> a(Model::Load(text1[i]), t);
//                    //assert(a.first > 0);
//
//                    ////vector�Ɋi�[����
//                    //obj.push_back(a);
//
//                    SpNewObject[i] = new Signboard(this, Stext1[i], "");
//                    if (GetParent() != nullptr)
//                    {
//                        this->PushBackChild(SpNewObject[i]);
//                    }
//                    SpNewObject[i]->Initialize();
//
//                    //status�v���X
//                    Sstatus[i]++;
//
//                }
//            }
//
//            //��񃍁[�h���Ă�����
//            if (Sstatus[i] == 1)
//            {
//
//                //Position�̖�
//                if (ImGui::TreeNode("position")) {
//
//                    //Position�Z�b�g
//                    ImGui::SliderFloat("x", &Spos[i].x, -200.0f, 200.0f);
//                    ImGui::SliderFloat("y", &Spos[i].y, -200.0f, 200.0f);
//                    ImGui::SliderFloat("z", &Spos[i].z, -200.0f, 200.0f);
//
//                    if (ImGui::TreeNode("InputPosition")) {
//
//                        ImGui::Text("x");
//                        ImGui::InputFloat("x", &Spos[i].x, -20.0f, 20.0f);
//                        ImGui::Text("y");
//                        ImGui::InputFloat("y", &Spos[i].y, -20.0f, 20.0f);
//                        ImGui::Text("z");
//                        ImGui::InputFloat("z", &Spos[i].z, -20.0f, 20.0f);
//
//                        ImGui::TreePop();
//                    }
//
//                    ImGui::TreePop();
//                }
//
//                //Scale�̖�
//                if (ImGui::TreeNode("scale")) {
//
//                    //Scale�Z�b�g
//                    ImGui::SliderFloat("x", &Sscale[i].x, -20.0f, 20.0f);
//                    ImGui::SliderFloat("y", &Sscale[i].y, -20.0f, 20.0f);
//                    ImGui::SliderFloat("z", &Sscale[i].z, -20.0f, 20.0f);
//
//                    if (ImGui::TreeNode("InputScale")) {
//
//                        ImGui::Text("x");
//                        ImGui::InputFloat("x", &Sscale[i].x, -20.0f, 20.0f);
//                        ImGui::Text("y");
//                        ImGui::InputFloat("y", &Sscale[i].y, -20.0f, 20.0f);
//                        ImGui::Text("z");
//                        ImGui::InputFloat("z", &Sscale[i].z, -20.0f, 20.0f);
//
//                        ImGui::TreePop();
//                    }
//
//                    ImGui::TreePop();
//                }
//
//                //rotate�̖�
//                if (ImGui::TreeNode("rotate")) {
//
//                    //Rotate�Z�b�g
//                    ImGui::SliderFloat("x", &Srotate[i].x, 0.0f, 360.0f);
//                    ImGui::SliderFloat("y", &Srotate[i].y, 0.0f, 360.0f);
//                    ImGui::SliderFloat("z", &Srotate[i].z, 0.0f, 360.0f);
//
//                    if (ImGui::TreeNode("rotate")) {
//
//                        ImGui::Text("x");
//                        ImGui::InputFloat("x", &Srotate[i].x, -20.0f, 20.0f);
//                        ImGui::Text("y");
//                        ImGui::InputFloat("y", &Srotate[i].y, -20.0f, 20.0f);
//                        ImGui::Text("z");
//                        ImGui::InputFloat("z", &Srotate[i].z, -20.0f, 20.0f);
//
//                        ImGui::TreePop();
//                    }
//
//                    ImGui::TreePop();
//                }
//
//                if (ImGui::TreeNode("StageSave")) {
//
//                    //�t�@�C���l�[�����͗�
//                    static char Stext2[MAX_OBJECT_SIZE][50] = {};
//
//                    //���͂��ꂽ������text1�Ɋi�[
//                    ImGui::InputText("ObjName", Stext2[i], sizeof(Stext2[i]));
//
//                    if (ImGui::Button("Save"))
//                    {
//                        SBasicPos = { Spos[i] };
//                        SBasicRotate = { Srotate[i] };
//                        SBasicScale = { Sscale[i] };
//
//                        const char* fileName = "Stage/World/World1/StageInformation/WorldStage1.txt";
//                        std::ofstream ofs;
//                        ofs.open(fileName, std::ios::app);
//
//                        ofs << std::endl;
//
//                        ofs << Stext1[i] << "," << Stext2[i] << "," << Spos[i].x << "," << Spos[i].y << "," << Spos[i].z << ","
//                            << Srotate[i].x << "," << Srotate[i].y << "," << Srotate[i].z << ","
//                            << Sscale[i].x << "," << Sscale[i].y << "," << Sscale[i].z;
//
//                        ofs.close();
//                    }
//                    ImGui::TreePop();
//                }
//
//                //�E�B���h�E�폜
//                if (ImGui::Button("close"))
//                {
//                    Sstatus[i]++;
//                }
//            }
//
//            ImGui::End();
//        }
//
//        //�`�悳���
//        if (Sstatus[i] >= 1)
//        {
//            SpNewObject[i]->SetPosition(Spos[i]);
//            SpNewObject[i]->SetRotate(Srotate[i]);
//            SpNewObject[i]->SetScale(Sscale[i]);
//        }
//    }
//}
//
////�J�����̑J�ڍ쐬(�R���C�_�[�ɓ���������J�����̃|�W�V�����ς���@�\)
//void ImGuiSet::CreateCameraTransition()
//{
//    //�e�I�u�W�F�N�g�̏��
//    static int Cstatus[MAX_OBJECT_SIZE] = {};
//    static Mob* CpNewObject[MAX_OBJECT_SIZE];
//    static XMFLOAT3 Cpos[MAX_OBJECT_SIZE];
//    static XMFLOAT3 CcameraPos[MAX_OBJECT_SIZE];
//    static XMFLOAT3 CcameraTar[MAX_OBJECT_SIZE];
//    static XMFLOAT3 CcolliderSize[MAX_OBJECT_SIZE];
//    static XMFLOAT3 CBasicPos = pPlayer_->GetPosition();
//    static XMFLOAT3 CBasicRotate = pPlayer_->GetRotate();
//    static XMFLOAT3 CBasicScale = pPlayer_->GetScale();
//
//    //Create3D�����������E�B���h�E�����@
//    for (int i = 0; i < CameraTransitionCount; i++)
//    {
//        if (Cstatus[i] == 1 || Cstatus[i] == 0)
//        {
//            //i��FBX�̌��ɂ���
//            char name[16];
//            sprintf_s(name, "FBX %d", i);
//
//            //window���
//            ImGui::Begin(name);
//
//            //�t�@�C���l�[�����͗�
//            static char text1[MAX_OBJECT_SIZE][50] = {};
//
//            //���͂��ꂽ������text1�Ɋi�[
//            ImGui::InputText("FBX filename", text1[i], sizeof(text1[i]));
//
//            //���[�h�{�^��
//            if (ImGui::Button("Load"))
//            {
//                //�����܂��������[�h���ĂȂ�������
//                if (Cstatus[i] == 0)
//                {
//
//                    //���[�h�����I�u�W�F�N�g�ɕK�v�ȃg�����X�t�H�[����p��
//                    Transform t;
//
//                    Cpos[i] = CBasicPos;
//                    CcameraTar[i] = CBasicRotate;
//                    CcolliderSize[i] = CBasicScale;
//
//                    //�v�b�V�����邽�߂�pair�^�����
//                    //first->���[�h�������f���ԍ�
//                    //second->���[�h�������f����transform
//                    std::pair<int, Transform> a(Model::Load(text1[i]), t);
//                    assert(a.first > 0);
//
//                    //vector�Ɋi�[����
//                    obj.push_back(a);
//
//                    CpNewObject[i] = new Mob(this, text1[i], "");
//                    if (GetParent() != nullptr)
//                    {
//                        this->PushBackChild(CpNewObject[i]);
//                    }
//                    CpNewObject[i]->Initialize();
//
//                    //status�v���X
//                    Cstatus[i]++;
//
//                }
//            }
//
//            //��񃍁[�h���Ă�����
//            if (Cstatus[i] == 1)
//            {
//
//                //Position�̖�
//                if (ImGui::TreeNode("position")) {
//
//                    //Position�Z�b�g
//                    ImGui::SliderFloat("x", &Cpos[i].x, -200.0f, 200.0f);
//                    ImGui::SliderFloat("y", &Cpos[i].y, -200.0f, 200.0f);
//                    ImGui::SliderFloat("z", &Cpos[i].z, -200.0f, 200.0f);
//
//                    if (ImGui::TreeNode("InputPosition")) {
//
//                        ImGui::Text("x");
//                        ImGui::InputFloat("x", &Cpos[i].x, -200.0f, 200.0f);
//                        ImGui::Text("y");
//                        ImGui::InputFloat("y", &Cpos[i].y, -200.0f, 200.0f);
//                        ImGui::Text("z");
//                        ImGui::InputFloat("z", &Cpos[i].z, -200.0f, 200.0f);
//
//                        ImGui::TreePop();
//                    }
//
//                    ImGui::TreePop();
//                }
//
//                //Position�̖�
//                if (ImGui::TreeNode("CameraPosition")) {
//
//                    //Position�Z�b�g
//                    ImGui::SliderFloat("x", &CcameraPos[i].x, -200.0f, 200.0f);
//                    ImGui::SliderFloat("y", &CcameraPos[i].y, -200.0f, 200.0f);
//                    ImGui::SliderFloat("z", &CcameraPos[i].z, -200.0f, 200.0f);
//
//                    if (ImGui::TreeNode("CameraInputPosition")) {
//
//                        ImGui::Text("x");
//                        ImGui::InputFloat("x", &CcameraPos[i].x, -200.0f, 200.0f);
//                        ImGui::Text("y");
//                        ImGui::InputFloat("y", &CcameraPos[i].y, -200.0f, 200.0f);
//                        ImGui::Text("z");
//                        ImGui::InputFloat("z", &CcameraPos[i].z, -200.0f, 200.0f);
//
//                        ImGui::TreePop();
//                    }
//
//                    ImGui::TreePop();
//                }
//
//                //Scale�̖�
//                if (ImGui::TreeNode("scale")) {
//
//                    //Scale�Z�b�g
//                    ImGui::SliderFloat("x", &CcolliderSize[i].x, -20.0f, 20.0f);
//                    ImGui::SliderFloat("y", &CcolliderSize[i].y, -20.0f, 20.0f);
//                    ImGui::SliderFloat("z", &CcolliderSize[i].z, -20.0f, 20.0f);
//
//                    if (ImGui::TreeNode("InputScale")) {
//
//                        ImGui::Text("x");
//                        ImGui::InputFloat("x", &CcolliderSize[i].x, -20.0f, 20.0f);
//                        ImGui::Text("y");
//                        ImGui::InputFloat("y", &CcolliderSize[i].y, -20.0f, 20.0f);
//                        ImGui::Text("z");
//                        ImGui::InputFloat("z", &CcolliderSize[i].z, -20.0f, 20.0f);
//
//                        ImGui::TreePop();
//                    }
//
//                    ImGui::TreePop();
//                }
//
//                //rotate�̖�
//                if (ImGui::TreeNode("rotate")) {
//
//                    //Rotate�Z�b�g
//                    ImGui::SliderFloat("x", &CcameraTar[i].x, 0.0f, 360.0f);
//                    ImGui::SliderFloat("y", &CcameraTar[i].y, 0.0f, 360.0f);
//                    ImGui::SliderFloat("z", &CcameraTar[i].z, 0.0f, 360.0f);
//
//                    if (ImGui::TreeNode("rotate")) {
//
//                        ImGui::Text("x");
//                        ImGui::InputFloat("x", &CcameraTar[i].x, -20.0f, 20.0f);
//                        ImGui::Text("y");
//                        ImGui::InputFloat("y", &CcameraTar[i].y, -20.0f, 20.0f);
//                        ImGui::Text("z");
//                        ImGui::InputFloat("z", &CcameraTar[i].z, -20.0f, 20.0f);
//
//                        ImGui::TreePop();
//                    }
//
//                    ImGui::TreePop();
//                }
//
//                if (ImGui::TreeNode("StageSave")) {
//
//                    //�t�@�C���l�[�����͗�
//                    static char text2[MAX_OBJECT_SIZE][50] = {};
//
//                    //���͂��ꂽ������text1�Ɋi�[
//                    ImGui::InputText("ObjName", text2[i], sizeof(text2[i]));
//
//                    if (ImGui::Button("Save"))
//                    {
//                        CBasicPos = { Cpos[i] };
//                        CBasicRotate = { CcameraTar[i] };
//                        CBasicScale = { CcolliderSize[i] };
//
//                        const char* fileName = "Stage/World/World1/StageInformation/WorldStage1.txt";
//                        std::ofstream ofs;
//                        ofs.open(fileName, std::ios::app);
//
//                        ofs << std::endl;
//
//                        ofs << text1[i] << "," << text2[i] << "," << Cpos[i].x << "," << Cpos[i].y << "," << Cpos[i].z << ","
//                            << CcameraTar[i].x << "," << CcameraTar[i].y << "," << CcameraTar[i].z << ","
//                            << CcolliderSize[i].x * 2 << "," << CcolliderSize[i].y * 2<< "," << CcolliderSize[i].z<< ","
//                            << CcameraPos[i].x << "," << CcameraPos[i].y << "," << CcameraPos[i].z;
//
//                        ofs.close();
//                    }
//                    ImGui::TreePop();
//                }
//
//                //�E�B���h�E�폜
//                if (ImGui::Button("close"))
//                {
//                    Cstatus[i]++;
//                }
//            }
//
//            ImGui::End();
//        }
//
//        //�`�悳���
//        if (Cstatus[i] >= 1)
//        {
//            CpNewObject[i]->SetPosition(Cpos[i]);
//            CpNewObject[i]->SetRotate(CcameraTar[i]);
//            CpNewObject[i]->SetScale(CcolliderSize[i]);
//        }
//    }
//}

//�J��
void ImGuiSet::Release()
{
}

void ImGuiSet::StartUpdate()
{
    pPlayer_ = (Player*)FindObject("Player");
}

void ImGuiSet::CreateStage(std::string filename)
{
    const char* fileName = filename.c_str();
    std::ifstream ifs(fileName);

    std::string buf;
    std::string data[14] = {""};

    int sum = 0;

    while (!ifs.eof())
    {
        std::getline(ifs, buf);
        
        for(int i = 0; i < buf.size(); i++)
        {
            if (buf[i] != ',')
            {
                data[sum] += buf[i];
            }
            else
                sum++;
        }

        std::string ModelPathName = data[0];
        std::string Name = data[1];

        Transform t;

        t.position_ = { std::stof(data[2]),std::stof(data[3]),std::stof(data[4]) };
        t.rotate_ = { std::stof(data[5]),std::stof(data[6]),std::stof(data[7]) };
        t.scale_ = { std::stof(data[8]),std::stof(data[9]),std::stof(data[10]) };

        XMFLOAT3 camPos;

        if(Name == "Camera")
            camPos = { std::stof(data[11]),std::stof(data[12]),std::stof(data[13]) };
        else
            camPos = { 0,0,0 };

        InstantiateString(ModelPathName,Name, t, camPos);


        for (int i = 0; i < 11; i++)
        {
            data[i] = "";
        }
        sum = 0;
    }

    
}

void ImGuiSet::InstantiateString(std::string ModelPathName, std::string inName,Transform t, XMFLOAT3 camPos)
{

    /////////////////////Camera////////////////////////

    if (inName == "Camera")
    {
        //�J������������ϐ��p��
        StageCameraTransition information;

        //�e��񏉊���
        information.CameraPosition = camPos;
        information.CameraTarget = t.rotate_;
        information.CollisionSize = t.scale_;

        //�R���X�g���N�^�Ă�
        CameraTransitionObject* pNewObject = new CameraTransitionObject(this, information);
        if (GetParent() != nullptr)
        {
            this->GetParent()->PushBackChild(pNewObject);
        }

        //��]�Ɗg���0�ɏ���������
        ARGUMENT_INITIALIZE(t.rotate_, XMFLOAT3(0, 0, 0));
        ARGUMENT_INITIALIZE(t.scale_, XMFLOAT3(0, 0, 0));

        pNewObject->SetTransform(t);
        pNewObject->Initialize();

        //�J��������ۑ�
        CameraTransition.push_back(information);
    }

    /////////////////////Light/////////////////////////
    
    if (inName == "Light")
    {
        Light::SetPositionAndIntensity(XMFLOAT4(t.position_.x, t.position_.y, t.position_.z,0),t.scale_.x);
    }


}

