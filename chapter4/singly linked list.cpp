#include <iostream>
#include "time.h"

using namespace std;

template <class T>
class Chain;

template <class T>
class ChainNode
{
    friend class Chain<T>;

public:
    ChainNode();
    ChainNode(T value);

private:
    T data;          // 값
    ChainNode *link; // 다음 노드
};

template <class T>
ChainNode<T>::ChainNode()
{
}
template <class T>
ChainNode<T>::ChainNode(T value)
{
    data = value;
}

template <class T>
class Chain // 노드 묶음
{
public:
    Chain();
    T Delete();     // first가 가르키고 있는 노드를 삭제하고 data를 반환
    bool Delete(T); // 전달된 element를 삭제하고 삭제했으면 true 못했으면 false
    void Insert(T);
    void InsertSorted(T); // insert후 바로 list sort
    void tempIterator();  // 리스트 원소 출력
    int length();
    void sort();

private:
    ChainNode<T> *first;
};

template <class T>
Chain<T>::Chain()
{
    first = new ChainNode<T>(); // 헤드노드 역할
    first->data = -1;
    first->link = nullptr;
}

template <class T>
void Chain<T>::Insert(T value) // 앞쪽에 추가하는 방법
{
    ChainNode<T> *newChainNode = new ChainNode<T>(value); // setData 기능만 추가
    newChainNode->link = first;                           // 새로운 노드의 link를 first로 설정
    first = newChainNode;                                 // 새로운 노드를 first로 설정
}

template <class T>
T Chain<T>::Delete() // first가 가르키는 노드 삭제
{
    if (first->data == -1)
    {
        cout << "no elements found" << endl;
        return first->data; // -1
    }

    ChainNode<T> *next = first->link;
    int retValue = first->data;

    ChainNode<T> *temp = first;
    first = next;
    delete temp;

    return retValue;
}

template <class T>
bool Chain<T>::Delete(T targetData)
{
    ChainNode<T> *current, *next;
    if (first->data != -1)
    {
        current = first;
        if (current->data == targetData) // 첫번째 노드가 해당 값을 가질 경우
        {
            ChainNode<T> *temp; // 사실 그냥 Delete() 호출해도됨
            temp = first;
            first = temp->link;
            delete temp;
            return true;
        }

        while (current->data != -1) // 헤드노드가 아니라면
        {
            ChainNode<T> *target = current->link;
            next = target->link;            // 다음노드 미리 설정
            if (target->data == targetData) // target이 맞다면
            {
                ChainNode<T> *temp; // temp 생성
                temp = target;      // delete 할 노드 temp로 이전

                current->link = next;
                // currnet의 다음 노드를 다음다음 노드로 설정
                delete temp;
                return true; // 잘 삭제했다
            }
            current = current->link;
        }
    }
    return false; // 삭제 못했다
}

template <class T>
int Chain<T>::length()
{
    int length = 0;
    ChainNode<T> *current = first;
    while (current->data != -1)
    {
        current = current->link;
        length++;
    }
    return length;
}

// list 1 2 3 -1
// length 3

template <class T>
void Chain<T>::sort()
{
    ChainNode *current = first;
    T *tempStore = new T[length()];

    for (int i = 0; i < length(); i++)
    {
        tempStore[i] = current->data;
        current = current->link;
    }
}

template <class T>
void Chain<T>::InsertSorted(T input)
{
    ChainNode<T> *current = first;
    ChainNode<T> *temp = new ChainNode<T>(input);

    if (current->data == -1) // 리스트 원소가 없다면
    {
        temp->link = first;
        first = temp;
        return;
    }

    if (current->link->data == -1) // 리스트 원소가 하나라면
    {
        if (input > current->data)
        {
            ChainNode<T> *headNode = current->link;
            current->link = temp; // temp 데이터가 크니까 뒤로 가야 한다
            temp->link = headNode;

            // temp->link = first
            // first = temp;
        }
        else
        {
            temp->link = current;
            first = temp; // temp 데이터가 작으니까 current가 앞으로 가야 한다
        }
        return;
    }
    // 지금 current는 head temp는 새로운 노드
    if (current->link->link->data == -1) // 리스트 원소가 2개라면
    {
        if (current->data >= input) // 젤 앞의 노드보다 데이터가 같거나 작으면 앞으로
        {
            temp->link = current;
            first = temp;
        }
        else if (current->link->data > input) // 젤 앞의 노드보다는 큰데 다음 노드보다는 작거나 같다면
        {
            temp->link = current->link;
            current->link = temp;
        }
        else // 제일 크다면
        {
            temp->link = current->link->link;
            current->link->link = temp;
        }
        return;
    }
    // current는 first
    ChainNode<T> *next = current->link;

    while (next->data != -1)
    {
        if (current->data < input && next->data > input) // 가운데 자리 찾았다
        {
            temp->link = current->link;
            current->link = temp;
            return;
        }
        current = current->link;
        next = current->link;
    }
    // current는 -1 바로 전
    if (next->data == -1)
    {
        current->link = temp;
        temp->link = next;
    }
    else
    {
        first->link = temp;
        first = temp;
    }
}

template <class T>
void Chain<T>::tempIterator()
{
    ChainNode<T> *current = first;
    cout << "remainings: ";

    while (current->data != -1) // 헤드노드가 아니라면
    {
        cout << current->data << " ";
        current = current->link;
    }
    cout << endl;
}

int main()
{
    Chain<int> chain;
    chain.Insert(0);
    chain.Insert(1);
    chain.Insert(2);
    chain.Insert(3);
    chain.tempIterator();

    cout << chain.Delete() << endl;
    chain.tempIterator();

    chain.Insert(4);
    cout << "delete(2) ok? " << (chain.Delete(2) ? "is ok" : "no") << endl;
    chain.tempIterator();

    chain.InsertSorted(2);
    cout << "insertSorted(2)" << endl;
    chain.tempIterator();

    Chain<int> chain2;
    chain2.InsertSorted(2);
    chain2.InsertSorted(1);
    chain2.InsertSorted(3);
    chain2.InsertSorted(8);
    chain2.InsertSorted(5);
    chain2.InsertSorted(4);
    cout << "chain 2 ";
    chain2.tempIterator();

    return 0;
}