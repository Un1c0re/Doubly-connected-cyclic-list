#pragma once

class List;

class Item {
	protected:
		Item* prev;
		Item* next;
		List* owner;
	public:
		Item();
		virtual ~Item();
		void PrintItem();
		Item* GetNext()  { return next; }
		Item* GetPrev()  { return prev; }
		List* GetOwner() { return owner; }
		friend class List;
};

class List {
	private:
		Item* head;
		Item* tail;
	public:
		List();
		~List();
		void Print();
		void PrintInfo();
		void Add(Item* item);
		Item* GetItem(int index);
		int GetIndex(Item* item);
		Item* GetHead();
		Item* GetTail();
		Item* RemoveIndex(int index);
		Item* RemoveItem(Item* item);
		Item* RemoveHead();
		Item* RemoveTail();
		void DeleteIndex(int index);
		void DeleteItem(Item* item);
		void DeleteHead();
		void DeleteTail();
		void Insert(Item* item, int index);
		int Count();
		void Clear();
};