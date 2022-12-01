#pragma once

#include<windows.h>
#include <fstream>
#include <tchar.h>
#include <windowsX.h>
#include <time.h>
#include"resource.h"

using namespace std;

class WriteProject
{
public:
	WriteProject(void);
public:
	~WriteProject(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static WriteProject* ptr;
	void Cls_OnClose(HWND hwnd);
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	HWND hDialog;
};