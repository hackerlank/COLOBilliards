///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Mesh.cpp
//	ryuji oka
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "Mesh.h"
#include "Scene.h"
#include "Manager.h"
#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �}�N����`
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �v���g�^�C�v�錾
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �O���[�o���ϐ�
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float Mesh::m_aHeightMap[(GYOU+1)*(RETU+1)]={NULL};
VERTEX_3D *Mesh::pVtx=NULL;
D3DXVECTOR3 Mesh::m_Center;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �R���X�g���N�^
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Mesh::Mesh(int nPriority):Scene(nPriority)
{
	m_pTexture=NULL;
	m_pVtxBuff=NULL;
	m_INDEX = ((RETU + 1) * 2 * GYOU + 2 * (RETU - 1));
	m_TOP = (GYOU+1) * (RETU+1);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �f�X�g���N�^
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Mesh::~Mesh()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Init�֐�
//	:
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HRESULT Mesh::Init(float Xsize,float Ysize,float Zsize,float Xpos,float Ypos,float Zpos,LPDIRECT3DTEXTURE9 pTexture)
{	

	for(int m=0;m<(RETU+1)*(GYOU+1);m++)
	{
			m_aHeightMap[m]=0;
	}
	
	LPDIRECT3DDEVICE9 pDevice=Manager::GetRenderer()->GetDevice();
	
	m_pNormalMap =  new D3DXVECTOR3[GYOU*RETU*2];
	
	OBJ_TYPE=1;//��ʂ����ɐݒ�
	m_pos = D3DXVECTOR3(Xpos,Ypos,Zpos);
	m_rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_scl = D3DXVECTOR3(1.0f,1.0f,1.0f);
	
	//���_�o�b�t�@�̊m��
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*m_TOP,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_3D,
									D3DPOOL_MANAGED,
									&m_pVtxBuff,
									NULL);
	
	//�C���f�N�X�o�b�t�@�̊m��
	pDevice->CreateIndexBuffer(sizeof(WORD)*m_INDEX,
									D3DUSAGE_WRITEONLY,
									D3DFMT_INDEX16,
									D3DPOOL_MANAGED,
									&m_pIdxBuff,
									NULL);
								

	//���_���̐ݒ�
	WORD *pIdx;

	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0,0,(void**)&pVtx,0);
	
	//���W
	float gyou=0;			//�s�̏㏸�ʂ��i�[����ϐ�
	float retu=0;			//��̏㏸�ʂ��i�[����ϐ�
	float X=0;				//�n�_��X���W���i�[����ϐ�
	float Y=0;				//�n�_��Y���W���i�[����ϐ�
	float Z=0;				//�n�_��Z���W���i�[����ϐ�
	float GSize=GYOU*SIZE;	//�c�̒������i�[����ϐ�
	float RSize=RETU*SIZE;	//���̒������i�[����ϐ�

	D3DXVECTOR3 vec0;
	D3DXVECTOR3 vec1;
	D3DXVECTOR3 *pNormal = &m_pNormalMap[0];

	//�s�̏㏸�ʌv�Z
	gyou=SIZE;
	
	//��̏㏸�ʌv�Z
	retu=SIZE;

	//�n�_�����߂�
	X=(RSize/2)*(-1);
	Y=0;
	Z=(GSize/2);

	int dbg=0;

	//���_���̐ݒ�
	for (int k = 0; k <= RETU; k++)
	{
		for (int i = 0; i <= GYOU; i++)
		{
			pVtx[i * (RETU + 1) + k].pos = D3DXVECTOR3(X + (SIZE * k), m_aHeightMap[i * (RETU+1) + k],Z - (SIZE * i));
			dbg++;
		}
	}

	for(int n=0; n<m_TOP; n++)
	{
		pVtx[n].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
		pVtx[n].col = D3DCOLOR_RGBA(255,255,255,255);
	}
	
	//�v�Z�p�ϐ�
	int o=0;

	//���_�e�N�X�`���ݒ�
	for (int V = 0, i = 0; i < m_TOP; i += (RETU + 1), V++)
	{
		for (int U = 0; U <= RETU; U++)
		{
			pVtx[i + U].tex = D3DXVECTOR2(U * 1.0f, V * 1.0f);
		}
	}
	m_pVtxBuff->Unlock();

	//�C���f�N�X�̒��_���ݒ�
	m_pIdxBuff->Lock(0,0,(void**)&pIdx,0);
	dbg=0;
	for (int i = 0, j = 0; j < m_INDEX; i += (RETU + 1), j += (RETU * 2) + 4)
	{
		for (int k = 0; k <= RETU; k++)
		{
			pIdx[j + k * 2] = (i + k + (RETU + 1));
			pIdx[j + k * 2 + 1] = i + k;
			
			dbg++;

		}
		if (j + (RETU * 2) + 3 < m_INDEX)
		{
			pIdx[j + (RETU * 2) + 2] = (i + RETU);
			pIdx[j + (RETU * 2) + 3] = (i + (RETU + 1) * 2);
			
			dbg++;
		}
	}

	m_pIdxBuff->Unlock();
	
	//�e�N�X�`���ǂݍ���
	m_pTexture=pTexture;

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Uninit�֐�
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Mesh::Uninit(void)
{	
	if(m_pNormalMap != NULL)
	{
		delete[] m_pNormalMap;
		m_pNormalMap = NULL;
	}

	if (m_pTexture != NULL)
	{
		m_pTexture = NULL;
	}
	
	if(m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	if(m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
	Release();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Update�֐�
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Mesh::Update(void)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Draw�֐�
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Mesh::Draw(void)
{	
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;
	
	LPDIRECT3DDEVICE9 pDevice = Manager::GetRenderer()->GetDevice();

	D3DXMatrixIdentity(&m_mtxWorld);	//���[���h�}�g���N�X�̏�����

	// ���[���h�}�g���b�N�X�̍쐬
	
	// �傫���𔽉f
	D3DXMatrixScaling(&mtxScl, m_scl.x, m_scl.y, m_scl.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScl);
	
	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTranslate, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTranslate);
	
	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0,m_pVtxBuff,0,sizeof(VERTEX_3D));
	
	//�C���f�N�X�o�b�t�@���o�C���h
	pDevice->SetIndices(m_pIdxBuff);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0,m_pTexture);

	//�|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,//�v�����~�e�B�u�̎��
									0,
									0,
									m_TOP,
									0,
									(m_INDEX-2));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	SetPosition�֐�
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Mesh::SetPosition(float x,float y,float z)
{
	m_pos.x=x;
	m_pos.y=y;
	m_pos.z=z;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	SetPosition�֐�
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Mesh::SetPosition(D3DXVECTOR3 pos)
{
	m_pos=pos;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	SetRotation�֐�
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Mesh::SetRotation(float x,float y,float z)
{
	m_rot.x=x;
	m_rot.y=y;
	m_rot.z=z;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	SetRotation�֐�
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Mesh::SetRotation(D3DXVECTOR3 rot)
{
	m_rot=rot;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	GetPosition�֐�
//	�v���C���[������Ƃ��̃|���S���S���_
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
D3DXVECTOR3 Mesh::GetPosition(D3DXVECTOR3 pos,int num)
{
	D3DXVECTOR3 ret;
	float retu=0;
	float gyou=0;
	retu = (pos.x + (((float)RETU*SIZE)/2))/SIZE;
	gyou = (-pos.z + (((float)GYOU*SIZE)/2))/SIZE;

	switch(num)
	{
	case 0:
		ret=pVtx[(int)gyou * (RETU + 1) + (int)retu].pos;
		break;
	
	case 1:
		ret=pVtx[((int)gyou * (RETU + 1) + (int)retu) + 1].pos;
		break;
	
	case 2:
		ret=pVtx[((int)gyou+1) * (RETU + 1) + (int)retu].pos;
		break;
	
	case 3:
		ret=pVtx[(((int)gyou+1) * (RETU + 1) + (int)retu) + 1].pos;
		break;

	default:
		break;
	}

	return ret;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Create�֐�
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Mesh* Mesh::Create(float Xsize,float Ysize,float Zsize,float Xpos,float Ypos,float Zpos,LPDIRECT3DTEXTURE9 pTexture,int nPriority)
{
	Mesh *pRet = new Mesh(nPriority);
	pRet->Init(Xsize,Ysize,Zsize,Xpos,Ypos,Zpos,pTexture);
	return pRet;
}