#include "tests.h"

using namespace std;

int main()
{
	if (tests::test1())
		cout << "-- test1: success" << endl;
	else
		cout << "-- test1: error" << endl;

	if (tests::test2())
		cout << "-- test2: success" << endl;
	else
		cout << "-- test2: error" << endl;

	if (tests::test3())
		cout << "-- test3: success" << endl;
	else
		cout << "-- test3: error" << endl;

	if (tests::test4())
		cout << "-- test4: success" << endl;
	else
		cout << "-- test4: error" << endl;

	if (tests::test5())
		cout << "-- test5: success" << endl;
	else
		cout << "-- test5: error" << endl;	

	if (tests::test6())
		cout << "-- test6: success" << endl;
	else
		cout << "-- test6: error" << endl;
}