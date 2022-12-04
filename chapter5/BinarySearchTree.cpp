#include <iostream>
#include "time.h"

using namespace std;

const int defaultSize = 10;
enum Boolean
{
    FALSE,
    TRUE
};

template <class K>
class Stack
{ // 출력용 스택
public:
    Stack(int maxStackSize = defaultSize);
    ~Stack();
    Boolean isFull();
    Boolean isEmpty();
    void Add(const K &item);
    K *Delete(K &);
    void stackEmpty() { cout << "currently stack is empty" << endl; }
    void stackFull() { cout << "currently stack is full" << endl; }
    void output();

private:
    int top;
    K *stack;
    int maxSize;
};

template <class K>
Stack<K>::Stack(int maxStackSize) : maxSize(maxStackSize)
{
    stack = new K[maxSize];
    top = -1;
}

template <class K>
Stack<K>::~Stack() {}

template <class K>
inline Boolean Stack<K>::isFull()
{
    if (top == maxSize - 1)
        return TRUE;
    else
        return FALSE;
}

template <class K>
inline Boolean Stack<K>::isEmpty()
{
    if (top == -1)
        return TRUE;
    else
        return FALSE;
}

template <class K>
void Stack<K>::Add(const K &item)
{
    if (isFull())
        stackFull();
    else
        stack[++top] = item;
    //아 귀찮아
}

template <class K>
K *Stack<K>::Delete(K &target) // 아 이거 삭제하는게 아니라
{
    if (isEmpty())
    {
        stackEmpty();
        return 0;
    }
    target = stack[top--];
    return &target; //이전 노드 돌려주는거네?
}

template <class K>
void Stack<K>::output()
{
    cout << "top = " << top << endl;
    for (int i = 0; i <= top; i++)
        cout << i << ":" << stack[i] << endl;
}

template <class K>
class Queue
{
public:
    Queue(int maxQueueSize = 5);
    bool isFull();
    bool isEmpty();
    void Add(const K &item);
    K *Delete(K &);

    void queueEmpty() { cout << "currently queue is empty" << endl; }
    void queueFull() { cout << "currently queue is full" << endl; }
    void output();

private:
    int maxSize;
    int front;
    int rear;
    K *queue;
};

template <class K>
Queue<K>::Queue(int maxQueueSize) : maxSize(maxQueueSize)
{
    queue = new K[maxSize];
    front = rear = -1;
}

template <class K>
inline bool Queue<K>::isFull()
{
    if (rear == maxSize - 1)
        return true;
    else
        return false;
}

template <class K>
inline bool Queue<K>::isEmpty()
{
    if (front == rear)
        return true;
    else
        return false;
}

template <class K>
void Queue<K>::Add(const K &target)
{
    if (isFull())
        queueFull();
    else
        queue[++rear] = target;
}

template <class K>
K *Queue<K>::Delete(K &target) // 아니 이거 삭제가 아니라 그냥 값 가져오는거네?
{
    if (isEmpty())
    {
        queueEmpty();
        return 0;
    }
    target = queue[++front];
    return &target;
}

template <class K>
void Queue<K>::output()
{
    cout << "front = " << front << "rear = " << rear << endl;
    for (int i = front + 1; i <= rear; i++)
        cout << i << ":" << queue[i] << endl;
}

class Tree;

class TreeNode // 사용할 트리 노드
{
    friend class Tree;
    friend class InorderIterator;
    friend int equal(TreeNode *, TreeNode *);

public:
    int hasChild();

private:
    TreeNode *LeftChild;  // 왼쪽 아기 노드
    TreeNode *RightChild; // 오른쪽 아기 노드
    int data;             // 값

    TreeNode() // 기본 생성자
    {
        LeftChild = RightChild = 0;
    };

    TreeNode(int ch, TreeNode *lefty, TreeNode *righty)
    {
        data = ch;
        LeftChild = lefty;
        RightChild = righty;
    }

    // ~TreeNode()
    // {
    //     cout << data << " deleted" << endl;
    // }
};

int TreeNode::hasChild()
{
    if (LeftChild == 0 && RightChild == 0)
        return 0;
    else if (LeftChild != 0 && RightChild == 0)
        return 1;
    else if (LeftChild == 0 && RightChild != 0)
        return 2;
    else
        return 3;
}

class Tree // 트리
{
    friend int operator==(const Tree &, const Tree &); // 비교 연산자
    friend class InorderIterator;                      // 이터레이터

private:
    TreeNode *root;
    int getHeight(TreeNode *root);
    void inorder(TreeNode *);   // left -> curr -> right 이렇게 하면 오름차순으로 방문
    void preorder(TreeNode *);  // curr -> left -> right
    void postorder(TreeNode *); // left -> right -> curr
    TreeNode *copy(TreeNode *); // copy
    int isSkewed(TreeNode *);   // returns skewed node data
    void doBalance(TreeNode *);
    // int split(int, Tree &, Tree &);
    void split(int, Tree &, Tree &, int &);
    Tree *TwoWayJoin(int *, Tree *, Tree *);
    Tree *ThreeWayJoin(Tree *, int *, Tree *);

public:
    // Tree(const Tree &);   // 복사 생성자
    Tree() { root = 0; }; // 기본 생성자
    bool Insert(int);
    int Delete(int);
    void getHeight();
    void inorder();   // inorder로 정렬
    void preorder();  // preorder로 정렬
    void postorder(); // postorder로 정렬
    void NoStackInorder();
    void NonrecInorder();
    void LevelOrder();
    void doBalance(); // tree를 balance하는 함수
    Tree *Copy();     // void Copy(Tree&);
    TreeNode *InorderSucc(TreeNode *);
};

class InorderIterator
{
public:
    int *Next();                            // 다음 노드 값
    InorderIterator(Tree tree) : tree(tree) // 생성자
    {
        currentNode = tree.root;
    }

private:
    Tree tree;               // 트리 저장
    Stack<TreeNode *> stack; // 따로 저장할 스택
    TreeNode *currentNode;   // 현재 노드
};

int *InorderIterator::Next() // 다음
{
    while (currentNode) //현재 노드가 null이 아니라면
    {
        stack.Add(currentNode);               // 현재 노드 스택에 추가하고
        currentNode = currentNode->LeftChild; // 왼쪽 자식 노드로 이동
    }
    if (!stack.isEmpty()) // 스택에 원소가 있다면
    {
        currentNode = *stack.Delete(currentNode); // 스택에서 현재 노드를 삭제하는게 아니라 값 가져와서
        int &temp = currentNode->data;            // 이거 부모노드 가져오는거네?
        currentNode = currentNode->RightChild;    // 이후에 현재 노드를 오른쪽 자식로 이동
        return &temp;                             // 현재 노드의 값 반환
    }
    return 0;
}

void Tree::inorder() // driver 함수
{
    inorder(root); // 루트부터 시작
}

void Tree::inorder(TreeNode *currentNode) // working horse 함수
{
    if (currentNode) // 현재 노드가 null이 아니라면
    {
        inorder(currentNode->LeftChild);       // 왼쪽 자식노드 호출하고
        std::cout << " " << currentNode->data; // 현재 노드 값 출력하고
        inorder(currentNode->RightChild);      // 오른쪽 자식노드 호출
    }                                          // 뭐가 어떻게 출력되는지 잘 모르겠네
}

void Tree::preorder() // driver 함수
{
    preorder(root); // 루트부터 시작
}

void Tree::preorder(TreeNode *currentNode) // working horse 함수
{
    if (currentNode) // 현재 노드가 null이 아니면
    {
        std::cout << currentNode->data << " "; // 현재 노드 값 출력하고
        preorder(currentNode->LeftChild);      // 왼쪽 자식 노드 호출
        preorder(currentNode->RightChild);     // 오른쪽 자식노드 호출
    }
}

void Tree::postorder() // driver 함수
{
    postorder(root); // root 부터 시작
}

void Tree::postorder(TreeNode *currentNode) // working horse 함수
{
    if (currentNode) // 현재 노드가 null이 아니라면
    {
        postorder(currentNode->LeftChild);     // 왼쪽 자식 노드 호출하고
        postorder(currentNode->RightChild);    // 오른쪽 자식노드 호출하고
        std::cout << currentNode->data << " "; // 현재 노드 값 출력
    }
}

TreeNode *Tree::copy(TreeNode *oNode)
{
    if (oNode)
    {
        TreeNode *temp = new TreeNode;
        temp->data = oNode->data;
        temp->LeftChild = copy(oNode->LeftChild);
        temp->RightChild = copy(oNode->RightChild);
        return temp;
    }
    return 0;
}

int operator==(const Tree &op1, const Tree &op2)
{
    return equal(op1.root, op2.root);
}

int equal(TreeNode *op1, TreeNode *op2)
{
    if ((!op1) && (!op2))
        return 1; // both a and b are 0
    if (op1 && op2 && (op1->data == op2->data) && equal(op1->LeftChild, op2->LeftChild) && equal(op1->RightChild, op2->RightChild))
        return 1;
    return 0;
}

bool Tree::Insert(int item)
{
    TreeNode *current = root; //루트부터 시작해서
    TreeNode *follow = 0;     // 따라와

    while (current) // 중복 값 확인
    {
        follow = current;          // 따라와
        if (item == current->data) // 중복 값은 저장안해
            return false;

        if (current->data > item)
            current = current->LeftChild;
        else
            current = current->RightChild;
    }

    current = new TreeNode; // 그냥 변수 재사용
    current->LeftChild = current->RightChild = 0;
    current->data = item;
    if (!root)
        root = current;
    else if (follow->data > item)
        follow->LeftChild = current;
    else
        follow->RightChild = current;
    return true;
}

int Tree::Delete(int target)
{
    TreeNode *current = root;
    TreeNode *follow = 0;
    TreeNode *successor = 0;
    TreeNode *predecessor = 0;
    TreeNode *temp = 0;
    int followFlag = 0;

    while (current != 0)
    {
        if (current->data == target)
            break;
        follow = current;
        if (current->data < target) // 크다면
        {
            current = current->RightChild;
            followFlag = 2;
        }
        else // 작다면
        {
            current = current->LeftChild;
            followFlag = 1;
        }
    }

    if (current == 0)
    {
        std::cout << target << ": non-existing element" << endl;
        return -999;
    }

    if (current->hasChild() == 0) // current가 leafNode라면
    {
        if (follow == 0) // current가 root 노드라면
            root = 0;
        else
        {
            if (followFlag == 1)
                follow->LeftChild = 0;
            else
                follow->RightChild = 0;
        }
    }
    else if (current->hasChild() == 3) // current 자식이 두개라면
    {
        successor = current->RightChild; // 일단 오른쪽에서 찾아
        predecessor = successor;

        while (successor->LeftChild != 0)
        {
            predecessor = successor;
            successor = successor->LeftChild; // 가장 작은 값 찾아야되
        }

        if (follow == 0) // root노드 라면
            root = successor;
        else
        {
            if (successor->hasChild() == 2) // 오른쪽 꼬리가 하나 있다면
                predecessor->LeftChild = successor->RightChild;
            else
                predecessor->LeftChild = 0;

            if (followFlag == 1)
                follow->LeftChild = successor;
            else
                follow->RightChild = successor;
        }

        successor->LeftChild = current->LeftChild;
        successor->RightChild = successor == current->RightChild ? 0 : current->RightChild;
    }
    else // current의 자식이 하나라면
    {
        successor = current->hasChild() == 1 ? current->LeftChild : current->RightChild;

        if (follow == 0) // current가 root 노드라면
            root = successor;
        else
        {
            if (follow->hasChild() == 1) // follow의 왼쪽이 current라면
                follow->LeftChild = successor;
            else
                follow->RightChild = successor;
        }
    }

    // leaf node 삭제 구현
    // non-leaft node 삭제 구현

    delete current;
    return target;
}

void Tree::getHeight()
{
    int height = getHeight(root);
    std::cout << "Tree height: " << height << endl;
}

int Tree::getHeight(TreeNode *root)
{
    if (root == 0)
        return 0;
    else
    {
        int lHeight = getHeight(root->LeftChild);
        int rHeight = getHeight(root->RightChild);

        if (lHeight >= rHeight)
            return lHeight + 1;
        else
            return rHeight + 1;
    }
}

int Tree::isSkewed(TreeNode *current) // private
{
    //해당 노드에서 |Tleft - Tright| >=3이면 unbalanced로 판단
    //하고 split()을 호출해야하지만 여기선 balaned인지 체크만
    if (current->hasChild() == 0)
        return -1;
    else if (current->hasChild() == 1)
        return getHeight(current->LeftChild) >= 3 ? current->data : -1; // skewed tree
    else if (current->hasChild() == 2)
        return getHeight(current->RightChild) >= 3 ? current->data : -1; // skewed tree
    else
        return max(isSkewed(current->LeftChild), isSkewed(current->RightChild));
}

void Tree::doBalance() // public
{
    doBalance(root);
}

void Tree::doBalance(TreeNode *current)
{
    if (current == 0)
        return;

    int mid = isSkewed(root);

    if (mid != -1)
    {
        int height = getHeight(root);
        int choice = 0;
        TreeNode *tmp = root;
        Tree sTree, bTree;

        std::cout << "before adjusting: " << height << endl;

        for (int i = 0; i < (int)(height / 2); i++)
            tmp = tmp->hasChild() == 1 ? tmp->LeftChild : tmp->RightChild;

        mid = tmp->data;
        split(mid, sTree, bTree, choice);

        Tree *newTree = TwoWayJoin(&mid, &sTree, &bTree);
        root = newTree->root;

        std::cout << "after adjusting: " << getHeight(root) << endl;
        return;
    }
}

void Tree::split(int i, Tree &B, Tree &C, int &x)
// Split the binary search tree with respect to key i
{
    if (!root)
    { // empty tree
        B.root = C.root = 0;
        x = 0;
        return;
    }
    int mode = 0;
    TreeNode *prev = root;
    TreeNode *current = root;
    C.root = root;

    while (current)
        if (i == current->data)
        { // split at t
            if (current == root)
            {
                x = current->data;
                B.root = current->LeftChild;
                C.root = current->RightChild;
                return;
            }
            if (mode == 0)
            { // left child을 뜯어 낸다
                prev->LeftChild = current->RightChild;
                B.root = current->LeftChild;
            }
            else
            {
                prev->RightChild = current->LeftChild;
                B.root = current->RightChild;
            }

            C.root = root;
            x = current->data;
            return;
        }
        else if (i < current->data)
        {
            prev = current;
            mode = 0;
            current = current->LeftChild;
        }
        else
        {
            prev = current;
            mode = 1;
            current = current->RightChild;
        }

    return;
}

Tree *Tree::TwoWayJoin(int *i, Tree *small, Tree *big)
{
    if (!small)
        return big;
    if (!big)
        return small;

    return root->hasChild() == 1 ? ThreeWayJoin(small, i, big) : ThreeWayJoin(big, i, small);
}

Tree *Tree::ThreeWayJoin(Tree *small, int *mid, Tree *big)
{
    TreeNode *newNode = new TreeNode();
    newNode->data = *mid;
    newNode->LeftChild = small->root;
    newNode->RightChild = big->root;

    Tree *newTree = new Tree();
    newTree->root = newNode;
    return newTree;
}

void Tree::NonrecInorder()
{
    Stack<TreeNode *> stack;
    TreeNode *currentNode = root;
    while (true)
    {
        while (currentNode)
        {
            stack.Add(currentNode);
            currentNode = currentNode->RightChild;
        }
        if (!stack.isEmpty())
        {
            currentNode = *stack.Delete(currentNode);
            std::cout << currentNode->data << endl;
            currentNode = currentNode->RightChild;
        }
        else
            break;
    }
}

void Tree::LevelOrder()
{
    Queue<TreeNode *> queue;
    TreeNode *currentNode = root;

    while (currentNode)
    {
        std::cout << currentNode->data << endl;

        if (currentNode->LeftChild)
            queue.Add(currentNode->LeftChild);
        if (currentNode->RightChild)
            queue.Add(currentNode->RightChild);
        currentNode = *queue.Delete(currentNode);
    }
}

void Tree::NoStackInorder() // inorder()와 비교
{
    if (!root)
        return;
    TreeNode *top = 0, *LastRight = 0, *p, *q, *r, *r1; // local variable이 key point
    p = q = root;
    while (1)
    {
        while (1)
        {
            if ((!p->LeftChild) && (!p->RightChild))
            {
                std::cout << p->data;
                break;
            }
            if (!p->LeftChild)
            {
                std::cout << p->data;
                r = p->RightChild;
                p->RightChild = q;
                q = p;
                p = r;
            }
            else
            {
                r = p->LeftChild;
                p->LeftChild = q;
                q = p;
                p = r;
            }
        }
        TreeNode *av = p;
        while (1)
        {
            if (p == root)
                return;
            if (!q->LeftChild)
            {
                r = q->RightChild;
                q->RightChild = p;
                p = q;
                q = r;
            }
            else if (!q->RightChild)
            {
                r = q->LeftChild;
                q->LeftChild = p;
                p = q;
                q = r;
                std::cout << p->data;
            }
            else if (q == LastRight)
            {
                r = top;
                LastRight = r->LeftChild;
                top = r->RightChild;
                r->LeftChild = r->RightChild = 0;
                r = q->RightChild;
                q->RightChild = p;
                p = q;
                q = r;
            }
            else
            {
                std::cout << q->data;
                av->LeftChild = LastRight;
                av->RightChild = top;
                top = av;
                LastRight = q;
                r = q->LeftChild;
                q->LeftChild = p;
                r1 = q->RightChild;
                q->RightChild = r;
                p = r1;
                break;
            }
        }
    }
}

int main(void)
{
    srand(time(NULL));
    Tree t;
    int eq = -1;
    char select = 'i';
    int max = 0, x = 0;
    while (select != 'q')
    {
        int rnd = 0;
        std::cout << "BinarySearchTree. Select i:Insert (0 for skewed), r: remove, d:Display, e:NonrecInorder, f:preorder, g:postorder, h:copy and compare, z:tree height, x:balance tree q : Quit =>";
        std::cin >> select;
        std::cout << endl;
        switch (select)
        {
        case 'i':
            std::cout << "The number of items = ";
            std::cin >> max;

            if (max == 0)
            {
                t.Insert(1);
                t.Insert(2);
                t.Insert(3);
                t.Insert(4);
                t.Insert(5);
                t.Insert(6);
                t.Insert(7);
                t.Insert(8);
                t.Insert(9);
                t.Insert(10);
            }
            else
            {
                for (int i = 0; i < max; i++)
                {
                    rnd = rand() / 100;
                    if (!t.Insert(rnd))
                        std::cout << "Insert Duplicated data" << endl;
                    std::cout << rnd << " ";
                }
                std::cout << endl;
            }
            break;
        case 'r':
            int x;
            std::cin >> x;
            std::cout << t.Delete(x); //입력된 x에 대한 tree 노드를 찾아 삭제한다.
            std::cout << endl;
            break;
        case 'd':
            t.inorder();
            std::cout << endl;
            break;
        case 'e':
            t.NonrecInorder();
            break;
        case 'f':
            t.preorder();
            break;
        case 'g':
            t.postorder();
            break;
        case 'h':
            eq = (t == Tree(t)); // copy constructor를 호출
            if (eq)
            {
                std::cout << "compare result: true" << endl;
            }
            else
                std::cout << "compare result: false" << endl;
            break;
        case 'q':
            std::cout << "Quit" << endl;
            break;
        case 'z':
            t.getHeight();
            break;
        case 'x':
            t.doBalance();
            break;
        default:
            std::cout << "WRONG INPUT  " << endl;
            std::cout << "Re-Enter" << endl;
            break;
        }
    }

    // system("pause");
    return 0;
}