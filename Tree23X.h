#pragma once

#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

#define uli long int
#define skip cout<<endl
#define co cout<<
#define en <<endl
#define MAXN 10

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
class Tree23X
{
public:
	T key[3];
	int size;
	Tree23X* parent;
	Tree23X* first;
	Tree23X* second;
	Tree23X* third;
	Tree23X* fourth;

	

	Tree23X() : size(0), key{ 0, 0, 0 }, first(nullptr), second(nullptr), third(nullptr), fourth(nullptr), parent(nullptr) {}
	Tree23X(T k) : size(1), key{ k, 0, 0 }, first(nullptr), second(nullptr), third(nullptr), fourth(nullptr), parent(nullptr) {}
	Tree23X(T k, Tree23X* first_, Tree23X* second_, Tree23X* third_, Tree23X* fourth_, Tree23X* parent_) :
		size(1), key{ k, 0, 0 }, first(first_), second(second_), third(third_), fourth(fourth_), parent(parent_) {}

	void sort();
	void insert_to_key(T k);
	void insert(T k);
	void split();
	void become_to_node(T k, Tree23X* x, Tree23X* y);
	void remove_from_node(T k);
	void remove(T k);
	void insert_for(Tree23X* t, T k);
	void show();



	bool is_null(Tree23X* t);
	bool find(T k);



	Tree23X<T>* search(T k);
	Tree23X<T>* search_min();
};



template<typename T>
void Tree23X<T>::sort()
{
	if (size == 0 || size == 1) return;
	if (size == 2) if (key[0] > key[1]) swap(key[0], key[1]);
	if (size == 3)
	{
		if (key[0] > key[1]) swap(key[0], key[1]);
		if (key[0] > key[2]) swap(key[0], key[2]);
		if (key[1] > key[2]) swap(key[1], key[2]);
	}
}

template<typename T>
void Tree23X<T>::insert_to_key(T k)
{
	key[size] = k;
	size++;
	sort();
}

template<typename T>
void Tree23X<T>::insert(T k)
{
	if (this == NULL) return;
	else if (is_null(this))	this->insert_to_key(k);
	else if (k <= this->key[0]) this->first->insert(k);
	else if ((this->size == 1) || ((this->size == 2) && k <= this->key[1])) this->second->insert(k);
	else this->third->insert(k);

	return split();
}

template<typename T>
void Tree23X<T>::split()
{
	if (size < 3) return;

	Tree23X* x = new Tree23X(key[0], first, second, nullptr, nullptr, parent);
	Tree23X* y = new Tree23X(key[2], third, fourth, nullptr, nullptr, parent);


	if (x->first != nullptr) x->first->parent = x;
	if (x->second) x->second->parent = x;
	if (y->first) y->first->parent = y;
	if (y->second) y->second->parent = y;

	if (parent)
	{
		parent->insert_to_key(key[1]);

		if (parent->first == this) parent->first = nullptr;
		else if (parent->second == this) parent->second = nullptr;
		else if (parent->third == this) parent->third = nullptr;

		if (parent->first == nullptr)
		{
			parent->first = x;
			parent->second = y;
			parent->third = parent->second;
			parent->fourth = parent->third;
		}
		else if (parent->second == nullptr)
		{
			parent->second = x;
			parent->third = y;
			parent->fourth = parent->third;
		}
		else if (parent->third == nullptr)
		{
			parent->third = x;
			parent->fourth = y;
		}
	}
	else
	{
		x->parent = this;
		y->parent = this;
		become_to_node(key[1], x, y);
	}
}

template<typename T>
void Tree23X<T>::become_to_node(T k, Tree23X* x, Tree23X* y)
{
	key[0] = k;
	key[1] = NULL;
	key[2] = NULL;
	first = x;
	second = y;
	third = nullptr;
	fourth = nullptr;
	parent = nullptr;
	size = 1;
}

template<typename T>
void Tree23X<T>::remove_from_node(T k)
{
	if (size >= 1 && key[0] == k)
	{
		key[0] = key[1];
		key[1] = key[2];
		size--;
	}
	else if (size == 2 && key[1] == k)
	{
		key[1] = key[2];
		size--;
	}
}


template<typename T>
bool Tree23X<T>::find(T k)
{
	for (int i = 0; i < size; ++i)
		if (key[i] == k) return true;
	return false;
}

template<typename T>
bool Tree23X<T>::is_null(Tree23X* t)
{
	return(t->first == nullptr && t->second == nullptr && t->third == nullptr);
}


template<typename T>
Tree23X<T>* Tree23X<T>::search(T k)
{
	if (!this) return nullptr;

	if (this->find(k)) return this;
	else if (k < this->key[0]) return this->first->search(k);
	else if ((this->size == 2) && (k < this->key[1]) || (this->size == 1)) return this->second->search(k);
	else if (this->size == 2) return this->third->search(k);
}

template<typename T>
Tree23X<T>* Tree23X<T>::search_min()
{
	if (!this) return this;
	if (!(this->first)) return this;
	else return this->first->search_min();
}


//Вывод по возростанию (In-order)
template<typename T>
void Tree23X<T>::show()
{
	if (this != nullptr)
	{
		this->first->show();
		if (this->key[0] != 0) co this->key[0] en;
		if (this->key[1] != NULL)  this->second->show(), co "" << this->key[1] en;
		else this->second->show();

		this->third->show();
	}
	else return;
}

template<typename T>
void Tree23X<T>::insert_for(Tree23X* t, T k)
{
	if (this != nullptr)
	{
		if (this->key[0] != NULL && this->key[0] != k) t->insert(this->key[0]);
		if (this->key[1] != NULL && this->key[1] != k) t->insert(this->key[1]);
		if (this->key[2] != NULL && this->key[2] != k) t->insert(this->key[2]);

		this->first->insert_for(t, k);
		this->second->insert_for(t, k);
		this->third->insert_for(t, k);
	}
	else return;
}

template<typename T>
void Tree23X<T>::remove(T k)
{
	Tree23X* item = this->search(k); // Ищем узел, где находится ключ k

	Tree23X* p = item->parent;

	if (!item->first)
	{
		if (item->size == 2 && item->key[1] == k) item->key[1] = NULL;
		else if (item->size == 2)
		{
			swap(item->key[0], item->key[1]);
			item->key[1] = NULL;
		}
		else
		{
			Tree23X* buf = new Tree23X();
			insert_for(buf, k);
			if (p->parent->first == p) p->parent->first = buf;
			else if (p->parent->second == p) p->parent->second = buf;
			else if (p->parent->third == p) p->parent->third = buf;
			delete p;
		}
	}
	else
	{
		Tree23X* buf = new Tree23X();
		item->insert_for(buf, k);
		if (p->first == item) p->first = buf;
		else if (p->second == item) p->second = buf;
		else if (p->third == item) p->third = buf;
		delete item;
	}

}
