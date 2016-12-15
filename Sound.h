#pragma once
#ifndef _Sound_H_
#define _Sound_H_

#include "main.h"

///////////////////////////////////////////////////////////////////////////////
// �T�E���h�t�@�C��
///////////////////////////////////////////////////////////////////////////////
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// BGM
	SOUND_LABEL_TIME,			// ���̊����߂�
	SOUND_LABEL_EARTH,			// �n����
	SOUND_LABEL_SE_DAMAGE,		// �Փ�
	SOUND_LABEL_SE_MISS,		// ����
	SOUND_LABEL_MAX,
} SOUND_LABEL;

///////////////////////////////////////////////////////////////////////////////
// �v���g�^�C�v�錾
///////////////////////////////////////////////////////////////////////////////
class Sound
{
public:
	Sound(){};
	~Sound(){};
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	static HRESULT PlaySound(SOUND_LABEL label);
	static void StopSound(SOUND_LABEL label);
	static void StopSound(void);

	static void SetVolume(SOUND_LABEL label,float vol);
	
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
private:
	static IXAudio2 *m_pXAudio2;									// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	static IXAudio2MasteringVoice *m_pMasteringVoice;				// �}�X�^�[�{�C�X
	static IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
	static BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^
	static DWORD m_aSizeAudio[SOUND_LABEL_MAX];						// �I�[�f�B�I�f�[�^�T�C�Y
};
#endif
