#pragma once
#ifndef _RENDERER_H_
#define _RENDERER_H_

class Scene;									//前方宣言（使いますよーっていう予約みたいなものだよ！！コンパイルが早くなるよ☆）
class Camera;
class Light;

class Renderer
{
public:
	Renderer();
	~Renderer();
	HRESULT Init(HWND hWnd, bool bWindow);		//デバイスの作成ダヨ
	void Uninit(void);							//正確な英語だとInitの反対はUnintじゃなくてFinalize（コレは田中先生のオリジナル）
	void Update(void);
	void Draw(void);
	LPDIRECT3DDEVICE9 GetDevice(void){return m_pD3DDevice;};
	D3DXMATRIX GetViewCamera(void);
	D3DXVECTOR3 GetRotCamera(void);
private:
	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	LPD3DXFONT m_pD3DFont;

	D3DLIGHT9 m_aLight[3];	//ライト情報

	D3DXVECTOR3 m_posCameraP; //カメラの視点
	D3DXVECTOR3 m_posCameraR; //カメラの注視点
	D3DXVECTOR3 m_vecCameraU; //カメラの上方向ベクトル
	D3DXVECTOR3 m_rotCamera;	//カメラの向き
	D3DXVECTOR3 m_rotModelCamera;	//モデルの向き
	float m_fLengthIntervalCamera;	//視点から注視点までの距離
	D3DXMATRIX m_mtxProjection; //プロジェクションマトリクス
	D3DXMATRIX m_mtxView;		//ビューマトリクス
	float m_moveCameraR;
	D3DXVECTOR3 m_moveCamera;	//カメラの移動量
	static Camera *m_pCamera;
	static Light *m_pLight;
	
	LPDIRECT3DSURFACE9 m_surfaceBackbff;
	LPDIRECT3DSURFACE9 m_surfaceDepthbff;
	LPDIRECT3DSURFACE9 m_surfaceBackbff2;
	LPDIRECT3DSURFACE9 m_surfaceDepthbff2;
};
#endif