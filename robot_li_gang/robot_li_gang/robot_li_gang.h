
// robot_li_gang.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Crobot_li_gangApp:
// �йش����ʵ�֣������ robot_li_gang.cpp
//

class Crobot_li_gangApp : public CWinApp
{
public:
	Crobot_li_gangApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Crobot_li_gangApp theApp;