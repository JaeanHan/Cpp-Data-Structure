#include <iostream>
#include <cstring>

using namespace std;

template <class T>
class Queue
{
public:
    Queue(int queueCapacity = 10);
    ~Queue();
    T &Front();
    T &Top();
    bool IsEmpty();
    void Push(T const &x);
    void Pop();
    template <class U>
    friend ostream &operator<<(ostream &os, Queue<U> &target);

private:
    T *queue;
    int front; // head
    int rear;  // tail
    int capacity;
    int time;
};

template <class T>
Queue<T>::Queue(int queueCapacity) : capacity(queueCapacity)
{
    queue = new T[capacity];
    front = -1;
    rear = -1;
    time = 0;
}

template <class T>
Queue<T>::~Queue()
{
    cout << "bye queue" << endl;
    delete[] queue;
}

template <class T>
inline bool Queue<T>::IsEmpty()
{
    return rear == front;
}

template <class T>
T &Queue<T>::Front()
{
    if (IsEmpty())
        // {
        //     cout << "Queue is empty. No front element" << endl;
        //     return queue[front + 1];
        // }
        throw "Queue is empty. No rear element";
    // cout << "front+1: " << front + 1 << endl;
    return queue[front + 1];
}

template <class T>
void Queue<T>::Push(const T &value)
{
    // if ((front + 1) % capacity == rear % capacity)
    if ((front + 1) % capacity == (rear + 1) % capacity && time > 0)
    // if ((rear + 1) % capacity == front)
    // if ((rear + 1) % capacity == front)
    {
        T *newQueue = new T[2 * capacity];
        int start = (front + 1) % capacity;

        if (start == 0)
        {
            memcpy(newQueue, queue, sizeof(T) * capacity);
            cout << "yes" << endl;
        }
        else
        {
            memcpy(newQueue, queue + start, sizeof(T) * (capacity - start));
            memcpy(newQueue + capacity - start, queue + (rear % capacity), sizeof(T) * (start - (rear % capacity)));
        }
        front = -1;
        rear = capacity - 1;
        capacity *= 2;
        delete[] queue;
        queue = newQueue;
    }

    rear = (rear + 1) % capacity;
    // cout << capacity << endl;
    // cout << "rear: " << rear << endl;
    time += 1;
    queue[rear] = value;
}

template <class T>
T &Queue<T>::Top()
{
    if (IsEmpty())
        // {
        //     cout << "Queue is empty. No rear element" << endl;
        //     return queue[rear];
        // }
        throw "Queue is empty. No top element";
    return queue[rear];
}

template <class T>
void Queue<T>::Pop()
{
    queue[++front].~T();
    // cout << "front after pop: " << front << endl;
}

template <class T>
ostream &operator<<(ostream &os, Queue<T> &target)
{
    os << "remainings: ";
    for (int i = 0; i < target.capacity; i++)
    {
        os << target.queue[i] << " ";
    }
    os << endl;
    return os;
}

int main()
{
    Queue<int> q(2);
    // cout << q;
    q.Push(1);
    q.Push(2);
    // cout << q;
    q.Push(3);
    q.Push(4);
    q.Push(5);
    q.Push(6);
    q.Push(7);
    q.Push(8);

    cout << q;
    cout << q.Front() << endl;
    q.Pop();
    cout << q;
    cout << q.Front() << endl;
    q.Pop();
    q.Pop();
    cout << q;
    cout << q.Front() << endl;
    q.Pop();
    q.Pop();
    q.Pop();
    cout << q.Front() << endl;
    q.Pop();
    cout << q.Top() << endl;
    q.Pop();
    q.Pop();

    return 0;
}