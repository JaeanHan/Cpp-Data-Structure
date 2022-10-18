#include <iostream>
#include "time.h"

using namespace std;

template <class T>
class CircularLinkedList;

template <class T>
class Node
{
    friend CircularLinkedList<T>;

public:
    Node();
    ~Node();
    Node(T &);

private:
    T data;
    Node<T> *link;
};

template <class T>
class CircularLinkedList
{
public:
    CircularLinkedList();
    ~CircularLinkedList();
    CircularLinkedList(int); // 길이 입력 받아서 난수 생성 모드
    void getData();          // 난수 생성
    void insert(T);          //그냥 insert
    void insertSorted(T);    // insert 정렬
    void deleteTarget(T &);
    void show();
    CircularLinkedList<T> &mergeSort(CircularLinkedList<T> *);

private:
    Node<T> *last;
};

template <class T>
Node<T>::Node() // 기본 생성자
{
    data = 0;
    link = 0;
}

template <class T>
Node<T>::Node(T &value) // data 생성자
{
    data = value;
    link = 0;
}

template <class T>
CircularLinkedList<T>::CircularLinkedList() // 헤드노드x
{
    last = 0;
}

template <class T>
CircularLinkedList<T>::CircularLinkedList(int mode)
{
    if (mode == 1) // 랜덤 난수 생성
    {
    }
}

template <class T>
CircularLinkedList<T>::~CircularLinkedList() {}

template <class T>
void CircularLinkedList<T>::getData()
{
    int initSize = 0;

    cout << "input random number as list length: ";
    cin >> initSize;
    srand(time(NULL));

    for (int i = 0; i < initSize; i++)
    {
        // this->insertSorted(rand() % 10);
        this->insertSorted(rand() % 9 + 1);
    }
    cout << "[length: " << initSize << "] ";
    this->show();
}

template <class T>
void CircularLinkedList<T>::insert(T value)
{
    Node<T> *insertItem = new Node<T>(value);
    if (!last)
    {
        insertItem->link = insertItem;
        last = insertItem;
    }
    else
    {
        insertItem->link = last->link;
        last->link = insertItem;
        last = insertItem;
    }
}

template <class T>
void CircularLinkedList<T>::insertSorted(T insertValue)
{
    Node<T> *insertItem = new Node<T>(insertValue);

    if (!last) // 원소가 없다면
    {
        insertItem->link = insertItem;
        last = insertItem;
        return;
    }

    Node<T> *current = last->link; // first element
    Node<T> *follow = last;        // last element

    if (last->link == last) // 원소가 하나 뿐이라면
    {
        if (current->data >= insertValue) // first element data
        {
            follow->link = insertItem;
            insertItem->link = current;
        }
        else // current->data < insertValue
        {
            current->link = insertItem;
            insertItem->link = follow;
            last = insertItem;
        }

        follow = current;
        current = current->link;
    }
    else // 원소 두개 이상이라면
    {
        // current = first
        //  follow = last
        if (current->data >= insertValue) // insertValue가 가장 작다면
        {
            follow->link = insertItem;
            insertItem->link = current;
            return;
        }

        while (current != last)
        {
            if (current->data == insertValue) // 중복값이면 바로 종료
            {
                insertItem->link = current->link;
                current->link = insertItem;
                return;
            }

            else if (current->data < insertValue && current->link->data > insertValue) // 중간자리
            {
                insertItem->link = current->link;
                current->link = insertItem;
                return;
            }

            follow = current;
            current = current->link;
        }

        // insertValue가 가장 크다면, 마지막 원소와 같다면
        insertItem->link = current->link;
        current->link = insertItem;
        last = insertItem;
    }
}

template <class T>
void CircularLinkedList<T>::show()
{
    if (!last)
    {
        cout << "list has no elements to dispay!" << endl;
        return;
    }
    Node<T> *current = last->link;
    int size = 0;

    cout << "remaining: ";

    while (current != last)
    {
        cout << current->data << " ";
        current = current->link;
        size++;
    }
    cout << last->data << endl;
    cout << "[size checked by iterator: " << size + 1 << "]\n"
         << endl;
}

template <class T>
CircularLinkedList<T> &CircularLinkedList<T>::mergeSort(CircularLinkedList<T> *operand)
{
    Node<T> *current1 = last->link;          // this first
    Node<T> *current2 = operand->last->link; // operand first
    CircularLinkedList<T> *result = new CircularLinkedList<int>();

    while (current1 != last && current2 != operand->last)
    {
        // cout << "@@" << endl;
        if (current1->data < current2->data)
        {
            // cout << "?? " << current1->data << endl;
            result->insert(current1->data);
            current1 = current1->link;
        }
        else if (current1->data > current2->data)
        {
            // cout << "!! " << current2->data << endl;
            result->insert(current2->data);
            current2 = current2->link;
        }
        else // current1 == current2
        {
            result->insert(current1->data);
            result->insert(current2->data);
            current1 = current1->link;
            current2 = current2->link;
        }
    }
    //함수화 가능
    if (current1 == this->last)
    {
        while (current2 != operand->last)
        {
            result->insert(current2->data);
            current2 = current2->link;
        }
        result->insert(current2->data); // last

        result->insertSorted(current1->data); // 여기서 와일문 또 돌려야돼?
    }
    else if (current2 == operand->last)
    {
        while (current1 != this->last)
        {
            result->insert(current1->data);
            current1 = current1->link;
        }
        result->insert(current1->data);
        result->insertSorted(current2->data);
    }

    return *result;
}

int main()
{
    CircularLinkedList<int> circularList;
    circularList.getData();

    CircularLinkedList<int> circularList2;
    circularList2.getData();

    CircularLinkedList<int> mergedList = circularList.mergeSort(&circularList2);
    mergedList.show();

    return 0;
}