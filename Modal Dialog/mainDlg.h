#pragma once
#include "header.h"

class mainModal
{
public:
	mainModal(void);
public:
	~mainModal(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static mainModal* ptr;
	BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
	void Cls_OnClose(HWND hwnd);
	HWND  hStatic1, hEdit2, hStatic2, hEdit4;
};
