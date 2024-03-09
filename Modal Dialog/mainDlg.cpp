#include "mainDlg.h"
#include "registrationModal.h"
#include "loginModal.h"

mainModal* mainModal::ptr = NULL;

mainModal::mainModal(void)
{
	ptr = this;
}

mainModal::~mainModal(void)
{

}

void mainModal::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, IDCANCEL);
}

BOOL mainModal::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	return TRUE;
}


void mainModal::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if(id == IDC_SIGNUP)
	{
		registrationModal dlg;
		INT_PTR result = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_SIGNUP), hwnd, registrationModal::DlgProc);
		
	}
	else if(id == IDC_LOGIN)
	{
		loginModal dlg;
		INT_PTR result = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_LOGIN), hwnd, loginModal::DlgProc);
	}
}

BOOL CALLBACK mainModal::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}
