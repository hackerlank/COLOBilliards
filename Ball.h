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


	int GetType(void){return OBJ_TYPE;};		//�I�u�W�F�N�g�̎�ނ�Ԃ�

	//�ʒu���̃Z�b�g&�Q�b�g
	void SetPosition(float x,float y,float z);
	void SetPosition(D3DXVECTOR3 pos);
	D3DXVECTOR3 GetPosition(void){return m_pos;};
	
	//�p�x���̃Z�b�g&�Q�b�g
	void SetRotation(float x,float y,float z);
	void SetRotation(D3DXVECTOR3 rot);
	D3DXVECTOR3 GetRotation(void){return m_rot;};

	//���݂̏�Ԃ̃Z�b�g
	void SetType(int nType){OBJ_TYPE = nType;};

	// �^���x�N�g���̃Z�b�g&�Q�b�g
	void SetAddVector(D3DXVECTOR3 ForceVector);
	D3DXVECTOR3 GetAddVector(void){return m_ForceVector;};
	
	// ��]���̃Z�b�g&�Q�b�g
	void SetSpin(D3DXVECTOR3 ForceSpin);
	D3DXVECTOR3 GetSpin(void){return m_ForceSpin;};

	// ���ʂ̈ʒu�擾
	static D3DXVECTOR3 GetWhiteBallPosition(void){return m_posWhiteBall;};
	// ���ʂ̉^���x�N�g�����Z�b�g
	static void SetWhiteBallAddVector(D3DXVECTOR3 addvec){m_WhiteBallForceVector = addvec;
														m_WhiteBallForceSpin = addvec/100;};

	void PocketMotion(void);

private:
	D3DXVECTOR3 m_pos; //�ʒu
	D3DXVECTOR3 m_rot; //����
	D3DXVECTOR3 m_scl; //�傫��

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