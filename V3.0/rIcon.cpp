#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

signed main()
{
	ShowWindow(GetConsoleWindow(),SW_HIDE); // 这个函数没讲过，反正就是隐藏自己的控制台窗口
	POINT p;
	while (1)
	{
		int i=(rand() % 4);
		if(i==1)DrawIcon(GetDC(0),(rand() % 1920),(rand() % 1080),LoadIcon(0,IDI_ERROR));
		else if(i==2)DrawIcon(GetDC(0),(rand() % 1920),(rand() % 1080),LoadIcon(0,IDI_WARNING));
		else if(i==3)DrawIcon(GetDC(0),(rand() % 1920),(rand() % 1080),LoadIcon(0,IDI_QUESTION));
		else if(i==4)DrawIcon(GetDC(0),(rand() % 1920),(rand() % 1080),LoadIcon(0,IDI_INFORMATION));
		Sleep(10);
	}
	return 0;
}
