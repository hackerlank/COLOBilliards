#pragma once
#ifndef _LIGHT_H_
#define _LIGHT_H_


class Light
{
public:
	Light(){};
	~Light(){};

	void SetLight(void);
private:
	D3DLIGHT9 m_aLight[3];	//ƒ‰ƒCƒgî•ñ
};
#endif