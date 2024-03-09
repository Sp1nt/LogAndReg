#include "loginModal.h"
#include <fstream>
#include <string>
using namespace std;

loginModal* loginModal::ptr = NULL;

loginModal::loginModal(void)
{
    ptr = this;
}

loginModal::~loginModal(void)
{

}

void loginModal::Cls_OnClose(HWND hwnd)
{
    EndDialog(hwnd, IDCANCEL);
}

BOOL loginModal::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
    hEdit = GetDlgItem(hwnd, IDC_EDIT2);
    hEdit2 = GetDlgItem(hwnd, IDC_EDIT4);
    return TRUE;
}


void loginModal::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    if (id == IDC_BUTTON3)
    {
        wifstream data("data.txt");
        TCHAR log[30], pass[30];
        int lengthLogin = GetWindowTextLength(hEdit);
        int lengthPassword = GetWindowTextLength(hEdit2);
        if (!lengthLogin || !lengthPassword)
        {
            MessageBox(hwnd, L"Не все поля заполнены!", L"Ошибка", 0);
        }
        else
        {
            if (data.is_open()) {
                int i = 0;
                wstring str;
                bool f = false;
                GetWindowText(hEdit, log, 30);
                GetWindowText(hEdit2, pass, 30);
                while (getline(data, str))
                {
                    i++;
                    if (i % 2 != 0)
                    {
                        if (_tcscmp(str.c_str(), log) == 0)
                            f = true;
                        else
                            f = false;
                    }
                    else
                    {
                        if (_tcscmp(str.c_str(), pass) == 0 && f == true)
                        {
                            MessageBox(hwnd, L"Вход успешен!", L"Успешно", 0);
                            EndDialog(hwnd, 0);
                            data.close();
                            return;
                        }
                    }
                }
                MessageBox(hwnd, L"Неверные данные", L"Ошибка", 0);
                data.close();
            }

        }
    }
}

BOOL CALLBACK loginModal::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
        HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
        HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
    }
    return FALSE;
}
