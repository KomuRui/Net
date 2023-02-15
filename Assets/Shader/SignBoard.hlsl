//������������������������������������������������������������������������������
 // �e�N�X�`�����T���v���[�f�[�^�̃O���[�o���ϐ���`
//������������������������������������������������������������������������������
Texture2D		g_texture: register(t0);	//�e�N�X�`���[
SamplerState	g_sampler : register(s0);	//�T���v���[

//������������������������������������������������������������������������������
 // �R���X�^���g�o�b�t�@
// DirectX �����瑗�M����Ă���A�|���S�����_�ȊO�̏����̒�`
//������������������������������������������������������������������������������
cbuffer global
{
	float4x4	g_matWVP;			  // ���[���h�E�r���[�E�v���W�F�N�V�����̍����s��
	float4x4	g_matNormalTrans;	  // �@���̕ϊ��s��i��]�s��Ɗg��̋t�s��j
	float4x4	g_matWorld;			  // ���[���h�ϊ��s��
	float4		g_vecLightDir;		  // ���C�g�̕����x�N�g��
	float4		g_vecCameraPosition;  // ���_�i�J�����̈ʒu�j
	float4      g_vecLightPosition;   // ���C�g�̈ʒu
	float4      g_aaaaa[3];           // �J�����̌����̈ʒu
	int         g_isLightIntensity;   // ���C�g�̋���
	float       g_isBrightness;       // ���邳
};

//������������������������������������������������������������������������������
// ���_�V�F�[�_�[�o�́��s�N�Z���V�F�[�_�[���̓f�[�^�\����
//������������������������������������������������������������������������������
struct VS_OUT
{
	float4 pos    : SV_POSITION;	//�ʒu
	float4 normal : TEXCOORD2;		//�@��
	float2 uv	  : TEXCOORD0;		//UV���W
	float4 eye	  : TEXCOORD1;		//����
	float4 norw   : TEXCOORD3;      //���[���h�}�g���N�X�����������@��
	float4 posw   : TEXCOORD4;      //���[���h�}�g���N�X�����������ʒu
};

//������������������������������������������������������������������������������
// ���_�V�F�[�_
//������������������������������������������������������������������������������
VS_OUT VS(float4 pos : POSITION, float4 Normal : NORMAL, float2 Uv : TEXCOORD)
{
	//�s�N�Z���V�F�[�_�[�֓n�����
	VS_OUT outData;

	outData.posw = mul(pos, g_matWorld);

	//���[�J�����W�ɁA���[���h�E�r���[�E�v���W�F�N�V�����s���������
	//�X�N���[�����W�ɕϊ����A�s�N�Z���V�F�[�_�[��
	outData.pos = mul(pos, g_matWVP);		

	//�@���̕ό`
	Normal.w = 0;					//4�����ڂ͎g��Ȃ��̂�0
	Normal = mul(Normal, g_matNormalTrans);		//�I�u�W�F�N�g���ό`����Ζ@�����ό`
	outData.normal = Normal;		//������s�N�Z���V�F�[�_�[��
	outData.norw = mul(Normal, g_matWorld);

	//�����x�N�g���i�n�C���C�g�̌v�Z�ɕK�v
	float4 worldPos = mul(pos, g_matWorld);					//���[�J�����W�Ƀ��[���h�s��������ă��[���h���W��
	outData.eye = normalize(g_vecCameraPosition - worldPos);	//���_���璸�_�ʒu�������Z�����������߂ăs�N�Z���V�F�[�_�[��

	//UV�u���W
	outData.uv = Uv;	//���̂܂܃s�N�Z���V�F�[�_�[��


	//�܂Ƃ߂ďo��
	return outData;
}

//������������������������������������������������������������������������������
// �s�N�Z���V�F�[�_
//������������������������������������������������������������������������������
float4 PS(VS_OUT inData) : SV_Target
{

	//���C�g�̌���
	float4 lightDir = g_vecLightDir;	//�O���[�o���ϐ��͕ύX�ł��Ȃ��̂ŁA�������񃍁[�J���ϐ���
	lightDir = normalize(lightDir);	//�����������K�v�Ȃ̂Ő��K��

	//�@���̓s�N�Z���V�F�[�_�[�Ɏ����Ă������_�ŕ⊮���꒷�����ς���Ă���
	//���K�����Ă����Ȃ��Ɩʂ̖��邳�����������Ȃ�
	inData.normal = normalize(inData.normal);

	float3 dir;
	float  len;
	float  colD;
	float  colA;
	float  col;
	float4 shade;

	//�_�����̕���
	dir = g_vecLightPosition.xyz - inData.posw.xyz;

	//�_�����̋���
	len = length(dir) / g_isLightIntensity;

	//�_�����̕�����normalize
	dir = dir / len;

	//�g�U
	colD = saturate(dot(normalize(inData.norw.xyz), dir));
	//����
	colA = saturate(1.0f / (1.0 + 0 * len + 0.2 * len * len));

	col = colD * colA;

	dir = g_aaaaa[1] - inData.posw.xyz;

	//�_�����̋���
	len = length(dir) / 1.5;

	//�_�����̕�����normalize
	dir = dir / len;

	//�g�U
	colD += saturate(dot(normalize(inData.norw.xyz), dir));
	//����
	colA += saturate(3.0f / (1.0 + 0 * len + 0.2 * len * len));

	dir = g_aaaaa[2] - inData.posw.xyz;

	//�_�����̋���
	len = length(dir) / 1.5;

	//�_�����̕�����normalize
	dir = dir / len;

	//�g�U
	colD += saturate(dot(normalize(inData.norw.xyz), dir));
	//����
	colA += saturate(3.0f / (1.0 + 0 * len + 0.2 * len * len));

	col = colD * colA;

	if (col > 1) col = 1;


	if (g_isBrightness == 0)
		shade = float4(col, col, col, 1.0f);
	else
		shade = float4(g_isBrightness, g_isBrightness, g_isBrightness, 1.0f);


	float4 diffuse = g_texture.Sample(g_sampler, inData.uv);
	//diffuse.a = 1;
	//shade.a = 1;

	//�ŏI�I�ȐF
	return  diffuse;
}