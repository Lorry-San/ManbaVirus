#include <windows.h>

HCRYPTPROV prov;

int random()
{
	if (prov == NULL)
	{
		if (!CryptAcquireContext(&prov, NULL, NULL, PROV_RSA_FULL, CRYPT_SILENT | CRYPT_VERIFYCONTEXT))
		{
			ExitProcess(1);
		}
	}
	int out;
	CryptGenRandom(prov, sizeof(out), (BYTE*)(&out));
	return out & 0x7fffffff;
}

void mess1(LPVOID lp)
{
	MessageBoxA(NULL, "lol", "MEMZ", MB_OK | MB_SYSTEMMODAL | MB_ICONSTOP);
}

void mess2(LPVOID lp)
{
	MessageBoxA(NULL, "lol", "MEMZ", MB_OK | MB_SYSTEMMODAL | MB_ICONSTOP);
}

void mess3(LPVOID lp)
{
	MessageBoxA(NULL, "lol", "MEMZ", MB_OK | MB_SYSTEMMODAL | MB_ICONSTOP);
}

//主函数
void MainProgram()
{
	int NumberOfMessageBox = 20;
	HWND hwnd[10005];
	HWND ThisProgram = GetForegroundWindow();
	NumberOfMessageBox += 3;
	ShowWindow(ThisProgram, SW_HIDE);
	Sleep(4000);
	for (int i = 1; i <= NumberOfMessageBox / 3; i++)
	{
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)mess1, 0, 0, 0);
		Sleep(90);
		hwnd[i] = FindWindowA(NULL, "MEMZ");
		ShowWindow(hwnd[i], SW_HIDE);
		MoveWindow(hwnd[i], random() % 1920, random() % 1080, 220, 180, false);
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)mess2, 0, 0, 0);
		Sleep(90);
		hwnd[i + 3334] = FindWindowA(NULL, "MEMZ");
		ShowWindow(hwnd[i + 3334], SW_HIDE);
		MoveWindow(hwnd[i + 3334], random() % 1920, random() % 1080, 220, 180, false);
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)mess3, 0, 0, 0);
		Sleep(90);
		hwnd[i + 6667] = FindWindowA(NULL, "MEMZ");
		ShowWindow(hwnd[i + 6667], SW_HIDE);
		MoveWindow(hwnd[i + 6667], random() % 1920, random() % 1080, 220, 180, false);
	}
	Sleep(1000);
	for (int i = 1; i <= NumberOfMessageBox; i++)
	{
		ShowWindow(hwnd[i], SW_SHOW);
		Sleep(15);
		ShowWindow(hwnd[i + 3334], SW_SHOW);
		Sleep(15);
		ShowWindow(hwnd[i + 6667], SW_SHOW);
	}
	Sleep(1000);
	for (int i = 1; i <= NumberOfMessageBox / 3; i++)
	{
		SendMessage(hwnd[i], WM_CLOSE, 0, 0);
		Sleep(5);
		SendMessage(hwnd[i + 3334], WM_CLOSE, 0, 0);
		Sleep(5);
		SendMessage(hwnd[i + 6667], WM_CLOSE, 0, 0);
		Sleep(5);
	}
	return;
}

int main()
{
	MainProgram();
	return 0;
}
