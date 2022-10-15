#include <iostream>

using namespace std;

template <class T>
class Chain;

template <class T>
class ChainIterator;

template <class T>
class ChainNode
{
    friend class Chain<T>;
    friend class ChainIterator;

public:
    ChainNode(T element = 0);

private:
    T data;
    ChainNode<T> *link;
};

template <class T>
class Chain
{
    friend class ChainIterator<T>;

public:
    Chain() { first = 0; }
    void Delete(void); // first 다음의 element를 삭제
    int Length();
    void Add(const T &element); // first 다음에 element 추가
    void Invert();
    void Concatenate(Chain<T> b);

    template <class T>
    friend ostream &operator<<(ostream &os, Chain<T>); // ??
private:
    ChainNode<T> *first;
};

template <class T>
class ChainIterator
{
public:
    ChainIterator(const Chain<T> &l) : list(l), current(l.first){};
    T& operator*() const {return current->data;}
    T* operator->() const {return &current->data;}

    ChainIterator<T>& operator ++(); // preincrement
    ChainIterator<T> operator ++(int); // post increment
    bool NotNull(); // check if the current element in list is non-null
    bool NextNotNull(); //check if the next element in list is non-null

    T* First(); // returns a pointer to first element
    T* Next(); // returns a pointer to the next element
private:
    const Chain<T>& list;
    ChainNode<T>* current;
};