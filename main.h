#pragma once
#ifndef _MAIN_H_
#define _MAIN_H_

//���������[�N����/////////////////////////////////////////////////////////////////////////////////////////////////////
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define D3D_DEBUG_INFO	//texture�̒��g�������悤��

#include <windows.h>
#include "d3dx9.h"													//�`�揈���p

//���������[�N�����֌W/////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
	#ifndef DBG_NEW
		#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
		#define new DBG_NEW
	#endif
#endif	//_DEBUG
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DIRECTINPUT_VERSION (0x0800)
#include "dinput.h"
#include "xaudio2.h"
#include "Renderer.h"
#include <dxerr.h>

//���C�u�����̃����N
#pragma comment (lib,"d3d9.lib")									//�`�揈���p
#pragma comment (lib,"d3dx9.lib")									//��L�̊g�����C�u����
#pragma comment (lib,"dxguid.lib")									//DirectX�R���|�l�[�g�g�p�ɕK�v
#pragma comment (lib,"winmm.lib")
#pragma comment (lib,"dinput8.lib")
#pragma comment (lib,"dxerr.lib")									//HRESULT������Ԃ��Ă���̂�������

#define SCREEN_WIDTH (1200)											//��ʂ̕�
#define SCREEN_HEIGHT (750)											//��ʂ̍���

#define MAX_KEYPATTERN (7)

#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE|D3DFVF_TEX1/*�e�N�X�`�����W*/)
#define FVF_VERTEX_3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)
//��L�̃t�H�[�}�b�g�ɍ��킹���\����
typedef struct
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
}VERTEX_2D;


/* ===== 3D�t�H�[�}�b�g�ɍ��킹���\���� ===== */
typedef struct
{
	D3DXVECTOR3 pos;		// ���_���W
	D3DXVECTOR3 nor;		// �@��
	D3DCOLOR col;			// ���_�J���[
	D3DXVECTOR2 tex;		// �e�N�X�`�����W
}VERTEX_3D;

typedef enum
{
	MODE_TITLE=0,
	MODE_TUTORIAL,
	MODE_GAME,
	MODE_RESULT,
	MODE_MAX,
}MODE;

void SetMode(MODE mode);
MODE GetMode(void); //���݂̃��[�h���擾�����I�I

#endif