#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>

using namespace std;

class Date 
{
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

        /* �����������ʹ��setfill(��0��)��setw(2)��*/
        void printFullYear();      //��YYYY-MM-DD����ʽ��ӡ��2011-01-08
        void printStandardYear(); //��YY-MM-DD����ʽ��ӡ������11-01-08
        /* ���㵱ǰ�������������֮���������꣬�����ǲ������ڱȵ�ǰ������������ע�����Ϊ���ڶ�������á�*/
        int fullYearsTo(Date &date);
        /* ���㵱ǰ�������������֮����������(��������)��������������ڵ�ǰ����֮ǰ�����ظ�����ע�����Ϊ���ڶ�������á�*/
        int daysTo(Date &date);
        /* �������������Ա�daysTo�������� */
        int getDayOfYear();  //���㵱ǰ�����Ǳ���ĵڼ���
        int getLeftDaysYear(); //���㵱ǰ���ھ౾��������м��죬��������ǰ������һ��
    private:
        int year;
        int month;
        int day;
        char separator = '-';  // ���ڷָ���
        /* �������ݳ�Ա�ͺ�����Ա */
        /*������̬��������ÿ�µ���������.cpp�ļ��ж��岢��ʼ�� */
        static int DAYS_PER_MONTH[12];
        /*��������£��жϲ��������Ƿ�Ϸ�������Ϸ�������day�����򷵻�1��*/
        int checkDay(int day);
        bool isLeapyear(int year);//�ϲ������Ƿ������ꡣ
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

    if (day > m[month-1] || day < 1)
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
    cout << setfill('0') << setw(2) << this->day;
}

void Date::printStandardYear()
{
    cout << this->year %100 << this->separator << setfill('0') << setw(2) << this->month << this->separator;
    cout << setfill('0') << setw(2) << this->day << endl;
}

int Date::fullYearsTo(Date &date)
{
    int y = date.year - this->year;
    if (this->month > date.month || (this->month == date.month && this->day > date.day))
        y--;
    
    return y;
}

int Date::daysTo(Date &date)
{
    int total = 0;

    int year = date.year;
    int month = date.month;
    int day = date.day;    
    
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

        Date temp_date(y, m, d);

        this->year = year;
        this->month = month;
        this->day = day;

        total = -this->daysTo(temp_date);
        
        this->year = y;
        this->month = m;
        this->day = d;
    }

    return total;
}

int Date::getDayOfYear()
{
    int m[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

    if (this->isLeapyear(this->year))
        m[1] = 29;

    int total = 0;    
    int i;

    for (i = this->month -1; i>0; i--)
        total += m[i-1];

    total += this->day;

    return total;
}

int Date::getLeftDaysYear()
{
    int m[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

    if (this->isLeapyear(this->year))
        m[1] = 29;

    int total = 0;    
    int i;

    for (i = this->month + 1; i <=12; i++)
        total += m[i-1];
    
    total += m[this->month - 1] - this->day;

    return total;
}

bool Date::isLeapyear(int year)
{
    if ((year%4==0 && year%100!=0) || year%400==0)
        return true;
    else
        return false;
}

int Date::checkDay(int day)
{
    int m[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

    if (day > m[this->month - 1] || day < 1)
        return 1;
    else
        return day;
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
    return this->birthDate.fullYearsTo(date);
}

int Employee::getYearsWorked(Date &date)
{
    return this->hireDate.fullYearsTo(date);
}

int Employee::getDaysWorked(Date &date)
{
    return this->hireDate.daysTo(date);
}

Employee::~Employee()
{
   ; 
}

int main()
{
    Date birth(1969, 8, 11);
    Date hire(1998, 4, 1);
    Date today(2010, 4, 30);
    Employee manager("Bob", "Blue", birth, hire);
    cout << endl;
    manager.print();
    cout << endl;
    cout << manager.getAge(today) << endl;
    cout << manager.getDaysWorked(today) << endl;

    system("PAUSE");
    return 0;
}