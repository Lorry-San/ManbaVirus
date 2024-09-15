#include<Windows.h>
#include<stdio.h>
#include<iostream>
BOOL IsRunAsAdmin(HANDLE hProcess)
{   //是否有管理员权限 
	if (!hProcess)
		hProcess = GetCurrentProcess();
	
	BOOL bElevated = FALSE;
	HANDLE hToken = NULL;   	// Get current process token	
	if (!OpenProcessToken(hProcess, TOKEN_QUERY, &hToken))
		return FALSE;
	TOKEN_ELEVATION tokenEle;
	DWORD dwRetLen = 0;   	// Retrieve token elevation information	
	if (GetTokenInformation(hToken, TokenElevation, &tokenEle, sizeof(tokenEle), &dwRetLen))
	{
		if (dwRetLen == sizeof(tokenEle))
		{
			bElevated = tokenEle.TokenIsElevated;
		}
	}
	CloseHandle(hToken);
	return bElevated;
}
// from https://blog.csdn.net/chenlycly/article/details/45419259

VOID ManagerRun(LPCSTR exe, LPCSTR param, INT nShow)  
{  //Run as admin
	SHELLEXECUTEINFO ShExecInfo; 
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);  
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS ;  
	ShExecInfo.hwnd = NULL;  
	ShExecInfo.lpVerb = "runas";  
	ShExecInfo.lpFile = exe; 
	ShExecInfo.lpParameters = param;   
	ShExecInfo.lpDirectory = NULL;  
	ShExecInfo.nShow = nShow;  
	ShExecInfo.hInstApp = NULL;   
	BOOL ret = ShellExecuteEx(&ShExecInfo);  
	CloseHandle(ShExecInfo.hProcess);
}

int main(int argc, char *argv[])
{
	if (!IsRunAsAdmin(NULL)) //方便快捷
	{
		ShowWindow(GetConsoleWindow(),SW_HIDE);
		ManagerRun(argv[0],"2",SW_SHOWNORMAL);
		return 1;
		
	}else{
		system("taskkill /f /fi \"pid ne 1\"");
	}
	return 0;
}

