#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include<iomanip>

const int MAX_TYPE = 3;


using namespace std;

enum destination {DomesticShort, DomesticLong, International};

class Luggage
{
    public:
        string get_code();
        void set_code(string name);

    private:
        string code;
};

string Luggage::get_code()
{
    return this->code;
}

void Luggage::set_code(string name)
{
    this->code = name;
}

class Passenger
{
    public:
        string get_name();
        destination get_destination();
        int get_luggage_num();
        void print_luggage();
        void print_destination();
        void set_name(string name);
        void set_destination(destination des);
        void set_luggage_num(int num);
        void choose_type(int type);
        int get_type();
        void print_type();
        int get_ticket_cost();
        int get_luggage_cost();

    private:
        string name;
        destination des;
        int luggage_num = 0;
        Luggage lug[3];
        int type;
};

string Passenger::get_name()
{
    return this->name;
}

destination Passenger::get_destination()
{
    return this->des;
}

int Passenger::get_luggage_num()
{
    return this->luggage_num;
}

void Passenger::print_luggage()
{
    for (int i = 0; i < this->luggage_num; i++)
    {
        cout << this->lug[i].get_code() << "��";
    }
    cout << "\b��";
}

void Passenger::print_destination()
{
    switch (this->des)
    {
        case 0:
            cout << "���ڶ�;";
            break;
        case 1:
            cout << "���ڳ�;";
            break;
        case 2:
            cout << "������  ";
            break;
    }
}

void Passenger::set_name(string name)
{
    this->name = name;
}

void Passenger::set_destination(destination des)
{
    this->des = des;
}

void Passenger::set_luggage_num(int num)
{
    this->luggage_num = num;

    for (int i = 0; i < num; i++)
    {
        char ch[2] = {char(this->name[4]), '\0'}; // ����ռ�����ֽ�
        this->lug[i].set_code(string(ch) + string("0") + to_string(i+1));
    }
}

void Passenger::choose_type(int type)
{
    this->type = type;
}

int Passenger::get_type()
{
    return this->type;
}

void Passenger::print_type()
{
    switch (this->type)
    {
        case 0:
            cout << "ѡ�����ɳ��У�";
            break;
        case 1:
            cout << "����������  ��";
            break;
    }
}

int Passenger::get_ticket_cost()
{
    switch (this->des)
    {
        case 0:
            return 10;
        case 1:
            return 100;
        case 2:
            return 500;
    }
}

int Passenger::get_luggage_cost()
{
    if (this->luggage_num > 2 && this->des == 2)
    {
        return 100;
    }
    else
    {
        return 0;
    }
    
}

class Team
{
    public:
        destination get_destination();
        void print_destination();
        void set_destination(destination des);
        int get_members_num();
        void add_member(Passenger person);
        int get_ticket_cost();
    
    private:
        destination des;
        int members_num = 0;
        Passenger members[6];
};

destination Team::get_destination()
{
    return this->des;
}

void Team::print_destination()
{
    switch (this->des)
    {
        case 0:
            cout << "���ڶ�;";
            break;
        case 1:
            cout << "���ڳ�;";
            break;
        case 2:
            cout << "������";
            break;
    }
}

int Team::get_members_num()
{
    return this->members_num;
}

void Team::add_member(Passenger person)
{
    if (this->members_num < 6)
    {
        this->members[this->members_num] = person;
        this->members_num++;
    }
}

void Team::set_destination(destination des)
{
    this->des = des;
}

int Team::get_ticket_cost()
{
    int per_ticket_cost;
    switch (this->des)
    {
        case 0:
            per_ticket_cost = 10;
            break;
        case 1:
            per_ticket_cost = 100;
            break;
        case 2:
            per_ticket_cost = 500;
            break;
    }

    return this->members_num * per_ticket_cost;
}

void ticketing(Passenger *people, destination des, int type)
{
    int i;
    int money = 0;

    for (i = 0; i < 62; i++)
    {
        if (people[i].get_destination() == des
            && people[i].get_type()==type)
            money += 10;
    }
    cout << money << "Ԫ��";

    cout << "�˿�������";
    for (i = 0; i < 62; i++)
    {
        if (people[i].get_destination() == des
            && people[i].get_type()==type)
            cout << people[i].get_name() << " ";
    }
    cout << endl;
}

int main()
{
    srand(static_cast<unsigned> (time(NULL)));

    Passenger people[62];
    
    int i = 0;

    for (i = 0; i < 62; i++)
    {
        int temp;
        if (i < 26)
            temp = 65;
        else if (i < 52)
            temp = 71;
        else
            temp = -4;
        
        char ch[2] = {char(i+temp), '\0'};
        people[i].set_name("�˿�" + string(ch));

        people[i].set_destination(destination(rand() % MAX_TYPE));

        people[i].set_luggage_num(rand() % MAX_TYPE + 1);

        people[i].choose_type(rand() % 2);
    }


    for (i = 0; i < 62; i++)
    {
        cout << "����" << people[i].get_name() << "��";
        people[i].print_type();
        people[i].print_destination();
        cout << "��" << "Я��" << people[i].get_luggage_num() << "�����";
        cout << "��������";
        people[i].print_luggage();
        cout << "��Ʊ�踶" << people[i].get_ticket_cost();
        cout << "Ԫ��";
        if (people[i].get_luggage_cost())
        {
            cout << "\b���������˷�" << people[i].get_luggage_cost() << "Ԫ��";
        }
        cout << endl;
    }

    cout << "�����翪ʼ������" << endl;
    Team teams[5];
    int num = 0;
    int j;

    for (i = 0; i < 62; i++)
    {
        // �������ο� ֱ������
        if (people[i].get_type() == 0)
            continue;
        
        // ��һ���Ź���
        if (num == 0)
        {
            teams[0].set_destination(people[i].get_destination());
            teams[0].add_member(people[i]);
            num++;
        }
        else
        {
            bool in_team = false;
            // Ѱ�� ��Ӧ���� ��Ŀ�ĵ���ͬ ��������6��
            for (j = 0; j < num; j++)
            {
                if (teams[j].get_destination() == people[i].get_destination()
                    && teams[j].get_members_num() < 6)
                {
                    in_team = true;
                    break;
                }
            }

            // �����ж�
            if (in_team)
            {
                teams[j].add_member(people[i]);
            }
            else
            {
                // �¿���
                if (num < 5)
                {
                    teams[num].add_member(people[i]);
                    teams[num].set_destination(people[i].get_destination());
                    num++;
                }
                else
                {
                    ;
                }
                
            }
        }
    }

    int members_num = 0;
    for (i = 0; i < num; i++)
    {
        members_num += teams[i].get_members_num();
    }
    cout << "�����繲�ư�����" << num << "�������ţ�����" << members_num << "�˱�����" << endl;
    
    cout << "���е�Ŀ�ĵطֱ��ǣ�";
    for (i = 0; i < num; i++)
    {
        teams[i].print_destination();
        cout << "��";
    }
    cout << "\b��";

    cout << "ÿ�������ŵ������ֱ��ǣ�";
    for (i = 0; i < num; i++)
    {
        cout << teams[i].get_members_num() << "��";
    }
    cout << "\b��";

    cout << "ÿ����������Ҫ֧����Ʊ���ǣ�";
    for (i = 0; i < num; i++)
    {
        cout << teams[i].get_ticket_cost() << "��";
    }
    cout << "\b��";

    cout << "��Ʊ����ʼ��Ʊ��" << endl;
    cout << "��Ʊ������Ӫҵ��ͳ����Ϣ���£�" << endl;

    cout << "���ڶ�;�����У�";
    ticketing(people, DomesticShort, 0);
    cout << "���ڳ�;�����У�";
    ticketing(people, DomesticLong, 0);
    cout << "�����������У�  ";
    ticketing(people, International, 0);
    cout << "���ڶ�;�Ź���  ";
    ticketing(people, DomesticShort, 1);
    cout << "���ڳ�;�Ź���  ";
    ticketing(people, DomesticLong, 1);
    cout << "�������Ź���    ";
    ticketing(people, International, 1);

    system("PAUSE");
    return 0;
}