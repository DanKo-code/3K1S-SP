#include "tests.h"

namespace tests
{
	// Не можем получить удаленные данные
	BOOL test1()
	{
		ht::HtHandle* htHandle = ht::create(1000, 3, 10, 256, L"./files/HTspaceTest1.ht");
		ht::Element* element = new ht::Element("test2", 6, "test2", 6);

		ht::insert(htHandle, element);
		ht::removeOne(htHandle, element);
		ht::get(htHandle, element);

		return strcmp(ht::getLastError(htHandle), "-- not found element (GET)") == 0;			
	}

	// Не можем удалить удаленные данные
	BOOL test2()
	{
		ht::HtHandle* htHandle = ht::create(1000, 3, 10, 256, L"./files/HTspaceTest2.ht");
		ht::Element* element = new ht::Element("test3", 6, "test3", 6);

		ht::insert(htHandle, element);
		ht::removeOne(htHandle, element);
		ht::removeOne(htHandle, element);

		return strcmp(ht::getLastError(htHandle), "-- not found element (DELETE)") == 0;
		
	}

	// Не можем получить несуществующих данных 1)
	BOOL test3(){
		ht::HtHandle* ht = ht::create(1000, 3, 10, 256, L"./files/HTspaceTest3.ht");
		ht::get(ht, new ht::Element("test3", 6, "test3", 6));

		const char* res1 = ht::getLastError(ht);
		const char* res2 = "-- not found element (GET)";

		return strcmp(res1, res2) == 0;
	}

	// Проверка вставляемых и вставленных
	BOOL test4()
	{
		ht::HtHandle* htHandle = ht::create(1000, 3, 10, 256, L"./files/HTspaceTest4.ht");
		ht::Element* insertEl = new ht::Element("test1", 6, "test1", 6);

		ht::insert(htHandle, insertEl);
		ht::Element* getEl = ht::get(htHandle, new ht::Element("test1", 6));

		if (
			getEl == NULL ||
			insertEl->keyLength != getEl->keyLength ||
			memcmp(insertEl->key, getEl->key, insertEl->keyLength) != NULL ||
			insertEl->payloadLength != getEl->payloadLength ||
			memcmp(insertEl->payload, getEl->payload, insertEl->payloadLength) != NULL
			)
			return false;

		return true;
	}

	// Не можем получить несуществующих данных 2)
	BOOL test5() {
		ht::HtHandle* ht = ht::create(1000, 3, 10, 256, L"./files/HTspaceTest5.ht");
		ht::removeOne(ht, new ht::Element("test3", 6, "test3", 6));

		const char* res1 = ht::getLastError(ht);
		const char* res2 = "-- not found element (DELETE)";

		return strcmp(res1, res2) == 0;
	}

	// Не можем обновить несуществующих данных
	BOOL test6() {
		ht::HtHandle* ht = ht::create(1000, 3, 10, 256, L"./files/HTspaceTest6.ht");
		ht::update(ht, new ht::Element("test3", 6, "test3", 6), "test3", 6);

		const char* res1 = ht::getLastError(ht);
		const char* res2 = "-- not found element (UPDATE)";

		return strcmp(res1, res2) == 0;
	}
}