// heap 구조를 트리에서
// 활주로 하나에서 land or take off
// 착륙전에 여건안되면 비행기는 순회하는데 그때 최대 대기시간은 랜덤으로 (Landing remaining time)
// 출발 예정시간에 출발을 못했다면 => 출발대기 시간(Take Off remaining time)

// 이륙 vs 착륙
// (이륙 비행기 queue => max heap) : 대기 많이 하는애들 먼저 이륙
// landing queue => min-heap queue : remaining time이 짧을 수록 앞으로
// usingType은 islanding or is taking off
// 꼭 스케쥴대로 안해도된다 안되니까
// 우선순위는 비행기 remaining time으로 판별되니까 비행기의 key는 비행기 Id가 아닌 remaining time

#include <iostream>
#include <string>
#include "time.h"

using namespace std;

const int LANDING_TIME = 180;  // in seconds
const int TAKE_OFF_TIME = 300; // in seconds
const string airNames[4] = {"Korean Air", "Thai Airways", "Emirates", "Air Madagascar"};

enum Type
{
    LANDING = 3,
    TAKEOFF = 5
};

class AirPlane;

class Time
{
protected:
    int hour;
    int minute;
    int second;

public:
    Time();
    Time(int);
    Time(int, int, int);
    Time(const Time &);
    void increaseTime(int timePassed);
    void reduceTime(int timePassed);
    int toMinutes();
};

Time::Time()
{
    hour = 0;
    minute = 0;
    second = 0;
}

Time::Time(int timeLeftMinute)
{
    increaseTime(timeLeftMinute);
}

Time::Time(int hour, int minute, int second)
{
    this->hour = hour;
    this->minute = minute;
    this->second = second;
}

Time::Time(const Time &time)
{
    this->hour = time.hour;
    this->minute = time.minute;
    this->second = time.second;
}

void Time::increaseTime(int timePassed)
{
    minute += timePassed;

    if (minute > 59)
    {
        minute -= 60;
        hour += 1;
    }
}

void Time::reduceTime(int timePassed)
{
    minute -= timePassed;

    if (minute < 0)
    {
        hour -= 1;
        minute += 60;
    }
}

int Time::toMinutes()
{
    return hour * 60 + minute;
}

class RealTime : public Time
{
    int year;
    int month;
    int day;

public:
    RealTime(time_t &now)
    {
        tm *time = localtime(&now);

        this->year = time->tm_year + 1900;
        this->month = time->tm_mon + 1;
        this->day = time->tm_mday;
        this->hour = time->tm_hour;
        this->minute = time->tm_min;
        this->second = time->tm_sec;

        delete time;
    }

    RealTime(const RealTime &op)
    {
        this->year = op.year;
        this->month = op.month;
        this->day = op.day;
        this->hour = op.hour;
        this->minute = op.minute;
        this->second = op.second;
    }

    void timeHandler(int minute)
    {
        increaseTime(minute);
    }

    void printRealSchedule()
    {
        if (hour > 24)
        {
            day += hour / 24;
            hour %= 24;
        }

        if (hour < 10)
            std::cout << "0";

        std::cout << hour << ":";

        if (minute < 10)
            std::cout << "0";

        std::cout << minute << " " << month << "/" << day;
    }

    int getTimeDifferenceMinute(const RealTime &time)
    {
        bool yearFlag = year == time.year;
        bool monthFlag = month == time.month;
        bool dayFlag = day == time.day;

        if (yearFlag && monthFlag && dayFlag)
            return (hour - time.hour) * 60 + minute - time.minute;
        else if (yearFlag && monthFlag && !dayFlag)
            return (day - time.day) * 24 * 60 + (hour - time.hour) * 60 + minute - time.minute;
        else
            return -999;
    }
};

class HeapNode;
class MaxHeap;
class MinHeap;

class AirPlane
{
    friend HeapNode;
    friend MaxHeap;
    friend MinHeap;

    int airId;
    string airName;
    Type usingType;
    Time *remainingTime;
    RealTime *scheduledTime;

public:
    AirPlane();
    AirPlane(int, string, Type, RealTime *);
    void setRemainingTime(int);
    void updateRemainingTime(int);
    void toString();
    Type getType();
    int getTimeDifference(const RealTime &);
};

AirPlane::AirPlane(int id, string name, Type type, RealTime *schedule)
{
    airId = id;
    airName = name;
    usingType = type;
    scheduledTime = schedule;
}

void AirPlane::setRemainingTime(int additional)
{
    remainingTime = new Time(0, additional, 0);
}

void AirPlane::updateRemainingTime(int timePassed)
{
    if (usingType == LANDING)
        remainingTime->reduceTime(timePassed);
    else
        remainingTime->increaseTime(timePassed);
}

void AirPlane::toString()
{
    std::cout << "[" << airName << "-" << airId << "|";
    scheduledTime->printRealSchedule();
    std::cout << "] " << (usingType == LANDING ? "landing" : "take off");
    std::cout << ", rt: " << remainingTime->toMinutes() << endl;
}

Type AirPlane::getType()
{
    return usingType;
}

int AirPlane::getTimeDifference(const RealTime &time)
{
    return scheduledTime->getTimeDifferenceMinute(time);
}

class HeapNode // template 써야하지만 함수 정의할 때 너무 번거로워서
{
    friend MaxHeap;
    friend MinHeap;

    AirPlane *airplane;

public:
    HeapNode(){};
    HeapNode(HeapNode *);
    HeapNode(AirPlane *);
};

HeapNode::HeapNode(HeapNode *copy)
{
    airplane = copy->airplane;
}

HeapNode::HeapNode(AirPlane *data)
{
    airplane = data;
}

class MaxHeap // take off queue
{
    HeapNode *heaps; // 비행기 배열은 차마 못하겠다
    int n;
    int maxSize;

public:
    MaxHeap(int);
    void insert(AirPlane *);
    AirPlane *pop();
    void increaseRemaining(int);
    void display();
    int size();
};

MaxHeap::MaxHeap(int size)
{
    maxSize = size;
    heaps = new HeapNode[maxSize + 1];
    n = 0;
}

void MaxHeap::insert(AirPlane *airplane)
{
    if (n == maxSize)
    {
        std::cout << "MaxHeap is Full" << endl;
        return;
    }

    int i = ++n;

    while (i > 1)
    {
        if (airplane->remainingTime->toMinutes() > heaps[i / 2].airplane->remainingTime->toMinutes())
        {
            heaps[i] = heaps[i / 2];
            i /= 2;
        }
        else
            break;
    }

    heaps[i] = new HeapNode(airplane);
}

void MaxHeap::increaseRemaining(int minutes)
{
    if (n == 0)
        return;

    for (int i = 1; i < n + 1; i++)
    {
        heaps[i].airplane->updateRemainingTime(1);
    }
}

AirPlane *MaxHeap::pop()
{
    if (n == 0)
    {
        std::cout << "MaxHeap is Empty" << endl;
        return 0;
    }

    AirPlane *retValue = heaps[1].airplane;
    HeapNode temp;
    heaps[1] = heaps[n--];
    int i = 1;
    int j = 2;

    while (j <= n)
    {
        if (j < n)
            if (heaps[j].airplane->remainingTime->toMinutes() < heaps[j + 1].airplane->remainingTime->toMinutes())
                j++;

        if (heaps[i].airplane->remainingTime->toMinutes() < heaps[j].airplane->remainingTime->toMinutes())
        {
            temp = heaps[i];
            heaps[i] = heaps[j];
            heaps[j] = temp;
            i = j;
            j *= 2;
        }
        else
            break;
    }
    return retValue;
}

void MaxHeap::display()
{
    if (n == 0)
    {
        std::cout << "(No Takeoff delayed)" << endl;
        return;
    }

    std::cout << "TakeOff Queue: " << n << endl;
    for (int i = 1; i < n + 1; i++)
        heaps[i].airplane->toString();
}

int MaxHeap::size()
{
    return n;
}

class MinHeap // landing queue
{
    HeapNode *heaps;
    int n;
    int maxSize;

public:
    MinHeap(int);
    void insert(AirPlane *);
    AirPlane *pop();
    void reduceRemaining(int);
    void display();
    int size();
};

MinHeap::MinHeap(int size)
{
    maxSize = size;
    n = 0;
    heaps = new HeapNode[maxSize + 1];
}

void MinHeap::insert(AirPlane *airplane)
{
    int i = ++n;

    while (i > 1)
    {
        if (airplane->remainingTime->toMinutes() < heaps[i / 2].airplane->remainingTime->toMinutes())
        {
            heaps[i] = heaps[i / 2];
            i /= 2;
        }
        else
            break;
    }

    heaps[i] = new HeapNode(airplane);
}

AirPlane *MinHeap::pop()
{
    if (n == 0)
    {
        std::cout << "MinHeap is Empty" << endl;
        return 0;
    }

    AirPlane *retVal = heaps[1].airplane;
    HeapNode temp;
    heaps[1] = heaps[n--];
    int i = 1;
    int j = 2;

    while (j <= n)
    {
        if (j < n)
            if (heaps[j].airplane->remainingTime->toMinutes() > heaps[j + 1].airplane->remainingTime->toMinutes())
                j++;
        if (heaps[i].airplane->remainingTime->toMinutes() > heaps[j].airplane->remainingTime->toMinutes())
        {
            temp = heaps[i];
            heaps[i] = heaps[j];
            heaps[j] = temp;
            i = j;
            j *= 2;
        }
        else
            break;
    }
    return retVal;
}

void MinHeap::reduceRemaining(int minutes)
{
    if (n == 0)
        return;

    for (int i = 1; i < n + 1; i++)
    {
        heaps[i].airplane->updateRemainingTime(minutes);
    }
    // std::cout << endl;
    // heaps[i].airplane->updateRemainingTime(minutes);
}

void MinHeap::display()
{
    if (n == 0)
    {
        std::cout << "(No landing delayed)" << endl;
        return;
    }

    std::cout << "Landing Queue: " << n << endl;
    for (int i = 1; i < n + 1; i++)
        heaps[i].airplane->toString();
}

int MinHeap::size()
{
    return n;
}

class ValueStack
{
    int valueStack;
    int n;

public:
    ValueStack()
    {
        valueStack = 0;
        n = 0;
    }
    void addValue(int value)
    {
        valueStack += value;
        n++;
    };
    int getAvg()
    {
        return valueStack == 0 ? 0 : valueStack / n;
    }
};

AirPlane *buildAirPlane(RealTime &tempTime)
{
    return new AirPlane(
        rand() % 100,
        airNames[rand() % 4],
        rand() % 2 == 0 ? LANDING : TAKEOFF,
        new RealTime(tempTime));
}

void createAirPlanes(AirPlane **&array, int size, const RealTime &currentTime)
{
    srand(time(NULL));

    RealTime temp(currentTime);
    int i;
    int delayMinute;
    int startTimerMinute = 0;
    array = new AirPlane *[size];

    for (i = 0; i < size; i++)
    {
        delayMinute = startTimerMinute < 20 ? rand() % 6 + 10 : 3;
        startTimerMinute += delayMinute;
        temp.increaseTime(delayMinute);
        array[i] = buildAirPlane(temp);
        array[i]->setRemainingTime(array[i]->getType() == LANDING ? rand() % 29 + 1 : 0); // 순회 가능 시간은 최대 30분으로 설정
    }
}

int main()
{
    int amount = 20; //비행기 개수 조절
    time_t now = time(NULL);
    RealTime current(now);
    AirPlane **rawAirplanes;
    MaxHeap takeoff(amount);   // 이륙 대기 큐
    MinHeap landing(amount);   // 착륙 대기 큐
    ValueStack avgTakeOffTime; // 평균 이륙 대기 시간
    ValueStack avgLandingTime; // 평균 착륙 대기 시간

    AirPlane *latestAirplane;
    int check;

    createAirPlanes(rawAirplanes, amount, current);

    int i = 0;
    int timer = 0;
    int runwayCount = 0;
    bool runwayFlag = true;

    std::cout << "[start]" << endl;
    std::cout << "current time: ";
    current.printRealSchedule();
    std::cout << endl;

    for (int j = 0; j < amount; j++)
        rawAirplanes[j]->toString();
    std::cout << "-------------------------------------------" << endl;

    while (true)
    {
        timer++;

        current.timeHandler(1);
        landing.reduceRemaining(1);
        takeoff.increaseRemaining(1);

        if (!runwayFlag)
            runwayCount--;

        if (!runwayFlag && runwayCount == 0)
            runwayFlag = true;

        if (runwayFlag) //활주로가 비어있을 때 만
        {
            if (landing.size() == 0 && takeoff.size() == 0)
            {
                latestAirplane = rawAirplanes[i];
                if (latestAirplane->getTimeDifference(current) == 0)
                {
                    runwayCount = latestAirplane->getType();
                    i++;
                    runwayFlag = false;
                }
            }
            else if (landing.size() > 0)
            {
                latestAirplane = landing.pop();
                runwayCount = latestAirplane->getType();
                // std::cout << "latestAirplane: " << latestAirplane << endl;
                avgLandingTime.addValue(-latestAirplane->getTimeDifference(current));
                runwayFlag = false;
            }
            else if (takeoff.size() > 0)
            {
                // std::cout << "latestAirplanew: " << i << endl;

                latestAirplane = takeoff.pop();
                runwayCount = latestAirplane->getType();
                avgTakeOffTime.addValue(-latestAirplane->getTimeDifference(current));
                runwayFlag = false;
            }
        }

        if (i < amount) // rawAirplanes 가 남았을 때
        {
            latestAirplane = rawAirplanes[i];
            check = latestAirplane->getTimeDifference(current);

            if (check == 0)
            {
                if (latestAirplane->getType() == LANDING)
                    landing.insert(rawAirplanes[i]);
                else
                    takeoff.insert(rawAirplanes[i]);
                i++;
            }
        }

        if (timer % 3 == 0)
        {
            std::cout << "current time: ";
            current.printRealSchedule();
            std::cout << endl;

            for (int k = i; k < amount; k++)
                rawAirplanes[k]->toString();

            landing.display();
            takeoff.display();

            std::cout << "average landing delay: " << avgLandingTime.getAvg() << endl;
            std::cout << "average takeoff delay: " << avgTakeOffTime.getAvg() << endl;

            std::cout << endl;
        }

        if (i == amount && landing.size() == 0 && takeoff.size() == 0)
        {
            std::cout << "-------------------------------------------" << endl;
            std::cout << "end time: ";
            current.printRealSchedule();
            std::cout << endl;

            for (int k = i; k < amount; k++)
                rawAirplanes[k]->toString();

            landing.display();
            takeoff.display();

            std::cout << "average landing delay: " << avgLandingTime.getAvg() << endl;
            std::cout << "average takeoff delay: " << avgTakeOffTime.getAvg() << endl;

            std::cout << endl;

            break;
        }
    }

    return 0;
}