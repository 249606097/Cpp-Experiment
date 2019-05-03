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
        cout << "�޷�Ϊ" << this->number << "����ͣ��λ" << endl;
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
    cout << "����ͣ����1Ԫ" << endl;
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
    cout << "����ͣ����3Ԫ" << endl;
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
    cout << "����ͣ����2Ԫ" << endl;
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
    cout << "ͣ����Ŀǰͣ����" << this->number << "��������";
    for (int i = 0; i < this->total; i++)
    {
        if (this->spaces[i] != NULL)
        {
            cout << this->spaces[i]->number << "��";
        }
    }
    cout << "������" << this->money << "Ԫͣ����" << endl;
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
            cout << one->number << "����ͣ����������ͣ��λ" << endl;
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
            cout << one->number << "�뿪ͣ������";
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
    cout << "������ͣ��λ������";
    cin >> N;// ����ͣ��λ�������˴�����2

    Park *park = new Park(N);// ����һ��ͣ��������

    Car car1("³B-12345","�µ�A6");  // �����γ�����
    car1.enter(park);    // car1����ͣ����������ͣ��λ

    Truck truck("³B-23456", 15);  // ������������
    truck.enter(park);   // truck����ͣ���������䳵λ

    car1.leave(park);   // car1�뿪ͣ����������ͣ����

    Bus bus("³B-34567", 50);  // ��������������
    bus.enter(park);   // bus����ͣ���������䳵λ

    /* ��ʾ��ǰͣ�ŵĳ����ĳ��ƺ��룬�Լ���ǰ��ȫ��ͣ��������*/
    park->showInfo();

    Car car2("³B-45678","����320");  // �����γ�����
    car2.enter(park); 
    // car2����ͣ����������ͣ��λ����Ϊû�п���ͣ��λ�������޷�����

    bus.leave(park);  // bus�뿪ͣ����������ͣ����
    truck.leave(park);  // truck�뿪ͣ����������ͣ����

    /* ��ʾ��ǰͣ�ŵĳ����ĳ��ƺ��룬�Լ���ǰ��ȫ��ͣ��������*/
    park->showInfo();
    delete park;

    system("PAUSE");
    return 0;
}
