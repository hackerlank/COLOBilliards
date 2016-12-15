#pragma once
#ifndef _Shadow_H_
#define _Shadow_H_

#include "Scene.h"

class Shadow:public Scene
{
public:
	Shadow(int nPriority=1);
	~Shadow();
	
	static Shadow* Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot,D3DXVECTOR3 scl,LPDIRECT3DTEXTURE9 pTexture,char *pModel,int nPriority=1);
	HRESULT Init(D3DXVECTOR3 pos,D3DXVECTOR3 rot,D3DXVECTOR3 scl,LPDIRECT3DTEXTURE9 pTexture,char *pModel);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	void TimeLeap(void){};

	//位置情報のセット&ゲット
	void SetPosition(float x,float y,float z);
	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void){return m_pos;};
	
	//角度情報のセット&ゲット
	void SetRotation(float x,float y,float z);
	void SetRotation(D3DXVECTOR3 rot);
	D3DXVECTOR3 GetRotation(void){return m_rot;};

	//現在の状態のセット
	void SetType(int nType){};
private:
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPD3DXMESH m_pMesh;	//メッシュ情報へのポインタ
	LPD3DXBUFFER m_pBuffMat;	//マテリアル情報へのポインタ
	DWORD m_numMat;	//マテリアルの数

	D3DXMATRIX m_mtxWorld;		//ワールドマトリクス

	D3DXVECTOR3 m_pos; //位置
	D3DXVECTOR3 m_rot; //向き
	D3DXVECTOR3 m_scl; //大きさ
	int moveflg3D;
	
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;
	VERTEX_2D *m_aVertex; //頂点情報
};
#endif