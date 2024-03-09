#pragma once
#include "header.h"

class registrationModal
{
public:
    registrationModal(void);
    ~registrationModal(void);
    static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
    static registrationModal* ptr;
    BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
    void Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
    void Cls_OnClose(HWND hwnd);
    HWND hEdit1, hEdit3, hName, hAge;
};