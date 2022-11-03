#include <iostream>
#include <string>
#include "time.h"

using namespace std;

class Product
{
public:
    Product();
    Product(string, int);
    ~Product();
    string getProductName();
    int getProductPrice();

    friend bool operator==(Product &, Product &);
    friend bool operator==(Product &, Product &);
    friend bool operator>(Product &, Product &);
    friend ostream &operator<<(ostream &, Product &);

private:
    string Name;
    int price;
};

Product::Product() {}

Product::~Product() {}

Product::Product(string name, int price) : Name(name)
{
    // this->Name = name;
    this->price = price;
}

string Product::getProductName()
{
    return Name;
}

int Product::getProductPrice()
{
    return price;
}

bool operator==(Product &op1, Product &op2)
{
    if (op1.getProductName() == op2.getProductName() && op1.getProductPrice() == op2.getProductPrice())
        return true;
    return false;
}

bool operator>(Product &op1, Product &op2) // 일단 price만이 순서에 영향을 주니까
{
    if (op1.getProductPrice() > op2.getProductPrice())
        return true;
    return false;
}

ostream &operator<<(ostream &os, Product &target)
{
    os << "product name of " << target.getProductName() << " / " << target.getProductPrice();
    return os;
}

template <class T>
class LinkedList;

template <class T>
class LinkedListIterator;

template <class T>
class DoublyNode
{
    friend class LinkedList<T>;
    friend class LinkedListIterator<T>;

public:
    DoublyNode();
    ~DoublyNode();
    DoublyNode(T);

private:
    DoublyNode<T> *llink;
    DoublyNode<T> *rlink;
    T data;
};

template <class T>
DoublyNode<T>::DoublyNode() {}

template <class T>
DoublyNode<T>::~DoublyNode() {}

template <class T>
DoublyNode<T>::DoublyNode(T data)
{
    this->data = data;
}

template <class T>
class LinkedList
{
    friend class LinkedListIterator<T>;

public:
    LinkedList();
    ~LinkedList();
    void Insert(T); // add sorted
    void Attach(T); // add on last
    void Delete(T);
    // void Delete(DoublyNode<T> *);
    void Merge(LinkedList<T> &); // inplace
    void testPrint();

    template <class U>
    friend ostream &operator<<(ostream &, LinkedList<U> &);
    template <class U>
    friend LinkedList<U> &operator+(LinkedList<U> &, LinkedList<U> &);

private:
    DoublyNode<T> *first;
    DoublyNode<T> *last;
    int size;
};

template <class T>
LinkedList<T>::LinkedList()
{
    T headData("headNode", -1);
    DoublyNode<T> *headNode = new DoublyNode<T>(headData);

    first = headNode;
    last = headNode;

    first->rlink = last;
    first->rlink = last;

    last->rlink = first;
    last->llink = first;

    size = 0;
}

template <class T>
LinkedList<T>::~LinkedList() {}

template <class T>
void LinkedList<T>::Insert(T data)
{
    // 가격 순으로 오름차순 정렬
    // 이름순으로 정렬?
    DoublyNode<T> *insertNode = new DoublyNode<T>(data);
    DoublyNode<T> *current = first;

    // cout << "first element: " << current->data.getProductPrice() << endl;

    int insertValue = insertNode->data.getProductPrice(); // 이름순이면 getProductName()

    while (true)
    {
        if (insertValue < current->rlink->data.getProductPrice())
        {
            insertNode->llink = current;
            insertNode->rlink = current->rlink;
            current->rlink->llink = insertNode;
            current->rlink = insertNode;
            break;
        }
        else if (current->rlink != first)
            current = current->rlink;
        else
        {
            insertNode->llink = current;
            insertNode->rlink = current->rlink;
            current->rlink->llink = insertNode;
            current->rlink = insertNode;
            last = insertNode;
            break;
        }
    }
    size++;
}

template <class T>
void LinkedList<T>::Attach(T data) // Insert와 달리 그저 마지막에 추가
{
    DoublyNode<T> *attachItem = new DoublyNode<T>(data);
    attachItem->rlink = last->rlink;
    last->rlink = attachItem;
    attachItem->llink = last;
    last = attachItem;
    size++;
}

template <class T>
void LinkedList<T>::Delete(T target)
{
    DoublyNode<T> *current = first->rlink;
    while (current != first)
    {
        if (current->data == target)
        {
            DoublyNode<T> *found = current;

            current->llink->rlink = current->rlink;
            current->rlink->llink = current->llink;
            delete found;
            size--;
            return;
        }
        current = current->rlink;
    }
    cout << target << " is not found" << endl;
}

// template <class T>
// void LinkedList<T>::Delete(DoublyNode<T> *target)
// {
//     // 노드를 매개변수로 받는데 노드의 주소값으로 비교
// }

template <class T>
void LinkedList<T>::Merge(LinkedList<T> &operand)
{
    //오퍼랜드 돌아가면서 적절한 자리에 추가 inplace
    DoublyNode<T> *curr1 = first->rlink;
    DoublyNode<T> *curr2 = operand.first->rlink;
    DoublyNode<T> *temp;

    while (curr2 != operand.first)
    {
        if (curr1->data > curr2->data)
        {
            temp = curr2->rlink;

            curr2->llink = curr1->rlink;
            curr1->llink->rlink = curr2;
            curr2->rlink = curr1;
            curr1->llink = curr2;

            curr2 = temp;
        }
        else if (curr1 != first)
            curr1 = curr1->rlink;
        else
        {
            temp = curr2->rlink;

            curr2->llink = curr1->llink;
            curr1->llink->rlink = curr2;
            curr2->rlink = curr1;
            curr1->llink = curr2;

            curr2 = temp;
        }
    }
}

template <class T>
void LinkedList<T>::testPrint() // for test only
{
    DoublyNode<T> *current = first->rlink;
    cout << "for test only: ";
    while (current != first)
    {
        cout << current->data.getProductPrice() << " ";
        current = current->rlink;
    }
    cout << endl;
    cout << "size: " << size << endl;
}

template <class T>
ostream &operator<<(ostream &os, LinkedList<T> &target)
{
    LinkedListIterator<T> temp(target);

    os << "iterator shows: ";
    while (temp.isNextNotNull())
    {
        T *target = temp.Next();
        // os << "[" + target->getProductName() << " : " << target->getProductPrice() << "] ";
        os << target->getProductPrice() << " ";
    }
    os << endl;
    return os;
}

template <class T>
class LinkedListIterator
{
    friend LinkedList<T>;

public:
    LinkedListIterator(LinkedList<T> &list);
    ~LinkedListIterator();
    bool isNotNull();     // or isFirst()
    bool isNextNotNull(); // isNextFirst()
    T *Next();            // nextNode
    DoublyNode<T> *getCurrent();

private:
    const LinkedList<T> &list; // 이렇게 안받아오면 주소값이 달라짐
    DoublyNode<T> *current;
};

template <class T>
LinkedListIterator<T>::LinkedListIterator(LinkedList<T> &list) : list(list)
{
    current = list.first;
    // cout << "created :" << current->data.getProductPrice() << endl;
}

template <class T>
LinkedListIterator<T>::~LinkedListIterator() {}

template <class T>
bool LinkedListIterator<T>::isNotNull()
{
    if (current == list.first)
        return false;
    return true;
}

template <class T>
bool LinkedListIterator<T>::isNextNotNull() // 딱 마지막 원소까지만 범위에 포함
{
    if (current->rlink == list.first)
        return false;
    return true;
}

template <class T>
T *LinkedListIterator<T>::Next()
{
    current = current->rlink; // 옮기는 것도 주의해서
    if (current != list.first)
        return &current->data;
    else
        return &current->llink->data;
}

template <class T>
DoublyNode<T> *LinkedListIterator<T>::getCurrent()
{
    return current;
}

template <class T>
LinkedList<T> &operator+(LinkedList<T> &op1, LinkedList<T> &op2)
{
    LinkedListIterator<T> src1(op1);
    LinkedListIterator<T> src2(op2);
    LinkedList<T> *dest = new LinkedList<T>();

    T curr1 = *src1.Next(); // 헤드노드를 제외한
    T curr2 = *src2.Next(); // 첫번째 원소부터 시작

    while (src1.isNotNull() && src2.isNotNull())
    {
        if (curr1 > curr2)
        {
            dest->Attach(curr2);
            curr2 = *src2.Next();
        }
        else if (curr2 > curr1)
        {
            dest->Attach(curr1);
            curr1 = *src1.Next();
        }
        else
        {
            dest->Attach(curr1);
            dest->Attach(curr2);
            curr1 = *src1.Next();
            curr2 = *src2.Next();
        }
    }

    if (src1.isNotNull())
    {
        while (src1.isNotNull())
        {
            dest->Attach(*src1.Next());
        }
    }
    else if (src2.isNotNull())
    {
        while (src2.isNotNull())
        {
            dest->Attach(*src2.Next());
        }
    }
    return *dest;
}

template <class T>
void GetData(LinkedList<T> *dest)
{
    srand(time(NULL));
    int length = 0;
    cout << "give number of list init in integer: "; // 이상한거 넣지마라
    cin >> length;

    for (int i = 0; i < length; i++)
    {
        dest->Insert(Product("product " + to_string(i), rand() % 100 * 100));
    }
}

int main()
{
    LinkedList<Product> list1;
    LinkedList<Product> list2;
    LinkedList<Product> list3;
    Product target;
    string deleteName;
    int deleteNum;
    int selectedCommand = 0;
    bool loopFlag = true;

    while (loopFlag)
    {
        cout << endl
             << "enter a number to select command: " << endl
             << "[1] fill up list1\t"
             << "[2] fill up list2\t"
             << "[3] print out list1\t"
             << "[4] print out list2" << endl
             << "[5] delete element on both lists\t"
             << "[6] test merge sort on list3\t"
             << "[7] test inplace merge sort on list1" << endl
             << "[q] quit" << endl;

        cin >> selectedCommand;

        switch (selectedCommand)
        {
        case 1:
            GetData(&list1);
            cout << list1;
            break;
        case 2:
            GetData(&list2);
            cout << list2;
            break;
        case 3:
            cout << list1;
            break;
        case 4:
            cout << list2;
            break;
        case 5:
            cout << "give name of delete target: ";
            cin >> deleteName;
            cout << "give price of delete target: ";
            cin >> deleteNum;
            target = Product(deleteName, deleteNum);
            list1.Delete(target);
            list2.Delete(target);
            break;
        case 6:
            list3 = list1 + list2;
            cout << "list3 " << list3;
            break;
        case 7:
            list1.Merge(list2);
            cout << list1;
            break;
        default:
            if (selectedCommand == 0)
                loopFlag = false;
            else
                cout << "give proper integer" << endl;
            break;
        }
    }
    cout << "bye!" << endl;

    return 0;
}