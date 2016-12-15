///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Shadow.cpp
//	ryuji oka
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "main.h"
#include "Shadow.h"
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
Shadow::Shadow(int nPriority):Scene(nPriority)
{
	m_pTexture = NULL;
	m_pMesh = NULL;
	m_pBuffMat = NULL;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// デストラクタ
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Shadow::~Shadow()
{
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ポリゴンの初期化処理
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HRESULT Shadow::Init(D3DXVECTOR3 pos,D3DXVECTOR3 rot,D3DXVECTOR3 scl,LPDIRECT3DTEXTURE9 pTexture,char *pModel)
{	
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
		pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*4,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&m_pVtxBuff,
								NULL);
	m_pVtxBuff->Lock(0,0,(void**)&m_aVertex,0);
	
	//座標
	m_aVertex[0].pos = D3DXVECTOR3(0,0,0.0f);
	m_aVertex[1].pos = D3DXVECTOR3(SCREEN_WIDTH,0,0.0f);
	m_aVertex[2].pos = D3DXVECTOR3(0,SCREEN_HEIGHT,0.0f);
	m_aVertex[3].pos = D3DXVECTOR3(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f);
		
	m_aVertex[0].rhw = 1.0f;
	m_aVertex[1].rhw = 1.0f;
	m_aVertex[2].rhw = 1.0f;
	m_aVertex[3].rhw = 1.0f;
	
	//色情報
	m_aVertex[0].col = D3DCOLOR_RGBA(1,1,1,120);
	m_aVertex[1].col = D3DCOLOR_RGBA(1,1,1,120);
	m_aVertex[2].col = D3DCOLOR_RGBA(1,1,1,120);
	m_aVertex[3].col = D3DCOLOR_RGBA(1,1,1,120);

	m_aVertex[0].tex = D3DXVECTOR2(0.0f/* 座標U */,0.0f /* 座標V */ );
	m_aVertex[1].tex = D3DXVECTOR2(1.0f/* 座標U */,0.0f /* 座標V */ );
	m_aVertex[2].tex = D3DXVECTOR2(0.0f/* 座標U */,1.0f /* 座標V */ );
	m_aVertex[3].tex = D3DXVECTOR2(1.0f/* 座標U */,1.0f /* 座標V */ );
		
	m_pVtxBuff->Unlock();
		
	//テクスチャ読み込み
	m_pTexture = pTexture;
	m_pos = pos;
	m_rot = rot;
	m_scl = scl*0.6f;
	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ポリゴンの終了処理
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Shadow::Uninit(void)
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
void Shadow::Update(void)
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ポリゴンの描画処理
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Shadow::Draw(void)
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




	//ステンシルテストを有効
	pDevice->SetRenderState(D3DRS_STENCILENABLE,TRUE);
	//Zバッファへの書き込みを無効化
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);
	//カラーバッファへの書き込みを無効化
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE,0);


	///////////////////////////////////////////////////////////////////
	// ステンシル設定1
	///////////////////////////////////////////////////////////////////

	//ステンシルテストに全てを合格させる
	pDevice->SetRenderState(D3DRS_STENCILFUNC,D3DCMP_ALWAYS);
	//ステンシルテスト合格、Zテスト合格の場合0にする
	pDevice->SetRenderState(D3DRS_STENCILPASS,D3DSTENCILOP_ZERO);
	//ステンシルテスト合格、Zテスト不合格の場合インクリメント
	pDevice->SetRenderState(D3DRS_STENCILZFAIL,D3DSTENCILOP_INCR);
	//ステンシルテスト不合格の場合0にする
	pDevice->SetRenderState(D3DRS_STENCILFAIL,D3DSTENCILOP_ZERO);
	//カリングを逆にする
	pDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CW);
	//影モデルの描画
	
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

	//ステンシル参照値"1"にする
	pDevice->SetRenderState(D3DRS_STENCILREF,1);

	///////////////////////////////////////////////////////////////////
	// ステンシル設定2
	///////////////////////////////////////////////////////////////////
	
	//ステンシル参照値以上で合格
	pDevice->SetRenderState(D3DRS_STENCILFUNC,D3DCMP_GREATEREQUAL);
	//ステンシルテスト合格、Zテスト合格の場合インクリメント
	pDevice->SetRenderState(D3DRS_STENCILPASS,D3DSTENCILOP_INCR);
	//ステンシルテスト合格、Zテスト不合格の場合0
	pDevice->SetRenderState(D3DRS_STENCILZFAIL,D3DSTENCILOP_ZERO);
	//ステンシルテスト不合格の場合0にする
	pDevice->SetRenderState(D3DRS_STENCILFAIL,D3DSTENCILOP_ZERO);
	//カリングを元に戻す
	pDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);
	//影モデルの描画
	
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

	//ステンシル参照値"1"にする
	pDevice->SetRenderState(D3DRS_STENCILREF,2);
	
	///////////////////////////////////////////////////////////////////
	// ステンシル設定3
	///////////////////////////////////////////////////////////////////
	
	//ステンシル参照値と同値で合格
	pDevice->SetRenderState(D3DRS_STENCILFUNC,D3DCMP_EQUAL);
	//ステンシルテスト合格、Zテスト合格の場合更新しない
	pDevice->SetRenderState(D3DRS_STENCILPASS,D3DSTENCILOP_INCR);
	//ステンシルテスト合格、Zテスト不合格の場合更新しない
	pDevice->SetRenderState(D3DRS_STENCILZFAIL,D3DSTENCILOP_ZERO);
	//ステンシルテスト不合格の場合更新しない
	pDevice->SetRenderState(D3DRS_STENCILFAIL,D3DSTENCILOP_ZERO);
	//カラーバッファへの書き込みを有効化
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE,D3DCOLORWRITEENABLE_RED|D3DCOLORWRITEENABLE_GREEN|D3DCOLORWRITEENABLE_BLUE|D3DCOLORWRITEENABLE_ALPHA);
	
	//画面サイズの2D半透明ポリゴンを描画(CSCENE2Dを使ってはいけない)
		
	//頂点バッファをデータストリームにバインド
	pDevice->SetStreamSource(0,m_pVtxBuff,0,sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,//プリンミティブの種類
									0,//描画するプリミティブ数
									2);
	
	//Zバッファへの書き込みを有効化
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
	//ステンシルテストを無効化
	pDevice->SetRenderState(D3DRS_STENCILENABLE,FALSE);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	SetPosition関数
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Shadow::SetPosition(float x,float y,float z)
{
	m_pos.x=x;
	m_pos.y=y;
	m_pos.z=z;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	SetPosition関数
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Shadow::SetPosition(D3DXVECTOR3 pos)
{
	m_pos=pos;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	SetRotation関数
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Shadow::SetRotation(D3DXVECTOR3 rot)
{
	m_rot=rot;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	SetRotation関数
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Shadow::SetRotation(float x,float y,float z)
{
	m_rot.x=x;
	m_rot.y=y;
	m_rot.z=z;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Create関数
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Shadow* Shadow::Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot,D3DXVECTOR3 scl,LPDIRECT3DTEXTURE9 pTexture,char *pModel,int nPriority)
{
	Shadow *pRet = new Shadow(nPriority);
	pRet->Init(pos,rot,scl,pTexture,pModel);
	return pRet;
}