#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>

using namespace std;

class Date{
    public:
        /* Ĭ�Ϲ��캯������fullyear����ʽ���������գ�Ĭ��ֵΪ1990��1��1�գ�ͬʱ�������ڷָ���Ϊ��-�� */
        Date(int year = 1990, int month = 1, int day = 1);

        /* get��set���� */
        // �������ڣ�����зǷ����»��գ�������Ϊ1
        void setDate(int year, int month, int day);
        void setYear(int year);
        int getYear();
        void setMonth(int month);
        int getMonth();
        void setDay(int month);
        int getDay();
        void setSeparator(char separator);

        /* �����������ʹ��setfill(��0��)��setw(2)����Ҫ����<iomanip>ͷ�ļ� */
        void printFullYear();      // ��YYYY-MM-DD����ʽ��ӡ��2011-01-08
        void printStandardYear(); // ��YY-MM-DD����ʽ��ӡ������11-01-08
        /*  ���㺯��  */
        // ���㵱ǰ�������������֮���������꣬�����ǲ������ڱȵ�ǰ����������
        int fullYearsTo(int year, int month, int day);
        /* ���㵱ǰ�������������֮����������(��������)��������������ڵ�ǰ����֮ǰ�����ظ����� */
        int operator -(Date one);
        bool operator <(Date one);
        bool operator >(Date one);
    private:
        int year;
        int month;
        int day;
        char separator = '-';  // ���ڷָ���
};

Date::Date(int year, int month, int day)
{
    this->year = year;
    this->month = month;
    this->day = day;
}

int correct_day(int year,int month, int day)
{
    int m[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if ((year%4==0 && year%100!=0) || year%400==0)
        m[1] = 29;

    if (day > m[month] || day < 1)
    {
        return 1;
    }
    else
    {
        return day;
    } 
}

int correct_month(int month)
{
    if (month > 12 || month < 1)
    {
        return 1;
    }
    else
    {
        return month;
    }
    
}

void Date::setDate(int year, int month, int day)
{
    this->year = year;
    this->month = correct_month(month);
    this->day = correct_day(year, month, day);
}

void Date::setYear(int year)
{
    this->year = year;
}

int Date::getYear()
{
    return this->year;
}

void Date::setMonth(int month)
{
    this->month = correct_month(month);
}

int Date::getMonth()
{
    return this->month;
}

void Date::setDay(int day)
{
    this->day = correct_day(this->year, this->month, day);
}

int Date::getDay()
{
    return this->day;
}

void Date::setSeparator(char separator)
{
    if (separator == '-' || separator == '*' || separator == '/')
        this->separator = separator;
}

void Date::printFullYear()
{
    cout << this->year << this->separator << setfill('0') << setw(2) << this->month << this->separator;
    cout << setfill('0') << setw(2) << this->day << endl;
}

void Date::printStandardYear()
{
    cout << this->year %100 << this->separator << setfill('0') << setw(2) << this->month << this->separator;
    cout << setfill('0') << setw(2) << this->day << endl;
}

int Date::fullYearsTo(int year, int month, int day)
{
    int y = year - this->year;
    if (this->month > month || (this->month == month && this->day > day))
        y--;
    
    return y;
}

int Date::operator-(Date one)
{
    int year = one.year;
    int month = one.month;
    int day = one.day;
    
    int total = 0;

    if (this->year < year || (this->year == year && this->month < month) || (this->year == year && this->month == month && this->day < day))
    {   
        int y=year-1;
        while (y > this->year)
        {
            if ((y%4==0 && y%100!=0) || y%400==0)
                total += 366;
            else
                total += 365;
            
            y--;
        }

        int i;
        if (this->year < year)
        {
            int m[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

            // ������� �������µ�
            if ((year%4==0 && year%100!=0) || year%400==0)
                m[1] = 29;
            else
                m[1] = 28;
                
            for (i=month-1; i>0; i--)
            {
                total += m[i-1];
            }

            total += day;

            // ��ǰ��� �������µ�
            if ((this->year%4==0 && this->year%100!=0) || this->year%400==0)
                m[1] = 29;
            else
                m[1] = 28;

            for (i=this->month+1; i<=12; i++)
            {
                total += m[i-1];
            }

            total += m[this->month-1] - this->day;
        }
        else
        {
            int m[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

            if ((year%4==0 && year%100!=0) || year%400==0)
                m[1] = 29;
            else
                m[1] = 28;

            for (i=month-1; i>this->month; i--)
            {
                total += m[i-1];
            }

            if (month == this->month)
            {
                total += (day - this->day);
            }
            else
            {
                total += day;
                total += m[this->month-1] - day;
            }
        }
    }
    else
    {
        int y = this->year;
        int m = this->month;
        int d = this->day;

        this->year = year;
        this->month = month;
        this->day = day;

        Date temp(y, m, d);
        
        total = (*this - temp);
        
        this->year = y;
        this->month = m;
        this->day = d;
    }

    return -total;
}
bool Date::operator <(const Date one)
{
    if ((*this - one) < 0)
        return true;
    else
     return false;
}

bool Date::operator >(const Date one)
{
    if ((*this - one) > 0)
        return true;
    else
     return false;
}

class Employee{
    public:
        //���캯����ʹ�á���Ա��ʼ��������ʼ�����ݳ�Ա
        Employee(string firstName, string lastName, Date &birthDate, Date &hireDate);
        //��ӡԱ������Ϣ������Date���print��������ӡԱ�������պ͹�Ӷ���ڡ�
        void print();
        //����Ա���ڲ���ָ��������ʱ���������ꡣ��ʹ��Date���fullYearsTo����
        int getAge(Date &date);
        //�����Ա���ڲ���ָ��������ʱ���������˶����ꡣ
        int getYearsWorked(Date &date);
        //�����Ա���ڲ���ָ��������ʱ�������˶����졣ʹ��Date���daysTo������
        int getDaysWorked(Date &date);
        ~Employee();   //��������
        static const Employee& getMostFaith(Employee employees[], int n)
        {
            int max = 0;
            for (int i = 1; i < n; i++)
            {
                if (employees[i].hireDate < employees[max].hireDate)
                    max = i;
            }
            return employees[max];
        }

    private:
        string firstName;
        string lastName;
        Date birthDate;    //��Ƕ���󣬳�������
        Date hireDate;     //��Ƕ���󣬹�������
};

Employee::Employee(string firstName, string lastName, Date &birthDate, Date &hireDate)
{
    this->firstName = firstName;
    this->lastName = lastName;
    this->birthDate = birthDate;
    this->hireDate = hireDate;
}

void Employee::print()
{
    cout << this->lastName << ", " << this->firstName << " Hired: ";
    this->hireDate.printFullYear();
    cout << " Birthday: ";
    this->birthDate.printFullYear();
    cout << endl;

    return;
}

int Employee::getAge(Date &date)
{
    return (date - this->birthDate) / 365;
}

int Employee::getYearsWorked(Date &date)
{
    return (date - this->hireDate) / 365;
}

int Employee::getDaysWorked(Date &date)
{
    return date - this->hireDate;
}

Employee::~Employee()
{
   ; 
}

int main()
{
    Date today(2010, 4, 30);

    Date birth1(1969, 8, 11);
    Date hire1(1998, 4, 1);

    Date birth2(1969, 8, 11);
    Date hire2(1998, 4, 2);

    Date birth3(1969, 8, 11);
    Date hire3(1998, 4, 3);

    Date birth4(1969, 8, 11);
    Date hire4(1998, 4, 4);

    Date birth5(1969, 8, 11);
    Date hire5(1998, 4, 5);

    Employee employees[5] = {
        {"A", "App", birth1, hire1}, 
        {"B", "Boy", birth2, hire2},
        {"C", "Car", birth3, hire3},
        {"D", "Dog", birth4, hire4},
        {"E", "Emm", birth5, hire5}
    };

    Employee one = Employee::getMostFaith(employees, 5);
    one.print();
    cout << "Has worked for "<< one.getDaysWorked(today) << " days"<< endl;

    system("PAUSE");
    return 0;
}