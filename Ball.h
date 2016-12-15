#pragma once
#ifndef _Ball_H_
#define _Ball_H_

class ObjectX;
#include "Scene.h"

class Ball:public Scene
{
public:
	Ball(int nPriority=4);
	~Ball();
	
	static Ball* Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot,D3DXVECTOR3 scl,char *pModel,int number,int nPriority=4);
	HRESULT Init(D3DXVECTOR3 pos,D3DXVECTOR3 rot,D3DXVECTOR3 scl,char *pModel,int number);
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

	// 運動ベクトルのセット&ゲット
	void SetAddVector(D3DXVECTOR3 ForceVector);
	D3DXVECTOR3 GetAddVector(void){return m_ForceVector;};
	
	// 回転情報のセット&ゲット
	void SetSpin(D3DXVECTOR3 ForceSpin);
	D3DXVECTOR3 GetSpin(void){return m_ForceSpin;};

	// 白玉の位置取得
	static D3DXVECTOR3 GetWhiteBallPosition(void){return m_posWhiteBall;};
	// 白玉の運動ベクトルをセット
	static void SetWhiteBallAddVector(D3DXVECTOR3 addvec){m_WhiteBallForceVector = addvec;
														m_WhiteBallForceSpin = addvec/100;};

	void PocketMotion(void);

private:
	D3DXVECTOR3 m_pos; //位置
	D3DXVECTOR3 m_rot; //向き
	D3DXVECTOR3 m_scl; //大きさ

	D3DXVECTOR3 m_ForceVector;
	D3DXVECTOR3 m_ForceSpin;

	static D3DXVECTOR3 m_WhiteBallForceVector;
	static D3DXVECTOR3 m_WhiteBallForceSpin;

	ObjectX *m_pBall;
	int m_Number;
	bool m_MoveFlg;
	float m_Cnt;

	bool m_Dflg;

	static D3DXVECTOR3 m_posWhiteBall;
};
#endif