#pragma warning(disable : 4996)

#include <windows.h>
#include <conio.h>
#include <iostream>

wchar_t* getWC(const char* c);

int main(int argc, char* argv[])
{
	wchar_t* eventName = getWC(argv[1]);

	HANDLE hStopEvent = CreateEvent(NULL,
		TRUE, //FALSE - автоматический сброс; TRUE - ручной
		FALSE,
		eventName);
	SetEvent(hStopEvent);
}

wchar_t* getWC(const char* c)
{
	wchar_t* wc = new wchar_t[strlen(c) + 1];
	mbstowcs(wc, c, strlen(c) + 1);

	return wc;
}