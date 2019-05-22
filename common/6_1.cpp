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
        cout << this->lug[i].get_code() << "、";
    }
    cout << "\b，";
}

void Passenger::print_destination()
{
    switch (this->des)
    {
        case 0:
            cout << "国内短途";
            break;
        case 1:
            cout << "国内长途";
            break;
        case 2:
            cout << "国际游  ";
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
        char ch[2] = {char(this->name[4]), '\0'}; // 中文占两个字节
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
            cout << "选择自由出行，";
            break;
        case 1:
            cout << "报名旅行社  ，";
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
            cout << "国内短途";
            break;
        case 1:
            cout << "国内长途";
            break;
        case 2:
            cout << "国际游";
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
    cout << money << "元，";

    cout << "乘客姓名：";
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
        people[i].set_name("乘客" + string(ch));

        people[i].set_destination(destination(rand() % MAX_TYPE));

        people[i].set_luggage_num(rand() % MAX_TYPE + 1);

        people[i].choose_type(rand() % 2);
    }


    for (i = 0; i < 62; i++)
    {
        cout << "我是" << people[i].get_name() << "，";
        people[i].print_type();
        people[i].print_destination();
        cout << "，" << "携带" << people[i].get_luggage_num() << "件行李，";
        cout << "行李编号是";
        people[i].print_luggage();
        cout << "买票需付" << people[i].get_ticket_cost();
        cout << "元。";
        if (people[i].get_luggage_cost())
        {
            cout << "\b，行李托运费" << people[i].get_luggage_cost() << "元。";
        }
        cout << endl;
    }

    cout << "旅行社开始报名。" << endl;
    Team teams[5];
    int num = 0;
    int j;

    for (i = 0; i < 62; i++)
    {
        // 自由行游客 直接跳出
        if (people[i].get_type() == 0)
            continue;
        
        // 第一个团购的
        if (num == 0)
        {
            teams[0].set_destination(people[i].get_destination());
            teams[0].add_member(people[i]);
            num++;
        }
        else
        {
            bool in_team = false;
            // 寻找 对应的团 （目的地相同 人数少于6）
            for (j = 0; j < num; j++)
            {
                if (teams[j].get_destination() == people[i].get_destination()
                    && teams[j].get_members_num() < 6)
                {
                    in_team = true;
                    break;
                }
            }

            // 进团判断
            if (in_team)
            {
                teams[j].add_member(people[i]);
            }
            else
            {
                // 新开团
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
    cout << "旅行社共计安排了" << num << "个旅行团，共计" << members_num << "人报名。" << endl;
    
    cout << "出行的目的地分别是：";
    for (i = 0; i < num; i++)
    {
        teams[i].print_destination();
        cout << "，";
    }
    cout << "\b；";

    cout << "每个旅行团的人数分别是：";
    for (i = 0; i < num; i++)
    {
        cout << teams[i].get_members_num() << "，";
    }
    cout << "\b；";

    cout << "每个旅行团需要支付的票价是：";
    for (i = 0; i < num; i++)
    {
        cout << teams[i].get_ticket_cost() << "，";
    }
    cout << "\b。";

    cout << "售票处开始售票。" << endl;
    cout << "售票结束，营业额统计信息如下：" << endl;

    cout << "国内短途自由行：";
    ticketing(people, DomesticShort, 0);
    cout << "国内长途自由行：";
    ticketing(people, DomesticLong, 0);
    cout << "国际游自由行：  ";
    ticketing(people, International, 0);
    cout << "国内短途团购：  ";
    ticketing(people, DomesticShort, 1);
    cout << "国内长途团购：  ";
    ticketing(people, DomesticLong, 1);
    cout << "国际游团购：    ";
    ticketing(people, International, 1);

    system("PAUSE");
    return 0;
}