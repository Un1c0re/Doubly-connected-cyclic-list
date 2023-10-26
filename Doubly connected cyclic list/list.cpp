#include "list.h"
#include <cstdio>
#include <iostream>
#include <cmath>


Item::Item() {
	prev = nullptr;
	next = nullptr;
	owner = nullptr;
}


Item::~Item() {
	if (owner) owner->RemoveItem(this);
}


void Item::PrintItem() {
	std::cout	<< "Item: "		<< this		<< "\t"
				<< "owner: "	<< owner	<< "\t"
				<< "prev: "		<< prev		<< "\t"
				<< "next: "		<< next		<< std::endl;
}


/*---------------------------------------------------------------------------*/


List::List() {
	head = nullptr;
	tail = nullptr;
}


List::~List() {
	Clear();
}


void List::Add(Item* item) {
	if (!item) return;
	item->owner = this;

	if (!head) {
		item->prev = item;
		item->next = item;

		head = item;
		tail = item;
	} else {
		tail->next = item;

		item->prev = tail;
		item->next = head;
		
		tail = item;
		head->prev = tail;
	}
}


Item* List::GetItem(int index) {
	if (index > this->Count()) return nullptr;

	Item* p;
	int i = 0;

	for (p = this->head; ; p = p->next, i++)
		if (i == index)
			return p;
}


int List::GetIndex(Item* item) {
	if (!item || item->owner != this) return -1;

	Item* p;
	int i = 0;

	for (p = head; ; p = p->next, i++) {
		if (p == item)
			return i;
		if (p == tail)
			break;
	}

	return -1;
}


Item* List::GetHead() {
	return this->head;
}


Item* List::GetTail() {
	return this->tail;
}


Item* List::RemoveIndex(int index) {
	Item* p = GetItem(index);
	if (!p) return nullptr;

	p->owner = nullptr;

	if (p == head && p == tail) {
		head = nullptr;
		tail = nullptr;
	} else {
		p->prev->next = p->next;
		p->next->prev = p->prev;

		if (p == head) head = p->next;
		if (p == tail) tail = p->prev;
	}
	return p;
}


Item* List::RemoveItem(Item* item) {
	if (item->owner == this)
		return RemoveIndex(GetIndex(item));

	return nullptr;
}


Item* List::RemoveHead() {
	return RemoveItem(this->head);
}


Item* List::RemoveTail() {
	return RemoveItem(this->tail);
}


void List::DeleteIndex(int index) {
	delete RemoveItem(GetItem(index));
}


void List::DeleteItem(Item* item) {
	delete RemoveItem(item);
}


void List::DeleteHead() {
	DeleteItem(this->head);
}


void List::DeleteTail() {
	DeleteItem(this->tail);
}


void List::Insert(Item* newItem, int index) {
	if (!newItem || newItem->owner != nullptr)
		return;

	Item* p = GetItem(index);

	if (!p)
		Add(newItem);
	else {
		newItem->next = p;
		newItem->prev = p->prev;
		newItem->owner = this;

		p->prev->next = newItem;

		if (p->prev == tail)
			head = newItem;

		p->prev = newItem;
	}
}


int List::Count() {
	if (!this->head) return 0;
	int i = 0, count = 0;

	for (Item* p = this->head; ; p = p->next, i++) {
		count++;
		if (p == tail) break;
	}

	return count;
}


void List::Clear() {
	Item* p = new Item();

	do {
		p = RemoveIndex(0);

		if (!p) break;

		delete p;
	} while (p);

	head = nullptr;
	tail = nullptr;
}


void List::PrintInfo() {
	std::cout	<< "List: " << this << "\n"
				<< "head: " << head << "\n"
				<< "tail: " << tail << std::endl;
}


void List::Print() {
	Item* p = head;

	for (int i = 0; ; i++, p = p->next) {
		std::cout	<< i
					<< "\tItem: "	<< p
					<< "\tOwner: "	<< p->owner
					<< "\tPrev: "	<< p->prev
					<< "\tNext: "	<< p->next 
					<< std::endl;

		if (p == tail) break;
	}
}