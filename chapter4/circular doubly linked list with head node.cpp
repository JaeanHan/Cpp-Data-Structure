//소스코드4.7: Doubly Linked List - 교재 소스코드

// 12.Doubly Linked List Implementation with C++
// circular doubly lists with head node 구현- 이코드를 수정하여 사용, 두개의 list를 만들고 list node에 정수 값이 sorted된 상태로 입력되게 하고, 두개의 list를 merge하여 합친 결과도 sorted list되게 한다.
#include <iostream>
#include "time.h"

using namespace std;

template <class T>
class CircularDoublyList;

template <class T>
class CircularDoublyListIterator;

template <class T>
class DoublyListNode
{
    friend class CircularDoublyList<T>;
    friend class CircularDoublyListIterator<T>;

public:
    DoublyListNode();
    DoublyListNode(T data);

private:
    T data;                           // T를 term으로 사용 => coef, exp, variabl로 표현할 수 있을 것
    DoublyListNode<T> *llink, *rlink; // prevNode, nextNode
};

template <class T>
DoublyListNode<T>::DoublyListNode()
{
}

template <class T>
DoublyListNode<T>::DoublyListNode(T data)
{
    this->data = data;
}

template <class T>
class CircularDoublyList
{
    friend class CircularDoublyListIterator<T>;

public:
    CircularDoublyList()
    {
        first = new DoublyListNode<T>;
        last = first;
        first->rlink = last;
        last->llink = first;
        first->data = -1;
    }
    CircularDoublyList(const CircularDoublyList<T> &);
    ~CircularDoublyList();
    int Size() const;
    bool Empty() const;
    void Attach(T);
    void Delete(DoublyListNode<T> *);
    // void Insert(DoublyListNode<T> *, DoublyListNode<T> *);
    void Insert(T);
    void InsertSorted(T);
    void Merge(CircularDoublyList<T> &);
    bool Delete(T);

    template <class U>
    friend ostream &operator<<(ostream &, CircularDoublyList<U> &);

    template <class Q>
    friend CircularDoublyList<Q> &operator+(const CircularDoublyList<Q> &, const CircularDoublyList<Q> &);

private:
    // int n; //number of items
    DoublyListNode<T> *first;
    DoublyListNode<T> *last;
    // static DoublyListNode<T> *av; //이거 어디에 쓰지?
};

template <class T>
class CircularDoublyListIterator
{
public:
    CircularDoublyListIterator(const CircularDoublyList<T> &l) : list(l)
    {
        current = l.first->rlink;
    }
    T *Next();
    T *First();
    bool NotNull();
    bool NextNotNull();

private:
    const CircularDoublyList<T> &list;
    DoublyListNode<T> *current;
};

// template <class T>
// DoublyListNode<T> *CircularDoublyList<T>::av = 0;

template <class T>
void CircularDoublyList<T>::Delete(DoublyListNode<T> *x)
{
    if (x == first)
        cerr << "Deletion of head node not permitted" << endl;
    else
    {
        x->llink->rlink = x->rlink;
        x->rlink->llink = x->llink;
        delete x;
    }
}

// template <class T>
// void CircularDoublyList<T>::Insert(DoublyListNode<T> *p, DoublyListNode<T> *x)
// // insert node p to the right of node x
// {
//     p->llink = x;
//     p->rlink = x->rlink;
//     x->rlink->llink = p;
//     x->rlink = p;
// }

template <class T>
void CircularDoublyList<T>::Insert(T x)
{
    DoublyListNode<T> *p;
    DoublyListNode<T> *temp = new DoublyListNode<T>(x); // temp만 초기화
    // temp->data = x;
    p = first;

    while (true) // 이렇게 할 수도 있구나
    {            //와 다음의 원소랑 비교하는 걸로하면 ==은 생각 안해도되는구나
        if (x < p->rlink->data)
        {
            temp->llink = p;
            temp->rlink = p->rlink;
            p->rlink->llink = temp;
            p->rlink = temp;
            break;
        }
        else if (p->rlink->data != -1)
            p = p->rlink;
        else
        {
            temp->llink = p;
            temp->rlink = p->rlink;
            p->rlink->llink = temp;
            p->rlink = temp;
            break;
        }
    }
    // Increase the number of nodes
    // n++; //이거 아까 주석처리
}

template <class T>
void CircularDoublyList<T>::InsertSorted(T data) //직접 구현해서 위랑 비교
{
    DoublyListNode<T> *item = new DoublyListNode<T>(data);
    DoublyListNode<T> *current = first->rlink; // 헤드 노드를 제외한 첫 번쨰 원소

    while (current != first)
    {
        if (current->data >= data)
        {
            item->llink = current->llink;
            current->llink->rlink = item;

            item->rlink = current;
            current->llink = item;
            return;
        }
        current = current->rlink;
    }

    if (current == first)
    {
        item->llink = last;
        item->rlink = first;

        last->rlink = item;
        first->llink = item;

        last = item;
    }
}

template <class T>
void CircularDoublyList<T>::Merge(CircularDoublyList<T> &b)
{
    auto current = b.first->rlink;
    while (current != b.first)
    {
        this->Insert(current->data);
        current = current->rlink;

        if (current->llink != b.first)
            b.Delete(current->llink);
    }
}

template <class T>
bool CircularDoublyList<T>::Delete(T _data)
{
    // for (auto current = first; first != last; first++) ++이 rlink인거는 어떻게 하는거지? current = cuffent->rlink인가?
    // {
    //     if (current->data == _data)
    //     {
    //         DoublyListNode<T> *found = current;
    //         found->llink->rlink = found->rlink;
    //         found->rlink->llink = found->llink;
    //         delete found;
    //         // Delete(current);
    //         return true;
    //     }
    // }
    DoublyListNode<T> *target = first->rlink;

    while (target != first) // 헤드노드 아니면
    {
        if (target->data == _data)
        {
            target->rlink->llink = target->llink;
            target->llink->rlink = target->rlink;
            delete target;
            return true;
        }
        target = target->rlink;
    }

    return false;
}

template <class T>
int CircularDoublyList<T>::Size() const
{
    // return ((first->data == -1) ? 0 : n);
    int size = 0;
    DoublyListNode<T> *current = first->rlink; // 첫 번째 노드
    while (current != first)
    {
        size++;
        current = current->rlink;
    }
    return size;
}

template <class T>
bool CircularDoublyList<T>::Empty() const
{
    return ((first->data == -1) ? 1 : 0);
}

template <class T>
T *CircularDoublyListIterator<T>::First()
{
    if (current != list.first) //지금 current가 가르키는 노드가 first이냐
        return &current->data; //아니면 current 노드의 데이터 주겠다
    else
        return 0;
}

template <class T>
T *CircularDoublyListIterator<T>::Next()
{
    current = current->rlink;  // current를 다음 노드로 바꾸고
    if (current != list.first) // current가 first 노드를 가르키지 않는다면
        return &current->data; // current 노드의 값을 주겠다
    else
    {
        DoublyListNode<T> *last = current->llink; //임의로 바꾼건데 current가 first노드라면
        return &last->data;                       // 이전 노드의 값을 주겠다
    }
    // return 0;
}

template <class T>
bool CircularDoublyListIterator<T>::NotNull()
{
    if (current != list.first) // current가 first인지
        return true;
    else
        return false;
}

template <class T>
bool CircularDoublyListIterator<T>::NextNotNull()
{
    if (current->rlink != list.first) // current의 다음 노드가 first인지
        return true;
    else
        return false;
}

template <class T>
CircularDoublyList<T>::CircularDoublyList(const CircularDoublyList<T> &l)
{
    // 복사 생성자 한번도 안씀
    if (l.first == 0)
    {
        first = 0;
        return;
    }
    first = new DoublyListNode<T>(l.first->data);
    DoublyListNode<T> *newnode = first;
    for (DoublyListNode<T> *current = l.first->link; current != l.first; current = current->link)
    {
        newnode->link = new DoublyListNode<T>(current->data);
        newnode = newnode->link;
    }
    newnode->link = first; // 마지막꺼 이어주기 (rlink)
}

template <class T>
CircularDoublyList<T>::~CircularDoublyList()
{
    if (first)
    {
        // DoublyListNode<T> *second = first->rlink;
        // first->rlink = av; // av가 뭐하는 변수인지 모르겠다
        // av = second;
        first = 0;
    }
}

template <class T>
ostream &operator<<(ostream &os, CircularDoublyList<T> &l)
{
    // 이터레이터 써야하는 이유구나 아니면 getter setter 엄청 만들어야하네
    CircularDoublyListIterator<T> li(l);
    if (!li.NotNull())
        return os;
    os << *li.First();
    while (li.NextNotNull())
        os << " + " << *li.Next();
    os << endl;
    return os;
}

// template <class T> // 실행 안되는 코드 private인데 당연히 접근안되지
// CircularDoublyList<T> &operator+(const CircularDoublyList<T> &op1, const CircularDoublyList<T> &op2)
// {
//     CircularDoublyList<T> *result = new CircularDoublyList<T>();
//     DoublyListNode<T> *op1Current = op1.first->rlink; // op1 iterator
//     DoublyListNode<T> *op2Current = op2.first->rlink; // op1 iterator

//     DoublyListNode<T> *op1Temp;
//     DoublyListNode<T> *op2Temp;

//     while (op1Current != op1.first && op2Current != op2.first)
//     {
//         op1Temp = op1Current;
//         op2Temp = op2Current;

//         if (op1Current->data < op2Current->data)
//         {
//             result->last->rlink->llink = op1Temp;
//             op1Temp->rlink = result->last->rlink;

//             op1Temp->llink = result->last;
//             result->last->rlink = op1Temp;

//             result->last = op1Temp;

//             op1Current = op1Current->rlink;
//         }
//         else if (op1Current->data > op2Current->data)
//         {
//             result->last->rlink->llink = op2Temp;
//             op2Temp->rlink = result->last->rlink;

//             op2Temp->llink = result->last;
//             result->last->rlink = op2Temp;

//             result->last = op2Temp;

//             op2Current = op2Current->rlink;
//         }

//         op1Temp->rlink = op2Temp;
//         op2Temp->llink = op1Temp;

//         result->last->rlink->llink = op2Temp;
//         op2Temp->rlink = result->last->rlink;

//         result->last->rlink = op1Temp;
//         op1Temp->llink = result->last;

//         result->last = op2Temp;

//         op1Current = op1Current->rlink;
//         op2Current = op2Current->rlink;
//     }

//     DoublyListNode<T> *remindHead = result->last->rlink;

//     if (op1Current->rlink == op1.first)
//     {
//         result->last->rlink = op2Current;
//         op2Current->llink = result->last;

//         while (op2Current->rlink != op2.first)
//         {
//             op2Current = op2Current->rlink;
//         }

//         op2Current->rlink = remindHead;
//         op2Current->rlink->llink = op2Current;
//         result->last = op2Current;
//     }
//     else if (op2Current->rlink == op2.first)
//     {
//         result->last->rlink = op1Current;
//         op1Current->llink = result->last;

//         while (op1Current->rlink != op1.first)
//         {
//             op1Current = op1Current->rlink;
//         }

//         op1Current->rlink = remindHead;
//         op1Current->rlink->llink = op1Current;
//         result->last = op1Current;
//     }

//     return *result;
// }

template <class T>
void CircularDoublyList<T>::Attach(T k) // 그냥 마지막에 붙이기
{
    DoublyListNode<T> *newnode = new DoublyListNode<T>(k);
    if (first == 0)
        first = last = newnode;
    else
    {
        newnode->rlink = last->rlink;
        newnode->llink = last; //이거 추가
        last->rlink = newnode;
        last = newnode;
    }
}

template <class T>
void GetData(CircularDoublyList<T> &a, int length)
{
    srand(time(NULL));

    for (int i = 0; i < length; i++)
    {
        a.Insert(rand() % 99 + 1);
        // a.InsertSorted(rand() % 99 + 1);
    }
}

template <class T>
CircularDoublyList<T> &operator+(const CircularDoublyList<T> &op1, const CircularDoublyList<T> &op2)
{
    CircularDoublyList<T> *result = new CircularDoublyList<T>();
    CircularDoublyListIterator<T> *it1 = new CircularDoublyListIterator<T>(op1);
    CircularDoublyListIterator<T> *it2 = new CircularDoublyListIterator<T>(op2);

    DoublyListNode<T> *temp1;
    DoublyListNode<T> *temp2;
    T curr1 = *it1->First();
    T curr2 = *it2->First();

    // while (it1->NextNotNull() && it2->NextNotNull())
    while (it1->NotNull() && it2->NotNull())
    {
        if (curr1 == curr2)
        {
            result->Attach(curr1);
            result->Attach(curr1);

            curr1 = *it1->Next();
            curr2 = *it2->Next();
        }
        else if (curr1 > curr2)
        {
            result->Attach(curr2);
            curr2 = *it2->Next();
        }
        else if (curr1 < curr2)
        {
            result->Attach(curr1);
            curr1 = *it1->Next();
        }
    }

    if (it1->NotNull())
    {
        while (it1->NotNull())
        {
            result->Attach(curr1);
            curr1 = *it1->Next();
        }
    }
    else if (it2->NotNull())
    {
        while (it2->NotNull())
        {
            result->Attach(curr2);
            curr2 = *it2->Next();
        }
    }

    cout << "size: " << result->Size() << endl; // test

    return *result;
}

int main()
{
    char select = '0';

    CircularDoublyList<float> a, b, c;
    // CircularDoublyListIterator<float> iter(a);

    float weight;
    while (select != 'q' && select != 'Q')
    {
        cout << endl
             << "Select command: a: Add to List a, b: Add to List b, d: Delete, m: Merge, p: PrintAll, q: exit" << endl;
        cin >> select;

        // 콘솔에 한글 출력하면 콘솔 갑자기 꺼짐 ㅠㅠ
        switch (select)
        {
        case 'a':
            // cout << "List a에 추가할 값을 입력 : " << endl;
            cout << "Add on List a: " << endl;

            cin >> weight;
            GetData(a, weight);
            // a.Insert(weight);
            break;
        case 'b':
            // cout << "List b에 추가할 값을 입력 : " << endl;
            cout << "Add on List b: " << endl;
            cin >> weight;
            // b.Insert(weight);
            GetData(b, weight);
            break;
        case 'd':
            // cout << "List a와 b에서 삭제할 값을 입력 : " << endl;
            cout << "delete from List a and b: " << endl;
            cin >> weight;
            if (a.Delete(weight))
                // cout << "List a에서" << weight << "값이 삭제됨." << endl;
                cout << weight << " was deleted from List a" << endl;
            else
                // cout << "List a에" << weight << "값이 없음." << endl;
                cout << weight << " was not found on List a" << endl;
            if (b.Delete(weight))
                // cout << "List b에서" << weight << "값이 삭제됨." << endl;
                cout << weight << " was deleted from List b" << endl;
            else
                // cout << "List b에" << weight << "값이 없음." << endl;
                cout << weight << " was not found on List b" << endl;
            break;
        case 'm':
            // TODO : a+b
            // a.Merge(b);
            // c = a.Merge(b);
            c = a + b;
            cout << c;
            break;
        case 'p':
            // cout << "List a의 출력: " << endl;
            cout << "List a : " << endl;
            cout << a << endl;
            // cout << "List b의 출력: " << endl;
            cout << "List b : " << endl;
            cout << b << endl;
            break;
        case 'q':
        case 'Q':
            select = 'q';
            cout << "Exit program.." << endl;
            break;
        default:
            cout << "WRONG INPUT  " << endl;
            cout << "Re-Enter" << endl;
        }
    }
    // system("pause");
    return 0;
}