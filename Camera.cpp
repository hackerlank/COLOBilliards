///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Camera.cpp
//	ryuji oka
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "main.h"
#include "Camera.h"
#include "Manager.h"
#include "InputKeyboard.h"
#include "Cue.h"
#include "Ball.h"

#define AngleOfView (3.14f/4.0f)										//����p
#define ASPECT ((float)SCREEN_WIDTH/(float)SCREEN_HEIGHT)				//�A�X�y�N�g��
#define ORIGINAL_NEAR (10.0f)											//�߂�
#define ORIGINAL_FAR (20000.0f)											//����
#define SPEED (1.0f)
#define PAIPAI (D3DX_PI / 180)											//�~�����̕ϊ�
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �v���g�^�C�v�錾
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �O���[�o���ϐ�
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float  Camera::m_CameraY=0;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �J�����̏���������
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Camera::Init(void)
{	
	//�J�����̏�����
	m_posCameraP = D3DXVECTOR3(0.0f,310.0f,210.0f);
	m_posCameraR = D3DXVECTOR3(0,10,0);
	m_veCameraU = D3DXVECTOR3(0.0f,1.0f,0.0f);
	m_moveCamera = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_rotCamera.y = 0;
	m_rotModelCamera.y=0;
	m_moveCameraR = 50;
	m_AngleOfView = AngleOfView;
	m_CameraMode = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �J�����̏I������
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Camera::Uninit(void)
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �J�����̍X�V����
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Camera::Update(void)
{
	// �J�����͂ӂ��̓���������
	// �P��Cue���甒���ւ̈�l�̎��_[m_CameraMode=0]
	// �Q�߂͏�����猩���낷���Վ��_[m_CameraMode=1]
	// ����̓v���C�����C�ӂɐ؂�ւ��邱�Ƃ��o����

	switch (m_CameraMode)
	{
		//��l�̎��_
	case 0:
		m_posCameraP = Cue::GetCuePosition();
		m_posCameraR = Ball::GetWhiteBallPosition();
		break;

		//���Վ��_
	case 1:
		m_posCameraP = D3DXVECTOR3(0.0f,310.0f,210.0f);
		m_posCameraR = D3DXVECTOR3(0.0f,  0.0f,  0.0f);
		break;
	}


	// �J�������[�h�؂�ւ�
	if(InputKeyboard::GetKeyboardTrigger(DIK_1))
	{
		m_CameraMode =0;
	}
	if(InputKeyboard::GetKeyboardTrigger(DIK_2))
	{
		m_CameraMode =1;
	}

	////���_�ʒu���쉺
	//if(InputKeyboard::GetKeyboardPress(DIK_N))
	//{
	//	m_posCameraP.y -= SPEED;
	//}

	////�����_�̏�ړ�
	//if(InputKeyboard::GetKeyboardPress(DIK_T))
	//{
	//	m_moveCameraR += SPEED;
	//}

	////�����_�̉��ړ�
	//if(InputKeyboard::GetKeyboardPress(DIK_B))
	//{
	//	m_moveCameraR -= SPEED;
	//}
	//
	////�Y�[���C��
	//if(InputKeyboard::GetKeyboardPress(DIK_Z))
	//{
	//	m_AngleOfView-=0.002f;
	//}

	////�Y�[���A�E�g
	//if(InputKeyboard::GetKeyboardPress(DIK_C))
	//{
	//	m_AngleOfView+=0.002f;
	//}

	//m_moveCamera = D3DXVECTOR3(pPosModel.x,pPosModel.y,pPosModel.z);
	//
	//m_posCameraP.x += (m_moveCamera.x+(200.0f*sinf(m_rotModelCamera.y)) - m_posCameraP.x)*0.05f+m_CameraY;
	//m_posCameraP.y =  pPosModel.y + 110.0f + m_CameraY;
	//m_posCameraP.z += (m_moveCamera.z+(200.0f*cosf(m_rotModelCamera.y)) - m_posCameraP.z)*0.05f+m_CameraY;

	//m_posCameraR.x += ( (pPosModel.x - sinf(pRotModel.y)*30.0f) - m_posCameraR.x) * 0.1f+m_CameraY;
	//m_posCameraR.y = pPosModel.y+m_moveCameraR + m_CameraY;
	//m_posCameraR.z += ( (pPosModel.z - cosf(pRotModel.y)*30.0f) - m_posCameraR.z) * 0.1f+m_CameraY;

	//	
	//if(CTimer::GetTimeUp()==true)
	//{
	//	m_rotModelCamera.y = m_rotModelCamera.y - D3DX_PI;
	//}

	//m_rotCamera.y += (m_rotModelCamera.y-m_rotCamera.y)*0.05f;
	//m_CameraY=0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �J�����̕`�揈��
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Camera::Draw(void)
{
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;

	D3DXMatrixIdentity(&m_mtxProjection);	//�v���W�F�N�V�����}�g���N�X�̏�����
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
								float(m_AngleOfView),
								float(ASPECT),
								ORIGINAL_NEAR,
								ORIGINAL_FAR); //�v���W�F�N�V�����}�g���N�X�̍쐬

	LPDIRECT3DDEVICE9 pDevice=Manager::GetRenderer()->GetDevice();
	pDevice->SetTransform(D3DTS_PROJECTION,&m_mtxProjection);	//�v���W�F�N�V�����}�g���N�X�̐ݒ�

	D3DXMatrixIdentity(&m_mtxView);	//�r���[�}�g���N�X�̏�����
	D3DXMatrixLookAtLH(&m_mtxView,
						&m_posCameraP,//�J�����̎��_
						&m_posCameraR,//�J�����̒����_
						&m_veCameraU//�J�����̏�����x�N�g��
						);	//�r���[�}�g���N�X�̍쐬
	pDevice->SetTransform(D3DTS_VIEW,
							&m_mtxView);	//�r���[�}�g���N�X�̐ݒ�
}