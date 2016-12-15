//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// InputKeyBoard.cpp
// �L�[�{�h���͂̊Ǘ�
// ryuji oka
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "main.h"
#include "InputKeyboard.h"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �v���g�^�C�v�錾
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �O���[�o���ϐ�
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LPDIRECTINPUTDEVICE8 InputKeyboard::m_pDIDevKeyboard = NULL;	// �L�[�{�[�h�ւ̃|�C���^
BYTE InputKeyboard::m_aKeyState[MAX_KEY] = {0};				// �L�[�{�[�h���
BYTE InputKeyboard::m_aKeyStateTrigger[MAX_KEY] = {0};			// �g���K�[
BYTE InputKeyboard::m_aKeyStateRelease[MAX_KEY] = {0};			// �����[�X
InputManager::REPEAT InputKeyboard::m_aKeyStateRepeat[MAX_KEY];		// ���s�[�g
/////////////////////////////////////////////////////////////////////////////////
// ������
/////////////////////////////////////////////////////////////////////////////////
HRESULT InputKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr;

	hr = InputManager::Init(hInstance, hWnd);

	if(FAILED(hr))
	{
		MessageBox(NULL, "InputKeyboard��InputManager�̏������G���[", "�G���[", MB_OK);
		return (hr);
	}

	hr = m_pDInput->CreateDevice(GUID_SysKeyboard, &m_pDIDevKeyboard, NULL);

	if(FAILED(hr))
	{
		MessageBox(NULL, "InputKeyboard��CreateDevice�̃G���[", "�G���[", MB_OK);
		return (hr);
	}

	hr = m_pDIDevKeyboard->SetDataFormat(&c_dfDIKeyboard);

	if(FAILED(hr))
	{
		MessageBox(NULL, "InputKeyboard��SetDataFormat�̃G���[", "�G���[", MB_OK);
		return (hr);
	}

	hr = m_pDIDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE) );

	if(FAILED(hr))
	{
		MessageBox(NULL, "InputKeyboard��SetCooperativeLevel�̃G���[", "�G���[", MB_OK);
		return (hr);
	}

	m_pDIDevKeyboard->Acquire(); // �A�N�Z�X���擾

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
		m_pDIDevKeyboard->Unacquire(); // �L�[�{�[�h�̃A�N�Z�X����j��(���͐���I��)
		m_pDIDevKeyboard->Release();
		m_pDIDevKeyboard = NULL;
	}
	InputManager::Uninit();
}

/////////////////////////////////////////////////////////////////////////////////
// �X�V
/////////////////////////////////////////////////////////////////////////////////
void InputKeyboard::Update(HWND hWnd)
{
	BYTE aKeyState[MAX_KEY];

	if(SUCCEEDED(m_pDIDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0]) ))
	{
		for(int nKey = 0; nKey < MAX_KEY; nKey++)
		{
			m_aKeyStateTrigger[nKey] = (aKeyState[nKey] ^ m_aKeyState[nKey]) & aKeyState[nKey]; // �g���K�[
			m_aKeyStateRelease[nKey] = (aKeyState[nKey] ^ m_aKeyState[nKey]) & m_aKeyState[nKey]; // �����[�X

			// ���s�[�g
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
// ���s�[�g�擾�֐�
/////////////////////////////////////////////////////////////////////////////////
bool InputKeyboard::GetKeyboardRepeat(int nKey, unsigned int nTimer, unsigned int nInterval)
{
	m_aKeyStateRepeat[nKey].nTimer = nTimer;
	m_aKeyStateRepeat[nKey].nInterval = nInterval;

	return (m_aKeyStateRepeat[nKey].state & 0x80) ? true : false;
}