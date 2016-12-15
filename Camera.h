#pragma once
#ifndef _Camera_H_
#define _Camera_H_


class Camera
{
private:
	D3DXVECTOR3 m_posCameraP; //カメラの視点
	D3DXVECTOR3 m_posCameraR; //カメラの注視点
	D3DXVECTOR3 m_veCameraU; //カメラの上方向ベクトル
	D3DXVECTOR3 m_rotCamera;	//カメラの向き
	D3DXVECTOR3 m_rotModelCamera;	//モデルの向き

	float m_fLengthIntervalCamera;	//視点から注視点までの距離
	
	D3DXMATRIX m_mtxProjection; //プロジェクションマトリクス
	D3DXMATRIX m_mtxView;		//ビューマトリクス
	
	float m_moveCameraR;
	
	D3DXVECTOR3 m_moveCamera;	//カメラの移動量
	float m_AngleOfView;

	static float m_CameraY;

	int m_CameraMode;			// カメラのモード
public:
	Camera(){};
	~Camera(){};

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	
	D3DXVECTOR3 GetRotCamera(void){return m_rotCamera;};
	D3DXMATRIX GetView(void){return m_mtxView;};

	static void SetCameraY(float y){m_CameraY = y;};
};
#endif