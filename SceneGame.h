#pragma once
#ifndef _SceneGame_H_
#define _SceneGame_H_

#include "main.h"
class SceneGame
{
public:
	SceneGame();
	~SceneGame();
	static void Init(HINSTANCE hInstance,
			HWND hWnd,
			BOOL bWindow);
	static void Uninit(void);
	static void Update(HWND hWnd);
	static void Draw(void);
};

#endif