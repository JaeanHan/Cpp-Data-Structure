#include <iostream>
#include <string>
#define N 10

using namespace std;

string names[10] = {"name1", "name2", "name3", "name4", "name5", "name6", "name7", "name8", "name9", "name10"};
float salaries[10] = {10.99, 9.99, 8.99, 7.99, 6.99, 5.99, 4.99, 3.99, 2.99, 1.99};
string depts[10] = {"dept1", "dept2", "dept3", "dept4", "dept5", "dept6", "dept7", "dept8", "dept9", "dept10"};

class Employee
{
    int id;
    string name;
    float salary;
    string dept;
    static int count;

public:
    Employee();
    Employee(int);
    Employee(const Employee &);
    ~Employee();
    int getId();
    string getName();
    Employee &operator=(const Employee &);
    int operator++();
    static int Show();
    friend ostream &operator<<(ostream &stream, Employee &);
};

Employee::Employee(){};

Employee::Employee(int n)
{
    id = n;
    name = names[n];
    salary = salaries[n];
    dept = depts[n];
};

Employee &Employee::operator=(const Employee &em)
{
    id = em.id;
    name = em.name;
    salary = em.salary;
    dept = em.dept;
    count = em.count;
    return *this;
};

int Employee::getId()
{
    return id;
}

string Employee::getName()
{
    return name;
}

class EmpTable
{
    int top;
    Employee *data[N];

public:
    EmpTable();
    ~EmpTable();
    void initializeEmployee();
    void showEmployee();
};

EmpTable::EmpTable() : top(N){};
EmpTable::~EmpTable()
{
    delete[] & data;
    cout << "data deleted" << endl;
}

void EmpTable::initializeEmployee()
{
    int n = top;

    for (int i = 0; i < n; i++)
    {
        data[i] = new Employee(i);
    }
};

void EmpTable::showEmployee()
{
    for (int i = 0; i < top; i++)
    {
        cout << "emmployee name: " << data[i]->getName() << " id : " << data[i]->getId() << endl;
    }
};

int Employee::count = N;

int main()
{
    int num = N;
    EmpTable empt;
    empt.initializeEmployee();
    empt.showEmployee();
    return 0;
}
