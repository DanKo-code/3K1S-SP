#pragma warning(disable : 4996)

#include <iostream>
#include <windows.h>
#include <string>
#include <sstream>
#include "sddl.h"

#include "../OS14_HTCOM_LIB/pch.h"
#include "../OS14_HTCOM_LIB/OS14_HTCOM_LIB.h"

#ifdef _WIN64
#pragma comment(lib, "../x64/Debug/OS14_HTCOM_LIB.lib")
#else
#pragma comment(lib, "../Debug/OS14_HTCOM_LIB.lib")
#endif

using namespace std;

string intToString(int number);
wchar_t* getWC(const char* c);
wchar_t* getFileName(const char* c);

int main(int argc, char* argv[])
{

	setlocale(LC_ALL, "Russian");

	try
	{
		HANDLE event = CreateEvent(NULL, TRUE, FALSE, getFileName(argv[1]));

		OS14_HTCOM_HANDEL h = OS14_HTCOM::Init();
		ht::HtHandle* ht = nullptr;
		
		wchar_t* fileName = getWC(argv[1]);

		if (argc == 4)
		{
			wchar_t* username = getWC(argv[2]);
			wchar_t* password = getWC(argv[3]);

			ht = OS14_HTCOM::HT::open(h, fileName, username, password, true);
		}
		else
		{
			ht = OS14_HTCOM::HT::open(h, fileName, true);
		}

		if (ht)
			cout << "-- open: success" << endl;
		else
			throw "-- open: error";

		while (WaitForSingleObject(event, 0) == WAIT_TIMEOUT) {
			int numberKey = rand() % 50;
			string key = intToString(numberKey);
			cout << key << endl;

			ht::Element* element = OS14_HTCOM::Element::createInsertElement(h, key.c_str(), key.length() + 1, "0", 2);
			if (OS14_HTCOM::HT::insert(h, ht, element))
				cout << "-- insert: success" << endl;
			else
				cout << "-- insert: error" << endl;

			delete element;

			Sleep(1000);
		}

		OS14_HTCOM::HT::close(h, ht);

		OS14_HTCOM::Dispose(h);
	}
	catch (const char* e) { cout << e << endl; }
	catch (int e) { cout << "HRESULT: " << e << endl; }

}

string intToString(int number)
{
	stringstream convert;
	convert << number;

	return convert.str();
}

wchar_t* getWC(const char* c)
{
	wchar_t* wc = new wchar_t[strlen(c) + 1];
	mbstowcs(wc, c, strlen(c) + 1);

	return wc;
}
wchar_t* getFileName(const char* c)
{
	const char* lastSlash = strrchr(c, '/');
	const char* filename = (lastSlash != NULL) ? lastSlash + 1 : c;
	return getWC(filename);
}