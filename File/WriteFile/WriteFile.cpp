#include "Header.h"

WriteProject* WriteProject::ptr = NULL;

WriteProject::WriteProject(void)
{
	ptr = this;
}

WriteProject::~WriteProject(void)
{

}

void WriteProject::Cls_OnClose(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

DWORD WINAPI Write(LPVOID lp)
{
	WriteProject* ptr = (WriteProject*)lp;
	HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, false, TEXT("{B8A2C367-10FE-494d-A869-841B2AF972E0}"));
	DWORD dwAnswer = WaitForSingleObject(hMutex, INFINITE);
	ofstream out(TEXT("write.txt"));
	if (!out.is_open())
	{
		MessageBox(0, TEXT("Error"), TEXT("Error"), MB_OK);
		return 1;
	}

	if (dwAnswer == WAIT_OBJECT_0)
	{
		int A[100];
		for (int i = 0; i < 100; i++)
		{
			A[i] = rand() % 50;
			out << A[i] << ' ';
		}
		out.close();

		ReleaseMutex(hMutex);

		MessageBox(ptr->hDialog, TEXT("Запись данных в файл result.txt завершена!"), TEXT("Мьютекс"), MB_OK | MB_ICONINFORMATION);
	}
	return 0;
	}

BOOL  WriteProject::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hDialog = hwnd;
	CreateThread(NULL, 0, Write, this, 0, NULL);
	return TRUE;
}

BOOL CALLBACK  WriteProject::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
	}
	return FALSE;
}

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrev, LPTSTR lpszCmdLine, int nCmdShow)
{
	WriteProject dlg;
	return DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, WriteProject::DlgProc);
}