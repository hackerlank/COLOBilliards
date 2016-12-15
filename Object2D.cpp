///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Object2D.cpp
//	ryuji oka
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "Object2D.h"
#include "Scene.h"
#include "Manager.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �}�N����`
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �v���g�^�C�v�錾
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �O���[�o���ϐ�
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �R���X�g���N�^
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Object2D::Object2D(int nPriority):Scene(nPriority)
{
	m_pVtxBuff	= NULL;
	m_pTexture	= NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �f�X�g���N�^
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Object2D::~Object2D()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Init�֐�
//	:
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HRESULT Object2D::Init(D3DXVECTOR3 pos,D3DXVECTOR3 size,LPDIRECT3DTEXTURE9 pTexture)
{	
	m_pos=pos;
	m_scl=size;
	LPDIRECT3DDEVICE9 pDevice=Manager::GetRenderer()->GetDevice();
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&m_pVtxBuff,
									NULL);
	m_pVtxBuff->Lock(0,0,(void**)&m_aVertex,0);
	
	//���W
	m_aVertex[0].pos = D3DXVECTOR3(pos.x,pos.y,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3(pos.x+size.x,pos.y,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3(pos.x,pos.y+size.y,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3(pos.x+size.x,pos.y+size.y,0.0f);
		
	m_aVertex[0].rhw = 1.0f;
	m_aVertex[1].rhw = 1.0f;
	m_aVertex[2].rhw = 1.0f;
	m_aVertex[3].rhw = 1.0f;
	
	//�F���
	m_aVertex[0].col = D3DCOLOR_RGBA(255,255,255,255);
	m_aVertex[1].col = D3DCOLOR_RGBA(255,255,255,255);
	m_aVertex[2].col = D3DCOLOR_RGBA(255,255,255,255);
	m_aVertex[3].col = D3DCOLOR_RGBA(255,255,255,255);

	m_aVertex[0].tex = D3DXVECTOR2(0.0f/* ���WU */,0.0f /* ���WV */ );
	m_aVertex[1].tex = D3DXVECTOR2(1.0f/* ���WU */,0.0f /* ���WV */ );
	m_aVertex[2].tex = D3DXVECTOR2(0.0f/* ���WU */,1.0f /* ���WV */ );
	m_aVertex[3].tex = D3DXVECTOR2(1.0f/* ���WU */,1.0f /* ���WV */ );
		
	m_pVtxBuff->Unlock();

	//�e�N�X�`���ǂݍ���
	m_pTexture=pTexture;
	
	OBJ_TYPE=NULL;
	return S_OK;
}

HRESULT Object2D::Init(D3DXVECTOR3 pos,D3DXVECTOR3 size,int alpha,LPDIRECT3DTEXTURE9 pTexture)
{	
	m_pos=pos;
	m_scl=size;
	LPDIRECT3DDEVICE9 pDevice=Manager::GetRenderer()->GetDevice();
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_2D,
									D3DPOOL_MANAGED,
									&m_pVtxBuff,
									NULL);
	m_pVtxBuff->Lock(0,0,(void**)&m_aVertex,0);
	
	//���W
	m_aVertex[0].pos = D3DXVECTOR3(pos.x,pos.y,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3(pos.x+size.x,pos.y,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3(pos.x,pos.y+size.y,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3(pos.x+size.x,pos.y+size.y,0.0f);
		
	m_aVertex[0].rhw = 1.0f;
	m_aVertex[1].rhw = 1.0f;
	m_aVertex[2].rhw = 1.0f;
	m_aVertex[3].rhw = 1.0f;
	
	//�F���
	m_aVertex[0].col = D3DCOLOR_RGBA(255,255,255,alpha);
	m_aVertex[1].col = D3DCOLOR_RGBA(255,255,255,alpha);
	m_aVertex[2].col = D3DCOLOR_RGBA(255,255,255,alpha);
	m_aVertex[3].col = D3DCOLOR_RGBA(255,255,255,alpha);

	m_aVertex[0].tex = D3DXVECTOR2(0.0f/* ���WU */,0.0f /* ���WV */ );
	m_aVertex[1].tex = D3DXVECTOR2(1.0f/* ���WU */,0.0f /* ���WV */ );
	m_aVertex[2].tex = D3DXVECTOR2(0.0f/* ���WU */,1.0f /* ���WV */ );
	m_aVertex[3].tex = D3DXVECTOR2(1.0f/* ���WU */,1.0f /* ���WV */ );
		
	m_pVtxBuff->Unlock();

	//�e�N�X�`���ǂݍ���
	m_pTexture=pTexture;
	
	OBJ_TYPE=NULL;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Uninit�֐�
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Object2D::Uninit(void)
{	
	if (m_pTexture != NULL)
	{
		m_pTexture = NULL;
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
void Object2D::Update(void)
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Draw�֐�
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Object2D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice=Manager::GetRenderer()->GetDevice();
	
	//���_�o�b�t�@���f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0,m_pVtxBuff,0,sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0,m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//�v�����~�e�B�u�̎��
									0,//�`�悷��v���~�e�B�u��
									2);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	�����ʒu�ɖ߂��֐�
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Object2D::TimeLeap(void)
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	SetPosition�֐�
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Object2D::SetPosition(float x,float y,float z)
{
	m_pos.x=x;
	m_pos.y=y;
	m_pos.z=z;
	
	m_pVtxBuff->Lock(0,0,(void**)&m_aVertex,0);
	
	//���W
	m_aVertex[0].pos = D3DXVECTOR3(m_pos.x,m_pos.y,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3(m_pos.x+m_scl.x,m_pos.y,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3(m_pos.x,m_pos.y+m_scl.y,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3(m_pos.x+m_scl.x,m_pos.y+m_scl.y,0.0f);
		
	m_pVtxBuff->Unlock();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	SetPosition�֐�
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Object2D::SetPosition(D3DXVECTOR3 pos)
{
	m_pos=pos;

	m_pVtxBuff->Lock(0,0,(void**)&m_aVertex,0);
	
	//���W
	m_aVertex[0].pos = D3DXVECTOR3(m_pos.x,m_pos.y,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3(m_pos.x+m_scl.x,m_pos.y,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3(m_pos.x,m_pos.y+m_scl.y,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3(m_pos.x+m_scl.x,m_pos.y+m_scl.y,0.0f);
		
	m_pVtxBuff->Unlock();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	SetRotation�֐�
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Object2D::SetRotation(float x,float y,float z)
{
	m_rot.x=x;
	m_rot.y=y;
	m_rot.z=z;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	SetRotation�֐�
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Object2D::SetRotation(D3DXVECTOR3 rot)
{
	m_rot=rot;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	SetRotation�֐�
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Object2D::SetScale(float x,float y,float z)
{
	m_scl.x=x;
	m_scl.y=y;
	m_scl.z=z;

	m_pVtxBuff->Lock(0,0,(void**)&m_aVertex,0);
	
	//���W
	m_aVertex[0].pos = D3DXVECTOR3(m_pos.x,m_pos.y,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3(m_pos.x+m_scl.x,m_pos.y,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3(m_pos.x,m_pos.y+m_scl.y,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3(m_pos.x+m_scl.x,m_pos.y+m_scl.y,0.0f);
		
	m_pVtxBuff->Unlock();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	SetRotation�֐�
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Object2D::SetScale(D3DXVECTOR3 scl)
{
	m_scl=scl;
	
	m_pVtxBuff->Lock(0,0,(void**)&m_aVertex,0);
	
	//���W
	m_aVertex[0].pos = D3DXVECTOR3(m_pos.x,m_pos.y,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3(m_pos.x+m_scl.x,m_pos.y,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3(m_pos.x,m_pos.y+m_scl.y,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3(m_pos.x+m_scl.x,m_pos.y+m_scl.y,0.0f);
		
	m_pVtxBuff->Unlock();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	SetAnimation�֐�
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Object2D::SetAnimation(int num)
{
	//���_���̐ݒ�
	VERTEX_2D *pVtx;

	m_pVtxBuff->Lock(0,0,(void**)&pVtx,0);
	
	pVtx[0].tex = D3DXVECTOR2( (((float)num-1.0f)/10) /* ���WU */, 0.0f /* ���WV */ );
	pVtx[1].tex = D3DXVECTOR2( ((float)num/10)		/* ���WU */, 0.0f /* ���WV */ );
	pVtx[2].tex = D3DXVECTOR2( (((float)num-1.0f)/10) /* ���WU */, 1.0f /* ���WV */ );
	pVtx[3].tex = D3DXVECTOR2( ((float)num/10)		/* ���WU */, 1.0f /* ���WV */ );

	m_pVtxBuff->Unlock();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Create�֐�
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Object2D* Object2D::Create(D3DXVECTOR3 pos,D3DXVECTOR3 size,LPDIRECT3DTEXTURE9 pTexture,int nPriority)
{
	Object2D *pRet = new Object2D(nPriority);
	pRet->Init(pos,size,pTexture);
	return pRet;
}

Object2D* Object2D::Create(D3DXVECTOR3 pos,D3DXVECTOR3 size,int alpha,LPDIRECT3DTEXTURE9 pTexture,int nPriority)
{
	Object2D *pRet = new Object2D(nPriority);
	pRet->Init(pos,size,alpha,pTexture);
	return pRet;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	SetAlpha�֐�
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Object2D::SetAlpha(int alpha)
{
	m_pVtxBuff->Lock(0,0,(void**)&m_aVertex,0);
	
	m_aVertex[0].col = D3DCOLOR_RGBA(255,255,255,alpha);
	m_aVertex[1].col = D3DCOLOR_RGBA(255,255,255,alpha);
	m_aVertex[2].col = D3DCOLOR_RGBA(255,255,255,alpha);
	m_aVertex[3].col = D3DCOLOR_RGBA(255,255,255,alpha);

	m_pVtxBuff->Unlock();
}