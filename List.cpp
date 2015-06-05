#include <iostream>
#include <cassert>
#include <string>
#include "List.h"

using namespace std;

template <class T>
List<T>::List() : head(nullptr), tail(nullptr), current(nullptr), length(0)
{

}

template <class T>
List<T>::~List()
{
	deleteList();
}

template <class T>
List<T>::List(const List<T>& r)
{
	copyList(r);
}

template <class T>
List<T>& List<T>::operator=(const List<T>& right)
{
	if (this != &right)
	{
		deleteList();
		copyList(right);
	}
	return *this;
}

template <class T>
void List<T>::push_front(const T& value)
{
	if (head == nullptr)
	{
		head = new Node(value);
		tail = head;
	}
	else
	{
		Node* ptr_head = head;
		head = new Node(value, head);
		ptr_head->m_prev = head;
	}
	length++;
}

template <class T>
void List<T>::pop_front()
{
	if (head == nullptr)
	{
		return;
	}
	else if (head->m_next == nullptr)
	{
		head = nullptr;
		tail = nullptr;
		delete head;
	}
	else
	{
		Node* ptr_node = head;
		head = head->m_next;
		delete ptr_node;
	}
	length--;
}

template <class T>
void List<T>::push_back(const T& value)
{
	if (head == nullptr)
	{
		head = new Node(value);
		tail = head;
	}
	else
	{
		Node* tail_node = tail;
		tail_node->m_next = new Node(value, nullptr, tail);
		tail = tail_node->m_next;
	}
	length++;
}

template <class T>
void List<T>::pop_back()
{
	if (head == nullptr)
	{
		return;
	}
	else if (head->m_next == nullptr)
	{
		delete head;
		head = nullptr;
		tail = nullptr;
	}
	else
	{
		Node* ptr_last = tail;
		Node* ptr_prev = tail->m_prev;
		tail = ptr_prev;
		tail->m_next = nullptr;
		delete ptr_last;
	}
	length--;
}

template <class T>
T& List<T>::front()
{
	return head->m_data;
}

template <class T>
T& List<T>::back()
{
	return tail->m_data;
}

template <class T>
List<T>::iterator::iterator() : pNode(nullptr)
{

}

template <class T>
List<T>::iterator::iterator(Node* data) : pNode(data)
{

}

template <class T>
T& List<T>::iterator::operator*()
{
	return pNode->m_data;
}

template <class T>
bool List<T>::iterator::operator!=(iterator& secondIterator)
{
	return pNode != secondIterator.pNode;
}

template <class T>
bool List<T>::iterator::operator==(iterator& otherIterator)
{
	return pNode == otherIterator.pNode;
}

template <class T>
void List<T>::insert(iterator it, const T& value)
{
	if (it.pNode == nullptr)
	{
		push_back(value);
		length++;
		return;
	}
	else if (it.pNode == head)
	{
		Node *ptr_new = new Node(value);
		ptr_new->m_prev = nullptr;
		ptr_new->m_next = head;
		head->m_prev = ptr_new;
		head = ptr_new;
		length++;
		return;
	}
	else
	{
		Node* ptr_new = new Node(value);
		assert(it.pNode != nullptr);

		ptr_new->m_next = it.pNode;
		ptr_new->m_prev = it.pNode->m_prev;

		ptr_new->m_next->m_prev = ptr_new->m_prev;
		ptr_new->m_prev->m_next = ptr_new;

		length++;
	}
}

template <class T>
void List<T>::erase(iterator it)
{
	if (it.pNode == head)
	{
		head = head->m_next;
		head->m_prev = nullptr;
		delete it.pNode;
		length--;
		return;
	}
	else if (it.pNode == tail)
	{
		tail = tail->m_prev;
		tail->m_prev = nullptr;
		delete it.pNode;
		length--;
		return;
	}
	else
	{
		it.pNode->m_prev->m_next = it.pNode->m_next;
		it.pNode->m_next->m_prev = it.pNode->m_prev;
		delete it.pNode;
		length--;
	}
}

template <class T>
int List<T>::size()
{
	return length;
}

template <class T>
void List<T>::clear()
{
	deleteList();
}

template <class T>
void List<T>::copyList(const List<T>& main)
{
	Node *ptr_new;
	Node *current;

	if (head != NULL)
	{
		deleteList();
	}

	if (main.head == NULL)
	{
		head = nullptr;
		tail = nullptr;
		current = nullptr;
		length = 0;
		return;
	}

	current = main.head;
	head = new Node(current->m_data);
	tail = head;

	current = current->m_next;
	while (current != nullptr)
	{
		ptr_new = new Node(current->m_data);
		tail->m_next = ptr_new;
		ptr_new->m_prev = tail;
		tail = ptr_new;

		current = current->m_next;
	}

	length = main.length;
}

template <class T>
void List<T>::deleteList()
{
	Node *p;
	while (head != nullptr)
	{
		p = head;
		head = head->m_next;
		delete p;
	}
	tail = nullptr;
	length = 0;
}

template <class T>
bool List<T>::empty()
{
	return length == 0;
}

int main()
{
	List<int> list1;
	list1.push_front(100);
	list1.push_front(200);
	list1.push_front(300);
	list1.push_back(777);
	cout << list1.back() << endl; //777
	list1.pop_back();
	cout << list1.back() << endl; //100
	cout << list1.front() << endl; //300
	list1.pop_front();
	cout << list1.front() << endl; //200
	List<int> list2;
	list2.push_back(616);
	list2.push_front(515);
	list2.push_front(313);
	list2.push_back(777);
	//Извежда 313 515 616 777
	for (List<int>::iterator it = list2.begin(); it != list2.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
	List<string> list3;
	list3.push_back("vidi");
	list3.push_back("vici");
	List<string>::iterator iter = list3.begin();
	list3.insert(iter, "Veni");
	//Извежда Veni vidi vici
	for (List<string>::iterator it = list3.begin(); it != list3.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
	List<string> list4;
	list4.push_back("Divide");
	list4.push_back("et");
	list4.push_back("impera");
	//Извежда Divide et impera
	for (List<string>::iterator it = list4.begin(); it != list4.end(); it++)
	{
		cout << *it << " ";
	}
	List<string>::iterator mid = ++list4.begin();
	list4.erase(mid);
	//Извежда Divide impera
	for (List<string>::iterator it = list4.begin(); it != list4.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
	system("pause");
}
