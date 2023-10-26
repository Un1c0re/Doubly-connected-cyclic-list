// Вариант 9. Класс «Двусвязный циклический список»
#include <iostream>
#include <fstream>
#include <ctime>
#include <Windows.h>
#include <list>
#include <algorithm>
#include "Object.hpp"


#define TEMPLATE template<typename Type>
#define T_PARAMS <Type>
#define PARAMS_1 <int>
#define PARAMS_2 <char>
#define MAX_VALUE 10000
//#define MAX_VALUE 10000.453
#define SEARCH_COUNT 100


TEMPLATE void listMenu(ObjectList T_PARAMS* myList);
TEMPLATE void FillListRandom(ObjectList T_PARAMS* myList, int size);
Object PARAMS_1* FillRandObject(int maxValue);
Object PARAMS_2* FillRandObject(float maxValue);
TEMPLATE void CompareFunction(ObjectList T_PARAMS* myList);
TEMPLATE int AverageResult(std::list T_PARAMS myList, int size);
TEMPLATE int AverageResult(ObjectList T_PARAMS* myList, int size);


/*---------------------------------------------------------------------------*/


int main() {
	setlocale(LC_ALL, "Russian");
	srand(time(nullptr));
	listMenu(new ObjectList PARAMS_1);
	return 0;
}


/*---------------------------------------------------------------------------*/


TEMPLATE
void listMenu(ObjectList T_PARAMS* myList) {
	int index = -1;
	int key = -1;

	Object T_PARAMS* newObject;
		std::string listMenu[9] = {
		"1. Вывести список элементов",
		"2. Вывести список объектов",
		"3. Добавить новый элемент в список",
		"4. Вставить новый элемент в список по индексу",
		"5. удалить элемента из списка по индексу",
		"6. Найти элемент по индексу",
		"7. составить таблицу сравнения с std::list",
		"8. очистить список",
		"0. выход"
	};
	do {
		system("cls");

		std::cout	<< "Курсовая работа по дисциплине \"Алгоритмы иструктуры данных\"\n"
					<< "Вариант 9. Двусвязный циклический список\n\n"
					<< "текущий список:\n";

		myList->PrintInfo();

		std::cout << "Количество элементов: " << myList->Count() << std::endl << std::endl;

		for (auto& i : listMenu)
			std::cout << i << std::endl;

		fflush(stdin);

		std::cin >> key;

		switch (key) {
		case 1:
			if (myList->Count() == 0)
				std::cout << "Список пуст\n";
			else 
				myList->Print();

			system("pause");
			break;

		case 2:
			if (myList->Count() == 0)
				std::cout << "Список пуст\n";
			else
				myList->PrintObjectList();

			system("pause");
			break;

		case 3:
			newObject = FillRandObject(MAX_VALUE);
			myList->Add(newObject);
			std::cout << "Элемент успешно вставлен в список\n";

			system("pause");
			break;

		case 4:
			std::cout << "Введите индекс по которому хотите вставить элемент : ";
			std::cin >> index;

			if (index > myList->Count()) {
				std::cout << "индекс больше размера списка\n";

				system("pause");
				break;
			}

			newObject = FillRandObject(MAX_VALUE);
			myList->Insert(newObject, index);

			std::cout << "Элемент успешно вставлен!\n";

			system("pause");
			break;

		case 5:
			std::cout << "Введите индекс элемента, который вы хотите удалить : ";
			std::cin >> index;

			if (index > myList->Count()) {
				std::cout << "индекс больше размера списка\n";

				system("pause");
				break;
			}

			newObject = (Object T_PARAMS*)myList->RemoveIndex(index);

			std::cout << "Элемент удален:\n";

			newObject->PrintObject();

			system("pause");
			delete newObject;
			break;

		case 6:
			std::cout << "Введите индекс элемента, который хотите найти:";
			std::cin >> index;

			newObject = (Object T_PARAMS*)myList->GetItem(index);

			if (newObject) {
				std::cout << "Элемент найден:\n";
				newObject->PrintObject();
			} else {
				std::cout << "Элемент не был найден\n";
			}

			system("pause");
			break;

		case 7:
			CompareFunction(myList);

			std::cout << "Результат сравнения записан в таблицу compareResult.csv\n";
			
			system("pause");
			break;

		case 8:
			myList->Clear();

			std::cout << "Список очищен\n";

			system("pause");
			break;

		case 0:
			return;
		}
	} while (key != -1);
}


TEMPLATE
void CompareFunction(ObjectList T_PARAMS* myList) {
	int size;
	std::ofstream fout("CompareResult.csv");
	time_t beforeSearch, afterSearch;
	std::list<int> stdList = {};

	fout << ";std::list;myList" << std::endl;
	fout << "Размер последовательности;Время поиска;Время поиска" << std::endl;

	for (size = 10000; size <= 200000; size += 10000) {
		fout << size << ";";
		FillListRandom(myList, size);

		for (int i = 0; i < size; i++)
			stdList.push_back(rand() % size);
		/*---------------------------------------*/
		/*fout << AverageResult(stdList, size) << ";";
		fout << AverageResult(myList, size) << std::endl;*/
		/*int middleMyList = myList->Count() / 2;
		std::list<int>::iterator it = stdList.begin();
		std::advance(it, size / 2);*/
		/* beforeSearch = GetTickCount64();
		for (auto i = stdList.begin(); i != stdList.end(); i++) {
		if (i == it) {
		stdList.emplace(i, rand() % size);
		break;
		}
		}
		afterSearch = GetTickCount64();
		fout << afterSearch - beforeSearch << ";";*/
		/*beforeSearch = GetTickCount64();
		myList->Insert(FillRandObject(MAX_VALUE), middleMyList);
		afterSearch = GetTickCount64();
		fout << afterSearch - beforeSearch << std::endl;*/

		beforeSearch = GetTickCount64();
		myList->RemoveIndex(size / 2);
		afterSearch = GetTickCount64();

		fout << afterSearch - beforeSearch << std::endl;

		myList->Clear();
		stdList.clear();
	}
}


TEMPLATE
int AverageResult(std::list T_PARAMS myList, int size) {
	long int sumOfSearchResults = 0;
	int searchKey = 0;
	int searchIndex = 0, j = 0;
	time_t beforeSearch, afterSearch;

	for (int i = 1; i <= SEARCH_COUNT; i++) {
		searchIndex = rand() % size;
		j = 0;

		for (auto it = myList.begin(); it != myList.end(); j++, it++) {
			if (j == searchIndex) {
				searchKey = *it;
				break;
			}
		}

		beforeSearch = GetTickCount64();
		for (auto it = myList.begin(); it != myList.end(); it++)
			if (*it == searchKey) break;
		afterSearch = GetTickCount64();

		sumOfSearchResults += afterSearch - beforeSearch;
	}
	return sumOfSearchResults / SEARCH_COUNT;
}


TEMPLATE
int AverageResult(ObjectList T_PARAMS* myList, int size) {
	ObjectList T_PARAMS& list = *myList;
	long int sumOfSearchResults = 0;
	int searchKey = 0;
	time_t beforeSearch, afterSearch;

	for (int i = 1; i <= SEARCH_COUNT; i++) {
		searchKey = list[rand() % size].GetValue();

		beforeSearch = GetTickCount64();
		list.FindObject(searchKey);
		afterSearch = GetTickCount64();

		sumOfSearchResults += afterSearch - beforeSearch;
	}
	return sumOfSearchResults / SEARCH_COUNT;
}


std::string GetRandString() {
	std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
	std::string letters;

	for (int i = 0; i < 5; i++)
		letters += alphabet[rand() % alphabet.size()];

	return letters;
}


char GetRandChar() {
	std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
	return alphabet[rand() % alphabet.size()];
}


bool GetRandBool() {
	return rand() % 2 == 0;
}


Object PARAMS_1* FillRandObject(int maxValue) {
	Object PARAMS_1* newObject = new Object PARAMS_1;
	newObject->SetValue(rand() % maxValue);
	return newObject;
}


Object PARAMS_2* FillRandObject(float maxValue) {
	Object PARAMS_2* object = new Object PARAMS_2;
	object->SetValue(GetRandChar());
	return object;
}


TEMPLATE
void FillListRandom(ObjectList T_PARAMS* myList, int size) {
	for (int i = 0; i < size; i++)
		myList->Add((Item*)FillRandObject(size));
}
