#ifndef _INPUTMANAGER_H_
#define _INPUTMANAGER_H_

#pragma once

#include "main.h"

class InputManager
{
public:
	InputManager(){}
	virtual ~InputManager(){}
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	virtual void Uninit(void);
	virtual void Update(HWND hWnd) = 0;

protected:
	// リピートの構造体
	typedef struct
	{
		BYTE state;		// ON/OFF
		unsigned int nTimer;	// リピートするまで
		unsigned int nCnt;	// カウンター
		unsigned int nInterval;
		unsigned int nRepeatCnt;
	} REPEAT;

	static LPDIRECTINPUT8 m_pDInput;
};
#endif