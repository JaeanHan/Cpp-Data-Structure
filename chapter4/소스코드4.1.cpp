//�ҽ� �ڵ�4.1: Linked List

#include <iostream>
using namespace std;

template <class T>
class Chain; // forward declaration
template <class T>
class ChainIterator;

template <class T>
class ChainNode // Chain들 관리하는 메인 클래스
{
	friend class Chain<T>;
	friend class ChainIterator<T>;

public:
	ChainNode(T element = 0); // 체인 노드 생성자

private:
	T data;				// 노드의 값
	ChainNode<T> *link; // 다음 노드의 포인터
};

template <class T>
class Chain // Chain 클래스 정의
{
	friend class ChainIterator<T>;

public:
	Chain() { first = 0; };		// 체인 생성자
	void Delete(void);			// 삭제
	int Length();				// 길이
	void Add(const T &element); // 새로운 노드 추가
	void Invert();
	void Concatenate(Chain<T> b); // 머지

	template <class U>
	friend ostream &operator<<(ostream &, Chain<U>); // 오퍼레이터 오버라이딩
private:
	ChainNode<T> *first; // 헤드 노드
};

template <class T>
class ChainIterator
{
public:
	ChainIterator(const Chain<T> &l) : list(l), current(l.first){};
	T &operator*() const { return current->data; }
	T *operator->() const { return &current->data; }
	// increment
	ChainIterator<T> &operator++();	  // preincrement
	ChainIterator<T> operator++(int); // post increment
	bool NotNull();					  // check the current element in list is non-null
	bool NextNotNull();				  // check the next element in list is non-null

	T *First(); // return a pointer to the first element of list
	T *Next();	// return a pointer to the next element of list
private:
	const Chain<T> &list;  // refers to an existing list
	ChainNode<T> *current; // points to a node in list
};

template <class T>
ChainNode<T>::ChainNode(T element)
{
	data = element;
	link = 0;
}

template <class T>
void Chain<T>::Delete(void) // delete the first element after first
// first 다음의 element 삭제
{
	ChainNode<T> *current, *next; // 2개 생성
	if (first != nullptr)		  // non-empty list
	{
		next = first->link; // 현재 노드의 link(다음노드)를 next에 저장

		ChainNode<T> *temp = first; // 현재 노드를 temp에 저장
		first = next;				// 다음노드를 first에 저장
		delete temp;				// 현재노드 삭제
	}
	else
		cout << "Error - Empty List. not deleted" << endl;
}

template <class T>
void Chain<T>::Add(const T &element) // add a new node after first
{
	ChainNode<T> *newnode = new ChainNode<T>(element); // 새로운 값에 대한 체인노드 생성
	if (!first)										   // first가 비었을 때, insert into empty list
	{
		first = newnode; // 새로운 노드는 first 노드로 설정
		return;
	}
	// insert a new node after first
	newnode->link = first; // 새로운 노드의 next를 이전 노드로 설정
	first = newnode;	   // first에 새로운 노드 저장
}

template <class T>
void Chain<T>::Invert()
{
	ChainNode<T> *p = first, *q = 0; // q trails p
	while (p)
	{
		ChainNode<T> *r = q;
		q = p;		 // r trails q
		p = p->link; // p moves to next node
		q->link = r; // link q to preceding node
	}
	first = q;
}

template <class T>
void Chain<T>::Concatenate(Chain<T> b)
{
	ChainNode<T> *p;
	if (!first)
	{
		first = b.first;
		return;
	}
	if (b.first)
	{
		// No loop body in this for loop. It just moves the pointer 'p' to the end of the A chain.
		for (p = first; p->link; p = p->link)
			;

		p->link = b.first;
	}
}

// pre-increment
template <class T>
ChainIterator<T> &ChainIterator<T>::operator++()
{
	current = current->link;
	return *this;
}

// post increment
template <class T>
ChainIterator<T> ChainIterator<T>::operator++(int)
{
	ChainIterator<T> old = *this;
	current = current->link;
	return old;
}

// check the current element in list is non-null
template <class T>
bool ChainIterator<T>::NotNull()
{
	if (current)
		return 1;
	else
		return 0;
}

// check the next element in list is non-null
template <class T>
bool ChainIterator<T>::NextNotNull()
{
	if (current && current->link)
		return 1;
	else
		return 0;
}

// return a pointer to the first element of list
template <class T>
T *ChainIterator<T>::First()
{
	if (list.first)
		return &list.first->data;
	else
		return 0;
}

// return a pointer to the next element of list
template <class T>
T *ChainIterator<T>::Next()
{
	if (current)
	{
		current = current->link;
		return &current->data;
	}
	else
		return 0;
}

/* chainiterator.cpp - iterator class�� ����ϴ� �ǽ�
 - template ���ÿ� chain.h, chain.cpp => ���ε� ó���� �ȵ� - visual studio2019�� ����
 - template ���ÿ� �ϳ��� file�� ó��
 Chain iterator �ǽ� - TODO�� �ּ�ó�� �Ǿ� �ִ� �κ��� ���� �ǽ��� �� ��.
�ִ�, �ּ�, ��� ���� ���ϴ� �Լ� �ۼ� �ɷ�
*/

/* template function */
template <class T>
int Show(const Chain<T> &l)
{
	ChainIterator<T> li(l); // li is associated with list l
	if (!li.NotNull())
		return 0;			  // empty list, return 0
	T retvalue = *li.First(); // get first element
	cout << retvalue;
	while (li.NextNotNull()) // make sure that next element exists
	{
		retvalue = *li.Next();
		cout << " <- " << retvalue;
	}
	return retvalue;
}

template <class T>
int sum(const Chain<T> &l)
{
	ChainIterator<T> li(l); // li is associated with list l
	if (!li.NotNull())
		return 0;			  // empty list, return 0
	T retvalue = *li.First(); // get first element
	while (li.NextNotNull())  // make sure that next element exists
		retvalue += *li.Next();
	return retvalue;
}

template <class T>
int SumProductFifth(const Chain<T> &l)
{
	// sum(Xi * Xi+5)
	return 0;
}

template <class T>
int Length(const Chain<T> &l)
{
	// list�� ����
	return 0;
}

template <class T>
int Maximum(const Chain<T> &l)
{
	// list���� �ִ밪
	return 0;
}

template <class T>
int Minimum(const Chain<T> &l)
{
	// list���� �ּҰ�
	return 0;
}

template <class T>
int MakeArray(const Chain<T> &l, int[])
{
	// list ���Ҹ� �о� �迭�� ����
	return 0;
}

int main(void)
{
	int select;
	// ChainNode<int> nd;
	Chain<int> a, b;
	ChainIterator<int> cit(a);
	int value;
	do
	{
		cout << endl
			 << "1. Add new value to chain 'A'" << endl
			 << "2. Add new value to chain 'B'"
			 << endl
			 << "3. Print all chains" << endl
			 << "4. Invert chain"
			 << endl
			 << "5. Concatenate A and B" << endl
			 << "6. Delete first node in chain"
			 << endl
			 << "7. Get Sum of the chain" << endl
			 << "8. Get length of the chain"
			 << endl
			 << "9. Get maximum value in chain" << endl
			 << "10. Quit" << endl
			 << endl;
		cout << "Select command (1~10) : ";
		cin >> select;
		switch (select)
		{
			// Case 1 : Add new value to chain 'A'
		case 1:
			cout << "Add a new value: ";
			cin >> value;
			a.Add(value);
			break;

			// Case 2 : Add new value to chain 'B'
		case 2:
			cout << "Add a new value: ";
			cin >> value;
			b.Add(value);
			break;

			// Case 3 : Print all chains
		case 3:
			cout << "Chain A : ";
			Show(a);
			cout << endl;
			cout << "Chain B : ";
			Show(b);
			cout << endl;
			break;

			// Case 4 : Invert chain
		case 4:
			cout << endl
				 << "Which chain will you invert?" << endl
				 << "1. Chain A" << endl
				 << "2. Chain B" << endl
				 << endl
				 << "Select command (1~2) : ";
			cin >> value;
			if (value == 1)
				a.Invert();
			else if (value == 2)
				b.Invert();
			else
				cout << "Invalid value! Return to menu..." << endl;
			break;

			// Case 5 : Concatenate A and B
		case 5:
			cout << endl
				 << "Concatenated chain" << endl;
			a.Concatenate(b);
			Show(a);
			cout << endl;
			break;

			// Case 6 : Delete first node in chain
		case 6:
			cout << endl
				 << "Which chain will you delete?" << endl
				 << "[1] Chain A" << endl
				 << "[2] Chain B" << endl
				 << endl
				 << "Select command (1~2) : ";
			cin >> value;

			if (value == 1)
				a.Delete();
			else if (value == 2)
				b.Delete();
			else
				cout << "Invalid value! Return to menu..." << endl;
			break;

			// Case 7 : Get Sum of the chain
		case 7:
			cout << endl
				 << "Which chain will you sum?" << endl
				 << "1. Chain A" << endl
				 << "2. Chain B" << endl
				 << endl
				 << "Select command (1~2) : ";
			cin >> value;

			if (value == 1)
				sum(a);
			else if (value == 2)
				sum(b);
			else
				cout << "Invalid value! Return to menu..." << endl;
			break;

			// Case 8 : Get length of the chain
		case 8:
			// TODO : Counting the number of nodes by using iterator class
			cout << endl
				 << "Which chain's length do you want?" << endl
				 << "[1] Chain A" << endl
				 << "[2] Chain B" << endl
				 << endl
				 << "Select command (1~2) : ";
			cin >> value;

			if (value == 1)
				cout << Length(a) << endl;
			else if (value == 2)
				cout << Length(b) << endl;
			else
				cout << "Invalid value! Return to menu..." << endl;
			break;
			// Case 9 : Get maximum value in chain
		case 9:
			// TODO : Find node with maximum value by using iterator class
			cout << endl
				 << "Which chain's max-value do you want?" << endl
				 << "[1] Chain A" << endl
				 << "[2] Chain B" << endl
				 << endl
				 << "Select command (1~2) : ";
			cin >> value;

			if (value == 1)
				cout << Maximum(a) << endl;
			else if (value == 2)
				cout << Maximum(b) << endl;
			else
				cout << "Invalid value! Return to menu..." << endl;
			break;

			// Case q : Quit the program
		case 10:
			cout << "Quit the program..." << endl;
			break;
		default:
			cout << "WRONG INPUT" << endl;
		}
	} while (select != 10);
	system("pause");
	return 0;
}
