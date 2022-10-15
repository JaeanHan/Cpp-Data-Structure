#include <iostream>
#include <cstring>

using namespace std;

template <class T>
class Dequeue
{
public:
    Dequeue();
    ~Dequeue();
    void push_front(const T &);
    void push_rear(const T &);
    T &pop_front();
    T &pop_rear();
    bool is_empty() const;

    template <class U>
    friend ostream &operator<<(ostream &os, Dequeue<U> &target);

private:
    T *dequeue;
    int front;
    int rear;
    int capacity;
    int front_count;
    int rear_count;
};

template <class T>
Dequeue<T>::Dequeue()
{
    capacity = 2;
    dequeue = new T[capacity];
    front = capacity / 3;
    rear = front;
    front_count = 0;
    rear_count = 0;
}

template <class T>
Dequeue<T>::~Dequeue()
{
    delete[] dequeue;
}

template <class T>
ostream &operator<<(ostream &os, Dequeue<T> &target)
{
    os << "remaining: ";
    for (int i = target.front + 1; i < target.rear + 1; i++)
    // for (int i = 0; i < target.capacity; i++)
    {
        os << target.dequeue[i] << " ";
    }
    os << endl;

    return os;
}

template <class T>
void Dequeue<T>::push_front(const T &value)
{
    if (front == -1)
    {
        capacity *= 2;
        T *newDequeu = new T[capacity];
        memcpy(newDequeu + capacity / 3, dequeue, sizeof(T) * (rear - front));
        delete[] dequeue;
        dequeue = newDequeu;
        rear = capacity / 3 - 1 + rear - front;
        front = capacity / 3 - 1;
    }
    // front_count++;
    dequeue[front--] = value;
}

template <class T>
void Dequeue<T>::push_rear(const T &value)
{
    if (rear + 1 == capacity)
    {
        capacity *= 2;
        T *newDequeu = new T[capacity];
        memcpy(newDequeu + capacity / 3, dequeue + front + 1, sizeof(T) * (rear - front));
        delete[] dequeue;
        dequeue = newDequeu;
        rear = capacity / 3 - 1 + rear - front;
        front = capacity / 3 - 1;
    }
    // rear_count++;
    dequeue[++rear] = value;
}

template <class T>
T &Dequeue<T>::pop_front()
{
    front++;
    // front_count--;
    return dequeue[front];
}

template <class T>
T &Dequeue<T>::pop_rear()
{
    rear--; // // rear_count--;
    return dequeue[rear + 1];
}

template <class T>
bool Dequeue<T>::is_empty() const
{
    return front == rear;
}

int main()
{
    Dequeue<int> q;
    q.push_front(1);
    q.push_rear(2);
    cout << q;
    cout << q.pop_front() << endl; // 1
    cout << q.pop_front() << endl; // 2

    q.push_rear(3);
    q.push_rear(4);
    cout << q;
    cout << q.pop_front() << endl; // 3
    cout << q;
    cout << q.pop_rear() << endl; // 4
    cout << q.pop_rear() << endl; // 3

    q.push_rear(5);
    q.push_rear(6);
    cout << q;
    cout << q.pop_rear() << endl; // 6
    cout << q.pop_rear() << endl; // 5

    cout << q;

    q.push_rear(7);
    q.push_rear(8);
    q.push_rear(9);
    q.push_rear(10);
    q.push_rear(11);
    cout << q;

    cout << q.pop_front() << endl;
    cout << q.pop_front() << endl;
    cout << q.pop_front() << endl;
    cout << q.pop_front() << endl;
    cout << q;

    q.push_front(12);
    q.push_front(13);
    q.push_front(14);
    q.push_front(15);
    cout << q.pop_rear() << endl;
    cout << q.pop_rear() << endl;
    cout << q.pop_rear() << endl;
    cout << q.pop_rear() << endl;

    cout << q;
    return 0;
}