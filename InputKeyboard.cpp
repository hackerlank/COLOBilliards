//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// InputKeyBoard.cpp
// キーボド入力の管理
// ryuji oka
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "InputKeyboard.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// プロトタイプ宣言
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// グローバル変数
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LPDIRECTINPUTDEVICE8 InputKeyboard::m_pDIDevKeyboard = NULL;	// キーボードへのポインタ
BYTE InputKeyboard::m_aKeyState[MAX_KEY] = {0};				// キーボード情報
BYTE InputKeyboard::m_aKeyStateTrigger[MAX_KEY] = {0};			// トリガー
BYTE InputKeyboard::m_aKeyStateRelease[MAX_KEY] = {0};			// リリース
InputManager::REPEAT InputKeyboard::m_aKeyStateRepeat[MAX_KEY];		// リピート
/////////////////////////////////////////////////////////////////////////////////
// 初期化
/////////////////////////////////////////////////////////////////////////////////
HRESULT InputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr;

	hr = InputManager::Init(hInstance, hWnd);

	if(FAILED(hr))
	{
		MessageBox(NULL, "InputKeyboardのInputManagerの初期化エラー", "エラー", MB_OK);
		return (hr);
	}

	hr = m_pDInput->CreateDevice(GUID_SysKeyboard, &m_pDIDevKeyboard, NULL);

	if(FAILED(hr))
	{
		MessageBox(NULL, "InputKeyboardのCreateDeviceのエラー", "エラー", MB_OK);
		return (hr);
	}

	hr = m_pDIDevKeyboard->SetDataFormat(&c_dfDIKeyboard);

	if(FAILED(hr))
	{
		MessageBox(NULL, "InputKeyboardのSetDataFormatのエラー", "エラー", MB_OK);
		return (hr);
	}

	hr = m_pDIDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE) );

	if(FAILED(hr))
	{
		MessageBox(NULL, "InputKeyboardのSetCooperativeLevelのエラー", "エラー", MB_OK);
		return (hr);
	}

	m_pDIDevKeyboard->Acquire(); // アクセス権取得

	for(int i = 0; i < MAX_KEY; i++)
	{
		m_aKeyStateRepeat[i].state = 0x00;
		m_aKeyStateRepeat[i].nTimer = 0;
		m_aKeyStateRepeat[i].nCnt = 0;
		m_aKeyStateRepeat[i].nInterval = 0;
		m_aKeyStateRepeat[i].nRepeatCnt = 0;
	}

	return (S_OK);
}

/////////////////////////////////////////////////////////////////////////////////
// Uninit
/////////////////////////////////////////////////////////////////////////////////
void InputKeyboard::Uninit(void)
{
	if(m_pDIDevKeyboard != NULL)
	{
		m_pDIDevKeyboard->Unacquire(); // キーボードのアクセス権を破棄(入力制御終了)
		m_pDIDevKeyboard->Release();
		m_pDIDevKeyboard = NULL;
	}
	InputManager::Uninit();
}

/////////////////////////////////////////////////////////////////////////////////
// 更新
/////////////////////////////////////////////////////////////////////////////////
void InputKeyboard::Update(HWND hWnd)
{
	BYTE aKeyState[MAX_KEY];

	if(SUCCEEDED(m_pDIDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0]) ))
	{
		for(int nKey = 0; nKey < MAX_KEY; nKey++)
		{
			m_aKeyStateTrigger[nKey] = (aKeyState[nKey] ^ m_aKeyState[nKey]) & aKeyState[nKey]; // トリガー
			m_aKeyStateRelease[nKey] = (aKeyState[nKey] ^ m_aKeyState[nKey]) & m_aKeyState[nKey]; // リリース

			// リピート
			if(aKeyState[nKey] && m_aKeyStateRepeat[nKey].nCnt < m_aKeyStateRepeat[nKey].nTimer)
			{
				m_aKeyStateRepeat[nKey].nCnt++;
			}
			else if(m_aKeyStateRelease[nKey])
			{
				m_aKeyStateRepeat[nKey].nCnt = 0;
				m_aKeyStateRepeat[nKey].nRepeatCnt = 0;
			}
			
			if(m_aKeyStateRepeat[nKey].nCnt >= m_aKeyStateRepeat[nKey].nTimer)
			{
				m_aKeyStateRepeat[nKey].nRepeatCnt++;
			}

			m_aKeyStateRepeat[nKey].state = 0x00;

			if(m_aKeyStateRepeat[nKey].nTimer != 0)
			{
				if(m_aKeyStateTrigger[nKey])
				{
					m_aKeyStateRepeat[nKey].state = 0x80;
				}

				if(m_aKeyStateRepeat[nKey].nCnt >= m_aKeyStateRepeat[nKey].nTimer &&
					m_aKeyStateRepeat[nKey].nRepeatCnt % (m_aKeyStateRepeat[nKey].nInterval + 1) == 0)
				{
					m_aKeyStateRepeat[nKey].state = 0x80;
				}
				
			}

			m_aKeyState[nKey] = aKeyState[nKey];
		}
	}
	else
	{
		m_pDIDevKeyboard->Acquire();
	}
}

/////////////////////////////////////////////////////////////////////////////////
// リピート取得関数
/////////////////////////////////////////////////////////////////////////////////
bool InputKeyboard::GetKeyboardRepeat(int nKey, unsigned int nTimer, unsigned int nInterval)
{
	m_aKeyStateRepeat[nKey].nTimer = nTimer;
	m_aKeyStateRepeat[nKey].nInterval = nInterval;

	return (m_aKeyStateRepeat[nKey].state & 0x80) ? true : false;
}