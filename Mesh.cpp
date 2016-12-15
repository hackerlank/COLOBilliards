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
// マクロ定義
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// プロトタイプ宣言
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// グローバル変数
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float Mesh::m_aHeightMap[(GYOU+1)*(RETU+1)]={NULL};
VERTEX_3D *Mesh::pVtx=NULL;
D3DXVECTOR3 Mesh::m_Center;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// コンストラクタ
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Mesh::Mesh(int nPriority):Scene(nPriority)
{
	m_pTexture=NULL;
	m_pVtxBuff=NULL;
	m_INDEX = ((RETU + 1) * 2 * GYOU + 2 * (RETU - 1));
	m_TOP = (GYOU+1) * (RETU+1);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// デストラクタ
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Mesh::~Mesh()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Init関数
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
	
	OBJ_TYPE=1;//種別を床に設定
	m_pos = D3DXVECTOR3(Xpos,Ypos,Zpos);
	m_rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_scl = D3DXVECTOR3(1.0f,1.0f,1.0f);
	
	//頂点バッファの確保
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*m_TOP,
									D3DUSAGE_WRITEONLY,
									FVF_VERTEX_3D,
									D3DPOOL_MANAGED,
									&m_pVtxBuff,
									NULL);
	
	//インデクスバッファの確保
	pDevice->CreateIndexBuffer(sizeof(WORD)*m_INDEX,
									D3DUSAGE_WRITEONLY,
									D3DFMT_INDEX16,
									D3DPOOL_MANAGED,
									&m_pIdxBuff,
									NULL);
								

	//頂点情報の設定
	WORD *pIdx;

	//頂点バッファをロック
	m_pVtxBuff->Lock(0,0,(void**)&pVtx,0);
	
	//座標
	float gyou=0;			//行の上昇量を格納する変数
	float retu=0;			//列の上昇量を格納する変数
	float X=0;				//始点のX座標を格納する変数
	float Y=0;				//始点のY座標を格納する変数
	float Z=0;				//始点のZ座標を格納する変数
	float GSize=GYOU*SIZE;	//縦の長さを格納する変数
	float RSize=RETU*SIZE;	//横の長さを格納する変数

	D3DXVECTOR3 vec0;
	D3DXVECTOR3 vec1;
	D3DXVECTOR3 *pNormal = &m_pNormalMap[0];

	//行の上昇量計算
	gyou=SIZE;
	
	//列の上昇量計算
	retu=SIZE;

	//始点を求める
	X=(RSize/2)*(-1);
	Y=0;
	Z=(GSize/2);

	int dbg=0;

	//頂点情報の設定
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
	
	//計算用変数
	int o=0;

	//頂点テクスチャ設定
	for (int V = 0, i = 0; i < m_TOP; i += (RETU + 1), V++)
	{
		for (int U = 0; U <= RETU; U++)
		{
			pVtx[i + U].tex = D3DXVECTOR2(U * 1.0f, V * 1.0f);
		}
	}
	m_pVtxBuff->Unlock();

	//インデクスの頂点情報設定
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
	
	//テクスチャ読み込み
	m_pTexture=pTexture;

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Uninit関数
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
//	Update関数
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Mesh::Update(void)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Draw関数
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Mesh::Draw(void)
{	
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;
	
	LPDIRECT3DDEVICE9 pDevice = Manager::GetRenderer()->GetDevice();

	D3DXMatrixIdentity(&m_mtxWorld);	//ワールドマトリクスの初期化

	// ワールドマトリックスの作成
	
	// 大きさを反映
	D3DXMatrixScaling(&mtxScl, m_scl.x, m_scl.y, m_scl.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScl);
	
	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTranslate, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTranslate);
	
	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデータストリームにバインド
	pDevice->SetStreamSource(0,m_pVtxBuff,0,sizeof(VERTEX_3D));
	
	//インデクスバッファをバインド
	pDevice->SetIndices(m_pIdxBuff);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0,m_pTexture);

	//ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,//プリンミティブの種類
									0,
									0,
									m_TOP,
									0,
									(m_INDEX-2));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	SetPosition関数
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Mesh::SetPosition(float x,float y,float z)
{
	m_pos.x=x;
	m_pos.y=y;
	m_pos.z=z;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	SetPosition関数
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Mesh::SetPosition(D3DXVECTOR3 pos)
{
	m_pos=pos;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	SetRotation関数
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Mesh::SetRotation(float x,float y,float z)
{
	m_rot.x=x;
	m_rot.y=y;
	m_rot.z=z;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	SetRotation関数
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Mesh::SetRotation(D3DXVECTOR3 rot)
{
	m_rot=rot;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	GetPosition関数
//	プレイヤーがいるとこのポリゴン４頂点
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
//	Create関数
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Mesh* Mesh::Create(float Xsize,float Ysize,float Zsize,float Xpos,float Ypos,float Zpos,LPDIRECT3DTEXTURE9 pTexture,int nPriority)
{
	Mesh *pRet = new Mesh(nPriority);
	pRet->Init(Xsize,Ysize,Zsize,Xpos,Ypos,Zpos,pTexture);
	return pRet;
}