///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ball.cpp
// ���ڊ��o���Ȃ������{�[���̊Ǘ�
//	ryuji oka
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "Ball.h"
#include "TextureManager.h"
#include "Scene.h"
#include "Manager.h"
#include "InputKeyboard.h"
#include "ObjectX.h"
#include "CollisionManager.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �}�N����`
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define FIELD_WIDTH (290)
#define FIELD_HEIGHT (163)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �v���g�^�C�v�錾
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �O���[�o���ϐ�
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
D3DXVECTOR3 Ball::m_posWhiteBall = D3DXVECTOR3(NULL,NULL,NULL);
D3DXVECTOR3 Ball::m_WhiteBallForceVector = D3DXVECTOR3(NULL,NULL,NULL);
D3DXVECTOR3 Ball::m_WhiteBallForceSpin = D3DXVECTOR3(NULL,NULL,NULL);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �R���X�g���N�^
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Ball::Ball(int nPriority)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �f�X�g���N�^
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Ball::~Ball()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Init�֐�
//	:
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HRESULT Ball::Init(D3DXVECTOR3 pos,D3DXVECTOR3 rot,D3DXVECTOR3 scl,char *pModel,int number)
{
	// ���f������
	m_pBall = 	ObjectX::Create(pos,rot,scl,Manager::m_pTextureManager->GetTexture(number),"data\\MODEL\\BilliardsBall.x",1);
	m_pos = pos;
	m_rot = rot;
	m_Dflg = false;
	// ���ʔԍ����L�^
	m_Number = number;

	// �f�o�b�O�p�̏�����
	if(number ==0)
	{
		m_ForceVector.x = 0;
		m_ForceSpin.x = 0;
		m_ForceSpin.y = 0;
		m_ForceSpin.z = 0;
		m_posWhiteBall = pos;
	}
	else
	{
		m_ForceVector.x = 0;
		m_ForceSpin.x = 0;
		m_ForceSpin.y = 0;
		m_ForceSpin.z = 0;
	}

	m_ForceVector.y = 0;
	m_ForceVector.z = 0;
	m_Cnt = 1;
	return S_OK;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Uninit�֐�
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Ball::Uninit(void)
{
	CollisionManager::ReleaseCollision(m_Number);
	m_pBall->Release();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Update�֐�
//	m_ForceVector�����Ɉړ�����
//	m_ForceSpin�����ɉ�]����
//	�ǔ���ƃ|�P�b�g����
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Ball::Update(void)
{
	if(m_Dflg)
	{
		PocketMotion();
		return;
	}

	if(m_Number == 0)
	{
		m_ForceVector += m_WhiteBallForceVector;
		m_WhiteBallForceVector.x = 0;
		m_WhiteBallForceVector.z = 0;
		m_ForceSpin += m_WhiteBallForceSpin;
		m_WhiteBallForceSpin.x = 0;
		m_WhiteBallForceSpin.z = 0;
	}

	// �x�N�g�������Z
	m_pos += m_ForceVector;

	// ���C�ɂ��x�N�g���̌��Z
	m_ForceVector = m_ForceVector * m_Cnt;
	
	// ��]�␳
	//D3DXVec3Normalize(&m_ForceSpin,&m_ForceSpin);
	//m_ForceVector = m_ForceVector + m_ForceSpin;

	m_rot += m_ForceSpin;
	m_ForceSpin = m_ForceSpin * m_Cnt;

	// �|�P�b�g����
	if((m_pos.z+10 >= ((float)FIELD_HEIGHT/2)
		&&(m_pos.x+10 >= ((float)FIELD_WIDTH/2)))
		||(m_pos.z+10 >= ((float)FIELD_HEIGHT/2)
		&&(m_pos.x-10 <= -((float)FIELD_WIDTH/2)))
		||(m_pos.z-10 <= -((float)FIELD_HEIGHT/2)
		&&(m_pos.x+10 >= ((float)FIELD_WIDTH/2)))
		||(m_pos.z-10 <= -((float)FIELD_HEIGHT/2)
		&&(m_pos.x-10 <= -((float)FIELD_WIDTH/2)))
		||((m_pos.x+5 >= -10)
		&&(m_pos.x-5 <= 10)
		&&(m_pos.z+5 >= ((float)FIELD_HEIGHT/2)))
		||((m_pos.x+5 >= -10)
		&&(m_pos.x-5 <= 10)
		&&(m_pos.z-5 <= -((float)FIELD_HEIGHT/2))))
	{
		CollisionManager::ReleaseCollision(m_Number);
		m_Dflg = true;
	}
	
	//if(m_pos.z+10 >= ((float)FIELD_HEIGHT/2)
	//	&&(m_pos.x+10 >= ((float)FIELD_WIDTH/2)))
	//{
	//	//��ӉE�[�̃|�P�b�g
	//	m_pos.y =30;
	//}
	//
	//if(m_pos.z+10 >= ((float)FIELD_HEIGHT/2)
	//	&&(m_pos.x-10 <= -((float)FIELD_WIDTH/2)))
	//{
	//	//��Ӎ��[�̃|�P�b�g
	//	m_pos.y =30;
	//}
	//
	//if(m_pos.z-10 <= -((float)FIELD_HEIGHT/2)
	//	&&(m_pos.x+10 >= ((float)FIELD_WIDTH/2)))
	//{
	//	//���ӉE�[�̃|�P�b�g
	//	m_pos.y =30;
	//}
	//
	//if(m_pos.z-10 <= -((float)FIELD_HEIGHT/2)
	//	&&(m_pos.x-10 <= -((float)FIELD_WIDTH/2)))
	//{
	//	//���Ӎ��[�̃|�P�b�g
	//	m_pos.y =30;
	//}
	//
	//if((m_pos.x+5 >= -10)
	//	&&(m_pos.x-5 <= 10)
	//	&&(m_pos.z+5 >= ((float)FIELD_HEIGHT/2)))
	//{
	//	//�����E�[�̃|�P�b�g
	//	m_pos.y =30;
	//}
	//
	//if((m_pos.x+5 >= -10)
	//	&&(m_pos.x-5 <= 10)
	//	&&(m_pos.z-5 <= -((float)FIELD_HEIGHT/2)))
	//{
	//	//�������[�̃|�P�b�g
	//	m_pos.y =30;
	//}

	/* �ǔ��� */
	
	// ���

	if(m_pos.z+5 >= ((float)FIELD_HEIGHT/2))
	{
		// ��Ӗ@���x�N�g��
		D3DXVECTOR3 norUP(0,0,-1);
		// �ꉞ���K�����Ă���
		D3DXVec3Normalize(&norUP, &norUP);
		// ���˃x�N�g���Z�o
		//D3DXVec3Normalize(&m_ForceVector, &(m_ForceVector - 2.0f * D3DXVec3Dot(&m_ForceVector, &norUP) * norUP));
		m_ForceVector = (m_ForceVector - 2.0f * D3DXVec3Dot(&m_ForceVector, &norUP) * norUP);

		// ���˕Ԃ莞�̕␳(�����W��)
		//m_ForceVector = m_ForceVector * 0.9f;
	}
	
	// ����
	else if(m_pos.z-5 <= -((float)FIELD_HEIGHT/2))
	{
		// ���Ӗ@���x�N�g��
		D3DXVECTOR3 norUP(0,0,1);
		// �ꉞ���K�����Ă���
		D3DXVec3Normalize(&norUP, &norUP);
		// ���˃x�N�g���Z�o
		//D3DXVec3Normalize(&m_ForceVector, &(m_ForceVector - 2.0f * D3DXVec3Dot(&m_ForceVector, &norUP) * norUP));
		m_ForceVector = (m_ForceVector - 2.0f * D3DXVec3Dot(&m_ForceVector, &norUP) * norUP);
		
		// ���˕Ԃ莞�̕␳(�����W��)
		//m_ForceVector = m_ForceVector * 0.9f;

	}
	
	// ����
	else if(m_pos.x+5 >= ((float)FIELD_WIDTH/2))
	{
		// ���Ӗ@���x�N�g��
		D3DXVECTOR3 norUP(-1,0,0);
		// �ꉞ���K�����Ă���
		D3DXVec3Normalize(&norUP, &norUP);
		// ���˃x�N�g���Z�o
		//D3DXVec3Normalize(&m_ForceVector, &(m_ForceVector - 2.0f * D3DXVec3Dot(&m_ForceVector, &norUP) * norUP));
		m_ForceVector = (m_ForceVector - 2.0f * D3DXVec3Dot(&m_ForceVector, &norUP) * norUP);

		// ���˕Ԃ莞�̕␳(�����W��)
		//m_ForceVector = m_ForceVector * 0.9f;
	}
	
	// �E��
	else if(m_pos.x-5 <= -((float)FIELD_WIDTH/2))
	{
		// �E�Ӗ@���x�N�g��
		D3DXVECTOR3 norUP(1,0,0);
		// �ꉞ���K�����Ă���
		D3DXVec3Normalize(&norUP, &norUP);
		// ���˃x�N�g���Z�o
		//D3DXVec3Normalize(&m_ForceVector, &(m_ForceVector - 2.0f * D3DXVec3Dot(&m_ForceVector, &norUP) * norUP));
		m_ForceVector = (m_ForceVector - 2.0f * D3DXVec3Dot(&m_ForceVector, &norUP) * norUP);
		
		// ���˕Ԃ莞�̕␳(�����W��)
		//m_ForceVector = m_ForceVector * 0.9f;
	}

	

	m_pBall->SetPosition(m_pos);
	m_pBall->SetRotation(m_rot);

	if(m_Number == 0)
	{
		m_posWhiteBall = m_pos;
	}

	m_Cnt -= 0.00001f;

	if(m_Cnt <=0 )
	{
		m_Cnt = 0;
	}
}

void Ball::PocketMotion(void)
{
	if(m_pos.y <=-10) return;
	m_pos.y --;
	m_pBall->SetPosition(m_pos);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Draw�֐�
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Ball::Draw(void)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Create�֐�
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Ball* Ball::Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot,D3DXVECTOR3 scl,char *pModel,int number,int nPriority)
{
	Ball *pRet = new Ball(nPriority);
	pRet->Init(pos,rot,scl,pModel,number);
	return pRet;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	SetPosition�֐�
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Ball::SetPosition(float x,float y,float z)
{
	m_pos.x=x;
	m_pos.y=y;
	m_pos.z=z;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	SetPosition�֐�
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Ball::SetPosition(D3DXVECTOR3 pos)
{
	m_pos=pos;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	SetRotation�֐�
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Ball::SetRotation(D3DXVECTOR3 rot)
{
	m_rot=rot;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	SetRotation�֐�
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Ball::SetRotation(float x,float y,float z)
{
	m_rot.x=x;
	m_rot.y=y;
	m_rot.z=z;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	SetAddVector�֐�
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Ball::SetAddVector(D3DXVECTOR3 ForceVector)
{
	m_ForceVector = ForceVector;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	SetSpin�֐�
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Ball::SetSpin(D3DXVECTOR3 ForceSpin)
{
	m_ForceSpin = ForceSpin;
}
