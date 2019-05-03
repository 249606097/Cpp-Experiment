#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

class Automobile;

class Park 
{
    public:
        Park(int total);
        ~Park();
        void showInfo();
        bool can_park();
        void park(Automobile* one);
        void leave(Automobile* one);
        void get_money(int money);
    private:
        int total;
        int number;
        Automobile **spaces;
        double money = 0;
};

class Automobile 
{
    public:
        string number;
        Automobile(string number);
        void enter(Park *park);
        void leave(Park *park);
        virtual void pay(Park* park){}
};

Automobile::Automobile(string number)
{
    this->number = number;
}

void Automobile::enter(Park *park)
{
    if (park->can_park())
    {
        park->park(this);
    }
    else
    {
        cout << "无法为" << this->number << "分配停车位" << endl;
    }
}

void Automobile::leave(Park *park)
{
    park->leave(this);
}

class Car: public Automobile
{
    public:
        Car(string number, string brand);
        void pay(Park* park);
    private:
        string brand;
};

Car::Car(string number, string brand):Automobile(number)
{
    this->brand = brand;
}

void Car::pay(Park* park)
{
    park->get_money(1);
    cout << "缴纳停车费1元" << endl;
}

class Truck: public Automobile
{
    public:
        Truck(string number, double weight);
        void pay(Park* park);
    private:
        double weight;
};

Truck::Truck(string number, double weight):Automobile(number)
{
    this->weight = weight;
}

void Truck::pay(Park* park)
{
    park->get_money(3);
    cout << "缴纳停车费3元" << endl;
}

class Bus: public Automobile
{
    public:
        Bus(string number, int carrier);
        void pay(Park* park);
    private:
        int carrier;
};

Bus::Bus(string number, int carrier):Automobile(number)
{
    this->carrier = carrier;
}

void Bus::pay(Park* park)
{
    park->get_money(2);
    cout << "缴纳停车费2元" << endl;
}

Park::Park(int total)
{
    this->total = total;
    this->number = 0;

    this->spaces = new Automobile*[total];
    
    for (int i = 0; i < total; i++)
    {
        this->spaces[i] = NULL;
    }
}

Park::~Park()
{
    delete [] spaces;
}

void Park::showInfo()
{
    cout << "停车场目前停放了" << this->number << "辆汽车：";
    for (int i = 0; i < this->total; i++)
    {
        if (this->spaces[i] != NULL)
        {
            cout << this->spaces[i]->number << "，";
        }
    }
    cout << "共收入" << this->money << "元停车费" << endl;
}

bool Park::can_park()
{
    if (this->number < total)
        return true;
    else
        return false;
}

void Park::park(Automobile* one)
{
    for (int i = 0; i < this->total; i++)
    {
        if (this->spaces[i] == NULL)
        {
            this->spaces[i] = one;
            this->number++;
            cout << one->number << "进入停车场，分配停车位" << endl;
            break;
        }
    }
}

void Park::leave(Automobile* one)
{
    for (int i = 0; i < this->total; i++)
    {
        if (this->spaces[i] == one)
        {
            this->spaces[i] = NULL;
            this->number--;
            cout << one->number << "离开停车场，";
            one->pay(this);
            break;
        }
    }
}

void Park::get_money(int money)
{
    this->money += money;
}

int main() 
{
    int N;
    cout << "请输入停车位数量：";
    cin >> N;// 输入停车位数量，此处输入2

    Park *park = new Park(N);// 创建一个停车场对象

    Car car1("鲁B-12345","奥迪A6");  // 创建轿车对象
    car1.enter(park);    // car1进入停车场，分配停车位

    Truck truck("鲁B-23456", 15);  // 创建卡车对象
    truck.enter(park);   // truck进入停车场，分配车位

    car1.leave(park);   // car1离开停车场，缴纳停车费

    Bus bus("鲁B-34567", 50);  // 创建公交车对象
    bus.enter(park);   // bus进入停车场，分配车位

    /* 显示当前停放的车辆的车牌号码，以及当前的全部停车费收入*/
    park->showInfo();

    Car car2("鲁B-45678","宝马320");  // 创建轿车对象
    car2.enter(park); 
    // car2进入停车场，分配停车位。因为没有空余停车位，所以无法分配

    bus.leave(park);  // bus离开停车场，缴纳停车费
    truck.leave(park);  // truck离开停车场，缴纳停车费

    /* 显示当前停放的车辆的车牌号码，以及当前的全部停车费收入*/
    park->showInfo();
    delete park;

    system("PAUSE");
    return 0;
}
