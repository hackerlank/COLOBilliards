///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// main.cpp
//	ryuji oka
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//���������[�N����/////////////////////////////////////////////////////////////////////////////////////////////////////
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "main.h"
#include "Sound.h"
#include "SceneGame.h"
#include "Fade.h"
#include <time.h>

#define CLASS_NAME "Billiards"												//�E�B���h�E�N���X�̖��O
#define WINDOW_NAME "Billiards"												//�E�B���h�E�̖��O
#define TOP (4)															//���_��
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �v���g�^�C�v�錾
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WndProc(HWND,
						UINT,
						WPARAM,
						LPARAM);
HRESULT Init(HINSTANCE hInstance,
			HWND hWnd,
			BOOL bWindow);
void Uninit(void);
void Update(HWND hWnd);
void Draw(void);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �O���[�o���ϐ�
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int g_nCountFPS = 0;
MODE g_mode = MODE_GAME;
HINSTANCE g_hInstance;

HWND hWnd;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// main�֐�
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int WINAPI WinMain(HINSTANCE hInstance,
					HINSTANCE hPrevInstance,
					LPSTR lpCmdLine,
					int nCmdShow)
{
	//���������[�N����
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;
	
	timeBeginPeriod(1);	//����\��ݒ�
	dwExecLastTime =
	dwFPSLastTime = timeGetTime(); //���ݎ������擾
	dwCurrentTime =
	dwFrameCount = 0;
	
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),
				CS_CLASSDC,
				WndProc,
				0,
				0,
				hInstance,
				NULL,
				LoadCursor(NULL,IDC_ARROW),
				(HBRUSH)(COLOR_WINDOW+1),
				NULL,
				CLASS_NAME,
				NULL
	};
	//HWND hWnd;
	MSG msg;

	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	//�E�B���h�E�̐���
	hWnd = CreateWindowEx(0,
							CLASS_NAME,
							WINDOW_NAME,
							WS_OVERLAPPEDWINDOW,
							CW_USEDEFAULT,
							CW_USEDEFAULT,
							SCREEN_WIDTH,//��
							SCREEN_HEIGHT,//����
							NULL,
							NULL,
							hInstance,
							NULL);

	//�E�B���h�E�̕\��
	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);
	
	//������
	Sound *pSound = new Sound;
	pSound->Init(hWnd);

	SceneGame::Init(hInstance,hWnd,0);
	
	//�t�F�[�h�̏�����
	InitFade();

	//InitTitle();

	//���b�Z�[�W���[�v
	while(1)
	{
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE) != 0)
		{
			if(msg.message == WM_QUIT)
			{
			break;
			}
			else
			{
				//���b�Z�[�W�|��Ƒ��o
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();
			if((dwCurrentTime - dwFPSLastTime) >= 500)
			{
				g_nCountFPS = (dwFrameCount*1000)/(dwCurrentTime-dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				dwFrameCount = 0;
			}

			if((dwCurrentTime - dwExecLastTime) >= (1000/60))
			{
				dwExecLastTime = dwCurrentTime;
				//�X�V����
				Update(hWnd);
				//�`�揈��
				Draw();
				dwFrameCount++;
			}
			timeEndPeriod(1); //����\��߂�
		}
	}

	//�E�B���h�E�N���X�o�^����
	UnregisterClass(CLASS_NAME,wcex.hInstance);

	//�I������
	//UninitTitle();
	SceneGame::Uninit();
	pSound->Uninit();
	delete pSound;
	
	return (int)msg.wParam;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �E�B���h�E�v���V�[�W��
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WndProc(HWND hWnd,
						UINT uMsg,
						WPARAM wParam,
						LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_DESTROY :
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN :
		switch(wParam)
		{

		//Esc�L�[�ŃE�B���h�E�����
		case VK_ESCAPE :
			DestroyWindow(hWnd);
			break;

		default:
			break;

		}
		break;

	default :
		break;
	}
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

void Update(HWND hWnd)
{
	//g_pCManage->Update(hWnd);
	switch(g_mode)
	{
	case MODE_TITLE:
		//UpdateTitle();
		break;

	case MODE_GAME:
		SceneGame::Update(hWnd);
		break;
	}
	UpdateFade();
}

void Draw(void)
{
	//g_pCManage->Draw();

	switch(g_mode)
	{
		case MODE_TITLE:
			//DrawTitle();
			break;

		case MODE_GAME:
			SceneGame::Draw();
			break;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���[�h���Z�b�g�I
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SetMode(MODE mode)
{
	g_mode = mode;
	switch(g_mode)
	{
	case MODE_TITLE:
		SetFade(FADE_IN);
		//�^�C�g���̏���������
		//InitTitle();
		break;

	case MODE_GAME:
		//�^�C�g���̏I������
		//UninitTitle();

		SetFade(FADE_IN);
		//SceneGame::Init(g_hInstance,hWnd,0);
		break;

	default:
		break;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���݂̃��[�h���擾�I
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MODE GetMode(void)
{
	return g_mode;
}
