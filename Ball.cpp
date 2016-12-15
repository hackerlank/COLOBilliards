///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Ball.cpp
// 直接干渉出来ない数字ボールの管理
//	ryuji oka
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "Ball.h"
#include "TextureManager.h"
#include "Scene.h"
#include "Manager.h"
#include "InputKeyboard.h"
#include "ObjectX.h"
#include "CollisionManager.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// マクロ定義
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define FIELD_WIDTH (290)
#define FIELD_HEIGHT (163)

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// プロトタイプ宣言
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// グローバル変数
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
D3DXVECTOR3 Ball::m_posWhiteBall = D3DXVECTOR3(NULL,NULL,NULL);
D3DXVECTOR3 Ball::m_WhiteBallForceVector = D3DXVECTOR3(NULL,NULL,NULL);
D3DXVECTOR3 Ball::m_WhiteBallForceSpin = D3DXVECTOR3(NULL,NULL,NULL);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// コンストラクタ
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Ball::Ball(int nPriority)
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// デストラクタ
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Ball::~Ball()
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Init関数
//	:
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
HRESULT Ball::Init(D3DXVECTOR3 pos,D3DXVECTOR3 rot,D3DXVECTOR3 scl,char *pModel,int number)
{
	// モデル生成
	m_pBall = 	ObjectX::Create(pos,rot,scl,Manager::m_pTextureManager->GetTexture(number),"data\\MODEL\\BilliardsBall.x",1);
	m_pos = pos;
	m_rot = rot;
	m_Dflg = false;
	// 識別番号を記録
	m_Number = number;

	// デバッグ用の初期化
	if(number ==0)
	{
		m_ForceVector.x = 0;
		m_ForceSpin.x = 0;
		m_ForceSpin.y = 0;
		m_ForceSpin.z = 0;
		m_posWhiteBall = pos;
	}
	else
	{
		m_ForceVector.x = 0;
		m_ForceSpin.x = 0;
		m_ForceSpin.y = 0;
		m_ForceSpin.z = 0;
	}

	m_ForceVector.y = 0;
	m_ForceVector.z = 0;
	m_Cnt = 1;
	return S_OK;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Uninit関数
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Ball::Uninit(void)
{
	CollisionManager::ReleaseCollision(m_Number);
	m_pBall->Release();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Update関数
//	m_ForceVectorを元に移動処理
//	m_ForceSpinを元に回転処理
//	壁判定とポケット判定
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Ball::Update(void)
{
	if(m_Dflg)
	{
		PocketMotion();
		return;
	}

	if(m_Number == 0)
	{
		m_ForceVector += m_WhiteBallForceVector;
		m_WhiteBallForceVector.x = 0;
		m_WhiteBallForceVector.z = 0;
		m_ForceSpin += m_WhiteBallForceSpin;
		m_WhiteBallForceSpin.x = 0;
		m_WhiteBallForceSpin.z = 0;
	}

	// ベクトルを加算
	m_pos += m_ForceVector;

	// 摩擦によるベクトルの減算
	m_ForceVector = m_ForceVector * m_Cnt;
	
	// 回転補正
	//D3DXVec3Normalize(&m_ForceSpin,&m_ForceSpin);
	//m_ForceVector = m_ForceVector + m_ForceSpin;

	m_rot += m_ForceSpin;
	m_ForceSpin = m_ForceSpin * m_Cnt;

	// ポケット判定
	if((m_pos.z+10 >= ((float)FIELD_HEIGHT/2)
		&&(m_pos.x+10 >= ((float)FIELD_WIDTH/2)))
		||(m_pos.z+10 >= ((float)FIELD_HEIGHT/2)
		&&(m_pos.x-10 <= -((float)FIELD_WIDTH/2)))
		||(m_pos.z-10 <= -((float)FIELD_HEIGHT/2)
		&&(m_pos.x+10 >= ((float)FIELD_WIDTH/2)))
		||(m_pos.z-10 <= -((float)FIELD_HEIGHT/2)
		&&(m_pos.x-10 <= -((float)FIELD_WIDTH/2)))
		||((m_pos.x+5 >= -10)
		&&(m_pos.x-5 <= 10)
		&&(m_pos.z+5 >= ((float)FIELD_HEIGHT/2)))
		||((m_pos.x+5 >= -10)
		&&(m_pos.x-5 <= 10)
		&&(m_pos.z-5 <= -((float)FIELD_HEIGHT/2))))
	{
		CollisionManager::ReleaseCollision(m_Number);
		m_Dflg = true;
	}
	
	//if(m_pos.z+10 >= ((float)FIELD_HEIGHT/2)
	//	&&(m_pos.x+10 >= ((float)FIELD_WIDTH/2)))
	//{
	//	//上辺右端のポケット
	//	m_pos.y =30;
	//}
	//
	//if(m_pos.z+10 >= ((float)FIELD_HEIGHT/2)
	//	&&(m_pos.x-10 <= -((float)FIELD_WIDTH/2)))
	//{
	//	//上辺左端のポケット
	//	m_pos.y =30;
	//}
	//
	//if(m_pos.z-10 <= -((float)FIELD_HEIGHT/2)
	//	&&(m_pos.x+10 >= ((float)FIELD_WIDTH/2)))
	//{
	//	//下辺右端のポケット
	//	m_pos.y =30;
	//}
	//
	//if(m_pos.z-10 <= -((float)FIELD_HEIGHT/2)
	//	&&(m_pos.x-10 <= -((float)FIELD_WIDTH/2)))
	//{
	//	//下辺左端のポケット
	//	m_pos.y =30;
	//}
	//
	//if((m_pos.x+5 >= -10)
	//	&&(m_pos.x-5 <= 10)
	//	&&(m_pos.z+5 >= ((float)FIELD_HEIGHT/2)))
	//{
	//	//中央右端のポケット
	//	m_pos.y =30;
	//}
	//
	//if((m_pos.x+5 >= -10)
	//	&&(m_pos.x-5 <= 10)
	//	&&(m_pos.z-5 <= -((float)FIELD_HEIGHT/2)))
	//{
	//	//中央左端のポケット
	//	m_pos.y =30;
	//}

	/* 壁判定 */
	
	// 上辺

	if(m_pos.z+5 >= ((float)FIELD_HEIGHT/2))
	{
		// 上辺法線ベクトル
		D3DXVECTOR3 norUP(0,0,-1);
		// 一応正規化しておく
		D3DXVec3Normalize(&norUP, &norUP);
		// 反射ベクトル算出
		//D3DXVec3Normalize(&m_ForceVector, &(m_ForceVector - 2.0f * D3DXVec3Dot(&m_ForceVector, &norUP) * norUP));
		m_ForceVector = (m_ForceVector - 2.0f * D3DXVec3Dot(&m_ForceVector, &norUP) * norUP);

		// 跳ね返り時の補正(反発係数)
		//m_ForceVector = m_ForceVector * 0.9f;
	}
	
	// 下辺
	else if(m_pos.z-5 <= -((float)FIELD_HEIGHT/2))
	{
		// 下辺法線ベクトル
		D3DXVECTOR3 norUP(0,0,1);
		// 一応正規化しておく
		D3DXVec3Normalize(&norUP, &norUP);
		// 反射ベクトル算出
		//D3DXVec3Normalize(&m_ForceVector, &(m_ForceVector - 2.0f * D3DXVec3Dot(&m_ForceVector, &norUP) * norUP));
		m_ForceVector = (m_ForceVector - 2.0f * D3DXVec3Dot(&m_ForceVector, &norUP) * norUP);
		
		// 跳ね返り時の補正(反発係数)
		//m_ForceVector = m_ForceVector * 0.9f;

	}
	
	// 左辺
	else if(m_pos.x+5 >= ((float)FIELD_WIDTH/2))
	{
		// 左辺法線ベクトル
		D3DXVECTOR3 norUP(-1,0,0);
		// 一応正規化しておく
		D3DXVec3Normalize(&norUP, &norUP);
		// 反射ベクトル算出
		//D3DXVec3Normalize(&m_ForceVector, &(m_ForceVector - 2.0f * D3DXVec3Dot(&m_ForceVector, &norUP) * norUP));
		m_ForceVector = (m_ForceVector - 2.0f * D3DXVec3Dot(&m_ForceVector, &norUP) * norUP);

		// 跳ね返り時の補正(反発係数)
		//m_ForceVector = m_ForceVector * 0.9f;
	}
	
	// 右辺
	else if(m_pos.x-5 <= -((float)FIELD_WIDTH/2))
	{
		// 右辺法線ベクトル
		D3DXVECTOR3 norUP(1,0,0);
		// 一応正規化しておく
		D3DXVec3Normalize(&norUP, &norUP);
		// 反射ベクトル算出
		//D3DXVec3Normalize(&m_ForceVector, &(m_ForceVector - 2.0f * D3DXVec3Dot(&m_ForceVector, &norUP) * norUP));
		m_ForceVector = (m_ForceVector - 2.0f * D3DXVec3Dot(&m_ForceVector, &norUP) * norUP);
		
		// 跳ね返り時の補正(反発係数)
		//m_ForceVector = m_ForceVector * 0.9f;
	}

	

	m_pBall->SetPosition(m_pos);
	m_pBall->SetRotation(m_rot);

	if(m_Number == 0)
	{
		m_posWhiteBall = m_pos;
	}

	m_Cnt -= 0.00001f;

	if(m_Cnt <=0 )
	{
		m_Cnt = 0;
	}
}

void Ball::PocketMotion(void)
{
	if(m_pos.y <=-10) return;
	m_pos.y --;
	m_pBall->SetPosition(m_pos);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Draw関数
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Ball::Draw(void)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Create関数
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Ball* Ball::Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot,D3DXVECTOR3 scl,char *pModel,int number,int nPriority)
{
	Ball *pRet = new Ball(nPriority);
	pRet->Init(pos,rot,scl,pModel,number);
	return pRet;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	SetPosition関数
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Ball::SetPosition(float x,float y,float z)
{
	m_pos.x=x;
	m_pos.y=y;
	m_pos.z=z;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	SetPosition関数
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Ball::SetPosition(D3DXVECTOR3 pos)
{
	m_pos=pos;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	SetRotation関数
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Ball::SetRotation(D3DXVECTOR3 rot)
{
	m_rot=rot;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	SetRotation関数
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Ball::SetRotation(float x,float y,float z)
{
	m_rot.x=x;
	m_rot.y=y;
	m_rot.z=z;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	SetAddVector関数
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Ball::SetAddVector(D3DXVECTOR3 ForceVector)
{
	m_ForceVector = ForceVector;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	SetSpin関数
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Ball::SetSpin(D3DXVECTOR3 ForceSpin)
{
	m_ForceSpin = ForceSpin;
}
