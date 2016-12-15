#pragma once

#ifndef _InputKeyboard_H_
#define _InputKeyboard_H_

#include "main.h"
#include "InputManager.h"

class InputKeyboard : public InputManager
{
public:
	InputKeyboard(){}
	~InputKeyboard(){}
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(HWND hWnd);
	static bool GetKeyboardPress(int nKey){return (m_aKeyState[nKey] & 0x80) ? true : false;}
	static bool GetKeyboardTrigger(int nKey){return (m_aKeyStateTrigger[nKey] & 0x80) ? true : false;}
	static bool GetKeyboardRelease(int nKey){return (m_aKeyStateRelease[nKey] & 0x80) ? true : false;}
	static bool GetKeyboardRepeat(int nKey, unsigned int nTimer, unsigned int nInterval);

private:
	static const int MAX_KEY = 256;					// �ő吔
	static LPDIRECTINPUTDEVICE8 m_pDIDevKeyboard;	// �L�[�{�[�h�ւ̃|�C���^
	static BYTE m_aKeyState[MAX_KEY];				// �L�[�{�[�h���
	static BYTE m_aKeyStateTrigger[MAX_KEY];		// �g���K�[
	static BYTE m_aKeyStateRelease[MAX_KEY];		// �����[�X
	static REPEAT m_aKeyStateRepeat[MAX_KEY];		// ���s�[�g
};
#endif