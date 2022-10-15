#include <iostream>
#include "time.h"

using namespace std;

class Chain;

class ChainNode
{
    friend class Chain;

public:
    ChainNode();
    ChainNode(int value);

private:
    int data;        // 값
    ChainNode *link; // 다음 노드
};

ChainNode::ChainNode()
{
}

ChainNode::ChainNode(int value)
{
    data = value;
}

class Chain // 노드 묶음
{
public:
    Chain();
    int Delete();     // first가 가르키고 있는 노드를 삭제하고 data를 반환
    bool Delete(int); // 전달된 element를 삭제하고 삭제했으면 true 못했으면 false
    void Insert(int);
    void InsertSorted(int); // insert후 바로 list sort
    void tempIterator();    // 리스트 원소 출력
    void sort();

private:
    ChainNode *first;
};

Chain::Chain()
{
    first = new ChainNode(); // 헤드노드 역할
    first->data = -1;
    first->link = nullptr;
}

void Chain::Insert(int value) // 앞쪽에 추가하는 방법
{
    ChainNode *newChainNode = new ChainNode(value); // setData 기능만 추가
    newChainNode->link = first;                     // 새로운 노드의 link를 first로 설정
    first = newChainNode;                           // 새로운 노드를 first로 설정
}

int Chain::Delete() // first가 가르키는 노드 삭제
{
    if (first->data == -1)
    {
        cout << "no elements found" << endl;
        return;
    }

    ChainNode *next = first->link;
    int retValue = first->data;

    ChainNode *temp = first;
    first = next;
    delete temp;

    return retValue;
}

bool Chain::Delete(int targetData)
{
    ChainNode *current, *next;
    if (first->data != -1)
    {
        current = first;
        if (current->data == targetData) // 첫번째 노드가 해당 값을 가질 경우
        {
            ChainNode *temp; // 사실 그냥 Delete() 호출해도됨
            temp = first;
            first = temp->link;
            delete temp;
            return true;
        }

        while (current->data != -1) // 헤드노드가 아니라면
        {
            ChainNode *target = current->link;
            next = target->link;            // 다음노드 미리 설정
            if (target->data == targetData) // target이 맞다면
            {
                ChainNode *temp; // temp 생성
                temp = target;   // delete 할 노드 temp로 이전

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

void Chain::sort()
{
    ChainNode *current = first;
    ChainNode *next;
}

void Chain::InsertSorted(int input)
{
    ChainNode *current = first;
    ChainNode *temp = new ChainNode(input);

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
            ChainNode *headNode = current->link;
            current->link = temp; // temp 데이터가 크니까 뒤로 가야 한다
            temp->link = headNode;
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
    ChainNode *next = current->link;

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

void Chain::tempIterator()
{
    ChainNode *current = first;
    cout << "remainings: ";

    while (current->data != -1) // 헤드노드가 아니라면
    {
        cout << current->data << " ";
        // ChainNode *next = current->link;
        current = current->link;
    }
    cout << endl;
}

int main()
{
    Chain chain;
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

    Chain chain2;
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