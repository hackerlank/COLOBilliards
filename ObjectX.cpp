///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CSeneX.cpp
//	ryuji oka
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "main.h"
#include "ObjectX.h"
#include "Scene.h"
#include "Manager.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// プロトタイプ宣言
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// グローバル変数
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// コンストラクタ
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ObjectX::ObjectX(int nPriority):Scene(nPriority)
{
	m_pTexture = NULL;
	m_pMesh = NULL;
	m_pBuffMat = NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// デストラクタ
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ObjectX::~ObjectX()
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ポリゴンの初期化処理
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HRESULT ObjectX::Init(D3DXVECTOR3 pos,D3DXVECTOR3 rot,D3DXVECTOR3 scl,LPDIRECT3DTEXTURE9 pTexture,char *pModel)
{	
	
	m_pShadow=Shadow::Create(pos,D3DXVECTOR3(0.0f,(0.5f*3.14f),0.0f),D3DXVECTOR3(1.0f,1.0f,1.0f),Manager::GetTexture(0),"data\\MODEL\\shadow000.x",1);

	LPDIRECT3DDEVICE9 pDevice = Manager::GetRenderer()->GetDevice();
	
	OBJ_TYPE=2;//種別を壁に設定
		D3DXLoadMeshFromX(pModel,
							D3DXMESH_SYSTEMMEM,
							pDevice,
							NULL,
							&m_pBuffMat,
							NULL,
							&m_numMat,
							&m_pMesh);
		
	//テクスチャ読み込み
	m_pTexture = pTexture;
	m_pos = pos;
	m_rot = rot;
	m_scl = scl;

	//初期位置を保存
	m_posStart = m_pos;
	m_rotStart = m_rot;
	m_sclStart = m_scl;

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ポリゴンの終了処理
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ObjectX::Uninit(void)
{
	if(m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
	
	if(m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}
	Release();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ポリゴンの更新処理
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ObjectX::Update(void)
{
	m_pShadow->SetPosition(m_pos);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ポリゴンの描画処理
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ObjectX::Draw(void)
{
	D3DXMATRIX mtxScl, mtxRot, mtxTrancelate;
	
	// マテリアル情報へのポインタ変数
	D3DXMATERIAL *pMat;

	// 現在のマテリアル情報を一時保存する変数
	D3DMATERIAL9 matDef;

	// デバイスオブジェクトの確保
	LPDIRECT3DDEVICE9 pDevice=Manager::GetRenderer()->GetDevice();

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// ワールドマトリックスの作成
	D3DXMatrixScaling(&mtxScl, m_scl.x, m_scl.y, m_scl.z);

	// 大きさを反映
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScl);

	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	// 向きを反映
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrancelate, m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrancelate);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);


	// 現在のマテリアルの一時保存
	pDevice->GetMaterial(&matDef);

	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	// マテリアルの数分ループ
	for (int nCntMat = 0; nCntMat < (int)m_numMat; nCntMat++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);


		if(pMat[nCntMat].pTextureFilename)
		{
			// テクスチャの設定
			pDevice->SetTexture(0, m_pTexture);
		}
		else
		{
			pDevice->SetTexture(0, NULL);
		}

		// 各パーツの描画
		m_pMesh->DrawSubset(nCntMat);
	}

	// マテリアルを元の状態に戻す
	pDevice->SetMaterial(&matDef);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	初期位置に戻す関数
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ObjectX::TimeLeap(void)
{
	m_pos = m_posStart;
	m_rot = m_rotStart;
	m_scl = m_sclStart;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	SetPosition関数
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ObjectX::SetPosition(float x,float y,float z)
{
	m_pos.x=x;
	m_pos.y=y;
	m_pos.z=z;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	SetPosition関数
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ObjectX::SetPosition(D3DXVECTOR3 pos)
{
	m_pos=pos;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	SetRotation関数
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ObjectX::SetRotation(D3DXVECTOR3 rot)
{
	m_rot=rot;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	SetRotation関数
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ObjectX::SetRotation(float x,float y,float z)
{
	m_rot.x=x;
	m_rot.y=y;
	m_rot.z=z;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Create関数
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ObjectX* ObjectX::Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot,D3DXVECTOR3 scl,LPDIRECT3DTEXTURE9 pTexture,char *pModel,int nPriority)
{
	ObjectX *pRet = new ObjectX(nPriority);
	pRet->Init(pos,rot,scl,pTexture,pModel);
	return pRet;
}