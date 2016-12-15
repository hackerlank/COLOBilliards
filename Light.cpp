///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Light.cpp
//	ryuji oka
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "main.h"
#include "Manager.h"
#include "Light.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �v���g�^�C�v�錾
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �O���[�o���ϐ�
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �|���S���̏���������
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Light::SetLight(void)
{
	//���C�g�̏�����
	D3DXVECTOR3 vecDir; //�v�Z�p�ϐ�
	LPDIRECT3DDEVICE9 pDevice=Manager::GetRenderer()->GetDevice();


	ZeroMemory(&m_aLight[0],sizeof(D3DLIGHT9)); //�������̒��g�����ׂăN���A
	m_aLight[0].Type = D3DLIGHT_DIRECTIONAL;	//���s����
	m_aLight[0].Diffuse = D3DXCOLOR(1.0f,0.9f,0.9f,1.0f); //���̐F
	vecDir = D3DXVECTOR3(0.5f,-0.7f,0.2f); //(-1<= n <=1)
	D3DXVec3Normalize((D3DXVECTOR3*)&m_aLight[0].Direction,&vecDir);

	pDevice->SetLight(0,&m_aLight[0]);	//���C�g�̐ݒ�
	pDevice->LightEnable(0,TRUE);		//���C�g��L���ɂ���
	

	ZeroMemory(&m_aLight[1],sizeof(D3DLIGHT9)); //�������̒��g�����ׂăN���A
	m_aLight[1].Type = D3DLIGHT_DIRECTIONAL;	//���s����
	m_aLight[1].Diffuse = D3DXCOLOR(1.0f,0.9f,0.9f,0.5f); //���̐F
	vecDir = D3DXVECTOR3(0.5f,0.1f,-0.8f); //(-1<= n <=1)
	D3DXVec3Normalize((D3DXVECTOR3*)&m_aLight[1].Direction,&vecDir);

	pDevice->SetLight(1,&m_aLight[1]);	//���C�g�̐ݒ�
	pDevice->LightEnable(1,TRUE);		//���C�g��L���ɂ���
	

	ZeroMemory(&m_aLight[2],sizeof(D3DLIGHT9)); //�������̒��g�����ׂăN���A
	m_aLight[2].Type = D3DLIGHT_DIRECTIONAL;	//���s����
	m_aLight[2].Diffuse = D3DXCOLOR(1.0f,0.9f,0.9f,0.5f); //���̐F
	vecDir = D3DXVECTOR3(0.1f,-0.8f,2.1f); //(-1<= n <=1)
	D3DXVec3Normalize((D3DXVECTOR3*)&m_aLight[2].Direction,&vecDir);

	pDevice->SetLight(2,&m_aLight[2]);	//���C�g�̐ݒ�
	pDevice->LightEnable(2,TRUE);		//���C�g��L���ɂ���
}