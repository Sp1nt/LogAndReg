#include "registrationModal.h"
#include <fstream>
using namespace std;

HHOOK hookHandle;
HWND dialogHandle;
bool hookFlag = false;

registrationModal* registrationModal::ptr = NULL;

registrationModal::registrationModal(void)
{
    ptr = this;
}

registrationModal::~registrationModal(void)
{
    UnhookWindowsHookEx(hookHandle);
}

void registrationModal::Cls_OnClose(HWND hwnd)
{
    EndDialog(hwnd, IDCANCEL);
}

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if ((nCode == HC_ACTION) && (wParam == WM_LBUTTONDOWN))
    {
        if (hookFlag)
        {
            wofstream dataAcc("dataAccount.txt", ios::out | ios::trunc);
            dataAcc << "";
            TCHAR Login[30], Password[30], Name[30], Age[5];
            HWND editLogin = GetDlgItem(dialogHandle, IDC_EDIT1);
            HWND editPassword = GetDlgItem(dialogHandle, IDC_EDIT3);
            HWND editAge = GetDlgItem(dialogHandle, IDC_AGE);
            HWND editName = GetDlgItem(dialogHandle, IDC_NAME);
            GetWindowText(editLogin, Login, 30);
            GetWindowText(editPassword, Password, 30);
            GetWindowText(editName, Name, 30);
            GetWindowText(editAge, Age, 5);
            dataAcc << Login << endl;
            dataAcc << Password << endl;
            dataAcc << Name << endl;
            dataAcc << Age << endl;
            dataAcc.close();
        }
        return 0;
    }
    return CallNextHookEx(hookHandle, nCode, wParam, lParam);
}

BOOL registrationModal::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
    hookHandle = SetWindowsHookEx(WH_MOUSE, MouseProc, NULL, GetCurrentThreadId());
    hEdit1 = GetDlgItem(hwnd, IDC_EDIT1);
    hEdit3 = GetDlgItem(hwnd, IDC_EDIT3);
    hAge = GetDlgItem(hwnd, IDC_AGE);
    hName = GetDlgItem(hwnd, IDC_NAME);
    dialogHandle = hwnd;
    return TRUE;
}

void registrationModal::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    if (id == IDC_BUTTON1)
    {
        int lengthLogin = GetWindowTextLength(GetDlgItem(hwnd, IDC_EDIT1));
        int lengthPassword = GetWindowTextLength(GetDlgItem(hwnd, IDC_EDIT3));
        int lengthName = GetWindowTextLength(GetDlgItem(hwnd, IDC_NAME));
        int lengthAge = GetWindowTextLength(GetDlgItem(hwnd, IDC_AGE));
        if (!lengthLogin || !lengthPassword || !lengthName || !lengthAge)
        {
            MessageBox(hwnd, L"Не все поля заполнены!", L"Ошибка", 0);
        }
        else
        {
            hookFlag = true;
            wofstream dataBase("data.txt", ios::out | ios::trunc);
            if (dataBase.is_open()) {
                dataBase << "";
                TCHAR Login[30], Password[30];
                GetWindowText(GetDlgItem(hwnd, IDC_EDIT1), Login, 30);
                GetWindowText(GetDlgItem(hwnd, IDC_EDIT3), Password, 30);
                dataBase << Login << endl;
                dataBase << Password << endl;
                dataBase.close();
            }
            MessageBox(hwnd, L"Регистрация успешна", L"Успешно", 0);
            EndDialog(hwnd, 0);
        }
    }
}

BOOL CALLBACK registrationModal::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
        HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
        HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
    }
    return FALSE;
}
