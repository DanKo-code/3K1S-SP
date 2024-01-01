#pragma warning(disable : 4996)

#include <iostream>
#include <windows.h>
#include <string>
#include <sstream>

#define HTPATH L"D:/3k1s/MyLabs/SP/SP_7/lab6-ht-service-user-com-dll/storage/HTspace.ht"

#include "../OS15_HTCOM_LIB/pch.h"
#include "../OS15_HTCOM_LIB/OS15_HTCOM_LIB.h"

#ifdef _WIN64
#pragma comment(lib, "../x64/Debug/OS15_HTCOM_LIB.lib")
#else
#pragma comment(lib, "../Debug/OS15_HTCOM_LIB.lib")
#endif

using namespace std;

string intToString(int number);
wchar_t* getWC(const char* c);
SECURITY_ATTRIBUTES getSecurityAttributes();
HANDLE createStopEvent(const wchar_t* stopEventName);

int main(int argc, char* argv[])
{
	
	setlocale(LC_ALL, "Russian");

	try
	{
		wchar_t* fileName = getWC(argv[1]);

		HANDLE hStopEvent = createStopEvent(fileName);

		OS15_HTCOM_HANDEL h = OS15_HTCOM::Init();
		ht::HtHandle* ht = nullptr;

		if (argc == 4)
		{
			wchar_t* username = getWC(argv[2]);
			wchar_t* password = getWC(argv[3]);

			ht = OS15_HTCOM::HT::open(h, fileName, username, password, true);
		}
		else
		{
			ht = OS15_HTCOM::HT::open(h, fileName, true);
		}

		if (ht)
			cout << "-- open: success" << endl;
		else
			throw "-- open: error";

		while (WaitForSingleObject(hStopEvent, 0) == WAIT_TIMEOUT) {
			int numberKey = rand() % 50;
			string key = intToString(numberKey);
			cout << key << endl;

			ht::Element* element = OS15_HTCOM::Element::createGetElement(h, key.c_str(), key.length() + 1);
			if (OS15_HTCOM::HT::removeOne(h, ht, element))
				cout << "-- remove: success" << endl;
			else
				cout << "-- remove: error" << endl;

			delete element;

			Sleep(1000);
		}

		OS15_HTCOM::HT::close(h, ht);

		cout << endl << "Удалить компонент и выгрузить dll, если можно:" << endl;
		OS15_HTCOM::Dispose(h);
	}
	catch (const char* e) { cout << e << endl; }
	catch (int e) { cout << "HRESULT: " << e << endl; }

}

wchar_t* getWC(const char* c)
{
	wchar_t* wc = new wchar_t[strlen(c) + 1];
	mbstowcs(wc, c, strlen(c) + 1);

	return wc;
}
string intToString(int number)
{
	stringstream convert;
	convert << number;

	return convert.str();
}

SECURITY_ATTRIBUTES getSecurityAttributes()
{
	const wchar_t* sdd = L"D:"
		L"(D;OICI;GA;;;BG)" //Deny guests
		L"(D;OICI;GA;;;AN)" //Deny anonymous
		L"(A;OICI;GA;;;AU)" //Allow read, write and execute for Users
		L"(A;OICI;GA;;;BA)"; //Allow all for Administrators
	SECURITY_ATTRIBUTES SA;
	ZeroMemory(&SA, sizeof(SA));
	SA.nLength = sizeof(SA);
	ConvertStringSecurityDescriptorToSecurityDescriptor(
		sdd,
		SDDL_REVISION_1,
		&SA.lpSecurityDescriptor,
		NULL);

	return SA;
}

HANDLE createStopEvent(const wchar_t* stopEventName)
{
	std::wstring closeEventName = L"Global\\"; closeEventName += stopEventName; closeEventName += L"-stopEvent";
	SECURITY_ATTRIBUTES SA = getSecurityAttributes();

	HANDLE hStopEvent = CreateEvent(
		&SA,
		TRUE, //FALSE - автоматический сброс; TRUE - ручной
		FALSE,
		closeEventName.c_str());

	return hStopEvent;
}