#ifndef LIST_H
#define LIST_H

template <class T>
class List
{
public:
	/*Вътре в класа List да бъде написана структура за елемент в свързания списък(Node).
		В структурата да има конструктор и член - променливи : m_data(int), m_next(Node*), m_prev(Node*)*/
	struct Node
	{
		T m_data;
		Node* m_next;
		Node* m_prev;

		Node(T data, Node *p_next = nullptr, Node *p_prev = nullptr) : m_data(data), m_next(p_next), m_prev(p_prev)
		{

		}
	};
	
	List();//Default-ен конструктор
	~List();//Деструктор
	List(const List&);
	List& operator=(const List&);

	void push_front(const T&);//добавя елемент в началото на списъка
	void pop_front(); //премахва елемент от началото на списъка
	void push_back(const T&);//добавя елемент в края на списъка
	void pop_back();//премахва елемент от края на списъка

	T& front();//връща стойността на елемента в началото на списъка
	T& back();//връща стойността на елемента в края на списъка

//Вътре в класа List да бъде имплементиран клас iterator.
	class iterator
	{
	public:
		//Да бъде написaн конструктор за този клас
		iterator();
		// Като член-променлива този клас има указател към Node.
		iterator(Node*);
		//връща стойността на даден Node (data)
		T& operator*();
		//префиксен оператор за инкрементиране (it = ++v.begin())
		iterator& operator++()
		{
			pNode = pNode->m_next;
			iterator temp(pNode);
			return temp;
		}
		//постфиксен оператор за инкрементиране (it = v.begin()++)
		iterator operator++(int)
		{
			iterator temp(pNode);
			pNode = pNode->m_next;
			return temp;
		}
		//проверява дали адресите на два Node-a са различни
		bool operator!=(iterator&);
		bool operator==(iterator&);

	private:
		Node* pNode;
		friend class List<T>;
	};

	//връща iterator към началото на списъка
	iterator begin()
	{
		iterator it(head);
		return it;
	}
	//връща iterator към края на списъка (един елемент след края на списъка)
	iterator end()
	{
		iterator it(tail->m_next);
		return it;
	}
	//вмъква елемент със стойност value на позиция iterator
	void insert(iterator, const T&);
	//изтрива елемент на позиция iterator
	void erase(iterator);
	//връща броя елементи в списъка
	int size();
	//изтрива всички елементи на списъка
	void clear();
	//проверява дали списъкът е празен
	bool empty();

private:
	Node* head;
	Node* tail;
	Node* current;
	unsigned int length;
	void copyList(const List<T>&);
	void deleteList();
};
#endif 
