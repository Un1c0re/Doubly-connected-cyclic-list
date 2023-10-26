#pragma once

#include "list.h"

#define TEMPLATE template<typename Type>
#define T_PARAMS <Type>


TEMPLATE class Object;


TEMPLATE
class ObjectList : public List {
	public:
		ObjectList T_PARAMS() : List() {}
		int FindObject(Type value);
		void PrintObjectList();
		Object T_PARAMS& operator[] (int i);
};


TEMPLATE
class Object : public Item {
	private:
		Type Value;

	public:
		Object T_PARAMS() : Item() {}
		Type GetValue() { return Value; }
		void SetValue(Type x) { Value = x; }
		void PrintObject();
};


/*---------------------------------------------------------------------------*/


TEMPLATE
Object T_PARAMS& ObjectList T_PARAMS::operator[](int i) {
	int count = Count();

	if (count) {
		if (i >= 0 && i < count)
			return *(Object T_PARAMS*)this->GetItem(i);
		else
			throw std::out_of_range("Индекс больше размера списка");
	}
	else
		throw std::length_error("Список пуст");
}


TEMPLATE
bool operator==(Object T_PARAMS object1, Object T_PARAMS object2) {
	return object1.GetValue() == object2.GetValue();
}


/*---------------------------------------------------------------------------*/


TEMPLATE
int ObjectList T_PARAMS::FindObject(Type value) {
	ObjectList T_PARAMS& list = *this;
	int i = 0;
	int size = list.Count();

	for (i = 0; i < size; i++) {
		if (list[i].GetValue() == value)
			return i;
	}

	return -1;
}


TEMPLATE
void Object T_PARAMS::PrintObject() {
	std::cout << "Value: " << this->GetValue() << std::endl;
}


TEMPLATE
void ObjectList T_PARAMS::PrintObjectList() {
	ObjectList T_PARAMS& list = *this;
	int size = list.Count();

	for (int i = 0; i < size; i++) {
		std::cout << "Object " << i << std::endl;
		list[i].PrintObject();
		std::cout << std::endl;
	}
}