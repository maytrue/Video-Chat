
// VideoPlayer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CVideoPlayerApp: 
// �йش����ʵ�֣������ VideoPlayer.cpp
//

class CVideoPlayerApp : public CWinApp
{
public:
	CVideoPlayerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CVideoPlayerApp theApp;