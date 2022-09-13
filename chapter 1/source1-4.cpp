#include <iostream>
using namespace std;
#define N 10

string deparments[10] = {"developement1", "developement2", "developement3", "developement4", "developement5", "marketing1", "marketing2", "marketing3", "marketing4", "marketing5"};

class Employee
{
    int number;
    string name;
    float salary;
    string dept;
    static int count;

public:
    Employee()
    {
        number = Employee::operator++();
        name = "name" + to_string(number);
        salary = 12.99;
        dept = deparments[number];
    };

    Employee(int number) : Employee() { this->number = number; };

    Employee(const Employee &em) : name(em.name), number(em.number), dept(em.dept){};

    ~Employee() { cout << name << " Employee destructor called" << endl; };

    static int Show();

    int getNumber() const;
    string getName() const;
    string getDept() const;

    Employee &operator=(const Employee &);
    int operator++();
    friend ostream &operator<<(ostream &stream, const Employee &);
};

int Employee::count = 0;

Employee &Employee::operator=(const Employee &em)
{
    name = em.name;
    number = em.number;
    dept = em.dept;
}

int Employee::operator++()
{
    return ++count;
};

int Employee::Show()
{
    count = 0;
    cout << "[Show] count : " << count << endl;
}

int Employee::getNumber() const
{
    return number;
}

string Employee::getName() const
{
    return name;
}

string Employee::getDept() const
{
    return dept;
}

ostream &operator<<(ostream &stream, const Employee &em)
{
    stream << "name : " << em.getName() << ", dept : " << em.getDept() << ", number : " << em.getNumber() << endl;
    return stream;
};

int main()
{
    Employee sd1;
    cout << "[sd1] " << sd1;

    Employee sd2(10);
    cout << "[sd2] " << sd2;

    Employee sd3(sd2);
    cout << "[sd3] " << sd3;

    Employee::Show();
    sd1.Show();

    Employee sd4 = sd2;
    cout << "[sd4] " << sd4;

    sd3 = sd2;
    cout << "[sd3 = sd2] " << sd3;

    cout << endl;
    cout << sd4;

    return 0;
}