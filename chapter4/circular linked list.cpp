#include <iostream>
#include <cstring>
#include "time.h"

using namespace std;

//소스 코드4.2: Circular Linked List - template 버젼으로 전환하기 OK
// head node를 갖고 circular list로서   class List{ private: Node *last;}로 구현하기 OK
//난수가 입력되면 정렬된 list를 만든다. OK
//두개의 list를 merge하여 정렬된 list를 만든다. OK
// 출력은 iterator를 사용한다. OK
// class Node, List, ListIterator OK

template <class T>
class List;

template <class T>
class CircularList;

template <class T>
class ListIterator;

template <class T>
class Node
{
    friend class List<T>;
    friend class CircularList<T>;
    friend class ListIterator<T>;

private:
    T data;        // 값
    Node<T> *link; // 다음 노드

public:
    Node(T, Node<T> *);
    ~Node();
};

template <class T>
class List
{
    friend ListIterator<T>;
    friend CircularList<T>;

public:
    List();
    ~List();
    List(List<T> *);
    List(CircularList<T> &);
    List(int);
    virtual void Add(T &);
    virtual bool Delete(T &);
    virtual void show();         // show elements by calling iterator
    virtual void sort(T *, int); // by bubble
    List<T> &mergeSort(List<T> *);
    // List<T> *mergeSort(CircularList<T> *);
    Node<T> *getLast();
    void setLast(Node<T> *);
    T *getDataSet();
    int getSize();

private:
    Node<T> *last;
};

template <class T>
class ListIterator
{
public:
    ListIterator(List<T> &target);
    ~ListIterator();
    bool isListNull();
    bool isNextItemNull();
    void printElements();
    // int *getFirst();
    // int *next();
private:
    Node<T> *current;    // current node pointer
    const List<T> &list; // list from parameter 리스트로 받음
};

template <class T>
class CircularList : public List<T>
{
public:
    CircularList();
    ~CircularList();
    CircularList(List<T> &);
    CircularList(List<T> *);
    void Add(T); //그냥 메인에서 넣을라고
    bool Delete(T &);
    void show();
    void sort(T *, int);                           // 아 그냥 super해서 쓰고싶다
    CircularList<T> &mergeSort(CircularList<T> *); // 아 그냥 업캐스팅 하고싶다
};

template <class T>
Node<T>::Node(T value, Node<T> *next)
{
    data = value;
    link = next;
}

template <class T>
Node<T>::~Node()
{
    // cout << "node with data of " << data << " is deconstructed" << endl;
    delete link;
}

template <class T>
List<T>::List()
{
    last = new Node<T>(0, 0); // tail 노드의 값은 0

    int initLength = 0;
    cout << "input number of list length : ";
    cin >> initLength;

    srand(time(NULL));

    T *initData = new T[initLength];

    for (int i = 0; i < initLength; i++) //입력 받은 수만큼
    {
        initData[i] = (int)rand() % 9 + 1; //난수 생성
        int currentNum = initData[i];
    }

    sort(initData, initLength);

    Node<T> *current = new Node<T>(initData[0], 0);
    last->link = current; // last는 첫번째를 가르키고

    for (int i = 1; i < initLength; i++)
    {
        current->link = new Node<T>(initData[i], 0); // 첫번째는 다음을
        current = current->link;
    }

    current->link = last; // 마지막은 라스트를 가르킨다
    last = current;       // 마지막 원소
}

template <class T>
List<T>::List(List<T> *copySource) // 복사 생성자
{
    last = copySource->last;
}

template <class T>
List<T>::List(CircularList<T> &source) // 업캐스팅 대용
{
    last = source->last;
    // list = source;
}

template <class T>
List<T>::List(int mode) // 그냥 아무것도 안하는 생성자 만들려고했는데 안됨
{
    last = new Node<T>(0, 0);
}

template <class T>
List<T>::~List() // 소멸자
{
}

template <class T>
Node<T> *List<T>::getLast() // 자식 클래스에서 쓸려고 만듬
{
    return last;
}

template <class T>
void List<T>::setLast(Node<T> *toThis) // 자식 클래스에서 쓸려고 만듬
{
    // Node<T> temp = toThis;
    // last = &toThis;
    last = toThis;
}

template <class T>
void List<T>::show() // iteraotor 사용해서 출력
{
    List<T> copy(this);
    ListIterator<T> *iter = new ListIterator<T>(copy);
    iter->printElements();
}

template <class T>
void List<T>::Add(T &item) // 마지막에 추가
{
    Node<T> *temp = new Node<T>(item, 0);
    if (last->data == 0) // last의 link가 first
    {
        last->link = temp;
        temp->link = last;
        last = temp;
    }
    else
    {
        temp->link = last->link;
        last->link = temp;
        last = temp;
    }
}

template <class T>
bool List<T>::Delete(T &targetData) // 원하는 원소 삭제
{
    Node<T> *current = last;
    Node<T> *follow = current->link; // 0
    current = follow->link;          // first

    while (current->data != 0)
    {
        if (current->data == targetData)
        {
            Node<T> *target = current;
            follow->link = current->link;
            // delete target;
            return true;
        }
        follow = current;
        current = current->link;
    }
    return false;
}

template <class T>
void List<T>::sort(T *array, int arraySize) // 정렬
{
    T *initData = array;
    int initLength = arraySize;

    for (int i = 0; i < initLength; i++) // 난수 배열 정렬
    {
        for (int j = 0; j < initLength - i - 1; j++)
        {
            if (initData[j] > initData[j + 1]) // 내림차순
            {
                T temp = initData[j];
                initData[j] = initData[j + 1];
                initData[j + 1] = temp;
            }
        }
    }
}

template <class T>
int List<T>::getSize() // 링크의 길이 반환
{
    int size = 0;
    Node<T> *current = last->link->link; // first

    while (current->data != 0)
    {
        size++;
        current = current->link;
    }
    // ??
    return size;
}

template <class T>
T *List<T>::getDataSet() // 현재 링크에서 값 추출해서 만든 배열 반환
{
    int size = 0;

    Node<T> *current = last->link->link; // first

    while (current->data != 0)
    {
        size++;
        current = current->link;
    }

    T *dataSet = new T[size];

    current = current->link; // first
    size = 0;

    while (current->data != 0)
    {
        dataSet[size++] = current->data;
        current = current->link;
    }

    return dataSet;
}

template <class T>
List<T> &List<T>::mergeSort(List<T> *operand)
{
    T *data1 = this->getDataSet();
    T *data2 = operand->getDataSet();

    int size1 = this->getSize();
    int size2 = operand->getSize();

    int destSize = size1 + size2;
    this->sort(data1, size1);
    operand->sort(data2, size2);

    T *destination = new T[destSize];
    int indexI = 0;
    int indexJ = 0;
    int indexK = 0;

    while (indexI != size1 && indexJ != size2)
    {
        if (data1[indexI] < data2[indexJ])
        {
            destination[indexK++] = data1[indexI++];
        }
        else if (data1[indexI] > data2[indexJ])
        {
            destination[indexK++] = data2[indexJ++];
        }
        else if (data1[indexI] == data2[indexJ])
        {
            destination[indexK++] = data1[indexI++];
            destination[indexK++] = data2[indexJ++];
        }
    }

    if (indexI == size1)
    {
        while (indexJ != size2)
        {
            destination[indexK++] = data2[indexJ++];
        }
    }
    else if (indexJ == size2)
    {
        while (indexI != size1)
        {
            destination[indexK++] = data1[indexI++];
        }
    }

    delete[] data1;
    delete[] data2;

    List<T> *mergedList = new List<T>(1); // last 노드 생성만하는 생성자

    Node<T> *current = new Node<T>(destination[0], 0);
    mergedList->last->link = current;
    current->link = mergedList->last;

    for (int i = 1; i < destSize; i++)
    {
        current->link = new Node<T>(destination[i], 0); // 첫번째는 다음을
        current = current->link;
    }

    current->link = mergedList->last; // 마지막은 라스트를 가르킨다
    mergedList->last = current;

    delete[] destination;

    return *mergedList;
}

template <class T>
ListIterator<T>::ListIterator(List<T> &target) : list(target)
{
    current = list.last;
}

template <class T>
bool ListIterator<T>::isListNull()
{
    return list.last == 0;
}

template <class T>
bool ListIterator<T>::isNextItemNull()
{
    return current->link->data == 0;
}

template <class T>
void ListIterator<T>::printElements()
{
    cout << "showing by iterator: ";
    current = current->link->link; // 지금 current는 last이기 때문에

    while (!current->data == 0)
    {
        cout << current->data << " ";
        current = current->link;
    }

    cout << endl;
}

template <class T>
CircularList<T>::CircularList()
{
}

template <class T>
CircularList<T>::~CircularList()
{
}

template <class T>
CircularList<T>::CircularList(List<T> &source) // 다운캐스팅 생성자
{
    this->setLast(source.getLast());
}

template <class T>
CircularList<T>::CircularList(List<T> *source) // 다운캐스팅 생성자
{
    this->setLast(source->getLast());
}

template <class T>
void CircularList<T>::show() // iterator해서 만들려다가 못함
{
    // List<T> source(this->last);
    // ListIterator<T> iter(source);
    // iter.printElements();

    Node<T> *current = this->getLast(); // last
    current = current->link->link;      // first

    cout << "remaining: ";

    while (!current->data == 0)
    {
        cout << current->data << " ";
        current = current->link;
    }

    cout << endl;
}

template <class T>
void CircularList<T>::Add(T value) // 마지막에 추가
{
    Node<T> *temp = new Node<T>(value, 0);
    Node<T> *last = this->getLast();
    if (last->data == 0) // last의 link가 first
    {
        last->link = temp;
        temp->link = last;
        this->setLast(temp);
    }
    else
    {
        temp->link = last->link;
        last->link = temp;
        this->setLast(temp);
    }
}

template <class T>
bool CircularList<T>::Delete(T &targetData) // 원하는 원소 삭제
{
    Node<T> *last = this->getLast();

    if (last->data == 0)
    {
        cout << "no elements to delete" << endl;
        return false;
    }

    Node<T> *current = last->link->link; // first
    Node<T> *follow = last->link;        // 0

    while (current->data != 0)
    {
        if (current->data == targetData)
        {
            // Node<T> *found = current;
            follow->link = current->link;
            // delete found;
            return true;
        }
        follow = current;
        current = current->link;
    }
    return false;
}

template <class T>
void CircularList<T>::sort(T *virtualParam, int tempStoreLength) // 정렬이긴한데 overide하고싶으니 억지로 매개변수 맞춤
{
    int size = 0;
    Node<T> *iter = this->getLast()->link->link;
    T *tempStore = new T[tempStoreLength]; // 100이상 안넣겠지?
    //반복 좀 적게 돌리고 싶은데

    while (iter->data != 0)
    {
        tempStore[size] = iter->data;
        size++;
        iter = iter->link;
    }

    T *dataChunk = new T[size];
    memcpy(dataChunk, tempStore, sizeof(T) * size);
    // delete[] tempStore;

    List<T>::sort(dataChunk, size);

    iter = iter->link; // 다시 first로
    size = 0;

    while (iter->data != 0)
    {
        iter->data = dataChunk[size];
        size++;
        iter = iter->link;
    }
}

template <class T>
CircularList<T> &CircularList<T>::mergeSort(CircularList<T> *operand)
{
    List<T> upcastSelf = List<T>(this);       // 금단의 업캐스팅
    List<T> upcastOperand = List<T>(operand); // 금단의 업캐스팅

    List<T> dest = upcastSelf.mergeSort(&upcastOperand);
    // dest.show();

    CircularList<T> *mergedList = new CircularList<T>(dest); //와 이게 기본생성자 호출이구나
    mergedList->show();

    return *mergedList;
}

int main()
{
    int input;
    CircularList<int> circularList;
    cout << "circular linked list ";
    circularList.show();
    cout << "66, 55, 88, 77 are added in order" << endl;
    circularList.Add(66);
    circularList.Add(55);
    circularList.Add(88);
    circularList.Add(77);
    circularList.show();
    cout << "enter number to delete from a list right above" << endl;
    cin >> input;
    circularList.Delete(input);
    cout << "after delete ";
    circularList.show();
    cout << "[Another list]";
    CircularList<int> circularList2;
    circularList2.show();

    circularList.sort(0, 100);
    cout << "[After sort] " << endl;
    cout << "list1: ";
    circularList.show();
    cout << "list2: ";
    circularList2.show();
    cout << endl;
    cout << "default constructor is called here getting length, but don't worry. Just give random number" << endl;
    CircularList<int> dest = circularList.mergeSort(&circularList2);
    cout << "merge list ";
    dest.show();

    cout << "========single list now========" << endl;

    List<int> iteratorTest;
    cout << "add to singly linked list: ";
    cin >> input;
    cout << endl;
    iteratorTest.Add(input);
    iteratorTest.show();
    cout << "what to delete in singly linked list?: ";
    cin >> input;
    iteratorTest.Delete(input);
    cout << "after delete ";
    iteratorTest.show();
    cout << "[another list]";
    List<int> mergeTest;
    mergeTest.show();
    cout << "[Merging Now]" << endl;
    List<int> dest2 = iteratorTest.mergeSort(&mergeTest);
    cout << "[After merge] ";
    dest2.show();
    return 0;
}