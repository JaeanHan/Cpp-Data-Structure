#include <iostream>
#include <cstring>

using namespace std;

template <class T>
class Dequeue
{
public:
    Dequeue(int dequeueCapacity = 2);
    ~Dequeue();
    bool isEmpty();
    void push_front(const T &);
    void push_rear(const T &);
    T &pop_front();
    T &pop_rear();

    template <class U>
    friend ostream &operator<<(ostream &os, Dequeue<U> &target);

private:
    T *dequeue;
    int front;
    int rear;
    int capacity;
};

template <class T>
Dequeue<T>::Dequeue(int dequeueCapacity) : capacity(dequeueCapacity)
{
    dequeue = new T[capacity];
    front = 0;
    rear = 1;
}

template <class T>
Dequeue<T>::~Dequeue()
{
    delete[] dequeue;
}

template <class T>
bool Dequeue<T>::isEmpty()
{
    return front == rear;
}

template <class T>
void Dequeue<T>::push_front(const T &value)
{
    if (isEmpty())
    {
        cout << "isEmpty front" << endl;
        return;
    }

    if (front == 0)
    {
        T *newDequeue = new T[2 * capacity];
        int dest = 2 * capacity / 3;

        memcpy(newDequeue + dest, dequeue + front, sizeof(T) * (rear - front));

        delete[] dequeue;
        dequeue = newDequeue;
        capacity *= 2;
        front = dest;
        rear = front + rear;
    }
    dequeue[front++] = value;
}

template <class T>
void Dequeue<T>::push_rear(const T &value)
{
    if (isEmpty())
    {
        cout << "isEmpty rear" << endl;
        return;
    }

    if (rear + 1 == capacity)
    {
        T *newDqeueue = new T[2 * capacity];
        int dest = 2 * capacity / 3;

        memcpy(newDqeueue + dest, dequeue + front, sizeof(T) * (rear - front));

        delete[] dequeue;
        dequeue = newDqeueue;
        capacity *= 2;
        front = dest;
        rear = front + rear;
    }
    dequeue[rear++] = value;
}

template <class T>
ostream &operator<<(ostream &os, Dequeue<T> &target)
{
    os << "remaining: ";
    for (int i = target.front; i < target.rear; i++)
    {
        os << target.dequeue[i] << " ";
    }
    os << endl;
    return os;
}

int main()
{
    Dequeue<int> q(2);
    q.push_rear(1);
    q.push_rear(2);
    q.push_rear(3);
    cout << q;

    return 0;
}