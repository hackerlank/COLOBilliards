#pragma once
#ifndef _Camera_H_
#define _Camera_H_


class Camera
{
private:
	D3DXVECTOR3 m_posCameraP; //�J�����̎��_
	D3DXVECTOR3 m_posCameraR; //�J�����̒����_
	D3DXVECTOR3 m_veCameraU; //�J�����̏�����x�N�g��
	D3DXVECTOR3 m_rotCamera;	//�J�����̌���
	D3DXVECTOR3 m_rotModelCamera;	//���f���̌���

	float m_fLengthIntervalCamera;	//���_���璍���_�܂ł̋���
	
	D3DXMATRIX m_mtxProjection; //�v���W�F�N�V�����}�g���N�X
	D3DXMATRIX m_mtxView;		//�r���[�}�g���N�X
	
	float m_moveCameraR;
	
	D3DXVECTOR3 m_moveCamera;	//�J�����̈ړ���
	float m_AngleOfView;

	static float m_CameraY;

	int m_CameraMode;			// �J�����̃��[�h
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