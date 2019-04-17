#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>

using namespace std;

class Date 
{
    public:
        /* 默认构造函数，以fullyear的形式给出年月日，默认值为1990年1月1日，同时设置日期分隔符为“-” */
        Date(int year = 1990, int month = 1, int day = 1);

        /* get、set方法 */
        // 设置日期，如果有非法的月或日，将其置为1
        void setDate(int year, int month, int day);
        void setYear(int year);
        int getYear();
        void setMonth(int month);
        int getMonth();
        void setDay(int month);
        int getDay();
        void setSeparator(char separator);

        /* 输出函数，请使用setfill(‘0’)和setw(2)。*/
        void printFullYear();      //以YYYY-MM-DD的形式打印，2011-01-08
        void printStandardYear(); //以YY-MM-DD的形式打印，比如11-01-08
        /* 计算当前日期与参数日期之间相差几个整年，仅考虑参数日期比当前日期晚的情况。注意参数为日期对象的引用。*/
        int fullYearsTo(Date &date);
        /* 计算当前日期与参数日期之间相差多少天(考虑闰年)，如果参数日期在当前日期之前，返回负数。注意参数为日期对象的引用。*/
        int daysTo(Date &date);
        /* 新增函数，可以被daysTo函数调用 */
        int getDayOfYear();  //计算当前日期是本年的第几天
        int getLeftDaysYear(); //计算当前日期距本年结束还有几天，不包括当前日期这一天
    private:
        int year;
        int month;
        int day;
        char separator = '-';  // 日期分隔符
        /* 新增数据成员和函数成员 */
        /*声明静态常变量，每月的天数，在.cpp文件中定义并初始化 */
        static int DAYS_PER_MONTH[12];
        /*根据年和月，判断参数日期是否合法。如果合法，返回day，否则返回1。*/
        int checkDay(int day);
        bool isLeapyear(int year);//断参数年是否是闰年。
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

            // 参数年的 计算整月的
            if ((year%4==0 && year%100!=0) || year%400==0)
                m[1] = 29;
            else
                m[1] = 28;
                
            for (i=month-1; i>0; i--)
            {
                total += m[i-1];
            }

            total += day;

            // 当前年的 计算整月的
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
        //构造函数，使用“成员初始化器”初始化数据成员
        Employee(string firstName, string lastName, Date &birthDate, Date &hireDate);
        //打印员工的信息。调用Date类的print函数，打印员工的生日和雇佣日期。
        void print();
        //计算员工在参数指定的日期时，满多少岁。请使用Date类的fullYearsTo函数
        int getAge(Date &date);
        //计算该员工在参数指定的日期时，工作满了多少年。
        int getYearsWorked(Date &date);
        //计算该员工在参数指定的日期时，工作了多少天。使用Date类的daysTo函数。
        int getDaysWorked(Date &date);
        ~Employee();   //析构函数

    private:
        string firstName;
        string lastName;
        Date birthDate;    //内嵌对象，出生日期
        Date hireDate;     //内嵌对象，雇用日期
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