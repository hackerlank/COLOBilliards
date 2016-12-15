#pragma once
#ifndef _Cue_H_
#define _Cue_H_

#include "Scene.h"

class Cue:public Scene
{
public:
	Cue(int nPriority=4);
	~Cue();
	
	static Cue* Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot,int nPriority=4);
	HRESULT Init(D3DXVECTOR3 pos,D3DXVECTOR3 rot);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	int GetType(void){return OBJ_TYPE;};		//オブジェクトの種類を返す

	//位置情報のセット&ゲット
	void SetPosition(float x,float y,float z);
	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void){return m_pos;};
	
	//角度情報のセット&ゲット
	void SetRotation(float x,float y,float z);
	void SetRotation(D3DXVECTOR3 rot);
	D3DXVECTOR3 GetRotation(void){return m_rot;};

	//現在の状態のセット
	void SetType(int nType){OBJ_TYPE = nType;};

	static D3DXVECTOR3 GetCuePosition(void){return m_sPos;};

private:
	D3DXVECTOR3 m_pos; //位置
	D3DXVECTOR3 m_rot; //向き
	D3DXVECTOR3 m_scl; //大きさ

	D3DXVECTOR3 m_fpos;	//初期位置

	static D3DXVECTOR3 m_sPos;

};
#endif