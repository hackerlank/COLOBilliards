///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Camera.cpp
//	ryuji oka
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "main.h"
#include "Camera.h"
#include "Manager.h"
#include "InputKeyboard.h"
#include "Cue.h"
#include "Ball.h"

#define AngleOfView (3.14f/4.0f)										//視野角
#define ASPECT ((float)SCREEN_WIDTH/(float)SCREEN_HEIGHT)				//アスペクト比
#define ORIGINAL_NEAR (10.0f)											//近さ
#define ORIGINAL_FAR (20000.0f)											//遠さ
#define SPEED (1.0f)
#define PAIPAI (D3DX_PI / 180)											//円周率の変換
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// プロトタイプ宣言
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// グローバル変数
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float  Camera::m_CameraY=0;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// カメラの初期化処理
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Camera::Init(void)
{	
	//カメラの初期化
	m_posCameraP = D3DXVECTOR3(0.0f,310.0f,210.0f);
	m_posCameraR = D3DXVECTOR3(0,10,0);
	m_veCameraU = D3DXVECTOR3(0.0f,1.0f,0.0f);
	m_moveCamera = D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_rotCamera.y = 0;
	m_rotModelCamera.y=0;
	m_moveCameraR = 50;
	m_AngleOfView = AngleOfView;
	m_CameraMode = 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// カメラの終了処理
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Camera::Uninit(void)
{

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// カメラの更新処理
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Camera::Update(void)
{
	// カメラはふたつの動きをする
	// １つはCueから白球への一人称視点[m_CameraMode=0]
	// ２つめは上方から見下ろす俯瞰視点[m_CameraMode=1]
	// これはプレイヤが任意に切り替えることが出来る

	switch (m_CameraMode)
	{
		//一人称視点
	case 0:
		m_posCameraP = Cue::GetCuePosition();
		m_posCameraR = Ball::GetWhiteBallPosition();
		break;

		//俯瞰視点
	case 1:
		m_posCameraP = D3DXVECTOR3(0.0f,310.0f,210.0f);
		m_posCameraR = D3DXVECTOR3(0.0f,  0.0f,  0.0f);
		break;
	}


	// カメラモード切り替え
	if(InputKeyboard::GetKeyboardTrigger(DIK_1))
	{
		m_CameraMode =0;
	}
	if(InputKeyboard::GetKeyboardTrigger(DIK_2))
	{
		m_CameraMode =1;
	}

	////視点位置操作下
	//if(InputKeyboard::GetKeyboardPress(DIK_N))
	//{
	//	m_posCameraP.y -= SPEED;
	//}

	////注視点の上移動
	//if(InputKeyboard::GetKeyboardPress(DIK_T))
	//{
	//	m_moveCameraR += SPEED;
	//}

	////注視点の下移動
	//if(InputKeyboard::GetKeyboardPress(DIK_B))
	//{
	//	m_moveCameraR -= SPEED;
	//}
	//
	////ズームイン
	//if(InputKeyboard::GetKeyboardPress(DIK_Z))
	//{
	//	m_AngleOfView-=0.002f;
	//}

	////ズームアウト
	//if(InputKeyboard::GetKeyboardPress(DIK_C))
	//{
	//	m_AngleOfView+=0.002f;
	//}

	//m_moveCamera = D3DXVECTOR3(pPosModel.x,pPosModel.y,pPosModel.z);
	//
	//m_posCameraP.x += (m_moveCamera.x+(200.0f*sinf(m_rotModelCamera.y)) - m_posCameraP.x)*0.05f+m_CameraY;
	//m_posCameraP.y =  pPosModel.y + 110.0f + m_CameraY;
	//m_posCameraP.z += (m_moveCamera.z+(200.0f*cosf(m_rotModelCamera.y)) - m_posCameraP.z)*0.05f+m_CameraY;

	//m_posCameraR.x += ( (pPosModel.x - sinf(pRotModel.y)*30.0f) - m_posCameraR.x) * 0.1f+m_CameraY;
	//m_posCameraR.y = pPosModel.y+m_moveCameraR + m_CameraY;
	//m_posCameraR.z += ( (pPosModel.z - cosf(pRotModel.y)*30.0f) - m_posCameraR.z) * 0.1f+m_CameraY;

	//	
	//if(CTimer::GetTimeUp()==true)
	//{
	//	m_rotModelCamera.y = m_rotModelCamera.y - D3DX_PI;
	//}

	//m_rotCamera.y += (m_rotModelCamera.y-m_rotCamera.y)*0.05f;
	//m_CameraY=0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// カメラの描画処理
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Camera::Draw(void)
{
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;

	D3DXMatrixIdentity(&m_mtxProjection);	//プロジェクションマトリクスの初期化
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
								float(m_AngleOfView),
								float(ASPECT),
								ORIGINAL_NEAR,
								ORIGINAL_FAR); //プロジェクションマトリクスの作成

	LPDIRECT3DDEVICE9 pDevice=Manager::GetRenderer()->GetDevice();
	pDevice->SetTransform(D3DTS_PROJECTION,&m_mtxProjection);	//プロジェクションマトリクスの設定

	D3DXMatrixIdentity(&m_mtxView);	//ビューマトリクスの初期化
	D3DXMatrixLookAtLH(&m_mtxView,
						&m_posCameraP,//カメラの視点
						&m_posCameraR,//カメラの注視点
						&m_veCameraU//カメラの上方向ベクトル
						);	//ビューマトリクスの作成
	pDevice->SetTransform(D3DTS_VIEW,
							&m_mtxView);	//ビューマトリクスの設定
}