//소스 코드4.2: Circular Linked List - template 버젼으로 전환하기
// head node를 갖고 circular list로서   class List{ private: Node *last;}로 구현하기
//난수가 입력되면 정렬된 list를 만든다.
//두개의 list를 merge하여 정렬된 list를 만든다.
// 출력은 iterator를 사용한다.
// class Node, List, ListIterator
#include <iostream>
using namespace std;

class List;

class Node
{
	friend class List;
	friend class ListIterator;
	friend class CircularList;

public:
	Node(int, Node *);
	~Node();

private:
	int num;
	Node *link;
};

class List
{
	friend class ListIterator;
	friend class CircularList;

public:
	List();
	~List();
	virtual void Add(int &);
	virtual void Delete(int &); //주어진 x 값을 갖는 노드를 삭제
	virtual void Show();
	// int Length( ); //count the number of nodes in a list
	// void Merge(List&, List&);//the merged nodes in a sequential order
private:
	Node *first;
};

class ListIterator
{
public:
	ListIterator(const List &lst);
	~ListIterator();
	bool NotNull();
	bool NextNotNull();
	int *First();
	int *Next();
	int &operator*() const;
	int *operator->() const;
	ListIterator &operator++(); // Next( )
	ListIterator operator++(int);
	bool operator!=(const ListIterator) const;
	bool operator==(const ListIterator) const;
	int *GetCurrent();

private:
	Node *current;	  // pointer to nodes
	const List &list; // existing list
};

class CircularList : public List
{
public:
	CircularList();
	~CircularList();
	void Add(int &);
	void Delete(int &);
	void Show();
	void DeleteNum(int &x);
};

// #include "listiterator.h"

Node::Node(int element = 0, Node *next = 0)
{
	num = element;
	link = next;
}

Node::~Node()
{
}

List::List()
{
	first = 0;
}

List::~List()
{
}

void List::Add(int &x)
{
	if (!first)
	{
		first = new Node(x);
		first->link = 0;
	}
	else
	{
		Node *n = new Node(x);
		n->link = first;
		first = n;
	}
}

void List::Delete(int &x)
{
	if (first == NULL)
		cout << " List is empty" << endl;
	// body of delete
	return;
}

void List::Show()
{
	Node *current;
	current = first;
	if (first)
		while (current)
		{
			cout << current->num << " ";
			current = current->link;
		}
	else
		cout << "List is empty" << endl;
}

/*
ListIterator::ListIterator(Node *ll){
}
*/

ListIterator::ListIterator(const List &lst) : list(lst), current(lst.first)
{
	cout << "List Iterator is constructed" << endl;
}

bool ListIterator::NotNull()
{
	if (list.first == 0)
		return false;
}

bool ListIterator::NextNotNull()
{
	if (current->link != 0)
		return true;
	else
		return false;
}

int *ListIterator::First()
{
	return &list.first->num;
}

int *ListIterator::Next()
{
	current = current->link;
	cout << "current = " << current->num;
	return &current->num;
}

int *ListIterator::GetCurrent()
{
	return &current->num;
}

ListIterator::~ListIterator()
{
}

int &ListIterator::operator*() const
{
	return current->num;
}

int *ListIterator::operator->() const
{
	return &current->num;
}

ListIterator &ListIterator::operator++()
{
	current = current->link;
	return *this;
}

ListIterator ListIterator::operator++(int)
{
	ListIterator old = *this;
	current = current->link;
	return old;
}

bool ListIterator::operator!=(const ListIterator right) const
{
	return current != right.current;
}

bool ListIterator::operator==(const ListIterator right) const
{
	return current == right.current;
}

CircularList::CircularList() : List() {}

CircularList::~CircularList() {}

void CircularList::Add(int &x)
{
	Node *newNode = new Node(x);
	if (first)
	{ // nonempty list
		newNode->link = first->link;
		first->link = newNode;
	}
	else
	{ // empty list
		first = newNode;
		newNode->link = newNode;
	}
}

void CircularList::Delete(int &x)
{
	Node *newNode = new Node(x);
	if (first)
	{ // nonempty list
		Node *Temp = first->link;
		first->link = first->link->link;
		delete Temp;
	}
	else
	{ // empty list
		cout << "empty list" << endl;
	}
}

void CircularList::DeleteNum(int &x)
{
	// Node *newNode = new Node(x);
	// first, medium, last üũ
	if (first)
	{ // nonempty list
		Node *CurrentNode = first;
		Node *PreNode = first;
		bool find = false;

		// while (CurrentNode->link != first || CurrentNode == first)
		while (CurrentNode->link != first)
		{
			if (CurrentNode->num == x)
			{
				find = true;

				if (CurrentNode == first) // first delete case
				{
					Node *Temp = CurrentNode;

					while (CurrentNode->link != first)
					{
						CurrentNode = CurrentNode->link;
					}
					first = first->link;
					delete Temp;

					CurrentNode->link = first;
					break;
				}
				else if (CurrentNode->link != first) // medium delete case
				{
					PreNode->link = CurrentNode->link;
					delete CurrentNode;
					break;
				}
			}

			PreNode = CurrentNode;
			CurrentNode = CurrentNode->link;
		} // while end

		if (find == false)
		{
			if (CurrentNode->num == x) // last Delte Case
			{
				PreNode->link = first;
				delete CurrentNode;
				find = true;
			}
		}
		if (find == false)
			cout << "can't find " << x << endl;
	}
	else
	{ // empty list
		cout << "empty list" << endl;
	}
}

void CircularList::Show()
{
	Node *np;
	np = first;
	if (np->num > 0)
		do
		{
			cout << np->num << " ";
			np = np->link;
		} while (np != first);
	else
		cout << "List is empty" << endl;
}

/* listIteratorTest.cpp - List Iterator를 사용
- Add( )에서 학생들이 실습할 코드로
  1) add된 데이터를 last node로 추가하는 코드 작성,
  2) 입력된 값이 sort되도록 add( )를 수정
  3) sum(xi * xi+5)를 구하는 코드 작성
*/
// #include "listiterator.h"
// int printAll(const List& l);//list iterator를 사용하여 작성하는 연습
// int sumProductFifthElement(const List& l);//list iterator를 사용하여 작성하는 연습
int sum(const List &l)
{
	ListIterator li(l);
	if (!li.NotNull())
		return 0;
	int retvalue = *li.First();
	while (li.NextNotNull() == true)
	{
		++li; // current를 증가시킴
		// retvalue = retvalue + *li.Next( );
		retvalue = retvalue + *li.GetCurrent(); //현재 current가 가르키는 node의 값을 가져옴
	}
	return retvalue;
}

double avg(const List &l)
{
	ListIterator li(l);
	if (!li.NotNull())
		return 0;
	int retvalue = *li.First();
	int count = 1;
	while (li.NextNotNull() == true)
	{
		++li;
		count++;
		// retvalue = retvalue + *li.Next( );
		retvalue = retvalue + *li.GetCurrent();
	}

	double result = (double)retvalue / count;

	return result;
}

int min(const List &l)
{
	ListIterator li(l);
	if (!li.NotNull())
		return -1;
	int minValue = *li.First();

	while (li.NextNotNull() == true)
	{
		++li;
		if (minValue > *li.GetCurrent())
		{
			minValue = *li.GetCurrent();
		}
	}
	return minValue;
}

int max(const List &l)
{
	ListIterator li(l);
	if (!li.NotNull())
		return -1;
	int maxValue = *li.First();

	while (li.NextNotNull() == true)
	{
		++li;
		if (maxValue < *li.GetCurrent())
		{
			maxValue = *li.GetCurrent();
		}
	}
	return maxValue;
}

void ListTesting()
{
	int ch;
	List st;
	while (1)
	{
		cout << "\n1.Add  2.Delete  3.Show  4. sum 5.avg 6.min 7.max 8.exit\nEnter ur choice: ";
		cin >> ch;
		switch (ch)
		{
		case 1:
			cout << "enter the element ";
			cin >> ch;
			st.Add(ch);
			break;
		case 2:
			st.Delete(ch);
			break;
		case 3:
			st.Show();
			break;
		case 4:
			cout << "sum( ) = " << sum(st) << endl;
			break;
		case 5:
			cout << "avg( ) = " << avg(st) << endl;
			break;
		case 6:
			cout << "min( ) = " << min(st) << endl;
			break;
		case 7:
			cout << "max( ) = " << max(st) << endl;
			break;
		case 8:
			return;
		}
	}

	return;
}

void main()
{
	cout << endl
		 << "List Testing begins: " << endl;
	CircularList st[4];
	while (1)
	{
		cout << "\n1.Make_List1  2.Make_List 3.Merge  4.Print_List  5.exit\nEnter ur choice: ";
		cin >> ch;
		switch (ch)
		{
		case 1:
			Make_List(st[0]);
			break;
		case 2:
			Make_List(st[1]);
			break;
		case 3:
			st[2] = st[0].Merge(st[1]);
			break;
		case 4:
			Print_List(st[0]);
			Print_List(st[1]);
			Print_List(st[3]);
			break;
		case 5:
			return;
		}
	}
	system("Pause");
}