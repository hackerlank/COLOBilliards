#pragma once
#ifndef _RENDERER_H_
#define _RENDERER_H_

class Scene;									//�O���錾�i�g���܂���[���Ă����\��݂����Ȃ��̂���I�I�R���p�C���������Ȃ�恙�j
class Camera;
class Light;

class Renderer
{
public:
	Renderer();
	~Renderer();
	HRESULT Init(HWND hWnd, bool bWindow);		//�f�o�C�X�̍쐬�_��
	void Uninit(void);							//���m�ȉp�ꂾ��Init�̔��΂�Unint����Ȃ���Finalize�i�R���͓c���搶�̃I���W�i���j
	void Update(void);
	void Draw(void);
	LPDIRECT3DDEVICE9 GetDevice(void){return m_pD3DDevice;};
	D3DXMATRIX GetViewCamera(void);
	D3DXVECTOR3 GetRotCamera(void);
private:
	LPDIRECT3D9 m_pD3D;
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	LPD3DXFONT m_pD3DFont;

	D3DLIGHT9 m_aLight[3];	//���C�g���

	D3DXVECTOR3 m_posCameraP; //�J�����̎��_
	D3DXVECTOR3 m_posCameraR; //�J�����̒����_
	D3DXVECTOR3 m_vecCameraU; //�J�����̏�����x�N�g��
	D3DXVECTOR3 m_rotCamera;	//�J�����̌���
	D3DXVECTOR3 m_rotModelCamera;	//���f���̌���
	float m_fLengthIntervalCamera;	//���_���璍���_�܂ł̋���
	D3DXMATRIX m_mtxProjection; //�v���W�F�N�V�����}�g���N�X
	D3DXMATRIX m_mtxView;		//�r���[�}�g���N�X
	float m_moveCameraR;
	D3DXVECTOR3 m_moveCamera;	//�J�����̈ړ���
	static Camera *m_pCamera;
	static Light *m_pLight;
	
	LPDIRECT3DSURFACE9 m_surfaceBackbff;
	LPDIRECT3DSURFACE9 m_surfaceDepthbff;
	LPDIRECT3DSURFACE9 m_surfaceBackbff2;
	LPDIRECT3DSURFACE9 m_surfaceDepthbff2;
};
#endif