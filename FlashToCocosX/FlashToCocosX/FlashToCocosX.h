
// FlashToCocosX.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CFlashToCocosXApp:
// �йش����ʵ�֣������ FlashToCocosX.cpp
//

class CFlashToCocosXApp : public CWinApp
{
public:
	CFlashToCocosXApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	
	DECLARE_MESSAGE_MAP()
};

extern CFlashToCocosXApp theApp;